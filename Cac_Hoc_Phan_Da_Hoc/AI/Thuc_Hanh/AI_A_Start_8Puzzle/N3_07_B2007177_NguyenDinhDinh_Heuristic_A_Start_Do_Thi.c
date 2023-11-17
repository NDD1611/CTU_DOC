#include <stdio.h>
#include <stdlib.h>

#define maxLength 100
#define maxVertice 5

const char* name[] = {"A", "B", "C", "D", "G"};

typedef struct {
	int neightbor[maxLength];
	int h;
}Vertices;

typedef struct{
	int num_vertice;
	Vertices v[maxLength];
}Graph;

typedef struct {
	int vertex;
}State;

typedef struct{
	State state;
	struct Node* Parent;
	int f;
	int g;
	int h;
}Node;

void printState(State state){
	printf("%s", name[state.vertex]);
}

int compareState(State state1, State state2){
	return state1.vertex == state2.vertex;
}

void initGraph(int n, Graph *G){
	G->num_vertice = n;
	int i, j;
	for(i=0; i< n; i++){
		for(j=0; j<n; j++){
			G->v[i].neightbor[j] = 0;
			G->v[i].h = 0;
		}
	}
}

typedef struct {
	Node* element[maxLength];
	int size;
}List;

void makeNullList(List *L){
	L->size = 0;	
}

int emptyList(List L){
	return L.size == 0;
}

int fullList(List L){
	return L.size == maxLength;
}

Node* elementAt(int p, List L){
	return L.element[p-1];
}

void pushList(Node* node,int position, List *L){
	if(!fullList(*L)){
		int q;
		for(q = L->size; q >= position; q--){
			L->element[q] = L->element[q-1];
		}
		L->element[position-1] = node;
		L->size++;
	} else {
		printf("List is full\n");
	}
}

void deleteList(int position, List *L){
	if(emptyList(*L)){
		printf("List is empty\n");
	} else if(position < 1 || position > L->size){
		printf("position iss not possible to delete\n");
	} else {
		int i;
		for(i = position-1; i < L->size; i++){
			L->element[i] = L->element[i+1];
		} 
		L->size--;
	}
}

Node* findState(State state, List L, int *position){
	int i;
	for(i=1; i<=L.size; i++){
		if(compareState(elementAt(i, L)->state, state)){
			*position = i;
			return elementAt(i, L);
		}
	}
	return NULL;
}

int goalCheck(State state, State goal){
	return compareState(state, goal);
}

void sortList(List *L){
	int i, j;
	for(i = 0; i < L->size-1; i++){
		for(j=i+1; j<L->size; j++){
			if(L->element[i]->f > L->element[j]->f){
				Node* node = L->element[i];
				L->element[i] = L->element[j];
				L->element[j] = node;
			}
		}
	}
}

Node* A_Start(Graph G, State state, State goal){
	List open;
	makeNullList(&open);
	List close;
	makeNullList(&close);
	Node* root = (Node*)malloc(sizeof(Node));
	root->Parent = NULL;
	root->state = state;
	root->g = 0;
	root->h = G.v[state.vertex].h;
	root->f  = root->g + root->h;
	pushList(root, open.size+1, &open);	
	while(!emptyList(open)){
		Node* node = elementAt(1, open);
		deleteList(1, &open);
		pushList(node, close.size+1, &close);
		
		if(goalCheck(node->state, goal)){
			return node;
		}
		int opt;
		for(opt = 0; opt < G.num_vertice; opt++){
			State newState;
			if(G.v[node->state.vertex].neightbor[opt] > 0){
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state.vertex = opt;
				newNode->Parent = node;
				newNode->g = node->g + G.v[node->state.vertex].neightbor[opt];
				newNode->h = G.v[opt].h;
				newNode->f = newNode->g + newNode->h;
				
				int pos_open, pos_close;
				Node* nodeFoundOpen = findState(newState, open, &pos_open);
				Node* nodeFoundClose = findState(newState, close, &pos_close);
				if(nodeFoundOpen == NULL && nodeFoundClose == NULL){
					pushList(newNode, open.size+1, &open);
				} else if(nodeFoundOpen != NULL && nodeFoundOpen->g > newNode->g){
					deleteList(pos_open, &open);
					pushList(newNode, pos_open, &open);
				} else if(nodeFoundClose != NULL && nodeFoundClose->g > newNode->g){
					deleteList(pos_close, &close);
					pushList(newNode, open.size+1, &open);
				}
			}
			sortList(&open);
		}
	}
	return NULL;
}


void printGoal(Node* p){
	Node* Array[maxLength];
	int index=0;
	while(p->Parent != NULL){
		Array[index] = p;
		p=p->Parent;
		index++;
	}
	Array[index] = p;
	index++;
	int i;
	for(i=index-1; i>=0; i--){
		printState(Array[i]->state);
		if(i > 0){
			printf("->");
		}
	}
}

int main(){
	int i,j;
	Graph graph;
	freopen("test.txt", "r", stdin);
	initGraph(maxVertice, &graph);
	for(i=0; i< maxVertice; i++){
		int x;
		scanf("%d", &x);
		graph.v[i].h = x;
		for(j=0; j<maxVertice; j++){
			scanf("%d", &x);
			graph.v[i].neightbor[j] = x;
		}
	}
	State A, G;
	A.vertex = 0;
	G.vertex = 4;
	
//	for(i=0; i<maxVertice; i++){
//		printf("%d ", graph.v[i].h);
//		for(j=0; j<maxVertice; j++){
//			printf("%d ", graph.v[i].neightbor[j]);
//		}
//		printf("\n");
//	}
//	
	Node* p = A_Start(graph, A, G);
	if(p == NULL){
		printf("Null");
	} else {
		printGoal(p);
	}
	return 0;
}
