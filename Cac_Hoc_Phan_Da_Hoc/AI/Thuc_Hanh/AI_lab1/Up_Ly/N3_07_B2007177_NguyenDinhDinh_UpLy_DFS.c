#include <stdio.h>
#include <stdlib.h>
#define max_length 100

const char* action[] = {"First action", "UP 1 2 3", "UP 2 3 4", "UP 3 4 5", "UP 4 5 6"};

typedef struct{
	int vt1, vt2, vt3, vt4, vt5, vt6;
}State;

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

int checkGoal(State s){
	return s.vt1 == 1 && s.vt2 == 1 && s.vt3 == 1 && s.vt4 == 1 && s.vt5 == 1 && s.vt6 == 1;
}

int A123(State cur, State *re){
	re->vt1 = -cur.vt1;
	re->vt2 = -cur.vt2;
	re->vt3 = -cur.vt3;
	re->vt4 = cur.vt4;
	re->vt5 = cur.vt5;
	re->vt6 = cur.vt6;
	return 1;
}

int A234(State cur, State *re){
	re->vt1 = cur.vt1;
	re->vt2 = -cur.vt2;
	re->vt3 = -cur.vt3;
	re->vt4 = -cur.vt4;
	re->vt5 = cur.vt5;
	re->vt6 = cur.vt6;
	return 1;
}

int A345(State cur, State *re){
	re->vt1 = cur.vt1;
	re->vt2 = cur.vt2;
	re->vt3 = -cur.vt3;
	re->vt4 = -cur.vt4;
	re->vt5 = -cur.vt5;
	re->vt6 = cur.vt6;
	return 1;
}

int A456(State cur, State *re){
	re->vt1 = cur.vt1;
	re->vt2 = cur.vt2;
	re->vt3 = cur.vt3;
	re->vt4 = -cur.vt4;
	re->vt5 = -cur.vt5;
	re->vt6 = -cur.vt6;
	return 1;
}

int call_operator(State cur, State *re, int opt){
	switch(opt){
		case 1: return A123(cur, re);
		case 2: return A234(cur, re);
		case 3: return A345(cur, re);
		case 4: return A456(cur, re);
		default: 
			printf("Error, call Operator");
			return 0;
	}
}

int compareState(State x, State y){
	return x.vt1 == y.vt1 && x.vt2 == y.vt2 && x.vt3 == y.vt3 && x.vt4 == y.vt4 && x.vt5 == y.vt5 && x.vt6 == y.vt6;
}

int findState(State cur, Stack Q){
	while(!emptyStack(Q)){
		Node* node = top(Q);
		if(compareState(cur, node->state)){
			return 1;
		}
		pop(&Q);
	}
	return 0;
}

void printState(State s){
	printf("%d %d %d %d %d %d\n", s.vt1, s.vt2, s.vt3, s.vt4, s.vt5, s.vt6);
}

Node* DFS(State cur){
	Stack open;
	Stack close;
	makeNullStack(&open);
	makeNullStack(&close);
	Node* root = (Node*)malloc(sizeof(Node));
	root->no_function = 0;
	root->Parent = NULL;
	root->state = cur;
	push(root, &open);
	while(!emptyStack(open)){
		Node* node = top(open);
		pop(&open);
		push(node, &close);
		if(checkGoal(node->state)){
			return node;
		}
		int opt;
		for(opt = 1; opt <= 4; opt++){
			State newState;
			if(call_operator(node->state, &newState, opt)){
				if(findState(newState, open) || findState(newState, close)){
					continue;
				}
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->no_function = opt;
				newNode->Parent= node;
				newNode->state = newState;
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
		p=p->Parent;
	}
	push(p, &s);
	int dem = 0;
	while(!emptyStack(s)){
		Node* node = top(s);
		printf("Action %d: %s\n", dem, action[node->no_function]);
		printState(node->state);
		dem++;
		pop(&s);
	}
}

int main(){
	State cur;
	cur.vt1 = 1;
	cur.vt2 = -1;
	cur.vt3 = 1;
	cur.vt4 = -1;
	cur.vt5 = 1;
	cur.vt6 = -1;
	
	Node* p = DFS(cur);
	printGoal(p);
	return 0;
}
