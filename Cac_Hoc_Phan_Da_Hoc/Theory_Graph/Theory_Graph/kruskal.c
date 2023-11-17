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
	int i, tong=0, nhom[100];
	List cung;
	for(i=1; i<=G->n; i++){
		nhom[i]=i;
	}
	makeNullList(&cung);
	while(cung.sl < G->n-1){
		 int j, min=99999, minindex=0;
		 for(j=0; j<G->m; j++){
		 	if(G->data[j].w < min){
		 		min=G->data[j].w;
		 		minindex=j;
			 }
		 }
		 int u, v;
		 u=G->data[minindex].u;
		 v=G->data[minindex].v;
		 if(nhom[u] == nhom[v]){
			 for(j=minindex; j<G->m-1; j++){
			 	G->data[j].u=G->data[j+1].u;
			 	G->data[j].v=G->data[j+1].v;
			 	G->data[j].w=G->data[j+1].w;
			 }
			 G->m--;
		 	continue;
		 }
		 pushList(&cung, G->data[minindex]);
		 int ntam=nhom[v];
		 for(j=1; j<= G->n; j++){
		 	if(nhom[j] == ntam){
				nhom[j]=nhom[u];
			}
		 }
		 tong += G->data[minindex].w;
		 for(j=minindex; j<G->m-1; j++){
		 	G->data[j].u=G->data[j+1].u;
		 	G->data[j].v=G->data[j+1].v;
		 	G->data[j].w=G->data[j+1].w;
		 }
		 G->m--;
		 if(cung.sl==G->n-1) break;
	}
	printf("%d\n", tong);
	for(i=0; i<cung.sl; i++){
		if(cung.data[i].u > cung.data[i].v){
			int temp;
			temp=cung.data[i].u;
			cung.data[i].u=cung.data[i].v;
			cung.data[i].v=temp;
		}
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
	ab(&G);
	return 0;
}

/*
4 4
1 2 3
2 3 6
4 3 1
1 4 9
kq
10
3 4 1
1 2 3
2 3 6

7 12
1 6 1
1 2 4
1 7 12
2 7 5
2 5 9
3 4 8
3 7 7
3 5 11
4 6 3
4 7 6
5 7 10
6 7 2
kq
26
1 6 1
6 7 2
4 6 3
1 2 4
3 7 7
2 5 9
*/
