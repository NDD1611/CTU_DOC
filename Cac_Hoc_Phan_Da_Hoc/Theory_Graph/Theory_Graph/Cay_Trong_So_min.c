#include <stdio.h>

typedef struct{
	int u, v, w;
}cung;
typedef struct{
	cung data[100];
	int n, m;
}Graph;
typedef struct{
	cung data[100];
	int sl;
}List;
void makeNullList(List *L){
	L->sl=0;
}
void pushList(List *L, cung x){
	L->data[L->sl].u=x.u;
	L->data[L->sl].v=x.v;
	L->data[L->sl].w=x.w;
	L->sl++;
}

void ab(Graph *G){
	int i, tong=0;
	List cung;
	makeNullList(&cung);
	for(i=0; i<G->n-1; i++){
		 int j, min=99999, minindex=0;
		 for(j=0; j<G->m; j++){
		 	if(G->data[j].w < min){
		 		min=G->data[j].w;
		 		minindex=j;
			 }
		 }
		 pushList(&cung, G->data[minindex]);
		 tong += G->data[minindex].w;
		 for(j=minindex; j<G->m-1; j++){
		 	G->data[j].u=G->data[j+1].u;
		 	G->data[j].v=G->data[j+1].v;
		 	G->data[j].w=G->data[j+1].w;
		 }
		 G->m--;
	}
	printf("%d\n", tong);
	for(i=0; i<cung.sl; i++){
		if(cung.data[i].u > cung.data[i].v){
			int temp;
			temp=cung.data[i].u;
			cung.data[i].u=cung.data[i].v;
			cung.data[i].v=temp;
		}
	}
	for(i=0; i<cung.sl; i++){
		printf("%d %d %d\n", cung.data[i].u, cung.data[i].v, cung.data[i].w);
	}
}

int main(){
	Graph G;
	scanf("%d%d", &G.n, &G.m);
	int i;
	for(i=0; i<G.m; i++){
		scanf("%d%d%d", &G.data[i].u, &G.data[i].v, &G.data[i].w);
	}
//	for(i=0; i<G.m; i++){
//		printf("%d %d %d\n", G.data[i].u, G.data[i].v, G.data[i].w);
//	}
	ab(&G);
	
	return 0;
}
