#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 3
#define EMPTY 0
#define MAX_OPERATOR 4
#define Maxlength 500

const char* action[] = {"First State",  "Move cell EMPTY to UP",
										"Move cell EMPTY to DOWN",
										"Move cell EMPTY to LEFT",
										"Move cell EMPTY to RIGHT"};

typedef struct {
	int puzzel[ROWS][COLS];
	int emptyRow;
	int emptyCol;
}State;

typedef struct Node {
	State state;
	struct Node* Parent;
	int no_func;
	int heuristic;
}Node;

typedef struct {
	Node* element[Maxlength];
	int size;
}List;

void makeNullList(List *L){
	L->size = 0;	
}

int emptyList(List L){
	return L.size == 0;
}

int fullList(List L){
	return L.size == Maxlength;
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

int compareState(State state1, State state2){
	if(state1.emptyRow != state2.emptyRow || state1.emptyCol != state2.emptyCol){
		return 0;
	}
	int row, col;
	for(row = 0; row < ROWS; row++){
		for(col = 0; col < COLS; col++){
			if(state1.puzzel[row][col] != state2.puzzel[row][col]){
				return 0;
			}
		}
	}
	return 1;
}

Node* findState(State state, List L, int *position){
	int i;
	for(i = 1; i <= L.size; i++){
		if(compareState(elementAt(i, L)->state, state)){
			*position = i;
			return elementAt(i, L);
		}
	}
	return NULL;
}


void sortList(List *L){
	int i, j;
	for(i = 0; i < L->size-1; i++){
		for(j=i+1; j<L->size; j++){
			if(L->element[i]->heuristic > L->element[j]->heuristic){
				Node* node = L->element[i];
				L->element[i] = L->element[j];
				L->element[j] = node;
			}
		}
	}
}

void printState(State state){
	int row, col;
	printf("\n-------------\n");
	for(row = 0; row < ROWS; row++){
		for(col = 0; col < COLS; col++){
			printf("| %d ", state.puzzel[row][col]);
		}
		printf("|\n");
	}
	printf("-------------\n");
}

int goalCheck(State state, State goal){
	return compareState(state, goal);
}

int UP(State state, State *r){
	*r = state;
	int ERC = state.emptyRow;
	int ECC = state.emptyCol;
	if(ERC > 0){
		r->emptyRow = ERC - 1;
		r->emptyCol = ECC;
		r->puzzel[ERC][ECC] = state.puzzel[ERC-1][ECC];
		r->puzzel[ERC-1][ECC] = EMPTY;
		return 1;
	}
	return 0;
}

int DOWN(State state, State *r){
	*r = state;
	int ERC = state.emptyRow;
	int ECC = state.emptyCol;
	if(ERC < ROWS-1){
		r->emptyRow = ERC + 1;
		r->emptyCol = ECC;
		r->puzzel[ERC][ECC] = state.puzzel[ERC+1][ECC];
		r->puzzel[ERC+1][ECC] = EMPTY;
		return 1;
	}
	return 0;
}

int LEFT(State state, State *r){
	*r = state;
	int ERC = state.emptyRow;
	int ECC = state.emptyCol;
	if(ECC > 0){
		r->emptyRow = ERC;
		r->emptyCol = ECC-1;
		r->puzzel[ERC][ECC] = state.puzzel[ERC][ECC-1];
		r->puzzel[ERC][ECC-1] = EMPTY;
		return 1;
	}
	return 0;
}

int RIGHT(State state, State *r){
	*r = state;
	int ERC = state.emptyRow;
	int ECC = state.emptyCol;
	if(ECC < COLS-1){
		r->emptyRow = ERC;
		r->emptyCol = ECC+1;
		r->puzzel[ERC][ECC] = state.puzzel[ERC][ECC+1];
		r->puzzel[ERC][ECC+1] = EMPTY;
		return 1;
	}
	return 0;
}

int callOperator(State cur, State *r, int opt){
	switch (opt){
		case 1: return UP(cur, r);
		case 2: return DOWN(cur, r);
		case 3: return LEFT(cur, r);
		case 4: return RIGHT(cur, r);
		default: printf("Error, call operator");
		return 0;
	}
}

int heuristic1(State state, State goal){
	int row, col, count;
	for(row = 0; row < ROWS; row++){
		for(col = 0; col < COLS; col++){
			if(state.puzzel[row][col] != goal.puzzel[row][col]){
				count++;
			}
		}
	}
	return count;
}

Node* BFS(State state, State goal){
	List open;
	List close;
	makeNullList(&open);
	makeNullList(&close);
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_func = 0;
	root->heuristic = heuristic1(state, goal);
	pushList(root, open.size+1, &open);
	while(!emptyList(open)){
		Node* node = elementAt(1, open);
		deleteList(1, &open);
		pushList(node, close.size+1, &close);
		
		if(goalCheck(node->state, goal)){
			return node;
		}
		int opt;
		for(opt = 1; opt <= 4; opt++){
			State newState;
			if(callOperator(node->state, &newState, opt)){
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newState;
				newNode->no_func = opt;
				newNode->Parent = node;
				newNode->heuristic = heuristic1(newState, goal);
				
				int pos_open, pos_close;
				Node* nodeFoundOpen = findState(newState, open, &pos_open);
				Node* nodeFoundClose = findState(newState, close, &pos_close);
				if(nodeFoundOpen == NULL && nodeFoundClose == NULL){
					pushList(newNode, open.size+1, &open);
				} else if(nodeFoundOpen != NULL && nodeFoundOpen->heuristic > newNode->heuristic){
					deleteList(pos_open, &open);
					pushList(newNode, open.size+1, &open);
				} else if(nodeFoundClose != NULL && nodeFoundClose->heuristic > newNode->heuristic){
					deleteList(pos_close, &close);
					pushList(newNode, close.size+1, &close);
				}
			}
			sortList(&open);
		}
	}
	return NULL;
}

void printGoal(Node* p){
	Node* Array[Maxlength];
	int index = 0;
	while(p->Parent != NULL){
		Array[index] = p;
		index++;
		p=p->Parent;
	}
	Array[index] = p;
	index++;
	int i;
	int dem = 0;
	for(i = index-1; i>=0; i--){
		printf("Action %d: %s\n", dem, action[Array[i]->no_func]);
		printState(Array[i]->state);
		dem++;
	}
	
}

int main(){
	State state;
	state.emptyCol = 1;
	state.emptyRow = 1;
	state.puzzel[0][0] = 3;
	state.puzzel[0][1] = 4;
	state.puzzel[0][2] = 5;
	state.puzzel[1][0] = 1;
	state.puzzel[1][1] = 0;
	state.puzzel[1][2] = 2;
	state.puzzel[2][0] = 6;
	state.puzzel[2][1] = 7;
	state.puzzel[2][2] = 8;
	
	State goal;
	goal.emptyCol = 0;
	goal.emptyRow = 0;
	goal.puzzel[0][0] = 0;
	goal.puzzel[0][1] = 1;
	goal.puzzel[0][2] = 2;
	goal.puzzel[1][0] = 3;
	goal.puzzel[1][1] = 4;
	goal.puzzel[1][2] = 5;
	goal.puzzel[2][0] = 6;
	goal.puzzel[2][1] = 7;
	goal.puzzel[2][2] = 8;
	
	Node* p = BFS(state, goal);
	printGoal(p);
	return 0;
}
