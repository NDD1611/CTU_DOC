#include <stdio.h>

typedef struct{
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
	List L; makeNullList(&L);
	int i;
	for(i=1; i<=G->n; i++){
		if(G->data[P][i]!=0){
			pushList(&L, i);
		}
	}
	return L;
}

void distan(Graph *G, List *S, int mark[], int *u1, int *v1){
	int i, min=9999;
	for(i=0; i<S->sl; i++){
		List L;
		int P = S->data[i];
		L=neighbors(G, P);
		int j;
		for(j=0; j<L.sl; j++){
			int H=L.data[j];
			if(mark[H]==0){
				if(G->data[P][H] < min){
					min = G->data[P][H];
					*u1=P;
					*v1=H;
				}
			}
		}
	}
	pushList(S, *v1);
	mark[*v1]=1;
}

void prim(Graph *G){
	List S;
	makeNullList(&S);
	int i, u[100], v[100], w[100], mark[100];
	for(i=1; i<=G->n; i++){
		mark[i]=0;
		u[i]=0;
		v[i]=0;
		w[i]=0;
	}
	pushList(&S, 1);
	mark[1]=1;
	int sum_w=0;
	for(i=1; i<G->n; i++){
		int u1, v1;
		distan(G, &S, mark, &u1, &v1);
		u[i]=u1;
		v[i]=v1;
		w[i]=G->data[u1][v1];
		sum_w = sum_w + G->data[u1][v1];
	}
	printf("\n%d\n", sum_w);
	for(i=1; i<G->n; i++){
	 printf("%d %d %d\n", u[i], v[i], w[i]);
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
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G.data[u][v]=w;
		G.data[v][u]=w;
	}
	prim(&G);
	return 0;
}
/*
4 4
1 2 4
2 3 6
3 4 1
1 4 8
kq 
11
1 2 4
2 3 6
3 4 1

7 12
1 6 1
1 2 4
1 7 12
2 7 5
2 5 9
3 4 8
3 7 7
3 5 11
4 6 3
4 7 6
5 7 10
6 7 2
kq
26
1 6 1
6 7 2
4 6 3
1 2 4
3 7 7
2 5 9
*/
