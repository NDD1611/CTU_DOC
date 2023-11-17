#include <stdio.h>

#define SIZE 7
#define maxLength 100
#define ROWS SIZE
#define COLUMNS SIZE
#define max_value SIZE+1

char filename[] = "data_7x7.txt";
int count = 0;
typedef struct {
	int element[maxLength];
	int size;
}List;
typedef struct {
	int cells[SIZE][SIZE];
	int constrain1[SIZE*SIZE][SIZE*SIZE];
	int constrain2[SIZE*SIZE][SIZE*SIZE];
	int n;
	char opera[SIZE*SIZE];
	int value[SIZE*SIZE];
}KenKen;
typedef struct {
	int x;
	int y;
}Coord;

void makeNullList(List *L){
	L->size = 0;	
}

int emptyList(List L){
	return L.size == 0;
}

int fullList(List L){
	return L.size == maxLength;
}

int elementAt(int p, List L){
	return L.element[p-1];
}

int checkElement(int x, List L){
	int i;
	for(i=0; i<L.size; i++){
		if(L.element[i] == x){
			return 1;
		}
	}
	return 0;
}

void pushList(List *L, int x){
	if(!fullList(*L)){
		L->element[L->size] = x;
		L->size++;
	} else {
		printf("List is full\n");
	}
}

int indexOf(Coord coord){ // chuyen doi chi so toa do thanh chi so dinh 
	return (SIZE*coord.x + coord.y);
}

Coord positionOfVertex(int vertex){
	Coord coord;
	coord.x = vertex / SIZE;
	coord.y = vertex % SIZE;
	return coord;
}

typedef struct {
	Coord data[maxLength];
	int size;	
}ListCoord;

void initListCoord(ListCoord *L){
	L->size = 0;
}

void appendList(ListCoord *L, Coord coord){
	L->data[L->size] = coord;
	L->size++;
}

void initKenKen(KenKen *kenken){
	int i, j;
	kenken->n = 0;
	for(i=0 ; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			kenken->cells[i][j] = 0;
		}
	}
	for(i=0; i<SIZE*SIZE; i++){
		kenken->opera[i] =  'N';
		kenken->value[i] = 0;
		for(j=0; j<SIZE*SIZE; j++){
			kenken->constrain1[i][j] = 0;
			kenken->constrain2[i][j] = 0;
		}
	}
}

void readData(KenKen *kenken){
	FILE* f = fopen(filename, "r");
	int i, j;
	if(f != NULL){
		int n;
		fscanf(f, "%d", &n);
		kenken->n = n;
		printf("%d\n", n);
		for(i=0; i<n; i++){
			int num, x, y, ope, value; 			// num so o cua moi dong du lieu
			fscanf(f, "%d", &num);
			printf("%d ", num);
			if(num == 1){
				fscanf(f, "%d%d%d", &x, &y, &value);
				printf("%d %d %d\n", x , y, value);
				Coord coord = {x, y};
				int index = indexOf(coord);
				kenken->value[index] = value;
			} else {
				ListCoord list;
				initListCoord(&list);
				for(j = 0; j<num; j++){
					fscanf(f, "%d%d", &x, &y);
					printf("%d %d ", x , y);
					Coord coord = {x, y};
					appendList(&list, coord);
				}
				fscanf(f, "%c%d\n", &ope, &value);
				printf("%c %d\n", ope, value);
				for(j=0; j<list.size; j++){
					int indexCoord = indexOf(list.data[j]);
					int k;
					kenken->opera[indexCoord] = ope;
					kenken->value[indexCoord] = value;
					for(k=0; k<list.size; k++){
						if(k != j){
							int indexCoord2 = indexOf(list.data[k]);
							kenken->constrain2[indexCoord][indexCoord2] = 1;
							kenken->constrain2[indexCoord2][indexCoord] = 1;
						}
					}
				}
			}
		}
	}
}

void taoRangBuocRC(KenKen *kenken, Coord position){ // tao rang buoc hang va cot cho 1 vi tri x, y
	int i;
	// tao rang buoc hang
	for(i=0; i<SIZE; i++){
		int indexCoord = indexOf(position);
		if(i != position.y){
			Coord coord = {position.x, i};
			int indexCoord2 = indexOf(coord);
			kenken->constrain1[indexCoord][indexCoord2] = 1;
			kenken->constrain1[indexCoord2][indexCoord] = 1;
		}
	}
	
	// tao rang buoc cot
	for(i=0; i<SIZE; i++){
		int indexCoord = indexOf(position);
		if(i != position.x){
			Coord coord = {i, position.y};
			int indexCoord2 = indexOf(coord);
			kenken->constrain1[indexCoord][indexCoord2] = 1;
			kenken->constrain1[indexCoord2][indexCoord] = 1;
		}
	}
}
int isFilledKenKen(KenKen *kenken){
	int i, j;
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			if(kenken->cells[i][j] == 0) return 0;
		}
	}
	return 1;
}

ListCoord getConstrains (KenKen *kenken, Coord coord){
	int i;
	int v = indexOf(coord);
	ListCoord result;
	initListCoord(&result);
	for(i=0; i<SIZE*SIZE; i++){
		if(kenken->constrain1[v][i] == 1){
			appendList(&result, positionOfVertex(i));
		}
	}
	return result;
}

List getAvailableValues(Coord position, KenKen *kenken){
	ListCoord posList = getConstrains(kenken, position);

	int i;
	List result;
	makeNullList(&result);
	int availables[max_value];
	for(i = 1; i<max_value; i++){
		availables[i]=1;
	}
	for(i = 0; i<posList.size; i++){
		Coord pos = posList.data[i];
		if(kenken->cells[pos.x][pos.y] != 0){
			availables[kenken->cells[pos.x][pos.y]]= 0;
		}
	}
	for(i=1; i<max_value; i++){
		if(availables[i]) pushList(&result, i);
	}
	return result;
}

ListCoord layRangBuocKhoi(KenKen *kenken, Coord position){ // tra ve cac coord co trong long cua position bao gom ca position
	int indexPosition = indexOf(position);
	int i;
	ListCoord result;
	initListCoord(&result);
	appendList(&result, position);
	for(i=0; i<SIZE*SIZE; i++){
		if(kenken->constrain2[indexPosition][i] != 0){
			Coord coord = positionOfVertex(i);
			appendList(&result, coord);
		}
	}
	return result;
}

void swap(int A[SIZE*SIZE], int x, int y){
	int temp = A[x];
	A[x] = A[y];
	A[y] = temp;
}
void permute(int num, int A[SIZE*SIZE], int l, int r, List *result, Coord coord, char ope, int value, List constrain1){
	int i;
	if (l == r){
		int j; 
		int kq = A[0];
		for(j=0; j<num; j++){
			if(j!=0){
				if(ope == '+'){
					kq += A[j];
				}
				if(ope == '-'){
					kq -= A[j];
				}
				if(ope == '*'){
					kq *= A[j];
				}
				if(ope == '/'){
					kq /= A[j];
				}
			}
		}
		if(kq == value){
			for(i=0; i<num; i++){
				if(checkElement(A[i], constrain1) == 1  && checkElement(A[i], *result) == 0){
					pushList(result, A[i]);
				}
			}
		}
	} else {
		for (i = l; i <= r; i++) {
			swap(A, l, i);
			permute(num, A, l+1, r, result, coord, ope, value, constrain1);
			swap(A, l, i);
		}
	}
}
List getAvailableValues2(Coord coord, KenKen *kenken){			// get cac gia tri co the co cua cua o trong dua vao constrain 2
	int index = indexOf(coord);
	int ope = kenken->opera[index];
	int value = kenken->value[index];
	List result;
	makeNullList(&result);
	ListCoord listCoord = layRangBuocKhoi(kenken, coord);
	int num = listCoord.size;
	List constrain1 = getAvailableValues(coord, kenken);
	int i;
	int i1, i2, i3, i4, i5, i6, i7;
	for(i1=1; i1<=SIZE; i1++){
		for(i2=1; i2<=SIZE; i2++){
			for(i3=1; i3<=SIZE; i3++){
				for(i4=1; i4<=SIZE; i4++){
					for(i5=1; i5<=SIZE; i5++){
						int A[SIZE*SIZE];
						A[0]=i1;
						A[1]=i2;
						A[2]=i3;
						A[3]=i4;
						A[4]=i5;
						int kq = A[0];
						int j;
						for(j=0; j<num; j++){
							if(j!=0){
								if(ope == '+'){
									kq += A[j];
								}
								if(ope == '-'){
									kq -= A[j];
								}
								if(ope == '*'){
									kq *= A[j];
								}
								if(ope == '/'){
									kq /= A[j];
								}
							}
						}
						if(kq == value){
							for(i=0; i<num; i++){
								if(checkElement(A[i], constrain1) == 1  && checkElement(A[i], result) == 0){
									pushList(&result, A[i]);
								}
							}
						}
					}
				}
			}
		}
	}
	return result;
}

Coord getNextMinDomainCell(KenKen *kenken){
	int minLength = 99999999;
	int i, j, a;
	Coord result;
	
	for(i=0; i<SIZE*SIZE; i++){
		Coord coord = positionOfVertex(i);
		if(kenken->opera[i] == 'N' && kenken->cells[coord.x][coord.y] == 0){
			return coord;
		}
	}
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			if(kenken->cells[i][j] == 0){
				Coord pos = {i, j};
				List constrain2 = getAvailableValues2(pos, kenken);
				int availablesLength = constrain2.size;
				if(availablesLength < minLength){
					minLength = availablesLength;
					result = pos;
				}
			}
		}
	}
	return result;
}

void printKenKen(KenKen *kenken){
	int i, j;
	printf("kenken:\n");
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLUMNS; j++){
			printf("%d ", kenken->cells[i][j]);
		}
		printf("\n");
	}
}

void clearConstrain1(KenKen *kenken){
	int i, j;
	for(i=0; i<SIZE*SIZE; i++){	
		for(j=0; j<SIZE*SIZE; j++){
			kenken->constrain1[i][j] = 0;
		}
	}
}

void printConstrain1(KenKen kenken){
	int i, j;
	for(i=0; i<SIZE*SIZE; i++){
		printf("%2d ", i);
		for(j=0; j<SIZE*SIZE; j++){
			printf("%d ", kenken.constrain1[i][j]);
		}
		printf("\n");
	}
}

void printConstrain2(KenKen kenken){
	int i, j;
	printf("\n");
	for(i=0; i<SIZE*SIZE; i++){
		printf("%2d ", i);
		for(j=0; j<SIZE*SIZE; j++){
			printf("%d ", kenken.constrain2[i][j]);
		}
		printf("%d %c ", kenken.value[i], kenken.opera[i]);
		printf("\n");
	}
}

void permute2(int num, int A[SIZE*SIZE], int l, int r,int *check, char ope, int value){
	int i;
	if (l == r){
		int j; 
		int kq = A[0];
		for(j=1; j<num; j++){
			if(ope == '+'){
				kq += A[j];
			}
			if(ope == '-'){
				kq -= A[j];
			}
			if(ope == '*'){
				kq *= A[j];
			}
			if(ope == '/'){
				kq /= A[j];
			}
		}
		if(kq == value){
			*check = 1;
		}
	} else {
		for (i = l; i <= r; i++) {
			swap(A, l, i);
			permute2(num, A, l+1, r, check, ope, value);
			swap(A, l, i);
		}
	}
}

int checkOldPosition(KenKen *kenken, Coord coord){
	int index = indexOf(coord);
	char ope = kenken->opera[index];
	int value = kenken->value[index];
	ListCoord listCoord = layRangBuocKhoi(kenken, coord);
	List giaTri;
	makeNullList(&giaTri);
	int i;
	int num = listCoord.size; 
	if(num == 1 && kenken->cells[coord.x][coord.y] != 0){
		return 1;
	}
	for(i=0; i<listCoord.size; i++){
		Coord position = listCoord.data[i];
		int value = kenken->cells[position.x][position.y];
		if(value == 0){
			return 1;
		}
		pushList(&giaTri, value);
	}
	int A[SIZE];
	for(i=0; i<giaTri.size; i++){
		A[i] = giaTri.element[i];
	}
	int check = 0;
	permute2(num ,A, 0, num-1, &check, ope, value);
	if(check == 1){
		return 1;
	}
	return 0;
}
int kenkenBackTracking(KenKen *kenken, Coord coord) {
	count++;
	int i, j;
	clearConstrain1(kenken);
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			if(kenken->cells[i][j] == 0){
				Coord pos = {i, j};
				taoRangBuocRC(kenken, pos);
			}
		}
	}
	if(checkOldPosition(kenken, coord) == 0){
		return 0;
	}
	if(isFilledKenKen(kenken)) {
		return 1;
	}
	Coord position = getNextMinDomainCell(kenken);
	int indexPosition = indexOf(position);
	List availables;
	makeNullList(&availables);
	if(kenken->opera[indexPosition] == 'N'){
		int value = kenken->value[indexPosition];
		pushList(&availables, value);
	} else {
		availables = getAvailableValues2(position, kenken);
	}
	if(availables.size == 0){
		return 0;
	}
	for(j=0; j<availables.size; j++){
		int value = availables.element[j];
		kenken->cells[position.x][position.y] = value;
		if(kenkenBackTracking(kenken, position)){
			return 1;
		}
		kenken->cells[position.x][position.y] = 0;
	}
	return 0;
}

int main(){
	KenKen kenken;
	initKenKen(&kenken);
	readData(&kenken);
	int A[SIZE*SIZE];
	int k, i, j;
	for(k=0; k<SIZE; k++){
		A[k] = k+1;
	}
	Coord coord = {0, 0};
	int kq = kenkenBackTracking(&kenken, coord);
	if(kq == 1){
		printf("KenKen solve:\n");
		printKenKen(&kenken);
		printf("state=%d", count);
	} else {
		printf("khong giai quyet duoc");
	}
	return 0;
}
