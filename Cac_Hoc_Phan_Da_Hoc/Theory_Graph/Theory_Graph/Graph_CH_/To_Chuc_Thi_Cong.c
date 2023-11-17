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
List neighbors(Graph *G, int P){
	int i;
	List L;
	makeNullList(&L);
	for(i=1; i<=G->n+2;i++){
		if(G->data[P][i]==1){
			pushList(&L, i);
		}
	}
	return L;
}

List taoA (Graph *G, int P){
	List L;
	makeNullList(&L);
	int i;
	for(i=1; i<=G->n; i++){
		if(G->data[i][P]==1){
			pushList(&L, i);
		}
	}
	return L;
}
void abc (Graph *G, int d[]){
	List dd;
	makeNullList(&dd);
	int cs[100]; // luu chi so bat dau som nhat
	int i;
	for(i=1; i<=G->n+2; i++){
		cs[i]=0;
	}
	
	pushList(&dd, 1);
	while(!(dd.sl==0)){
		int P;
		P=dd.data[dd.sl-1];
		dd.sl--;
		
		List L = neighbors(G, P);
		
		for(i=0; i<L.sl; i++){
			int cstam;
			int H;
			H=L.data[i];
			cstam = cs[P]+ d[P];
			if(cstam > cs[H]){
				cs[H]=cstam;
			}
			pushList(&dd, H);
		}
	}
	
	makeNullList(&dd);
	pushList(&dd, G->n);
	int cst[G->n+3]; // luu chi so bat dai tre nhat
	for(i=1; i<=G->n+2; i++){
		cst[i]=0;
	}
	cst[G->n+2]=cs[G->n+2];
	while(!(dd.sl==0)){
		int P;
		P=dd.data[dd.sl-1];
		dd.sl--;
		
		List L = neighbors(G, P);
		int min=99999;
		for(i=0; i<L.sl; i++){
			int cstam;
			int H;
			H=L.data[i];
			cstam=cst[H]-d[P];
			if(cstam < min){
				min=cstam;
			}
		}
		cst[P]=min;
		
		L = taoA(G, P);
		for(i=0; i<L.sl; i++){
			pushList(&dd, L.data[i]);
		}
	}
	
	printf("%d\n", cs[G->n+2]);
	for(i=1; i<=G->n+2; i++){
		printf("%d-%d\n", cs[i], cst[i]);
	}
	
}
int main (){
	Graph G;
	scanf("%d", &G.n);
	int d[100];
	int i, j;
	for(i=1; i<=G.n+2; i++){
		d[i]=0;
		for(j=1; j<=G.n+2; j++){
			G.data[i][j]=0;
		}
	}
	
	
	for(i=1; i<=G.n; i++){
		int u, v;
		scanf("%d", &u);
		d[i]=u;
		do {
			scanf("%d", &v);
			G.data[v][i]=1;
		}while(v>0);
	}
	int anfa, beta;
	anfa=11;
	beta=12;
	G.data[anfa][1]=1;
	G.data[G.n][beta]=1;
	d[anfa]=0;
	d[beta]=1;
	
	
	abc(&G, d);
	return 0;
}
/*
10
7 0
3 1 0
1 2 0
8 1 0
2 3 4 0
1 3 4 0
1 3 4 0
2 6 0
2 8 0
1 5 7 9 0
*/
/* Ket qua
21
0-0
7-11
10-14
7-7
15-18
15-15
15-19
16-16
18-18
20-20
0-0
21-21
*/
