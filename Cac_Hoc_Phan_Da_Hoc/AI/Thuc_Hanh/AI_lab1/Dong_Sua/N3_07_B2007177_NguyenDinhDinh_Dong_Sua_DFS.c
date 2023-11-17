#include <stdio.h>
#include <stdlib.h>

#define tank_X 10
#define tank_Y 5
#define tank_Z 6
#define goal 8
#define empty 0
#define Maxlength 100

const char* action[] = {"First Action", "X-->Y", "X-->Z", "Y-->X", "Y-->Z", "Z-->X", "Z-->Y"};

typedef struct{
	int x;
	int y;
	int z;
}State;

typedef struct {
	State state;
	struct Node* Parent;
	int no_function;
}Node;

typedef struct {
	Node* Element[Maxlength];
	int Top_idx;
}Stack;

void makeNullState(State *state){
	state->x = 0;
	state->y = 0;
	state->z = 0;
}

void printState(State state){
	printf("X: %d ----- Y: %d ----- Z: %d\n", state.x, state.y, state.z);
}

void push(Node* x, Stack *stack){
	if(fullStack(*stack)){
		printf("Error! Stack is full");
	} else {
		stack->Top_idx--;
		stack->Element[stack->Top_idx] = x;
	}
}

void makeNullStack(Stack *stack){
	stack->Top_idx = Maxlength;
}

int emptyStack(Stack stack){
	return stack.Top_idx == Maxlength;
}

Node* top(Stack stack){
	if(!emptyStack(stack)){
		return stack.Element[stack.Top_idx];
	}
	return NULL;
}

void pop(Stack *stack){
	if(!emptyStack(*stack)){
		stack->Top_idx++;
	} else {
		printf("Error! Stack is empty");
	}
}

int fullStack(Stack stack){
	return stack.Top_idx==0;
}

int PourXY(State cur, State *result){
	if(cur.x > 0 && cur.y < tank_Y){
		result->x = cur.x - (tank_Y - cur.y);
		if(result->x < 0){
			result->x = 0;
		}
		result->y = cur.x + cur.y;
		if(result->y > tank_Y){
			result->y = tank_Y;
		}
		result->z = cur.z;
		return 1;
	}
	return 0;
}
int PourXZ(State cur, State *result){
	if(cur.x > 0 && cur.z < tank_Z){
		result->x = cur.x - (tank_Z - cur.z);
		if(result->x < 0){
			result->x = 0;
		}
		result->z = cur.x + cur.z;
		if(result->z > tank_Z){
			result->z = tank_Z;
		}
		result->y = cur.y;
		return 1;
	}
	return 0;
}
int PourYX(State cur, State *result){
	if(cur.y > 0 && cur.x < tank_X){
		result->y = cur.y - (tank_X - cur.x);
		if(result->y < 0){
			result->y = 0;
		}
		result->x = cur.x + cur.y;
		if(result->x > tank_X){
			result->x = tank_X;
		}
		result->z = cur.z;
		return 1;
	}
	return 0;
}
int PourYZ(State cur, State *result){
	if(cur.y > 0 && cur.z < tank_Z){
		result->y = cur.y - (tank_Z - cur.z);
		if(result->y < 0){
			result->y = 0;
		}
		result->z = cur.y + cur.z;
		if(result->z > tank_Z){
			result->z = tank_Z;
		}
		result->x = cur.x;
		return 1;
	}
	return 0;
}
int PourZX(State cur, State *result){
	if(cur.z > 0 && cur.x < tank_X){
		result->z = cur.z - (tank_X - cur.x);
		if(result->z < 0){
			result->z = 0;
		}
		result->x = cur.x + cur.z;
		if(result->x > tank_X){
			result->x = tank_X;
		}
		result->y = cur.y;
		return 1;
	}
	return 0;
}
int PourZY(State cur, State *result){
	if(cur.z > 0 && cur.y < tank_Y){
		result->z = cur.z - (tank_Y - cur.y);
		if(result->z < 0){
			result->z = 0;
		}
		result->y = cur.z + cur.y;
		if(result->y > tank_Y){
			result->y = tank_Y;
		}
		result->x = cur.x;
		return 1;
	}
	return 0;	
}

int call_operator(State cur, State *result, int opt){
	switch (opt){
		case 1: return PourXY(cur, result);
		case 2: return PourXZ(cur, result);
		case 3: return PourYX(cur, result);
		case 4: return PourYZ(cur, result);
		case 5: return PourZX(cur, result);
		case 6: return PourZY(cur, result);
		default: 
			printf("Error, Call Operator");
			return 0;
	}
}

int goalcheck(State state){
	return (state.x == goal || state.y == goal || state.z == goal);
}

int compareState(State x, State y){
	return (x.x == y.x && x.y == y.y && x.z == y.z);
}

int findState(State state, Stack S){
	while(!emptyStack(S)){
		Node* node = top(S);
		if(compareState(node->state, state)){
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
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	push(root, &open);
	while(!emptyStack(open)){
		Node* node = top(open);
//		printf("Action: %s\n", action[node->no_function]);
//		printState(node->state);
		pop(&open);
		push(node, &close);
		if(goalcheck(node->state)){
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
				push(newNode, &open);
			}
		}
	}
	return NULL;
}

void printGoal(Node* p){
	Stack stack;
	makeNullStack(&stack);
	while(p->Parent != NULL){
		push(p, &stack);
		p = p->Parent;
	}
	push(p, &stack);
	int count = 0;
	while(!emptyStack(stack)){
		Node* node = top(stack);
		printf("Action %d: %s\n", count, action[node->no_function]);
		printState(node->state);
		pop(&stack);
	}
}

int main(){
	State cur;
	cur.x = 10;
	cur.y = 0;
	cur.z = 0;
	Node* p = DFS(cur);
	printGoal(p);
	return 0;
}


