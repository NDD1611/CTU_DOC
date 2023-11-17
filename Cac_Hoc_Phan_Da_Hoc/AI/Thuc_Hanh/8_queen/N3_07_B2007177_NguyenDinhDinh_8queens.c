#include <stdio.h>


#define size 8
#define maxLength 100

typedef struct{
	int banco[size][size];
	int constrain[size][size];
	int soquan;
}HAU;

typedef struct {
	int x;
	int y;
}Coord;

typedef struct {
	Coord data[maxLength];
	int count;	
}ListCoord;

void initListCoord(ListCoord *L){
	L->count = 0;
}

void appendList(ListCoord *L, Coord coord){
	L->data[L->count] = coord;
	L->count++;
}

void clearBanCo(int banco[size][size]){
	int i, j;
	for (i=0; i<size; i++){
		for(j=0; j<size; j++){
			banco[i][j]=0;
		}
	}
}

void clearConstrain(int constrain[size][size]){
	int i, j;
	for (i=0; i<size; i++){
		for(j=0; j<size; j++){
			constrain[i][j]=0;
		}
	}
}

void taoRangBuoc(HAU *hau){
	int i, j;
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			if(hau->banco[i][j] != 0){
				int num = hau->banco[i][j]; 
				hau->constrain[i][j] = num;
				int c, h;
				
				// cot
				for(c=0; c<size; c++){
					hau->constrain[c][j] = num;
				}
				//hang
				for(c=0; c<size; c++){
					hau->constrain[i][c] = num;
				}
				//cheo1
				c=j;
				h=i;
				while(1){
					hau->constrain[h][c] = num;
					h--;
					c++;
					if(h<0 || c ==size) break;
				}
				//cheo2
				c=j;
				h=i;
				while(1){
					hau->constrain[h][c] = num;
					h--;
					c--;
					if(h<0 || c<0) break;
				}
				//cheo3
				c=j;
				h=i;
				while(1){
					hau->constrain[h][c] = num;
					h++;
					c--;
					if(h == size || c<0) break;
				}
				//cheo 4
				c=j;
				h=i;
				while(1){
					hau->constrain[h][c] = num;
					h++;
					c++;
					if(h ==size || c == size) break;
				}
			}
		}
	}
}

void printArray(int a[size][size]){
	int i, j;
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			if(a[i][j] != 0){
				printf("%c ", 254);
			} else{
				printf("%d ",a[i][j]);
			}
		}
		printf("\n");
	}
}

int backTracking(HAU *hau){
	clearConstrain(hau->constrain);
	taoRangBuoc(hau);
//	printf("rang buoc\n");
//	printArray(hau->constrain);
	int i, j;
	if(hau->soquan == 9){
		return 1;
	}
	int check=0;
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			if(hau->constrain[i][j] == 0){
				check = 1;
			}
		}
	}
	if(check == 0){
		return 0;
	}
	
	ListCoord list;
	initListCoord(&list);
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			if(hau->constrain[i][j] == 0){
				Coord coord = {i, j};
				appendList(&list, coord);
			}
		}
	}
	
	for(i=0; i<list.count; i++){
		hau->banco[list.data[i].x][list.data[i].y] = hau->soquan;
//		printf("dien %d tai vi tri %d - %d\n",hau->soquan, list.data[i].x, list.data[i].y);
		hau->soquan++;
		if(backTracking(hau)){
			return 1;
		}
		hau->banco[list.data[i].x][list.data[i].y] = 0;
		hau->soquan--;
	}
	return 0;
}

int main(){
	HAU hau;
	clearBanCo(hau.banco);
	clearConstrain(hau.constrain);
	hau.soquan = 1;
	taoRangBuoc(&hau);
	int re = backTracking(&hau);
	if(re == 1){
		printf("Resolve\n", re);
	}
	printArray(hau.banco);
//	int i; 
//	for(i=1; i<255; i++){
//		printf("%c %d\n", i, i);
//	}
	return 0;
}
