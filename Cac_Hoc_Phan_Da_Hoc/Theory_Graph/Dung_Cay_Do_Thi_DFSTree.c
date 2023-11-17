#include <stdio.h>
#define max 100

typedef struct{
    int data[max][max];
    int n, m;
} Graph;
typedef struct{
	int data[max];
	int size;
}List;
typedef struct {
	int data[max];
	int top;
}Stack;

void makeNullStack(Stack *S){
	S->top = -1;	
}

void pushStack(Stack *S, int x){
	S->top++;
	S->data[S->top] = x;
}

int popStack(Stack *S){
	int kq;
	kq=S->data[S->top];
	S->top--;
	return kq;
}
int emptyStack(Stack S){
	if(S.top < 0){
		return 1;
	} else {
		return 0;
	}
}

List neighbors(Graph *G, int x){
	List L;
	L.size = 0;
	int i;
	
	for(i=1; i<=G->n; i++){
		if(G->data[x][i]==1){
			L.data[L.size]= i;
			L.size++;
		}
	}
	return L;
}

void DFSTree(Graph *G, int x, List *STT, List *Parent){
	Stack S;
	int P, K;
	List L;
	int i;
	makeNullStack(&S);
	pushStack(&S, x);
	Parent->data[x]=0;
	
	while(!(emptyStack(S))){
		P = popStack(&S);
		if(STT->data[P]!=0) continue;
		
		STT->size++;
		STT->data[P]=STT->size;
		
		L = neighbors(G, P);
		
		for(i=0; i<L.size; i++){
			pushStack(&S, L.data[i]);
			K=L.data[i];
			if(K != x){
				if(STT->data[K] == 0){
					Parent->data[K] = P;
				}
			}
		}
	}
}


int main() {
    Graph G;
    int i, j, u, v;
    scanf("%d%d",&G.n, &G.m);
    
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
	
	List STT, Parent;
	STT.size=0;
	Parent.size=0;
	
	for(i=1; i<=G.n; i++){
		STT.data[i]=0;
		Parent.data[i]=0;
	}
	
	for(i=1; i<=G.n; i++){
		if(STT.data[i]==0){
			DFSTree(&G, i, &STT, &Parent);
		}
	}
    
    for(i=1; i<=G.n; i++){
    	printf("%d %d\n", i, Parent.data[i]);
	}
    return 0;
}
