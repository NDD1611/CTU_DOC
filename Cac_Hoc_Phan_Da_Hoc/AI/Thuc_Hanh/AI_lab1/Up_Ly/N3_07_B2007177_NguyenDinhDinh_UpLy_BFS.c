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
	Node* Elements[max_length];
	int front, rear;
}Queue;

int empty_Queue(Queue Q){
	return Q.front == -1;
}

void makeNull_Queue(Queue *Q){
	Q->rear = -1;
	Q->front = -1;
}

int full_Queue(Queue Q){
	return ((Q.rear - Q.front + 1) % max_length) == 0;
}

Node* get_Front(Queue Q){
	if(empty_Queue(Q)){
		printf("Queue is empty");
	} else {
		return Q.Elements[Q.front];
	}
}

void del_Queue(Queue *Q){
	if(!empty_Queue(*Q)){
		if(Q->front == Q->rear){
			makeNull_Queue(Q);
		} else {
			Q->front = (Q->front+1) % max_length;
		}
	} else {
		printf("Error, Delete");
	}
}

void push_Queue(Node* x, Queue *Q){
	if(!full_Queue(*Q)){
		if(empty_Queue(*Q)){
			Q->front = 0;
		}
		Q->rear = (Q->rear+1) % max_length;
		Q->Elements[Q->rear] = x;
	} else {
		printf("Error, delete");
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

int findState(State cur, Queue Q){
	while(!empty_Queue(Q)){
		Node* node = get_Front(Q);
		if(compareState(cur, node->state)){
			return 1;
		}
		del_Queue(&Q);
	}
	return 0;
}

void printState(State s){
	printf("%d %d %d %d %d %d\n", s.vt1, s.vt2, s.vt3, s.vt4, s.vt5, s.vt6);
}

Node* DFS(State cur){
	Queue open;
	Queue close;
	makeNull_Queue(&open);
	makeNull_Queue(&close);
	Node* root = (Node*)malloc(sizeof(Node));
	root->no_function = 0;
	root->Parent = NULL;
	root->state = cur;
	push_Queue(root, &open);
	while(!empty_Queue(open)){
		Node* node = get_Front(open);
		del_Queue(&open);
		push_Queue(node, &close);
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
				push_Queue(newNode, &open);
			}
		}
	}
	return NULL;
}

void printGoal(Node* p){
	Node* Array[100];
	int index=0;
	while(p->Parent != NULL){
		Array[index] = p;
		index++;
		p = p->Parent;
	}
	Array[index] = p;
	index++;
	int dem = 0;
	int i;
	for(i = index-1; i>=0; i--){
		Node* node = Array[i];
		printf("Action %d: %s\n", dem, action[node->no_function]);
		dem++;
		printState(node->state);
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
