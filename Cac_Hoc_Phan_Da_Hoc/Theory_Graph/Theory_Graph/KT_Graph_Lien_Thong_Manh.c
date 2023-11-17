#include <stdio.h>

typedef struct{
	int data[100];
	int sl;
}List;
typedef struct {
	int data[100][100];
	int n, m;
}Graph;
void makeNullList(List *L){
	L->sl=0;
}
void pushList(List *L, int x){
	L->data[L->sl]=x;
	L->sl++;
}
List neighbors(Graph *G, int x){
	int i;
	List L;
	makeNullList(&L);
	for(i=1; i<=G->n;i++){
		if(G->data[x][i]==1){
			pushList(&L,i);
		}
	}
	return L;
}
int tonTaiDuongDi(Graph *G, int x, int y){
	List dd;
	makeNullList(&dd);
	int mark[G->n];
	int i;
	for(i=1; i<=G->n;i++){
		mark[i]=0;
	}
	pushList(&dd, x);
	while(!(dd.sl==0)){
		int P;
		P=dd.data[dd.sl-1];
		dd.sl--;
		
		if(mark[P]!=0) continue;
		
		mark[P]=1;
		List L;
		L=neighbors(G, P);
		
		for(i=0; i<L.sl;i++){
			pushList(&dd, L.data[i]);
		}
	}
	if(mark[y]!=0) return 1;
	
	return 0;
}

int main()
{
	Graph G;
	scanf("%d%d", &G.n, &G.m);
	int i, j, u, v;
	for(i=1; i<=G.n;i++){
		for(j=1; j<=G.n; j++){
			G.data[i][j]=0;
		}		
	}
	
	for(i=1; i<=G.m; i++){
		scanf("%d%d", &u, &v);
		G.data[u][v]=1;
	}
	
	int kt=1;
	for(i=1; i<=G.n;i++){
		for(j=1; j<=G.n; j++){
			if(i!=j){
				int tontai;
				tontai=tonTaiDuongDi(&G, i, j);
				if(tontai==0){
					kt=0;
					break;
				}
			}
		}		
	}
	if(kt==1){
		printf("strong connected");
	} else {
		printf("unconnected");
	}
	return 0;
}
