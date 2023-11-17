#include <stdio.h>
#include <stdlib.h>

#define tankcapacity_X 9
#define tankcapacity_Y 4
#define empty 0
#define goal 6
#define Maxlength 100

typedef struct {
	int x;
	int y;
}State;

const char* action[] = {"First State", "Pour Water Full X", "Pour Water Full Y",
						"Pour Water Empty X", "Pour Water Empty Y",
						 "Pour Water X to Y", "Pour Water Y to X"};

void makeNullState(State *state){
	state->x = 0;
	state->y = 0;
}

void print_state(State state){
	printf("\n X:%d ---- Y:%d", state.x, state.y);
}

int goalcheck(State state){
	return 	(state.x == goal || state.y == goal);
}

int pourWaterFullX(State cur_state, State *result){
	if(cur_state.x < tankcapacity_X){
		result->x = tankcapacity_X;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}

int pourWaterFullY(State cur_state, State *result){
	if(cur_state.y < tankcapacity_Y){
		result->y = tankcapacity_Y;
		result->x = cur_state.x;
		return 1;
	}
	return 0;
}

int pourWaterEmptyX(State cur_state, State *result){
	if(cur_state.x > 0){
		result->x = empty;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}

int pourWaterEmptyY(State cur_state, State *result){
	if(cur_state.y > 0){
		result->y = empty;
		result->x = cur_state.x;
		return 1;
	}
	return 0;
}

int pourWaterXY(State cur_state, State *result){
	if(cur_state.x > 0 && cur_state.y < tankcapacity_Y){
		result->x = cur_state.x - (tankcapacity_Y - cur_state.y);
		if(result->x < 0){
			result->x = empty;
		}
		result->y = (cur_state.y + cur_state.x);
		if(result->y > tankcapacity_Y){
			result->y = tankcapacity_Y;
		}
		return 1;
	}
	return 0;
}

int pourWaterYX(State cur_state, State *result){
	if(cur_state.x < tankcapacity_X && cur_state.y > 0){
		result->x = cur_state.x + cur_state.y;
		if(result->x > tankcapacity_X){
			result->x = tankcapacity_X;
		}
		result->y = cur_state.y - (tankcapacity_X - cur_state.x);
		if(result->y < 0){
			result->y = empty;
		}
		return 1;
	}
	return 0;
}

int call_operator(State cur_state, State *result, int option){
	switch(option){
		case 1: return pourWaterFullX(cur_state, result);
		case 2: return pourWaterFullY(cur_state, result);
		case 3: return pourWaterEmptyX(cur_state, result);
		case 4: return pourWaterEmptyY(cur_state, result);
		case 5: return pourWaterXY(cur_state, result);
		case 6: return pourWaterYX(cur_state, result);
		default : 
			printf("Error calls operators");
			return 0;
	}
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

int empty_Queue(Queue Q){
	return Q.front == -1;
}

void makeNull_Queue(Queue *Q){
	Q->rear = -1;
	Q->front = -1;
}

int full_Queue(Queue Q){
	return ((Q.rear - Q.front + 1) % Maxlength) == 0;
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
			Q->front = (Q->front+1) % Maxlength;
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
		Q->rear = (Q->rear+1) % Maxlength;
		Q->Elements[Q->rear] = x;
	} else {
		printf("Error, delete");
	}
}

int CompareState(State state1, State state2){
	if(state1.x == state2.x && state1.y == state2.y){
		return 1;
	}
	return 0;
}

int find_State(State state, Queue open){
	while(!empty_Queue(open)){
		if(CompareState(get_Front(open)->state, state)){
			return 1;
		}
		del_Queue(&open);
	}
	return 0;
}

Node* BFS_Algorithm(State state){
	Queue open, close;
	makeNull_Queue(&open);
	makeNull_Queue(&close);
	Node* root = (Node*)malloc(sizeof(Node));
	root->no_function = 0;
	root->Parent = NULL;
	root->state = state;
	push_Queue(root, &open);
	while(!empty_Queue(open)){
		Node* node = get_Front(open);
		del_Queue(&open);
		push_Queue(node, &close);
		if(goalcheck(node->state)){
			return node;
		}
		int opt;
		for(opt = 1; opt <=6; opt++){
			State newstate;
			makeNullState(&newstate);
			if(call_operator(node->state, &newstate, opt)){
				if(find_State(newstate, open) || find_State(newstate, close)){
					continue;
				}
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->no_function = opt;
				newNode->Parent = node;
				newNode->state = newstate;
				push_Queue(newNode, &open);
			}
		}
	}
	return NULL;
}

void print_Goal(Node* node){
	Node* Elements[Maxlength];
	int index = 0;
	while(node->Parent != NULL){
		Elements[index] = node;
		index++;
		node = node->Parent;
	}
	int i;
	int no_action=0;
	for(i = index-1; i>=0; i--){
		printf("\nAction %d: %s", no_action, action[Elements[i]->no_function]);
		print_state(Elements[i]->state);
		no_action++;
	}
}

int main(){
	State cur;
	makeNullState(&cur);
	Node* p = BFS_Algorithm(cur);
	print_Goal(p);
	return 0;
}
