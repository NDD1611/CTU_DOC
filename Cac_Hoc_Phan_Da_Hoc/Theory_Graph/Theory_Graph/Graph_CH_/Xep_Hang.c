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
		if(G->data[P][i]!=0){
			pushList(&L, i);
		}
	}
	return L;
}

void Xep_Hang(Graph *G){
	List dd;
	makeNullList(&dd);
	int  hang[100];
	int i;
	for(i=1; i<=G->n; i++){
		hang[i]=0;
	}
	
	pushList(&dd, 1);
	
	while(!(dd.sl==0)){
		int P;
		P=dd.data[dd.sl-1];
		dd.sl--;
		
		List L;
		L=neighbors(G, P);
		
		for(i=0; i<L.sl; i++){
			int H, htam;
			H=L.data[i];
			htam=hang[P]+1;
			if(hang[H]<htam){
				hang[H]=htam;
			}
			pushList(&dd, H);
		}
	}
	for(i=1; i<=G->n; i++){
		printf("%d\n", hang[i]);
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
	}
	Xep_Hang(&G);
	return 0;
}




