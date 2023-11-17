#include <stdio.h>
#include <stdlib.h>


#define max_length 100

typedef struct{
	int si;
	int quy;
	char vt;
}State;

const char* action[] = {"First action", "Chuyen 1 tu si A->B", "Chuyen 2 tu si A->B",
						"Chuyen 1 con quy A->B", "Chuyen 2 con quy A->B","Chuyen 1 tu si va 1 con quy A->B",
						"Chuyen 1 tu si B->A", "Chuyen 2 tu si B->A", "Chuyen 1 con quy B->A",
						"Chuyen 2 con quy B->A", "Chuyen 1 tu si va 1 con quy B->A"};

void printState(State state){
	printf("Tu si: %d ----- Con quy: %d ----- Vi tri bo: %c\n", state.si, state.quy, state.vt);
}

typedef struct{
	State state;
	struct Node* Parent;
	int no_function;
}Node;

typedef struct{
	Node* element[max_length];
	int topId;
} Stack;

void makeNullStack(Stack *S){
	S->topId = max_length;
}

int emptyStack(Stack S){
	if(S.topId == max_length){
		return 1;
	}
	return 0;
}

Node* top(Stack S){
	if(!emptyStack(S)){
		return S.element[S.topId];
	}
	return NULL;
}

void pop(Stack *S){
	if(!emptyStack(*S)){
		S->topId++;
	}else{
		printf("Error, Stack is empty");
	}
}

int fullStack(Stack S){
	return S.topId == 0;
}

void push(Node* node, Stack *S){
	if(fullStack(*S)){
		printf("Error, stack is full");
	} else {
		S->topId--;
		S->element[S->topId] = node;
	}
}

int goalcheck(State state){
	return state.si == 0 && state.quy == 0 && state.vt == 'B';
}

int checkOver(State cur){
	if(cur.si == cur.quy){
		return 1;
	} 
	if(cur.si == 0 || cur.si == 3){
		return 1;
	}
	return 0;
}

int AB1S(State cur, State *re){
	if(cur.si >= 1){
		re->si = cur.si - 1;
		re->quy = cur.quy;
		re->vt = 'B';
		if(checkOver(*re)){
			return 1;
		}
	}
	return 0;
}

int AB2S(State cur, State *re){
	if(cur.si >= 2){
		re->si = cur.si - 2;
		re->quy = cur.quy;
		re->vt = 'B';
		if(checkOver(*re)){
			return 1;
		}
	}
	return 0;
}

int AB1Q(State cur, State *re){
	if(cur.quy >= 1){
		re->si = cur.si;
		re->quy = cur.quy - 1;
		re->vt = 'B';
		if(checkOver(*re)){
			return 1;
		}
	}
	return 0;
}

int AB2Q(State cur, State *re){
	if(cur.quy >= 2){
		re->si = cur.si;
		re->quy = cur.quy - 2;
		re->vt = 'B';
		if(checkOver(*re)){
			return 1;
		}
	}
	return 0;
}

int AB1S1Q(State cur, State *re){
	if(cur.quy >= 1 && cur.si >= 1){
		re->si = cur.si - 1;
		re->quy = cur.quy - 1;
		re->vt = 'B';
		if(checkOver(*re)){
			return 1;
		}
	}
	return 0;
}

int BA1S(State cur, State *re){
	if((3-cur.si) >= 1){
		re->si = cur.si + 1;
		re->quy = cur.quy;
		re->vt = 'A';
		if(checkOver(*re)){
			return 1;
		}
	}
	return 0;
}

int BA2S(State cur, State *re){
	if((3-cur.si) >= 2){
		re->si = cur.si + 2;
		re->quy = cur.quy;
		re->vt = 'A';
		if(checkOver(*re)){
			return 1;
		}
	}
	return 0;
}

int BA1Q(State cur, State *re){
	if((3-cur.quy) >= 1){
		re->si = cur.si;
		re->quy = cur.quy + 1;
		re->vt = 'A';
		if(checkOver(*re)){
			return 1;
		}
	}
	return 0;
}


int BA2Q(State cur, State *re){
	if((3-cur.quy) >= 2){
		re->si = cur.si;
		re->quy = cur.quy + 2;
		re->vt = 'A';
		if(checkOver(*re)){
			return 1;
		}
	}
	return 0;
}


int BA1S1Q(State cur, State *re){
	if((3-cur.quy) >= 1 && (3-cur.si) >=1){
		re->si = cur.si + 1;
		re->quy = cur.quy + 1;
		re->vt = 'A';
		if(checkOver(*re)){
			return 1;
		}
	}
	return 0;
}

int call_operator(State cur, State *re, int opt){
	if(cur.vt == 'A'){
		switch(opt){
			case 1: return AB1S(cur, re);
			case 2: return AB2S(cur, re);
			case 3: return AB1Q(cur, re);
			case 4: return AB2Q(cur, re);
			case 5: return AB1S1Q(cur, re);
		}
	} else if(cur.vt == 'B') {
		switch(opt){
			case 6: return BA1S(cur, re);
			case 7: return BA2S(cur, re);
			case 8: return BA1Q(cur, re);
			case 9: return BA2Q(cur, re);
			case 10: return BA1S1Q(cur, re);			
		}
	}
	return 0;
}

int findState(State state, Stack S){
	while(!emptyStack(S)){
		Node* node = top(S);
		if(state.si == node->state.si && state.quy == node->state.quy && state.vt == node->state.vt){
			return 1;
		}
		pop(&S);
	}
	return 0;
}

Node* DFS(State state){
	Stack open;
	Stack close;
	makeNullStack(&open);
	makeNullStack(&close);
	Node* root = (Node*)malloc(sizeof(Node));
	root->no_function = 0;
	root->Parent = NULL;
	root->state = state;
	push(root, &open);
	while(!emptyStack(open)){
		Node* node = top(open);
//		printState(node->state);
		pop(&open);
		push(node, &close);
		if(goalcheck(node->state)){
			return node;
		}
		int opt;
		for(opt = 1; opt <= 10; opt++){
			State newstate;
			if(call_operator(node->state, &newstate, opt)){
				if(findState(newstate, open) || findState(newstate, close)){
					continue;
				}
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->no_function = opt;
				newNode->Parent = node;
				newNode->state = newstate;
				push(newNode, &open);
			}
		}
	}
	return NULL;
}

void printGoal(Node* p){
	Stack s;
	makeNullStack(&s);
	while(p->Parent != NULL){
		push(p, &s);
		p = p->Parent;
	}
	push(p, &s);
	int dem = 0;
	while(!emptyStack(s)){
		Node* node = top(s);
		printf("Action %d: %s\n", dem, action[node->no_function]);
		dem++;
		printState(node->state);
		pop(&s);
	}
}

int main(){
	State cur;
	cur.si = 3;
	cur.quy = 3;
	cur.vt = 'A';
	Node* p = DFS(cur);
	printGoal(p);
	return 0;
}


