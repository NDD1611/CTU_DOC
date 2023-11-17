#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

#define tankcapacity_X 9
#define tankcapacity_Y 4
#define goal 6

const char* action[] = {"First State", "Pour Water Full X", "Pour Water Full Y",
						"Pour Water Empty X", "Pour Water Empty Y",
						 "Pour Water X to Y", "Pour Water Y to X"};


typedef struct{
	int x;
	int y;
}State;

void makeNullState(State *s){
	s->x=0;
	s->y=0;
}

void printState(State s){
	printf("X: %d ----- Y: %d\n", s.x, s.y);
}

typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function;
}Node;

int goalcheck(State state){
	if(state.x == goal || state.y == goal){
		return 1;
	}
	return 0;
}

int PourWaterFullX(State cur, State *result){
	if(cur.x < tankcapacity_X){
		result->x = tankcapacity_X;
		result->y = cur.y;
		return 1;
	}
	return 0;
}

int PourWaterFullY(State cur, State *result){
	if(cur.y < tankcapacity_Y){
		result->x = cur.x;
		result->y=tankcapacity_Y;
		return 1;
	}
	return 0;
}

int PourWaterEmptyX(State cur, State *result){
	if(cur.x > 0){
		result->x = 0;
		result->y = cur.y;
		return 1;
	}
	return 0;
}

int PourWaterEmptyY(State cur, State *result){
	if(cur.y > 0){
		result->x = cur.x;
		result->y = 0;
		return 1;
	}
	return 0;
}

int PourWaterXY(State cur, State *result){
	if(cur.x > 0 && cur.y < tankcapacity_Y){
		result->x = cur.x - (tankcapacity_Y-cur.y);
		if(result->x < 0){
			result->x = 0;
		}
		result->y = cur.x + cur.y;
		if(result->y > tankcapacity_Y){
			result->y = tankcapacity_Y;
		}
		return 1;
	}
	return 0;
}

int PourWaterYX(State cur, State *result){
	if(cur.x < tankcapacity_X && cur.y > 0){
		result->x = cur.x + cur.y;
		if(result->x > tankcapacity_X){
			result->x = tankcapacity_X;
		}
		result->y = cur.y - (tankcapacity_X - cur.x);
		if(result->y < 0){
			result->y = 0;
		}
		return 1;
	}
	return 0;
}

int call_operator(State cur, State *result, int opt){
	switch (opt){
		case 1: return PourWaterFullX(cur, result);
		case 2: return PourWaterFullY(cur, result);
		case 3: return PourWaterEmptyX(cur, result);
		case 4: return PourWaterEmptyY(cur, result);
		case 5: return PourWaterXY(cur, result);
		case 6: return PourWaterYX(cur, result);
		default :
			printf("Error!, Call Operator");
			return 0;
	}
}

int compareState(State x, State y){
	if(x.x == y.x && x.y == y.y){
		return 1;
	}
	return 0;
}

int findState(State state, queue<Node*> Q){
	while(!Q.empty()){
		Node* node = Q.front();
		if(compareState(state, node->state)){
			return 1;
		}
		Q.pop();
	}
	return 0;
}

Node* BFS(State cur){
	queue<Node*> open;
	queue<Node*> close;
	Node* root = (Node*)malloc(sizeof(Node));
	root->no_function = 0;
	root->Parent = NULL;
	root->state = cur;
	open.push(root);
	while(!open.empty()){
		Node* node = open.front();
		open.pop();
		close.push(node);
		if(goalcheck(node->state)){
			return node;
		}
		int opt;
		for(opt = 1; opt <= 6; opt++){
			State newState;
			makeNullState(&newState);
			if(call_operator(node->state, &newState, opt)){
				if(findState(newState, open) || findState(newState, close)){
					continue;
				}
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->no_function = opt;
				newNode->Parent = node;
				newNode->state = newState;
				//printf("newState %d %d %d\n", newState.x, newState.y, newNode->no_function);
				open.push(newNode);
			}
		}
	}
	return NULL;
}

void printGoal(Node* p){
	Node* Array[100];
	int index = 0;
	while(p->Parent != NULL){
		Array[index] = p;
		index++;
		p = p->Parent;
	}
	Array[index] = p;
	index++;
	int i;
	int dem = 0;
	for(i = (index-1); i>=0; i--){
		printf("Action %d: %s\n",dem, action[Array[i]->no_function]);
		dem++;
		printState(Array[i]->state);
	}
}

int main(){
	State cur;
	cur.x = 5;
	cur.y = 4;
	Node* p = BFS(cur);
	printGoal(p);
	return 0;
}

