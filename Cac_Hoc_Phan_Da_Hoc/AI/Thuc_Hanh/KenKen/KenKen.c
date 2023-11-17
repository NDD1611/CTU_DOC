#include <stdio.h>

#define SIZE 9
#define maxLength 100
#define ROWS SIZE
#define COLUMNS SIZE
#define max_value SIZE+1


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
	FILE* f = fopen("data6_9x9.txt", "r");
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
int isFilledKenKen(KenKen kenken){
	int i, j;
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			if(kenken.cells[i][j] == 0) return 0;
		}
	}
	return 1;
}

ListCoord getConstrains (KenKen kenken, Coord coord){
	int i;
	int v = indexOf(coord);
	ListCoord result;
	initListCoord(&result);
	for(i=0; i<SIZE*SIZE; i++){
		if(kenken.constrain1[v][i] == 1){
			appendList(&result, positionOfVertex(i));
		}
	}
	return result;
}

List getAvailableValues(Coord position, KenKen kenken){
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
		if(kenken.cells[pos.x][pos.y] != 0){
			availables[kenken.cells[pos.x][pos.y]]= 0;
		}
	}
	for(i=1; i<max_value; i++){
		if(availables[i]) pushList(&result, i);
	}
	return result;
}

ListCoord layRangBuocKhoi(KenKen kenken, Coord position){ // tra ve cac coord co trong long cua position bao gom ca position
	
	int indexPosition = indexOf(position);
	int i;
	ListCoord result;
	initListCoord(&result);
	appendList(&result, position);
	for(i=0; i<SIZE*SIZE; i++){
		if(kenken.constrain2[indexPosition][i] != 0){
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
//			printf("%d ", A[j]);
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
//			printf("\n");
//		printf("X%d Y%d ope%c value%d KQ%d\n", coord.x, coord.y, ope, value, kq);
		if(kq == value){
			for(i=0; i<num; i++){
//				printf("%d ", A[i]);
				if(checkElement(A[i], constrain1) == 1  && checkElement(A[i], *result) == 0){
					pushList(result, A[i]);
				}
			}
//			printf("\n");
		}
	} else {
		for (i = l; i <= r; i++) {
			swap(A, l, i);
			permute(num, A, l+1, r, result, coord, ope, value, constrain1);
			swap(A, l, i);
		}
	}
}
List getAvailableValues2(Coord coord, KenKen kenken){			// get cac gia tri co the co cua cua o trong dua vao constrain 2
	int index = indexOf(coord);
	int ope = kenken.opera[index];
	int value = kenken.value[index];
//	printf("%c %d %d\n", ope, value, index);
	List result;
	makeNullList(&result);
	ListCoord listCoord = layRangBuocKhoi(kenken, coord);
	int num = listCoord.size;	// so phan tu co trong long tai vi tri coord
//	printf("num %d ", num);
//	int A[SIZE*SIZE];
	int i;
//	for(i=0; i<SIZE; i++){
//		A[i] = i+1;
//	}
	List constrain1 = getAvailableValues(coord, kenken);
//	for(i=0; i<constrain1.size; i++){
//		printf("%d ", constrain1.element[i]);
//	}
//	char c;
//	scanf("%c", &c);

//	permute(num, A, 0, SIZE-1, &result, coord, ope, value, constrain1);

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
//								A[5]=i6;
//								A[6]=i7;
								int kq = A[0];
								int j;
								for(j=0; j<num; j++){
						//			printf("%d ", A[j]);
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
						//				printf("%d ", A[i]);
										if(checkElement(A[i], constrain1) == 1  && checkElement(A[i], result) == 0){
											pushList(&result, A[i]);
										}
									}
						//			printf("\n");
								}
//						for(i6=1; i6<=SIZE; i6++){
//							for(i7=1; i7<=SIZE; i7++){
//							}
//						}
					}
				}
			}
		}
	}
	return result;
}

Coord getNextMinDomainCell(KenKen kenken){
	int minLength = 99999999;
	int i, j, a;
	Coord result;
	
	for(i=0; i<SIZE*SIZE; i++){
		Coord coord = positionOfVertex(i);
//			printf("%d %d\n", coord.x, coord.y);
		if(kenken.opera[i] == 'N' && kenken.cells[coord.x][coord.y] == 0){
			return coord;
		}
	}
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			if(kenken.cells[i][j] == 0){
				Coord pos = {i, j};
				List constrain2 = getAvailableValues2(pos, kenken);
				
				printf("Mien gia tri cua %d %d: ", i,j);
				int a;
				for(a=0; a<constrain2.size; a++){
					printf("%d ", constrain2.element[a]);
				}printf("\n");
				
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


int checkConstrain2(KenKen kenken, Coord position, int value){
	ListCoord list = layRangBuocKhoi(kenken, position);
	if(list.size == 0){
		return 1;
	}
	int i;
	for(i=0; i<list.size; i++){
		Coord coord = list.data[i];
		if(kenken.cells[coord.x][coord.y] == 0){
			return 1;
		}
	}
	int index = indexOf(position);
	if(kenken.opera[index]=='+'){
		int tong= value; // kenken.cells[position.x][position.y];
		for(i=0; i<list.size; i++){
			Coord coord = list.data[i];
			tong = tong + kenken.cells[coord.x][coord.y];
		}
		if(tong == kenken.value[index]){
			return 1;
		} else {
			return 0;
		}
	}
	if(kenken.opera[index] == '*'){
		int nhan = value;//kenken.cells[position.x][position.y];
		for(i=0; i<list.size; i++){
			Coord coord = list.data[i];
			nhan = nhan * kenken.cells[coord.x][coord.y];
		}
		printf("value %d nhan %d\n",value, nhan);
		if(nhan == kenken.value[index]){
			printf("return 1\n");
			return 1;
		} else {
			printf("return 0\n");
			return 0;
		}
	}
	if(kenken.opera[index]=='-'){
		
	}
	if(kenken.opera[index]=='/'){
		
	}
	
}

void printKenKen(KenKen kenken){
	int i, j;
	printf("kenken:\n");
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLUMNS; j++){
			printf("%d ", kenken.cells[i][j]);
		}
		printf("\n");
	}
}

void clearConstrain1(KenKen *kenken){
	int i, j;
	for(i=0; i<SIZE*SIZE; i++){		// clear constrains1
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
//		printf("X%d Y%d ope%c value%d KQ%d\n", coord.x, coord.y, ope, value, kq);
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

int checkOldPosition(KenKen kenken, Coord coord){
	int index = indexOf(coord);
	char ope = kenken.opera[index];
	int value = kenken.value[index];
	ListCoord listCoord = layRangBuocKhoi(kenken, coord);
	List giaTri;
	makeNullList(&giaTri);
	int i;
	int num = listCoord.size; 
	if(num == 1 && kenken.cells[coord.x][coord.y] != 0){
		return 1;
	}
	for(i=0; i<listCoord.size; i++){
		Coord position = listCoord.data[i];
		int value = kenken.cells[position.x][position.y];
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
	printKenKen(*kenken);
	int i, j;
	clearConstrain1(kenken);
	for(i=0; i<SIZE; i++){		// tao rang buoc cho cac o co gia tri bang 0
		for(j=0; j<SIZE; j++){
			if(kenken->cells[i][j] == 0){
				Coord pos = {i, j};
				taoRangBuocRC(kenken, pos);
			}
		}
	}
	if(checkOldPosition(*kenken, coord) == 0){
		printf("checkOldPosition return 0");
		return 0;
	}
	if(isFilledKenKen(*kenken)) {
		printf("cac o da co gia tri\n");
		return 1;
	}
	Coord position = getNextMinDomainCell(*kenken);
	
//	printf("\nCount %d\n", count);
	printf("chon vi tri ke tiep: %d %d\n", position.x, position.y);
	
	int indexPosition = indexOf(position);
	List availables;
	makeNullList(&availables);
	if(kenken->opera[indexPosition] == 'N'){
		int value = kenken->value[indexPosition];
		pushList(&availables, value);
	} else {
		availables = getAvailableValues2(position, *kenken);
		
//		printf("\nMiengia tri\n");
//		int a;
//		for(a=0; a<availables.size; a++){
//			printf("%d ", availables.element[a]);
//		}

	}
	if(availables.size == 0){
		printf("khong co mien gia tri\n");
		return 0;
	}
	
	printf("\nmien gia tri cua o %d %d: ", position.x, position.y);
	
	for(j=0; j<availables.size; j++){
		int value = availables.element[j];
		printf("%d ", value);
	}
	printf("\n");
	for(j=0; j<availables.size; j++){
		int value = availables.element[j];
		kenken->cells[position.x][position.y] = value;
		
		printf("dien %d vao %d %d\n", value, position.x, position.y);
		
		if(kenkenBackTracking(kenken, position)){
			return 1;
		}
		printf("tra ve 0 tai %d %d\n", position.x, position.y);
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
//	kenken.cells[0][7] = 9;
//	kenken.cells[0][8] = 5;
//	kenken.cells[1][7] = 1;
//	kenken.cells[0][8] = 3;
//	kenken.cells[2][0] = 8;
//	kenken.cells[5][0] = 1;
//	kenken.cells[6][0] = 9;
//	kenken.cells[8][0] = 4;
//	kenken.cells[6][5] = 1;
//	kenken.cells[6][6] = 2;
//	kenken.cells[6][8] = 6;
//	kenken.cells[7][8] = 8;
//	kenken.cells[8][4] = 2;
//	kenken.cells[8][5] = 5;
//	kenken.cells[8][6] = 6;
//	kenken.cells[8][8] = 9;

	int kq = kenkenBackTracking(&kenken, coord);
	
	List constrain1 = getAvailableValues(coord, kenken);
	printf("khong co mien gia tri\n");
	printKenKen(kenken);
	return 0;
}