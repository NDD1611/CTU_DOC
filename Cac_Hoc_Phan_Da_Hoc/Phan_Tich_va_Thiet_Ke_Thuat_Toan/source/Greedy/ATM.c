
//Nguyen Dinh Dinh B2007177

#include <stdio.h>
#include <string.h>

typedef struct {
	char ten[100];
	int mg, st;
}Tien;

int readData(Tien A[], int *n){
	FILE* f;
	f=fopen("ATM.txt", "r");
	int i=0;
	if(f!=NULL){
		while(!feof(f)){
			fscanf(f, "%d", &A[i].mg);
			fgets(A[i].ten, 100, f);
			A[i].st=0;
			A[i].ten[strlen(A[i].ten)-1]=A[i].ten[strlen(A[i].ten)];
			i++;
		}
	} else printf("loi mo file");
	fclose(f);
	*n=i;
}

void swap(Tien *x, Tien *y){
	Tien temp;
	temp=*x;
	*x=*y; 
	*y=temp;
}

void Bubble (Tien A[], int n){
	int i, j;
	for(i=0; i<n; i++){
		for(j=n-1; j>i; j--){
			if(A[j].mg > A[j-1].mg){
				swap(&A[j], &A[j-1]);
			}
		}
	}
}

void Greedy(Tien A[], int n, int stien){
	int tien, i=0;
	tien=stien;
	while(i<n){
		int sdu, st; // sdu so du, st so to
		st=(int)(tien/A[i].mg);
		A[i].st=st;
		sdu=tien%A[i].mg;
		tien=sdu;
		i++;
	}
	int j, stra=0, stt=1;
		printf("STT |   Menh Gia   |      Ten Tien     |   So to\n");
	for(j=0; j<n; j++){
		if(A[j].st!=0){
			printf("%-4d|    %-10d|%s|   %3d\n", stt, A[j].mg, A[j].ten ,A[j].st);
			stt++;
		}
		stra=stra+(A[j].mg*A[j].st);
	}
	printf("So tien can rut: %d\n", stien);
	printf("So tien da tra: %d\n", stra);
	printf("So tien con thieu: %d", stien-stra);
}

int main(){
	
	Tien A[100];
	int n;
	readData(A, &n);
	int i;
	Bubble(A, n);
	int stien;
	printf("Vui long nhap so tien can rut: ");
	scanf("%d", &stien);
	Greedy(A, n, stien);
	
	return 0;
}
