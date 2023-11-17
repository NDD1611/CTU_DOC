#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

#define Maxlength 7


const char* action[] = {"First action", "UP 1 2 3", "UP 2 3 4", "UP 3 4 5", "UP 4 5 6"};

void printArray(int A[]){
	int i;
	for(i=1; i< Maxlength; i++){
		printf("%d ", A[i]);
	}
}

typedef struct{
	int vt1, vt2, vt3, vt4, vt5, vt6;
}State;

typedef struct Node{
	State state;
	Node* Parent;
	int no_function;
}Node;

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

int findState(State cur, stack<Node*> Q){
	while(!Q.empty()){
		Node* node = Q.top();
		if(compareState(cur, node->state)){
			return 1;
		}
		Q.pop();
	}
	return 0;
}

void printState(State s){
	printf("%d %d %d %d %d %d\n", s.vt1, s.vt2, s.vt3, s.vt4, s.vt5, s.vt6);
}

Node* DFS(State cur){
	stack<Node*> open;
	stack<Node*> close;
	Node* root = (Node*)malloc(sizeof(Node));
	root->no_function = 0;
	root->Parent = NULL;
	root->state = cur;
	open.push(root);
	while(!open.empty()){
		Node* node = open.top();
		open.pop();
		close.push(node);
		if(checkGoal(node->state)){
			return node;
		}
		for(int opt = 1; opt <= 4; opt++){
			State newState;
			if(call_operator(node->state, &newState, opt)){
				if(findState(newState, open) || findState(newState, close)){
					continue;
				}
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->no_function = opt;
				newNode->Parent= node;
				newNode->state = newState;
				open.push(newNode);
			}
		}
	}
	return NULL;
}

void printGoal(Node* p){
	stack<Node*> s;
	while(p->Parent != NULL){
		s.push(p);
		p=p->Parent;
	}
	s.push(p);
	int dem = 0;
	while(!s.empty()){
		Node* node = s.top();
		printf("Action %d: %s\n", dem, action[node->no_function]);
		printState(node->state);
		dem++;
		s.pop();
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
