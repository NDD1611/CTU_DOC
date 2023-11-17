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

void HADDOCK(Graph G){
	List dd;
	makeNullList(&dd);
	pushList(&dd, 1);
	
	int mark[sz];
	int i;
	for(i=1; i<=G.n; i++){
		mark[i]=0;
	}
	int kt=0;
	while(!(dd.sl==0)){
		int P = dd.data[dd.sl-1];
		dd.sl--;
		
		if(mark[P]!=0) continue;
		mark[P]=1;
		
		List L = neighbors(G, P);
		
		for(i=0; i<L.sl; i++){
			int H=L.data[i];
			pushList(&dd, H);
			if(mark[H]!=0){
				kt=1;
				break;
			}
		}
	}
	if(kt==1){
		printf("NO");
	} else printf("YES");
}


int tontai(Graph G, int x, int y){
	List dd;
	makeNullList(&dd);
	int mark[100];
	int i;
	for(i=1; i<=G.n; i++){
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
	
	if(mark[y]!=0){
		return 1;
	}
	else return 0;
}

void LTM(Graph G){
int i, j;	
	int kt = 1;
	for(i=1; i<=G.n; i++){
		for(j=1; j<=G.n; j++){
			if(i != j){
				if(tontai(G, i, j) == 0){
					kt=0;
				}
			}
		}
	}
	if(kt==1){
		printf("strong connected");
	} else printf("unconnected");
	
}

void Xep_Hang(Graph G){	//xep hang do thi
	int hang[sz];
	int i;
	for(i=1; i<=G.n; i++){
		hang[i]=0;
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
	for(i=1; i<=G.n; i++){
		printf("%d\n", hang[i]);
	}
}

void Can_Da(Graph G){	//Bai toan can da
	int hang[sz];
	int i;
	for(i=1; i<=G.n; i++){
		hang[i]=0;
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
	int j;
	for(i=0; i<G.n; i++){
		for(j=1; j<=G.n; j++){
			if(hang[j]==i){
				printf("%d ", j);
			}
		}
	}
	
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
		G.data[u][v]=1;
	}
	
	Can_Da(G);
	
	return 0;
}
