#include <stdio.h>

typedef struct {
	int data[100][100];
	int n, m;
}Graph;

typedef struct {
	int data[100];
	int size;
}List;

List neighbors ( Graph *G, int P){
	int i;
	List L;
	L.size=0;
	for(i=1; i<=G->n; i++){
		if(G->data[P][i]==1){
			L.data[L.size] = i;
			L.size++;
		}
	}
	return L;
}

int Haddock(Graph *G){
	int S[100], top = -1, i, j;
	List L;
	top++;
	S[top] = 1;
	int mark[100], size=0;
	int kt=0;
	while(!(top<0)){
		int P;
		P = S[top];
		top--;
		
		size++;
		mark[size]=P;
		
		L = neighbors(G, P);
		for(i=0; i<L.size; i++){
			top++;
			S[top]= L.data[i];
		}
		
		for(i=1; i<=size; i++){
			for(j=i+1; j<=size; j++){
				if(mark[i] == mark[j]){
					kt=1;
					return kt;
				}
			}
		}
	}
	return kt;
}

int main (){
	
	Graph G;
	int i, j, u, v;
	scanf("%d%d", &G.n, &G.m);
	for(i=1; i<=G.n; i++){
		for(j=1; j<=G.n; j++){
			G.data[i][j] = 0;
		}
	}
	for(i=1; i<=G.m; i++){
			scanf("%d%d", &u, &v);
			G.data[u][v] = 1;
	}
	int kt = Haddock(&G);
	if(kt==1){
		printf("NO");
	}else {
		printf("YES");
	}
	return 0;
}
