#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

#define tank_X 10
#define tank_Y 5
#define tank_Z 6
#define goal 8
#define Maxlength 100

const char* action[] = {"First Action", "X-->Y", "X-->Z", "Y-->X", "Y-->Z", "Z-->X", "Z-->Y"};

typedef struct{
	int x;
	int y;
	int z;
}State;

typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function;
}Node;

void makeNullState(State *state){
	state->x = 0;
	state->y = 0;
	state->z = 0;
}

void printState(State state){
	printf("X: %d ----- Y: %d ----- Z: %d\n", state.x, state.y, state.z);
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

int findState(State state, stack<Node*> S){
	while(!S.empty()){
		Node* node = S.top();
		if(compareState(node->state, state)){
			return 1;
		}
		S.pop();
	}
	return 0;
}

Node* DFS(State state){
	stack<Node*> open;
	stack<Node*> close;
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	open.push(root);
	while(!open.empty()){
		Node* node = open.top();
		open.pop();
		close.push(node);
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
				open.push(newNode);
			}
		}
	}
	return NULL;
}

void printGoal(Node* p){
	stack<Node*> stack;
	while(p->Parent != NULL){
		stack.push(p);
		p = p->Parent;
	}
	stack.push(p);
	int count = 0;
	while(!stack.empty()){
		Node* node = stack.top();
		printf("Action %d: %s\n", count, action[node->no_function]);
		printState(node->state);
		stack.pop();
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


