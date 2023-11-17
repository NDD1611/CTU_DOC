
//Nguyen Dinh Dinh B2007177

#include <stdio.h>

typedef struct{
	float tl, gt, dg;
	char ten[50];
	int PA;
}dovat;

void read(dovat A[], int *n, float *W){
	FILE* f;
	f=fopen("data_Ba_Lo_3.txt", "r");
	int j=0;
	fscanf(f, "%f", W);
	if(f!=NULL){
		while(!feof(f)){
			fscanf(f, "%f%f%[^\n]", &A[j].tl, &A[j].gt, &A[j].ten);
			A[j].dg=A[j].gt/A[j].tl;
			A[j].PA=0;
			j++;
		}
	} else printf("Loi mo file");
	fclose(f);
	*n=j;
}

void in(dovat A[], float W, int n){
	int i;
	printf("\nTrong luong cua ba lo la: %.2f\n", W);
	printf("|---|--------|-------|-------|---------------------------------|\n");
	printf("|STT|   TL   |  GT   |   DG  |               Ten               |\n");
	printf("|---|--------|-------|-------|---------------------------------|\n");
	for(i=0; i<n; i++){
		printf("|%2d |  %5.2f | %5.2f | %5.2f | %23s         |\n", i+1, A[i].tl, A[i].gt, A[i].dg ,A[i].ten);
	}
	printf("|---|--------|-------|-------|---------------------------------|\n");
}

void swap(dovat *x, dovat *y){
	dovat temp = *x;
	*x=*y;
	*y=temp;
}

void Bubble_Sort(dovat A[], int n){
	int i, j;
	for(i=0; i<n; i++){
		for(j=n-1; j>i; j--){
			if(A[j].dg > A[j-1].dg){
				swap(&A[j], &A[j-1]);
			}
		}
	}
}

void Greedy(dovat A[], int n, float WW){
	int i;
	float tongW=0, tongGT=0;
	float W = WW;
	for(i=0; i<n; i++){
		A[i].PA=(int)W/A[i].tl;
		if(A[i].PA > 1){
			A[i].PA=1;
		}
		tongGT = tongGT+A[i].PA*A[i].gt;
		tongW=tongW+(A[i].PA*A[i].tl);
		W=W-(A[i].PA*A[i].tl);
	}	
	printf("\nPhuong an la: ");
	for(i=0; i<n; i++){
		printf("%d ", A[i].PA);
	}
	printf("\nTong gia tri cua ba lo la: %.2f", tongGT);
	printf("\nTong trong luong cua ba lo la: %.2f", tongW);
	printf("\nTrong luong con lai cua ba lo la: %.2f", WW-tongW);
	
}

int main(){
	dovat A[100];
	int n;
	float W;
	read(A, &n, &W);
	Bubble_Sort(A, n);
	in(A, W, n);
	Greedy(A, n, W);
	return 0;
}
