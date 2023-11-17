#include <stdio.h>

typedef struct {
	int data[100][100];
	int n, m;
}Graph;
typedef struct{
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

void Moore_Dijkstra(Graph *G, int x, int n){
	List dd;
	makeNullList(&dd);
	int mark[100], cs[100], parent[100];
	int i;
	for(i=1; i<=G->n; i++){
		mark[i]=0;
		cs[i]=0;
		parent[i]=0;
	}
	pushList(&dd, x);
	while(!(dd.sl==0)){
		int P, min, minindex;
		min=cs[dd.data[0]];
		minindex=0;
		for(i=1; i<dd.sl; i++){
			if(cs[dd.data[i]] < min){
				min=cs[dd.data[i]];
				minindex=i;
			}
		}
		
		P=dd.data[minindex];
		
		for(i=minindex; i<dd.sl-1; i++){
			dd.data[i]=dd.data[i+1];
		}
		dd.sl--;
		
		if(mark[P]!=0) continue;
		mark[P]=1;
		
		List L;
		L=neighbors(G, P);
		for(i=0; i<L.sl; i++){
			int H;
			H=L.data[i];
			int cstam;
			int j, kt;
			kt=0;
			for(j=0; j<dd.sl; j++){
				if(dd.data[j] == H){
					kt=1;
				}
			}
			cstam=cs[P]+G->data[P][H];
			if(kt==1){
				if(cs[H] > cstam){
					cs[H]=cstam;
					parent[H]=P;
				}
			} else {
				if(mark[H]==0){
					cs[H]=cstam;
					parent[H]=P;
					pushList(&dd, H);
				}
			}
		}
	}
	printf("\n");
	for(i=1; i<=G->n; i++){
		printf("%d %d %d\n", i, parent[i], cs[i]);
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
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G.data[u][v]=w;
		G.data[v][u]=w;		
	}
	
	Moore_Dijkstra(&G, 1, G.n);
	
	return 0;
}

/*
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
/* Ket qua
1 0 0
2 1 1
3 6 6
4 5 5
5 1 3
6 2 5
7 6 7
8 3 7
9 8 10
10 7 9
*/
