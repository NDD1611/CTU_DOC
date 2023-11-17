#include <stdio.h>
typedef struct{
	int u, v;
}Edge;
typedef struct {
	int n, m;
	Edge data[100];
}Graph;
typedef struct{
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

void Phan_Chia(Graph *G){
	List n1, n2;
	makeNullList(&n1);
	makeNullList(&n2);
	int n[100]; // cho biet dinh dang o trong nhom may
	int i;
	for(i=1; i<=G->n; i++){
		n[i]=0;
	}
	
	int kt=1;
	for(i=1; i<=G->m; i++){
		int u,v;
		u=G->data[i].u;
		v=G->data[i].v;
		if(n[u]==0 && n[v]==0){
			n[u]=1;
			n[v]=2;
			pushList(&n1, u);
			pushList(&n2, v);
		} else if(n[u]==1 && n[v]==0){
			n[v]=2;
			pushList(&n2, v);
		} else if(n[u]==2 && n[v]==0){
			n[v]=1;
			pushList(&n1, v);
		} else if(n[u]==n[v]){
			kt=0;
		}
	}
	if(kt==0){
		printf("IMPOSSIBLE");
	} else {
		for(i=0; i<n1.sl; i++){
			printf("%d ", n1.data[i]);
		}
		printf("\n");
		for(i=0; i<n2.sl; i++){
			printf("%d ", n2.data[i]);
		}
	}
}

int main(){
	
	Graph G;
	scanf("%d%d", &G.n, &G.m);
	int i;
	for(i=1; i<=G.m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		G.data[i].u=u;
		G.data[i].v=v;
	}
	Phan_Chia(&G);
	
	return 0;
}



