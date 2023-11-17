#include <stdio.h>

typedef struct {
	int u;
	int v; 
	int w;
}Edge;
typedef struct{
	int n, m;
	Edge data[100];
}Graph;

void Bell_Man_Ford(Graph *G, int s){
	int cs[100], parent[100];
	int i, it;
	for(i=1; i<=G->n; i++){
		cs[i]=999999;
		parent[i]=0;
	}
	cs[s]=0;
	parent[s]=0;
	for(it=1; it<=G->n; it++){
		for(i=0; i<G->m; i++){
			int u, v, w;
			u=G->data[i].u;
			v=G->data[i].v;
			w=G->data[i].w;
			if(cs[u]+w < cs[v]){
				cs[v]= cs[u]+w;
				parent[v]=u;
			}
		}
	}
//	for(i=1; i<=G->n; i++){
//		printf("%d %d %d\n", i, parent[i], cs[i]);
//	}

		for(i=0; i<G->m; i++){
			int u, v, w;
			u=G->data[i].u;
			v=G->data[i].v;
			w=G->data[i].w;
			if(cs[u]+w < cs[v]){
				printf("YES");
				return;
			}
		}
		printf("NO");
	
}

int main(){
	Graph G;
	scanf("%d%d", &G.n, &G.m);
	int i;
	for(i=0; i<G.m; i++){
		scanf("%d%d%d", &G.data[i].u, &G.data[i].v, &G.data[i].w);
	}	
	int s;
	scanf("%d", &s);

	Bell_Man_Ford(&G, s);
	return 0;
}
