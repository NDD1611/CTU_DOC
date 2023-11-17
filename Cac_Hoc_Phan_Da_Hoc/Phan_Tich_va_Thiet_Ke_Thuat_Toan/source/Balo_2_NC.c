#include <stdio.h>

typedef struct {
	char ten[30];
	float tl, gt, dg;
	int sl, PA;
}Vat;

void read_data(Vat A[], int *n, float *w){
	FILE* f;
	int j=0;
	f=fopen("Balo_2.txt", "r");
	fscanf(f, "%f", w);
	if(f!=NULL){	
		while(!feof(f)){
			fscanf(f, "%f%f%d%[^\n]", &A[j].tl, &A[j].gt, &A[j].sl, &A[j].ten);
			A[j].dg=A[j].gt/A[j].tl;
			j++;
		}
	} else printf("Loi mo file");
	fclose(f);
	*n=j;
}

void Bubble_Sort(Vat A[], int n){
	int i, j;
	for(i=0; i<n; i++){
		for(j=n-1; j>i; j--){
			if(A[j].dg > A[j-1].dg){
				Vat temp = A[j];
				A[j]=A[j-1];
				A[j-1]=temp;
			}
		}
	}
}

void Nhanh_Can(int i, Vat A[], int n, float *v, float *CT, float *TGT, float *GTLNTT, int x[]){
	int sl = *v/A[i].tl;
	//if(sl > A[i].sl) sl = A[i].sl;
	int j;
	for(j=sl; j>=0; j--){
		*TGT = *TGT + j*A[i].gt;
		*v = *v - j*A[i].tl;
		*CT = *TGT + *v*A[i+1].dg;
		if(*CT > *GTLNTT){
			x[i]=j;
			if(i==n-1 || *v==0){
				if(*TGT > *GTLNTT){
					*GTLNTT=*TGT;
					int k;
					for(k=0; k<n; k++){
						A[k].PA=x[k];
					}
				}
			} else {
				Nhanh_Can(i+1, A, n, v, CT, TGT, GTLNTT, x);
			}
		}
		x[i]=0;
		*TGT = *TGT - j*A[i].gt;
		*v = *v + j*A[i].tl;
	}
}

int main(){
	Vat A[100];
	int n, x[n], i;
	float w, v;
	read_data(A, &n, &w);
	v=w;
	float CT=0, TGT=0, GTLNTT=0;
	Bubble_Sort(A, n);
	for(i=0; i<n; i++){
		x[i]=0;
	}
	Nhanh_Can(0, A, n, &v, &CT, &TGT, &GTLNTT, x);
		printf("\n\nTrong Luong   Gia Tri	 So Luong 	Ten 		Don Gia\n");
	for(i=0; i<n; i++){
		printf("%10.2f %10.2f %10d %-20s %10.2f\n", A[i].tl, A[i].gt, A[i].sl, A[i].ten, A[i].dg);
	}
	float tongGT=0;
	float tongTL=0;
	printf("Phuong an: ");
	for(i=0; i<n; i++){
		printf("%d ", A[i].PA);
		tongTL=tongTL+A[i].PA*A[i].tl;
		tongGT=tongGT+A[i].PA*A[i].gt;
	}
	printf("\nTrong luong vua ba lo: %.2f", w);
	printf("\nTong gia tri cua ba lo: %.2f\n", tongGT);
	printf("Tong trong luong cua ba lo: %.2f\n", tongTL);
	return 0;
}
