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

void Moore_Dijkstra(Graph G, int x){
	List dd;
	makeNullList(&dd);
	int mark[sz];
	int cs[sz];
	int parent[sz];
	int i; 
	for(i=1; i<=G.n; i++){
		mark[i]=0;
		parent[i]=0;
		cs[i]=0;
	}
	pushList(&dd, x);
	
	while(!(dd.sl==0)){
		int  P, min=9999, index=0;
		for(i=0; i<dd.sl; i++){
			P=dd.data[i];
			if(cs[P] < min){
				min=cs[P];
				index=i;
			}
		}
		P=dd.data[index];
		
		for(i=index; i<dd.sl-1; i++){
			dd.data[i]=dd.data[i+1];
		}
		dd.sl--;
		
		if(mark[P]!=0) continue;
		mark[P]=1;
		
		List L = neighbors(G, P);
		
		for(i=0; i<L.sl; i++){
			int H=L.data[i];
			int cstam=cs[P]+G.data[P][H];
			if(mark[H]==0){
				pushList(&dd, H);
				if(cs[H]==0){
					cs[H]=cstam;
					parent[H]=P;
				} else {
					if(cstam < cs[H]){
						cs[H]=cstam;
						parent[H]=P;
					}
				}
			}
		}
	}
	printf("\n");
	for(i=1; i<=G.n; i++){
		printf("%d %d %d\n", i, parent[i], cs[i]);
	}
	/*
6 9
1 2 7
1 3 9
1 5 14
2 3 10
2 4 15
3 4 11
3 5 2
4 6 6
5 6 9
	*/
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
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G.data[u][v]=w;
		G.data[v][u]=w;
	}
	//co nhap dinh xuat phat va ket thuc
	Moore_Dijkstra(G, 1);
	
	return 0;
}
