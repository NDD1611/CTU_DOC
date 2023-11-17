#include <stdio.h>
#define sz 50

typedef struct{
	int data[sz][sz];
	int n, m;
}Graph;

typedef struct {
	int data[sz];
	int sl;
}List;

void makeNullList(List *L){
	L->sl=0;
}

void pushList(List *L, int x){
	L->data[L->sl]=x;
	L->sl++;
}

List neighbors(Graph G, int P){
	int i;
	List L;
	makeNullList(&L);
	for(i=1; i<=G.n; i++){
		if(G.data[P][i] != 0){
			pushList(&L, i);
		}
	}
	return L;
}

void Prim(Graph G, int x){
	List dd;
	makeNullList(&dd);
	int mark[sz];
	int i, j;
	int DSU[sz];
	int DSV[sz];
	int DSW[sz];
	for(i=1; i<=G.n; i++){
		mark[i]=0;
		DSU[i]=0;
		DSV[i]=0;
		DSW[i]=0;
	}
	pushList(&dd, x);
	mark[x]=1;
	for(i=1; i<G.n; i++){
		int ut, vt, wt=9999;
		for(j=0; j<dd.sl; j++){
			int P=dd.data[j];
			List L = neighbors(G, P);
			int k;
			for(k=0; k<L.sl; k++){
				int H=L.data[k];
				if(mark[H]==0){
					if(G.data[P][H] < wt){
						wt=G.data[P][H];
						ut=P;
						vt=H;
					}
				}
			}
		}
		DSU[i]=ut;
		DSV[i]=vt;
		mark[vt]=1;
		pushList(&dd, vt);
		DSW[i]=wt;
	}
	
	for(i=1; i<G.n; i++){
		printf("%d %d %d\n", DSU[i], DSV[i], DSW[i]);
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
	for(i=0; i<G.m; i++){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G.data[u][v]=w;
		G.data[v][u]=w;
	}
	for(i=1; i<=G.n; i++){
		for(j=1; j<=G.n; j++){
			printf("%d ", G.data[i][j]);
		}printf("\n");
	}
	Prim(G, 1);
	return 0;
}
