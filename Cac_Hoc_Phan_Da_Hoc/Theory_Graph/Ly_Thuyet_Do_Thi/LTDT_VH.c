#include <stdio.h>
#define sz 100

typedef struct{
	int data[sz][sz];
	int n, m;
}Graph;

typedef struct{
	int data[sz];
	int Front, Rear, Count;
}Queue;

typedef struct{
	int data[sz];
	int sl;
}List;

void makeNullQueue(Queue *Q ){
	Q->Front=0;
	Q->Rear=-1;
	Q->Count=0;
}

void makeNullList(List *L){
	L->sl=0;
}

void pushList(List *L, int x){
	L->data[L->sl]=x;
	L->sl++;
}

void pushQueue ( Queue *Q, int x){
	Q->Rear++;
	Q->data[Q->Rear]=x;
	Q->Count++;
}

List neighbors(Graph G, int x){
	List L;
	makeNullList(&L);
	int i;
	for(i=1; i<=G.n; i++){
		if(G.data[x][i]==1){
			pushList(&L, i);
		}
	}
	return L;
}

void BFS(Graph G, int mark[], int x){ // duyet theo chieu rong Queue
	Queue dd;
	makeNullQueue(&dd);
	pushQueue(&dd, x);
	int i; 
	for(i=1; i<=G.n; i++){
		mark[i]=0;
	} 
	while(!(dd.Count==0)){
		int P = dd.data[dd.Front];
		dd.Front++;
		dd.Count--;

		if(mark[P] != 0) continue;
		printf("%d\n", P);
		mark[P]=1;
		
		List L = neighbors(G, P);
		
		int i;
		for(i=0; i<L.sl; i++){
			int H=L.data[i];
			pushQueue(&dd, H);
		}
	}
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
	
1
2
4
12
6
7
10
11
5
13
3
8
9
	*/
}

void DFS(Graph G, int mark[], int x){ // duyet theo chieu sau dung Stack
	List dd;
	makeNullList(&dd);
	pushList(&dd, x);
	int i;
	for(i=1; i<=G.n; i++){
		mark[i]=0;
	}
	
	while(!(dd.sl==0)){
		int P = dd.data[dd.sl-1];
		dd.sl--;
		
		if(mark[P]!=0) continue;
		mark[P]=1;
		printf("%d\n", P);
		
		List L = neighbors(G, P);
		
		for(i=0; i<L.sl; i++){
			int H = L.data[i];
			pushList(&dd, H);
		}
	}
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

1
12
11
10
4
7
6
13
5
9
8
3
2
	*/
}

void DDQ(Graph G, int mark[], int x){ // duyet theo chieu sau dung de quy
	if(mark[x] != 0) return;
	mark[x]=1;
	printf("%d\n", x);
	List L = neighbors(G, x);
	int i;
	for(i=0; i<L.sl; i++){
		int H = L.data[i];
		DDQ(G, mark, H);
	}
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

1
2
4
6
5
8
9
7
3
13
12
10
11
	*/
}

void BFS_DC(Graph G, int mark[], int x, int parent[]){ // duyet dung cay Queue
	Queue dd;
	makeNullQueue(&dd);
	pushQueue(&dd, x);
	
	while(!(dd.Count==0)){
		int P = dd.data[dd.Front];
		dd.Front++;
		dd.Count--;
		
		if(mark[P] != 0) continue;
		mark[P]=1;
		
		List L = neighbors(G, P);
		
		int i;
		for(i=0; i<L.sl; i++){
			int H = L.data[i];
			if(parent[H] == 0 && mark[H]==0){
				pushQueue(&dd, H);
				parent[H]=P;
			}
		}
	}
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

1 0
2 1
3 7
4 1
5 6
6 4
7 4
8 5
9 5
10 12
11 12
12 1
13 6
	*/
}

void DFS_DC(Graph G, int mark[], int x, int parent[]){ // duyet va dung cay Stack
	List dd;
	makeNullList(&dd);
	pushList(&dd, x);
	
	while(!(dd.sl==0)){
		int P = dd.data[dd.sl-1];
		dd.sl--;
		
		if(mark[P] != 0) continue;
		mark[P]=1;
		
		List L = neighbors(G, P);
		
		int i;
		for(i=0; i<L.sl; i++){
			int H = L.data[i];
			if(mark[H]==0){
				pushList(&dd, H);
				parent[H]=P;	
			}
		}
	}
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

1 0
2 4
3 7
4 1
5 6
6 7
7 4
8 9
9 5
10 11
11 12
12 1
13 6
	*/
}

void DFS_DC_DQ(Graph G, int mark[], int x, int parent[]){ // duyet dung cay de quy
	if(mark[x]!=0) return;
	mark[x]=1;
	
	List L = neighbors(G, x);
	int i;
	for(i=0; i<L.sl; i++){
		int H = L.data[i];
		if(mark[H]==0){
			parent[H]=x;
			DFS_DC_DQ(G, mark, H, parent);
		}
	}
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

1 0
2 1
3 7
4 2
5 6
6 4
7 6
8 5
9 8
10 12
11 10
12 1
13 6
	*/
}

void DT_LT(Graph G){	//Kiem tra do thi co lien thong khong
	List dd;
	makeNullList(&dd);
	pushList(&dd, 1);
	
	int mark[sz];
	int i;
	for(i=1; i<=G.n; i++){
		mark[i]=0;
	}
	
	while(!(dd.sl==0)){
		int P = dd.data[dd.sl-1];
		dd.sl--;
		
		if(mark[P]!=0) continue;
		mark[P]=1;
		
		List L = neighbors(G, P);
		for(i=0; i<L.sl; i++){
			int H = L.data[i];
			pushList(&dd, H);
		}
	}
	
	int kt=1;
	for(i=1; i<=G.n; i++){
		if(mark[i]==0){
			kt=0;
		}
	}
	if(kt==1){
		printf("YES");
	} else printf("NO");
	
	/*
4 3
1 2
2 3
3 4
YES

4 2
3 4
1 2
NO
	*/
}

void KT_CT(Graph G){		//kiem tra do thi co chu trinh hay khong
	List dd;
	makeNullList(&dd);
	pushList(&dd, 1);
	int mark[sz], parent[sz];
	int i;
	for(i=1; i<=G.n; i++){
		mark[i]=0;
		parent[i]=0;
	}
	int kt=0;
	while(!(dd.sl==0)){
		
		int P = dd.data[dd.sl-1];
		dd.sl--;
		
		if(mark[P]!=0) continue;
		mark[P]=1;
		
		List L = neighbors(G, P);
		for(i=0; i<L.sl; i++){
			int H=L.data[i];
			if(H==parent[P]) continue;
			if(mark[H]==0){
				parent[H]=P;
				pushList(&dd, H);
			}
			
			if(mark[H]==1){
				kt=1;
				break;
			}
		}
	}
	if(kt==1){
		printf("YES");
	} else{
		printf("NO");
	}
}


int main (){
	Graph G;
	scanf("%d%d", &G.n, &G.m);
	int i, j;
	for(i=1; i<=G.n; i++){
		for(j=1; j<=G.n; j++){
			G.data[i][j]=0;	
		}
	}
	for(i=1; i<=G.m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		G.data[u][v]=1;
		G.data[v][u]=1;
	}
	
	int mark[sz], parent[sz];
	for(i=1; i<=G.n; i++){
		mark[i]=0;
		parent[i]=0;
	}
	
	
	return 0;
}
