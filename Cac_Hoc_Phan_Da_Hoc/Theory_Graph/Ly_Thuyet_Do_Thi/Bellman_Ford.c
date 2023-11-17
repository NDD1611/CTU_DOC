#include <stdio.h>
#define sz 50

typedef struct{
	int u, v, w;
}cung;


void Bellman_Ford(cung G[], int n, int m){
	
	int i, j;
	int cs[sz], parent[sz];
	for(i=1; i<=n; i++){
		cs[i]=999999;
		parent[i]=0;
	}
	cs[1]=0;
	parent[1]=0;
	for(i=1; i<=n; i++){
		for(j=0; j<m; j++){
			int u, v, w;
			u=G[j].u;
			v=G[j].v;
			w=G[j].w;
			if(cs[u] + w < cs[v]){
				cs[v]=cs[u]+w;
				parent[v]=u;
			}
		}
	}
	
	printf("\nThong tin:\n");
	for(i=1; i<=n; i++){
		printf("%d %d %d\n", i, parent[i], cs[i]);
	}
	for(j=0; j<m; j++){
		int u, v, w;
		u=G[j].u;
		v=G[j].v;
		w=G[j].w;
		if(cs[u] + w < cs[v]){
			printf("\nCo chu trinh am");
			return;
		}
	}
	printf("\nKhong co chu trinh am");
}

int main(){
	cung G[sz];
	int n, m;
	scanf("%d%d", &n, &m);
	int i;
	for(i=0; i<m; i++){
		scanf("%d%d%d", &G[i].u, &G[i].v, &G[i].w);
	}
	
	Bellman_Ford(G, n, m);
	return 0;
}
