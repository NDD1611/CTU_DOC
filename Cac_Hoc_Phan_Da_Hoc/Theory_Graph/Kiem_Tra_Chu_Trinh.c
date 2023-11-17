#include <stdio.h>
typedef struct {
    int data[100];
    int top;
} Stack;
typedef struct {
    int A[100][100];
    int n;  // so dinh
    int m;  // so cung
}Graph;
typedef struct {
    int data[100];
    int size;
}List;

void push(Stack *S, int x){
    S->data[S->top]=x;
    S->top++;
}

List neighbors (Graph *G, int x){
    int i;
    List L;
    L.size=0;
    for(i=1; i<=G->n; i++){
        if(G->A[x][i]==1){
            L.data[L.size]= i;
            L.size++;
        }
    }
    return L;
}

int cochutrinh (Graph *G){
	Stack S;
	int x, parent, i, j;
	List mark, neigh;
	mark.size= neigh.size = 0;
	S.top=-1;
	S.top++;
	S.data[S.top]=1; // dua dinh 1 vao stack
	S.top++;
	S.data[S.top]=0; // cha cua dinh xuat phat la 0
	while(!(S.top<0)) {
		parent = S.data[S.top];
		S.top--;
		x = S.data[S.top];
		S.top--;
		
		mark.data[mark.size] = x;
		mark.size++;
		
		for(i=0; i<mark.size; i++){
			for(j=i+1; j<mark.size; j++){
				if(mark.data[j] == mark.data[i]){
					return 1;
				}
			}
		}
		
		neigh = neighbors(G, x);
		for(i=0; i<neigh.size; i++){
			if(neigh.data[i] != parent) {
				S.top++;
				S.data[S.top]=neigh.data[i];
				S.top++;
				S.data[S.top]=x;
			}
		}
	}
	return 0;
}


int main (){
    int i, j, u, v;
    Graph G;
    scanf("%d%d", &G.n, &G.m);
    
    for(i=1; i<=G.n; i++){
        for(j=1; j<=G.n; j++){
            G.A[i][j]=0;
        }
    }
    
    for(i=1; i<=G.m; i++){
        scanf("%d%d",&u, &v);
        G.A[u][v] = 1;
        G.A[v][u] = 1;
    }
    
    int kt = cochutrinh(&G);
    if(kt == 1) {
    	printf("YES");
	} else {
		printf("NO");
	}
    
    return 0;
}
