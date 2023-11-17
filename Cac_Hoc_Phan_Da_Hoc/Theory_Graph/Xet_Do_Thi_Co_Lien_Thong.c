#include <stdio.h>
#define max 100

typedef struct {
	int data[max][max];
	int n, m;
}Graph;
typedef struct {
	int data[max];
	int size;
}List;
typedef struct {
	int data[max];
	int top;
}Stack;
void pushStack(Stack *S, int x){
	S->top++;
	S->data[S->top]=x;
}
int popStack(Stack *S){
	int kq;
	kq = S->data[S->top];
	S->top--;
	return kq;
}
List neighbors(Graph *G, int x){
	List L;
	L.size=0;
	int i;
	for(i=0; i<=G->n;i++){
		if(G->data[x][i]==1){
			L.data[L.size]=i;
			L.size++;
		}
	}
	return L;
}
void DFS(Graph *G, int x, List *STT){
	Stack S;
	S.top=-1;
	List L;
	pushStack(&S, x);
	int P, i;
	while(!(S.top<0)){
		P = popStack(&S);
		if(STT->data[P]!=0) continue;
		
		STT->size++;
		STT->data[P]= STT->size;
		
		L = neighbors(G, P);
		for(i=0; i<L.size; i++){
			pushStack(&S, L.data[i]);
		}
	}
}

int main(){
	Graph G;
	scanf("%d%d", &G.n, &G.m);
	int i, j, u, v;
	for(i=1; i<=G.n; i++){
		for(j=1; j<=G.n; j++){
			G.data[i][j]=0;
		}
	}
	
	for(i=1; i<=G.m; i++){
		scanf("%d%d", &u, &v);
		G.data[u][v]=1;
		G.data[v][u]=1;
	}
	
	List STT;
	STT.size=0;
	DFS(&G, 1, &STT);
	
	int kt=1;
	for(i=1; i<=G.n; i++){
		if(STT.data[i]==0){
			kt=0;
		}
	}
	if(kt==0){
		printf("NO");
	} else printf("YES");
	
	return 0;
}
