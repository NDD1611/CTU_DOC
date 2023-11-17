#include <stdio.h>
#define sz 50

typedef struct{
	int data[sz][sz];
	int n, m;
}Graph;
typedef struct{
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
List neighbors(Graph G, int x){
	int i;
	List L;
	makeNullList(&L);
	for(i=1; i<=G.n; i++){
		if(G.data[x][i]!=0){
			pushList(&L, i);
		}
	}
	return L;
}

void Chia_Keo(Graph G){
	int hang[sz];
	int i;
	for(i=1; i<=G.n; i++){
		hang[i]=1;
	}
	List dd;
	makeNullList(&dd);
	pushList(&dd, 1);
	
	while(!(dd.sl==0)){
		int P = dd.data[dd.sl-1];
		dd.sl--;

		List L=neighbors(G, P);
		for(i=0; i<L.sl; i++){
			int H= L.data[i];
			pushList(&dd, H);
			int hTam = hang[P]+1;
			if(hTam > hang[H]){
				hang[H]=hTam;
			}
		}
	}
	int tong=0;
	for(i=1; i<=G.n; i++){
		tong += hang[i];
		printf("%d\n", hang[i]);
	}
	printf("%d", tong);
}

int main(){
	Graph G;
	scanf("%d%d", &G.n, &G.m);
	int i, j;
	for(i=1; i<=G.m; i++){
		for(j=1; j<=G.m; j++){
			G.data[i][j]=0;
		}
	}
	for(i=1; i<=G.m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		// chia keo se them cung theo cach nguoc lai voi binh thuong  
		G.data[v][u]=1;
	}
	
	Chia_Keo(G);
	
	return 0;
}
