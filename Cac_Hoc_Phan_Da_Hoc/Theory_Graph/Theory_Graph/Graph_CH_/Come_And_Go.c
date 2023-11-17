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

int tontai(Graph *G, int x, int y){
	List dd;
	makeNullList(&dd);
	int mark[100];
	int i;
	for(i=1; i<=G->n; i++){
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
		
		for(i=0; i<L.sl; i++){
			int H;
			H=L.data[i];
			pushList(&dd, H);
		}
	}
	
	if(mark[y]==0) return 0;
	return 1;
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
		if(w==1){
			G.data[u][v]=1;
		}
		if(w==2){
			G.data[u][v]=1;
			G.data[v][u]=1;
		}
	}
	
	int kt=1;
	for(i=1; i<=G.n; i++){
		for(j=1; j<=G.n; j++){
			if(i != j){
				int kt2;
				kt2= tontai(&G, i, j);
				if(kt2==0) kt=0;
			}
		}
	}
	if(kt==0) {
		printf("NO");
	} else {
		printf("OKIE");
	}
	
	return 0;
}
