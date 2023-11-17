#include <stdio.h>
#include <stdlib.h>

#define tank_X 8
#define tank_Y 5
#define tank_Z 3
#define goal 4
#define empty 0
#define Maxlength 100

const char* action[] = {"First Action", "X-->Y", "X-->Z", "Y-->X", "Y-->Z", "Z-->X", "Z-->Y"};

typedef struct {
	int x;
	int y;
	int z;
}State;

void makeNullState(State *state){
	state->x = 0;
	state->y = 0;
	state->z = 0;
}

int compareState(State x, State y){
	return (x.x == y.x && x.y == y.y && x.z == y.z);
}

typedef struct {
	State state;
	struct Node* Parent;
	int no_function;
}Node;

typedef struct{
	Node* Elements[Maxlength];
	int front, rear;
}Queue;

int emptyQueue(Queue Q){
	return Q.front == -1;
}

void makeNullQueue(Queue *Q){
	Q->rear = -1;
	Q->front = -1;
}

int fullQueue(Queue Q){
	return ((Q.rear - Q.front + 1) % Maxlength) == 0;
}

Node* getFront(Queue Q){
	if(emptyQueue(Q)){
		printf("Queue is empty");
	} else {
		return Q.Elements[Q.front];
	}
}

void delQueue(Queue *Q){
	if(!emptyQueue(*Q)){
		if(Q->front == Q->rear){
			makeNullQueue(Q);
		} else {
			Q->front = (Q->front+1) % Maxlength;
		}
	} else {
		printf("Error, Delete");
	}
}

void pushQueue(Node* x, Queue *Q){
	if(!fullQueue(*Q)){
		if(emptyQueue(*Q)){
			Q->front = 0;
		}
		Q->rear = (Q->rear+1) % Maxlength;
		Q->Elements[Q->rear] = x;
	} else {
		printf("Error, delete");
	}
}

int checkgoal(State s){
	return s.x == goal || s.y == goal || s.z == goal;
}

int PourXY(State cur, State *re){
	if(cur.x > 0 && cur.y < tank_Y){
		re->x = cur.x - (tank_Y - cur.y);
		if(re->x < 0){
			re->x = 0;
		}
		re->y = cur.x + cur.y;
		if(re->y > tank_Y){
			re->y = tank_Y;
		}
		re->z = cur.z;
		
		return 1;
	}
	return 0;
}

int PourXZ(State cur, State *re){
	if(cur.x > 0 && cur.z < tank_Z){
		re->x = cur.x - (tank_Z - cur.z);
		if(re->x < 0){
			re->x = 0;
		}
		re->y = cur.y;
		re->z = cur.x + cur.z;
		if(re->z > tank_Z){
			re->z = tank_Z;
		}
		
		return 1;
	}
	return 0;
}

int PourYX(State cur, State *re){
	if(cur.y > 0 &&  cur.x < tank_X){
		re->x = cur.x + cur.y;
		if(re->x > tank_X){
			re->x = tank_X;
		}
		re->y = cur.y - (tank_X - cur.x);
		if(re->y < 0){
			re->y = 0;
		}
		re->z = cur.z;
		
		return 1;
	}
	return 0;
}

int PourYZ(State cur, State *re){
	if(cur.y > 0 && cur.z < tank_Z){
		re->x = cur.x;
		re->y = cur.y - (tank_Z - cur.z);
		if(re->y < 0){
			re->y = 0;
		}
		re->z = cur.z + cur.y;
		if(re->z > tank_Z){
			re->z = tank_Z;
		}
		
		return 1;
	}
	return 0;
}

int PourZX(State cur, State *re){
	if(cur.z > 0 && cur.x < tank_X){
		re->x = cur.x + cur.z;
		if(re->x > tank_X){
			re->x = tank_X;
		}
		re->y = cur.y;
		re->z = cur.z - (tank_X - cur.x);
		if(re->z < 0){
			re->z = 0;
		}
		
		return 1;
	}
	return 0;
}

int PourZY(State cur, State *re){
	if(cur.z > 0 && cur.y < tank_Y){
		re->x = cur.x;
		re->y = cur.z + cur.y;
		if(re->y > tank_Y){
			re->y = tank_Y;
		}
		re->z = cur.z - (tank_Y - cur.y);
		if(re->z < 0){
			re->z = 0;
		}
		
		return 1;
	}
	return 0;
}

int call_operator(State cur, State *re, int opt){
	switch (opt){
		case 1: return PourXY(cur, re);
		case 2: return PourXZ(cur, re);
		case 3: return PourYX(cur, re);
		case 4: return PourYZ(cur, re);
		case 5: return PourZX(cur, re);
		case 6: return PourZY(cur, re);
		default: 
			printf("Error, call operator");
			return 0;
	}
}

int findState(State state, Queue Q){
	while(!emptyQueue(Q)){
		Node* node = getFront(Q);
		if(compareState(state, node->state)){
			return 1;
		}
		delQueue(&Q);
	}
	return 0;
}

void printState(State state){
	printf("X: %d ----- Y: %d ----- Z: %d\n", state.x, state.y, state.z);
}

Node* BFS(State state){
	Queue open;
	Queue close;
	makeNullQueue(&open);
	makeNullQueue(&close);
	Node* root = (Node*)malloc(sizeof(Node));
	root->no_function = 0;
	root->Parent = NULL;
	root->state = state;
	pushQueue(root, &open);
	while(!emptyQueue(open)){
		Node* node = getFront(open);
		delQueue(&open);
		pushQueue(node, &close);
		if(checkgoal(node->state)){
			return node;
		}
		int opt;
		for(opt = 1; opt <= 6; opt++){
			State newstate;
			makeNullState(&newstate);
			if(call_operator(node->state, &newstate, opt)){
				if(findState(newstate, open) || findState(newstate, close)){
					continue;
				}
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->no_function = opt;
				newNode->Parent = node;
				newNode->state = newstate;
				pushQueue(newNode, &open);
			}
		}
	}
	return NULL;
}

void printGoal(Node* p){
	Node* re[Maxlength];
	int index = 0;
	while(p->Parent != NULL){
		re[index] = p;
		index++;
		p = p->Parent;
	}
	re[index] = p;
	index++;
	int i;
	int dem = 0;
	for(i = index-1; i >= 0; i--){
		printf("Action %d: %s\n",dem, action[re[i]->no_function]);
		dem++;
		printState(re[i]->state);
	}
}

int main(){
	State cur;
	cur.x = tank_X;
	cur.y = 0;
	cur.z = 0;
	
	Node* p = BFS(cur);
	printGoal(p);
	return 0;
}





