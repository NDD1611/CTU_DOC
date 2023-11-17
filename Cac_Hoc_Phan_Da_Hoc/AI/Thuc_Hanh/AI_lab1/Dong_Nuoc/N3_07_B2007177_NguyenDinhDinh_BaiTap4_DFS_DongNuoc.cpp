#include <stdio.h>
#include <stdlib.h>
#include <stack>

#define tankcapacity_X 9
#define tankcapacity_Y 4
#define goal 6

const char* action[] = {"First State", "Pour Water Full X", "Pour Water Full Y",
						"Pour Water Empty X", "Pour Water Empty Y",
						 "Pour Water X to Y", "Pour Water Y to X"};

using namespace std;

typedef struct{
	int x;
	int y;
}State;

void makeNullState(State *state){
	state->x=0;
	state->y=0;
}

void print_state(State state){
	printf("\nX: %d ------- Y: %d", state.x, state.y);
}

int goalcheck(State state){
	return (state.x == goal || state.y == goal);
}

typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function;
}Node;

int pourWaterFullX(State cur, State *result){
	if(cur.x < tankcapacity_X){
		result->x = tankcapacity_X;
		result->y = cur.y;
		return 1;
	}
	return 0;
}
int pourWaterFullY(State cur, State *result){
	if(cur.y < tankcapacity_Y){
		result->y = tankcapacity_Y;
		result->x = cur.x;
		return 1;
	}
	return 0;
}

int pourWaterEmptyX(State cur, State *result){
	if(cur.x > 0){
		result->x = 0;
		result->y = cur.y;
		return 1;
	}
	return 0;
}

int pourWaterEmptyY(State cur, State *result){
	if(cur.y > 0){
		result->y = 0;
		result->x = cur.x;
		return 1;
	}
	return 0;
}

int pourWaterXY(State cur, State *result){
	if(cur.x > 0 && cur.y < tankcapacity_Y){
		result->x = cur.x - (tankcapacity_Y-cur.y);
		if(result->x < 0){
			result->x= 0;
		}
		result->y = cur.y+cur.x;
		if(result->y > tankcapacity_Y){
			result->y = tankcapacity_Y;
		}
		return 1;
	}
	return 0;
}

int pourWaterYX(State cur, State *result){
	if(cur.y > 0 && cur.x < tankcapacity_X){
		result->x = cur.x+cur.y;
		if(result->x > tankcapacity_X){
			result->x= tankcapacity_X;
		}
		result->y =cur.y - (tankcapacity_X-cur.x);
		if(result->y < 0){
			result->y = 0;
		}
		return 1;
	}
	return 0;
}

int call_operator(State cur, State *result, int opt){
	switch (opt){
		case 1: return pourWaterFullX(cur, result);
		case 2: return pourWaterFullY(cur, result);
		case 3: return pourWaterEmptyX(cur, result);
		case 4: return pourWaterEmptyY(cur, result);
		case 5: return pourWaterXY(cur, result);
		case 6: return pourWaterYX(cur, result);
		default:
			printf("Error, call_operator");
			return 0;
	}
}

int find_state(State state, stack<Node*> s){
	while(!s.empty()){
		Node* node = s.top();
		if(node->state.x == state.x && node->state.y == state.y){
			return 1;
		}
		s.pop();
	}
	return 0;
}

Node* Dong_Nuoc_DFS(State state){
	stack<Node*> open;
	stack<Node*> close;
	Node* root = (Node*)malloc(sizeof(Node));
	root->no_function=0;
	root->Parent=NULL;
	root->state=state;
	open.push(root);
	while(!open.empty()){
		Node* node = open.top();
		open.pop();
		close.push(node);
		if(goalcheck(node->state)){
			return node;
		}
		for(int opt = 1; opt <= 6; opt++){
			State newstate;
			makeNullState(&newstate);
			if(call_operator(node->state, &newstate, opt) == 1){
				if(find_state(newstate, open) || find_state(newstate, close)){
					continue;
				}
				Node* newnode = (Node*)malloc(sizeof(Node));
				newnode->state = newstate;
				newnode->Parent = node;
				newnode->no_function=opt;
				open.push(newnode);
			}
		}	
	}
	return NULL;
}

void print_goal(Node* p){
	stack<Node*> stackGoal;
	int dem = 0;
	while(p->Parent != NULL){
		stackGoal.push(p);
		p = p->Parent;
	}
	stackGoal.push(p);
	dem = 0;
	while(!stackGoal.empty()){
		Node* node = stackGoal.top();
		printf("\nAction %d: %s", dem, action[node->no_function]);
		dem++;
		print_state(node->state);
		stackGoal.pop();
	}
}

int main(){
	State cur;
	makeNullState(&cur);
	Node* p = Dong_Nuoc_DFS(cur);
	print_goal(p);
	return 0;
}




