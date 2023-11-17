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
List neighbors(Graph *G, int x){
	List L;
	makeNullList(&L);
	int i;
	for(i=1; i<=G->n; i++){
		if(G->data[x][i]!=0){
			pushList(&L, i);
		}
	}	
	return L;
}

int cochutrinh(Graph *G){
	int mark[100];
	int i;
	for(i=1; i<=G->n; i++){
		mark[i]=0;
	}
	List dd;
	makeNullList(&dd);
	pushList(&dd, 1);
	
	while(!(dd.sl==0)){
		int P;
		P=dd.data[dd.sl-1];
		dd.sl--;
		
		if(mark[P]!=0) continue;
		
		mark[P]=1;
		
		List L;
		L = neighbors(G, P);
		
		for(i=0; i<L.sl;i++){
			int H;
			H=L.data[i];
			if(mark[H]!=0) return 1;
			pushList(&dd, H);
		}
	}
	return 0;
}
		// la 1 do thi co huong, neu co chu trinh thi khong say, nguoc lai khong co chu trinh thi se say
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
	}
	
	int kt;
	kt = cochutrinh(&G);
	
	if(kt==1){
		printf("NO");
	} else printf("YES");
	
	return 0;
}
