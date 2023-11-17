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
	state->x  = 0;
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

typedef struct {
	Node* Element[Maxlength];
	int Top_idx;
}Stack;


void push(Node* x, Stack *stack){
	if(full_Stack(*stack)){
		printf("Error! Stack is full");
	} else {
		stack->Top_idx--;
		stack->Element[stack->Top_idx] = x;
	}
}

void makeNull_Stack(Stack *stack){
	stack->Top_idx = Maxlength;
}

int empty_Stack(Stack stack){
	return stack.Top_idx == Maxlength;
}

Node* top(Stack stack){
	if(!empty_Stack(stack)){
		return stack.Element[stack.Top_idx];
	}
	return NULL;
}

void pop(Stack *stack){
	if(!empty_Stack(*stack)){
		stack->Top_idx++;
	} else {
		printf("Error! Stack is empty");
	}
}

int full_Stack(Stack stack){
	return stack.Top_idx==0;
}

int CompareState(State state1, State state2){
	if(state1.x == state2.x && state1.y == state2.y){
		return 1;
	}
	return 0;
}

int find_State(State state, Stack openStack){
	while(!empty_Stack(openStack)){
		if(CompareState(top(openStack)->state, state)){
			return 1;
		}
		pop(&openStack);
	}
	return 0;
}

int goalCheck(State state){
	return (state.x == goal || state.y == goal);
}

Node* DFS_Algorithm(State state){
	Stack open_DFS;
	Stack close_DFS;
	makeNull_Stack(&open_DFS);
	makeNull_Stack(&close_DFS);
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	push(root, &open_DFS);
	while(!empty_Stack(open_DFS)){
		Node* node = top(open_DFS);
		pop(&open_DFS);
		push(node, &close_DFS);
		if(goalcheck(node->state)){
			return node;	
		}
		
		int opt;
		for(opt = 1; opt <=6; opt++){
			State newState;
			makeNullState(&newState);
			if(call_operator(node->state, &newState, opt)){
				if(find_State(newState, open_DFS) || find_State(newState, close_DFS)){
					continue;
				}
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newState;
				newNode->Parent = node;
				newNode->no_function = opt;
				push(newNode, &open_DFS);
			}
		}
	}
	return NULL;
}

void print_WaysToGetGoal(Node* node){
	Stack stackPrint;
	makeNull_Stack(&stackPrint);
	while(node->Parent != NULL){
		push(node, &stackPrint);
		node = node->Parent;
	}
	push(node, &stackPrint);
	int no_action = 0;
	while(!empty_Stack(stackPrint)){
		printf("\n Action %d: %s", no_action, action[top(stackPrint)->no_function]);
		print_state(top(stackPrint)->state);
		pop(&stackPrint);
		no_action++;
	}
}

int main(){
	State cur_state, result;
	cur_state.x = 0;
	cur_state.y = 0;
	Node* p = DFS_Algorithm(cur_state);
	print_WaysToGetGoal(p);
	return 0;
}
