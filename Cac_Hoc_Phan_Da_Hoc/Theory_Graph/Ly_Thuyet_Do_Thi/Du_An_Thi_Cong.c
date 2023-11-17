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
	for(i=1; i<=G.n+2; i++){
		if(G.data[x][i]!=0){
			pushList(&L, i);
		}
	}
	return L;
}

List Tao_Anh(Graph G, int P){
	int i;
	List L;
	makeNullList(&L);
	for(i=1; i<=G.n+2; i++){
		if(G.data[i][P]!=0){
			pushList(&L, i);
		}
	}
	return L;
}
void Thi_Cong(Graph G, int d[sz], int A, int B){
	List dd;
	makeNullList(&dd);
	pushList(&dd, A);
	int css[sz]; // css[] chua thoi gian som nhat de bat dau cong viec 
	int i;
	for(i=1; i<=B; i++){
		css[i]=0;
	}
	while(!(dd.sl==0)){
		int P=dd.data[dd.sl-1];
		dd.sl--;
		
		List L = neighbors(G, P);
		
		int i;
		for(i=0; i<L.sl; i++){
			int H = L.data[i];
			pushList(&dd, H);
			int hTam = css[P]+d[P];
			if(hTam > css[H]){
				css[H]=hTam;
			}
		}
		
	}
	
	makeNullList(&dd);
	int cst[sz];
	for(i=1; i<=B; i++){
		cst[i]=0;
	}
	cst[B]=css[B];
	pushList(&dd, G.n);
	while(!(dd.sl==0)){
		int P=dd.data[dd.sl-1];
		dd.sl--;
		
		List L = neighbors(G, P);
		int min=99999;
		for(i=0; i<L.sl; i++){
			int H=L.data[i];
			int cstam = cst[H]-d[P];
			if(cstam < min){
				min=cstam;
			}
		}
		cst[P]=min;
		
		L=Tao_Anh(G, P);
		for(i=0; i<L.sl; i++){
			int H=L.data[i];
			pushList(&dd, H);
		}
	}
	
	for(i=1; i<=B; i++){
		printf("%d-%d\n", css[i], cst[i]);
	}
	
}

int main(){
	
	Graph G;
	scanf("%d", &G.n);
	int i, j;
	int d[sz];
	int A=G.n+1;
	int B=G.n+2;
	for(i=1; i<=B; i++){
		for(j=1; j<=B; j++){
			G.data[i][j]=0;
		}
	}
	for(i=1; i<=G.n; i++){
		int  v;
		scanf("%d", &d[i]);
		do {
			scanf("%d", &v);
			G.data[v][i]=1;
		}while(v>0);
	}
	G.data[A][1]=1;
	G.data[G.n][B]=1;
	d[A]=0;
	d[B]=1;
	
	
	Thi_Cong(G, d, A, B);
	
	return 0;
}
