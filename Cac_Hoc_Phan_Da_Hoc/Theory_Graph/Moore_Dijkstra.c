#include <stdio.h>

typedef struct {
	int data[100][100];
	int n, m;
}Graph;

typedef struct {
	int data[100];
	int size;
}List;

List neighbors(Graph *G, int P){
	List L;
	L.size=0;
	int i;
	for(i=1; i<=G->n; i++){
		if(G->data[P][i] != 0){
			L.data[L.size]=i;
			L.size++;
		}
	}	
	return L;
}

void makeNullList(List *L){
	L->size=0;
}

void pushList(List* L, int x){
	L->data[L->size]=x;
	L->size++;
}
int Moore_Dijkstra(Graph *G, int x, int n){
	int i, j;
	int mark[100];
	List duongdi;
	List L;
	int dodai[100];
	for(i=1; i<=G->n; i++){
		dodai[i]=-1;
	}
	makeNullList(&duongdi);
	for(i=1; i<=G->n; i++){
		mark[i]=0;
	}
	List doiduyet;
	makeNullList(&doiduyet);
	pushList(&doiduyet, x);
	dodai[x]=0;
	while(!(doiduyet.size==0)) {
		int P;
		P=doiduyet.data[0];
		int min= P, minindex=0;
		for(i=0; i<doiduyet.size; i++){ // tim phan tu co do dai duong di ngan nhat de duyet
			P=doiduyet.data[i];
			if(dodai[P] < min){
				min = dodai[P];
				minindex=i;
			}
		}
		
		P = doiduyet.data[minindex]; 
		pushList(&duongdi, P);
		
		for(i=minindex; i<doiduyet.size; i++){
			doiduyet.data[i]= doiduyet.data[i+1];
		}
		doiduyet.size--;
		
		L=neighbors(G, P);
		
		for(i=0; i<L.size; i++){
			int H, kt, dodaiH, index;
			H=L.data[i];
			kt = 0;
			for(j=0; j<doiduyet.size; j++){
				if(H==doiduyet.data[j]){
					kt=1;
					index=j;
				}
			}
			dodaiH=dodai[P]+G->data[P][H];
			if(kt==1){
				if(dodaiH < dodai[doiduyet.data[index]]){
					dodai[doiduyet.data[index]]=dodaiH;
				}
			}else {
				pushList(&doiduyet, H);
				dodai[H]=dodaiH;
			}
		}
	}
	for(i=0; i<duongdi.size; i++){
		printf("%d -> ", duongdi.data[i]);
	}
	return dodai[n];
}

int main (){
	
	Graph G;
	int i, j, u, v, w;
	scanf("%d%d", &G.n, &G.m);
	for(i=1; i<=G.n; i++){
		for(j=1; j<=G.n; j++){
			G.data[i][j]=0;
		}
	}
	
	for(i=1; i<=G.m;i++){
		scanf("%d%d%d", &u, &v, &w);
		G.data[u][v]=w;
	}
	int kq;
	kq = Moore_Dijkstra(&G, 1, 5);
	printf("\n%d", kq);
	return 0;
}
