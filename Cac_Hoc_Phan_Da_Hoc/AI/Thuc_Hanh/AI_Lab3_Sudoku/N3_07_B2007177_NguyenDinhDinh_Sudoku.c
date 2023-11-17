#include <stdio.h>
#include <stdlib.h>


#define maxLength 100
#define ROWS 9
#define COLUMNS 9
#define EMPTY 0
#define AREA_SQUARE 3
#define INF 999999
#define max_value 10

int Counter = 0;
typedef struct {
	int x;
	int y;
}Coord;

typedef struct {
	Coord data[maxLength];
	int size;	
}ListCoord;

typedef struct{
	int data[ROWS*COLUMNS][ROWS*COLUMNS];
	int n;
}Constrains;

typedef struct {
	int cells[ROWS][COLUMNS];
	Constrains constrains;
}Sudoku;

typedef struct {
	int element[maxLength];
	int size;
}List;

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

void pushList(List *L, int x){
	if(!fullList(*L)){
		L->element[L->size] = x;
		L->size++;
	} else {
		printf("List is full\n");
	}
}

void deleteList(int position, List *L){
	if(emptyList(*L)){
		printf("List is empty\n");
	} else if(position < 1 || position > L->size){
		printf("position iss not possible to delete\n");
	} else {
		int i;
		for(i = position-1; i < L->size; i++){
			L->element[i] = L->element[i+1];
		} 
		L->size--;
	}
}

void initSudoku(Sudoku *sudoku){
	int i, j;
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLUMNS; j++){
			sudoku->cells[i][j] = 0;
		}
	}
	initConstrains(&sudoku->constrains);
}

void initListCoord(ListCoord *L){
	L->size = 0;
}

void appendList(ListCoord *L, Coord coord){
	L->data[L->size] = coord;
	L->size++;
}

void initConstrains(Constrains *Con){
	int i,j;
	for(i=0; i<81; i++){
		for(j=0; j<81; j++){
			Con->data[i][j] = 0;
		}
	}
	Con->n = ROWS*COLUMNS;
}

int indexOf(Coord coord){ // chuyen doi chi so toa do thanh chi so dinh 
	return (ROWS*coord.x + coord.y);
}

Coord positionOfVertex(int vertex){
	Coord coord;
	coord.x = vertex / ROWS;
	coord.y = vertex % COLUMNS;
	return coord;
}

int addConstrain(Constrains *con, Coord source, Coord target){
	int u = indexOf(source);
	int v = indexOf(target);
	if(con->data[u][v] == 0){
		con->data[u][v] = 1;
		con->data[v][u] = 1;
		return 1;
	}
	return 0;
}

ListCoord getConstrains (Constrains con, Coord coord){
	int i;
	int v = indexOf(coord);
	ListCoord result;
	initListCoord(&result);
	for(i=0; i<con.n; i++){
		if(con.data[v][i] == 1){
			appendList(&result, positionOfVertex(i));
		}
	}
	return result;
}

void initSudokuValues(Sudoku *sudoku, int inputs[ROWS][COLUMNS]){
	int i, j;
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLUMNS; j++){
			sudoku->cells[i][j] = inputs[i][j];
		}
	}
	initConstrains(&sudoku->constrains);
}

void printSudoku(Sudoku sudoku){
	int i, j;
	printf("Sudoku:\n");
	for(i=0; i<ROWS; i++){
		if(i % AREA_SQUARE == 0) printf("-------------------------\n");
		for(j=0; j<COLUMNS; j++){
			if(j % AREA_SQUARE == 0) printf("| ");
			printf("%d ", sudoku.cells[i][j]);
		}
		printf("|\n");
	}
	printf("-------------------------\n");
}

int isFilledSudoku(Sudoku sudoku){
	int i, j;
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLUMNS; j++){
			if(sudoku.cells[i][j] == 0) return 0;
		}
	}
	return 1;
}

void spreadConstrainsFrom(Coord position, Constrains *con, ListCoord *changeds){
	int row = position.x;
	int column = position.y;
	int i, j;
	//tao rang buoc theo cot
	for(i=0; i<ROWS; i++){
		if(i != row){
			Coord pos = {i, column};
			if(addConstrain(con, position, pos)){
				appendList(changeds, pos);
			}
		}
	}
	
	//tao rang buoc theo hang
	for(i=0; i<COLUMNS; i++){
		if(i != column){
			Coord pos = {row, i};
			if(addConstrain(con, position, pos)){
				appendList(changeds, pos);
			}
		}
	}
	// tao rang buoc theo khoi
	for(i=0; i<AREA_SQUARE; i++){
		for(j=0; j<AREA_SQUARE; j++){
			int areaX = (row/AREA_SQUARE)*AREA_SQUARE;
			int areaY = (column/AREA_SQUARE)*AREA_SQUARE;
			if(areaX+i != row || areaY+j != column){
				Coord pos = {areaX+i, areaY+j};
				if(addConstrain(con, position, pos)){
					appendList(changeds, pos);
				}
			}
		}
	}
}

List getAvailableValues(Coord position, Sudoku sudoku){
	ListCoord posList = getConstrains(sudoku.constrains, position);

	int i;

	int availables[max_value];
	for(i = 1; i<max_value; i++){
		availables[i]=1;
	}
	for(i = 0; i<posList.size; i++){
		Coord pos = posList.data[i];
		if(sudoku.cells[pos.x][pos.y] != EMPTY){
			availables[sudoku.cells[pos.x][pos.y]]= 0;
		}
	}
	List result;
	makeNullList(&result);
	for(i=1; i<max_value; i++){
		if(availables[i]) pushList(&result, i);
	}
	return result;
}

Coord getNextEmptyCell(Sudoku sudoku){
	int i, j;
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLUMNS; j++){
			Coord pos = {i, j};
			if(sudoku.cells[i][j] == EMPTY) return pos;
		}
	}
}

Coord getNextMinDomainCell(Sudoku sudoku){
	int minLength = INF;
	int i, j, a;
	Coord result;
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLUMNS; j++){
			if(sudoku.cells[i][j] == EMPTY){
				Coord pos = {i, j};
				List mienGia = getAvailableValues(pos, sudoku);
				int availablesLength = mienGia.size;
				if(availablesLength < minLength){
					minLength = availablesLength;
					result = pos;
				}
			}
		}
	}
	return result;
}

void clearConstrains(Constrains *con){
	int i, j;
	for(i=0; i<81; i++){
		for(j=0; j<81; j++){
			con->data[i][j] = 0;
		}
	}
}

int sudokuBackTracking(Sudoku *sudoku) {
	int i, j;
	
	clearConstrains(&sudoku->constrains);
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLUMNS; j++){
			if(sudoku->cells[i][j] != EMPTY){
				ListCoord history;
				initListCoord(&history);
				Coord pos = {i, j};
				spreadConstrainsFrom(pos, &sudoku->constrains, &history);
			}
		}
	}
	if(isFilledSudoku(*sudoku)) {
		return 1;
	}
	Coord position = getNextMinDomainCell(*sudoku);
	List availables = getAvailableValues(position, *sudoku);
	if(availables.size == 0){
		return 0;
	}
	for(j=0; j<availables.size; j++){
		int value = availables.element[j];
		sudoku->cells[position.x][position.y] = value;
		Counter++;
		if(sudokuBackTracking(sudoku)){
			return 1;
		}
		sudoku->cells[position.x][position.y] = EMPTY;
	}
	return 0;
}


Sudoku resolveSudoku(Sudoku sudoku){
	int i, j;
	clearConstrains(&sudoku.constrains);
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLUMNS; j++){
			if(sudoku.cells[i][j] != EMPTY){
				ListCoord history;
				initListCoord(&history);
				Coord pos = {i, j};
				spreadConstrainsFrom(pos, &sudoku.constrains, &history);
			}
		}
	}
	
	Counter = 0;
	if(sudokuBackTracking(&sudoku)){
		printf("Solved\n");
	} else{
		printf("Can not Solve\n");
	}
	printf("Explored State %d states\n", Counter);
	return sudoku;
}

int inputs1[9][9] = {
{9,7,0,0,1,3,2,0,0},
{0,0,0,0,0,0,6,0,7},
{0,8,0,0,0,0,0,0,0},
{0,0,0,0,0,0,9,8,0},
{0,9,0,5,0,0,0,7,0},
{0,0,0,0,0,2,0,0,0},
{0,0,0,0,3,5,0,1,0},
{0,3,4,9,0,0,0,0,0},
{0,0,6,0,0,0,8,0,0}};

int main(){
	Sudoku sudoku;
	initSudoku(&sudoku);
	initSudokuValues(&sudoku, inputs1);
	printSudoku(sudoku);
	Sudoku result = resolveSudoku(sudoku);
	printSudoku(result);
	return 0;
}
