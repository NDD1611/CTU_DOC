#include <stdio.h>

typedef struct {
	int data[100][100];
	int n, m;
}Graph;
typedef struct {
	int data[100];
	int size;
}List;
typedef struct {
    int data[100];
    int Front, Rear;
    int Count;
}Queue;

void makeNullList(List *L){
	L->size=0;
}

void pushList(List *L, int x){
	L->data[L->size]=x;
	L->size++;
}

List neighbors(Graph *G, int P){
	List L;
	makeNullList(&L);
	int i;
	for(i=1; i<=G->n; i++){
		if(G->data[P][i] != 0){
			pushList(&L, i);
		}
	}
	return L;
}

void makeNullQueue(Queue *Q){
    Q->Front = 0;
    Q->Rear=-1;
    Q->Count=0;
}
void push_queue(Queue *Q, int x){
    Q->Rear++;
    Q->data[Q->Rear]=x;
    Q->Count++;
}
int pop_queue(Queue *Q){
    int result;
    result = Q->data[Q->Front];
    Q->Front++;
    Q->Count--;
    return result;
}

void BFS ( Graph *G, int x){
    Queue Q;
    List L, mark;
    makeNullList(&mark);
    int P, i, j;
    makeNullQueue(&Q);
    for(i=1; i<=G->n; i++){
    	mark.data[i]=0;
	}
    push_queue(&Q, x);
    while(!(Q.Count==0)){
        P=pop_queue(&Q);
        if(mark.data[P] != 0) continue;
        
        mark.size++;
        mark.data[P]=mark.size;
        L = neighbors(G, P);
        for(i=0; i<L.size; i++){
            push_queue(&Q, L.data[i]);
        }
    }
    
    for(i=1; i<=G->n; i++){
    	for(j=1; j<=G->n; j++){
    		if(mark.data[j]==i){
    			printf("%d ", j);
			}
		}
	}
}

void DFS(Graph *G, int x){
	List dd;
	makeNullList(&dd);
    List mark;
    makeNullList(&mark);
    int i, j, P;
    for(i=1; i<=G->n; i++){
    	mark.data[i]=0;
	}
    pushList(&dd,x);
    while(!(dd.size==0)){
        P=dd.data[dd.size-1];            // cho dinh P bang phan tu dinh cua Stack
        dd.size--;
        if(mark.data[P]!=0) continue;    // neu P da duoc duyet thi qua vong lap ke tiep nguoc lai thi duyet P
        
        mark.size++;
        mark.data[P]= mark.size;
        
        List L;
        L = neighbors(G, P);      // lay lang gieng cua P
        
        for(i=0; i<L.size;i++){
            pushList(&dd,L.data[i]);
        }
    }
    for(i=1; i<=G->n; i++){
    	for(j=1; j<=G->n; j++){
    		if(mark.data[j]==i){
    			printf("%d ", j);
			}
		}
	}
}

void Moore_Dijkstra_VH(Graph *G, int x, int y){
	int n = G->n;
	List dd;
	makeNullList(&dd);
	int parent[n+1];
	int mark[n+1];
	int cs[n+1];
	int i, j;
	for(i=1; i<=n ; i++){
		parent[i]=0;
		cs[i]=0;
		mark[i]=0;
	}
	pushList(&dd, x);
	parent[x]=0;
	cs[x]=0;
	while(!(dd.size==0)){
		int ptmin, minindex;
		ptmin= dd.data[0];
		minindex=0;
		for(i=1; i<dd.size; i++){
			if(cs[dd.data[i]] < cs[ptmin]){
				ptmin=dd.data[i];
				minindex=i;
			}
		}
		
		int P = ptmin;
		for(i=minindex; i<dd.size-1;i++){
			dd.data[i]=dd.data[i+1];
		}	
		dd.size--;	
		
		mark[P]=1;
		
		List L;
		L = neighbors(G, P);
		
		for(i=0; i<L.size; i++){
			int kt=0;
			int H=L.data[i];
			for(j=0; j<dd.size; j++){
				if(dd.data[j]==H){
					kt=1;
				}
			}
			
			int cstam = cs[P]+G->data[P][H];
			if(kt==1){
				if(cstam < cs[H]){
					parent[H]=P;
					cs[H]=cstam;
				}
			} else {
				if(mark[H]==0){
					parent[H]=P;
					cs[H]=cstam;
					pushList(&dd, H);
				}
			}
		}
	}
	
	printf("\n");
	for(i=1; i<=G->n; i++){
		printf("%d ", i);
	}
	printf("\n");
	for(i=1; i<=G->n; i++){
		printf("%d ", parent[i]);
	}
	printf("\n");
	for(i=1; i<=G->n; i++){
		printf("%d ", cs[i]);
	}
}


int main(){
	
	Graph G;
	scanf("%d%d", &G.n, &G.m);
	int i, j;
	for(i=1; i<=G.n;i++){
		for(j=1; j<=G.n;j++){
			G.data[i][j]=0;
		}
	}
	
	for(i=1; i<=G.m; i++){
		int v, u, w;
		scanf("%d%d%d", &u, &v, &w);
		G.data[u][v]=w;
		G.data[v][u]=w;	
	}

//	for(i=1; i<=G.m; i++){
//		int v, u;
//		scanf("%d%d", &u, &v);
//		G.data[u][v]=1;
//		G.data[v][u]=1;	
//	}
	
	printf("\n\n");
	for(i=1; i<=G.n;i++){
		for(j=1; j<=G.n;j++){
			printf("%d ", G.data[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	
	Moore_Dijkstra_VH(&G, 1, G.n);
	//BFS(&G, 1);
	//DFS(&G, 1);
	return 0;
}

/* vo huong
10 21
1 2 1
1 3 10
1 4 6
1 5 3
2 6 4
2 3 10
3 6 1
3 7 4
3 4 4
3 8 1
4 8 3
4 5 2
5 8 6
5 9 8
6 7 2
6 10 5
7 10 2
7 8 5
8 10 8
8 9 3 
9 10 5
*/
/*
13 16
1 4
1 2
1 12
2 4
3 7
4 6
4 7
5 6
5 8
5 9
6 7
6 13
8 9
10 11
10 12
11 12
*/
