#include <stdio.h>

typedef struct{
	int data[100][100];
	int n, m;
}Graph;
typedef struct {
	int  data[100];
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
	List L;
	makeNullList(&L);
	int i;
	for(i=1; i<=G->n; i++){
		if(G->data[P][i]!=0){
			pushList(&L, i);
		}
	}	
	return L;
}

int tarjan (Graph *G, int lt[], int x){
	List dd;
	makeNullList(&dd);
	int i, mark[100], parent[100], Ptam, Parenttam, kt=0;
	for(i=1; i<=G->n; i++){
		mark[i]=0;
		parent[i]=0;
	}
	parent[x]=x;
	pushList(&dd, x);
	pushList(&dd, parent[x]);
	//printf("\n\n");
	while(!(dd.sl==0)){
		int parentP=dd.data[dd.sl-1];
		dd.sl--;
		int P=dd.data[dd.sl-1];
		dd.sl--;
		//printf("%d %d\n", P, parentP);
		if(mark[P]!=0) continue;
		mark[P]=1;
		parent[P]=parentP;
		List L=neighbors(G, P);
		for(i=0; i<L.sl; i++){
			int H=L.data[i];
			if(lt[H]==0){
				if(mark[H]!=0){
					Ptam=H;
					Parenttam=P;
					kt=1;
				} else {
					pushList(&dd, H);
					pushList(&dd, P);
				}
			}
		}
		if(kt==1){
			break;
		}
	}
//	printf("\n\n%d %d\n", Ptam, Parenttam);
//	for(i=1; i<=G->n; i++){
//		printf("%d %d %d\n", i, mark[i], parent[i]);
//	}
	if(kt==1){
		lt[Ptam]=1;
		lt[Parenttam]=1;
		while(Parenttam!=Ptam){
			int H=Parenttam;
			Parenttam=parent[H];
			lt[Parenttam]=1;
		}
		return 1;
	} else return 0;
}

int main(){
	Graph G;
	scanf("%d%d", &G.n, &G.m);
	int i, j;
	for(i=1; i<=G.n; i++){
		for(j=1; j<=G.n; j++){
			G.data[i][j]=0;
		}
	}
	
	for(i=1; i<=G.m; i++){
		int u,v;
		scanf("%d%d", &u, &v);
		G.data[u][v]=1;
	}
	int lt[100];
	for(i=1; i<=G.n; i++){
		lt[i]=0;
	}
	int kt, dem=0; 
	j=1;
	//printf("\n\n");
	while(1){
		kt=0;
		if(lt[j]==0){
			kt = tarjan(&G, lt, j);
			if(kt) dem++;
		}
//		if(kt==1) {
//			printf("\nlan so: %d %d\n", kt, j);
//			for(i=1; i<=G.n; i++){
//				if(lt[i]!=0) printf("%d ", i);
//			}
//		} 
		if(j>G.n) break;
		j++;
	}
	printf("%d", dem);
	return 0;
}
/*
8 13
1 2
1 3
2 1
2 8
3 4
3 5
4 2
4 7
4 8
5 3
5 7
6 7
7 6
*/
