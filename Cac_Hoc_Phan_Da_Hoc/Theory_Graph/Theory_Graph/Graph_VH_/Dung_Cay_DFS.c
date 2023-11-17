#include <stdio.h>

typedef struct {
	int data[100][100];
	int n, m;
}Graph;

typedef struct {
	int data[100];
	int sl;
}List;

void makeNullList(List *L){
	L->sl=0;
}
void pushList(List *L, int x){
	L->data[L->sl]=x;
	L->sl++;
}
List neighbors(Graph *G, int P){
	List L;
	makeNullList(&L);
	int i; 
	for(i=1; i<=G->n; i++){
		if(G->data[P][i]!=0){
			pushList(&L, i);
		}
	}
	return L;
}

void DungCay(Graph *G, int x, int mark[], int parent[]){
	List dd;
	makeNullList(&dd);
	pushList(&dd, x);
	
	while(!(dd.sl==0)){
		int P;
		P=dd.data[dd.sl-1];
		dd.sl--;
		
		if(mark[P]!= 0) continue;
		
		mark[P]=1;
		
		List L;
		L = neighbors(G, P);
		
		int i; 
		for(i=0; i<L.sl; i++){
			int H;
			H=L.data[i];
			if(parent[P] != H && mark[H]==0){
				pushList(&dd, H);
				parent[H]=P;
			}
		}
	}
	
}

int main(){
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
	
	int mark[100], parent[100];
	for(i=1; i<=G.n; i++){
		mark[i]=0;
		parent[i]=0;
	}
	for(i=1; i<=G.n; i++){
		if(mark[i]==0){
			DungCay(&G, i, mark, parent);
		}
	}
	
	for(i=1; i<=G.n; i++){
		printf("%d %d\n", i, parent[i]);
	}
	return 0;
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
*/
/*	Ket qua
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

