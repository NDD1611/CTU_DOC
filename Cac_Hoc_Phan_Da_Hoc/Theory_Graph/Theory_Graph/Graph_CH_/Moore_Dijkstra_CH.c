#include <stdio.h>

typedef struct{
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
		if(G->data[P][i]!= 0){
			pushList(&L, i);
		}
	}
	return L;
}

void Moore_Dijkstra(Graph *G, int x, int n){
	List dd;
	makeNullList(&dd);
	int mark[100], parent[100], cs[100];
	int i;
	for(i=1; i<=G->n; i++){
		mark[i]=0;
		parent[i]=0;
		cs[i]=0;
	}
	pushList(&dd, x);
	
	while(!(dd.sl==0)){
		int P, min, minindex;
		min=cs[dd.data[0]];
		minindex=0;
		for(i=0; i<dd.sl; i++){
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
		
		mark[P]=1;
		
		List L;
		L=neighbors(G, P);
		for(i=0; i<L.sl; i++){
			int H;
			H=L.data[i];
			int j, kt=0;
			for(j=0; j<dd.sl; j++){
				if(dd.data[j]==H){
					kt=1;
				}
			}
			int cstam;
			cstam=cs[P]+G->data[P][H];
			if(kt==1){
				if(cstam < cs[H]){
					cs[H]=cstam;
					parent[H]=P;
				}
			} else {
				if(mark[H]==0){
					cs[H]=cstam;
					pushList(&dd, H);
					parent[H]=P;
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
	}
	
	Moore_Dijkstra(&G, 1, G.n);
	return 0;
}

/*
6 10
1 2 7
1 3 1
2 4 4
2 6 1
3 2 5
3 6 7
3 5 2
5 4 5
5 2 2
6 5 3
*/
/*kq i  parent  cs
1 0 0
2 5 5
3 1 1
4 5 8
5 3 3
6 2 6
*/





