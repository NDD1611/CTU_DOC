#include <stdio.h>

#define sz 50

typedef struct{
	float tl, gt, dg;
	int sl, PA;
	char ten[100];
}Vat;

typedef struct{
	int tl, gt, sl, PA;
	char ten[100];
}VatInt;

void read(Vat A[], int *n, float *w){
	FILE* f=fopen("Balo_2.txt","r");
	if(f!=NULL){
		fscanf(f, "%f", w);
		int j=0;
		while(!feof(f)){
			fscanf(f, "%f%f%d%[^\n]", &A[j].tl, &A[j].gt, &A[j].sl, &A[j].ten);
			A[j].dg = A[j].gt/A[j].tl;
			A[j].PA=0;
			j++;
		}
		*n=j;
	} else printf("Loi mo file");
	fclose(f);
}

void readInt(VatInt A[], int *n, int *w){
	FILE* f=fopen("Balo_2.txt","r");
	if(f!=NULL){
		fscanf(f, "%d", w);
		int j=0;
		while(!feof(f)){
			fscanf(f, "%d%d%d%[^\n]", &A[j].tl, &A[j].gt, &A[j].sl, &A[j].ten);
			A[j].PA=0;
			j++;
		}
		*n=j;
	} else printf("Loi mo file");
	fclose(f);
}

void In(Vat A[], int n, float w){
	printf("trong luong cua balo: %.2f\n", w);
	int i;
	for(i=0; i<n; i++){
		printf("%-10.2f %-10.2f %-10.2f %-10d %-20s %-10d\n", A[i].tl, A[i].gt, A[i].dg, A[i].sl, A[i].ten, A[i].PA);
	}
}


void InInt(VatInt A[], int n, int w){
	printf("trong luong cua balo: %d\n", w);
	int i;
	for(i=0; i<n; i++){
		printf("%-10d %-10d %-10d %-20s %-10d\n", A[i].tl, A[i].gt, A[i].sl, A[i].ten, A[i].PA);
	}
}

void Bubble_Sort(Vat A[], int n){
	int i, j;
	for(i=0; i<n-1; i++){
		for(j=n-1; j>i; j--){
			if(A[j].dg > A[j-1].dg){
				Vat temp = A[j];
				A[j]=A[j-1];
				A[j-1]=temp;
			}
		}
	}
}

void Tham_An(Vat A[], int n, float w){
	int i;
	for(i=0; i<n; i++){
		A[i].PA=w/A[i].tl;
		if(A[i].PA > A[i].sl) A[i].PA=A[i].sl;
		w = w - A[i].PA*A[i].tl;
	}
}

void Nhanh_Can(int i, Vat A[], int n, float *w, float *TGT, float *CT, float *GTLNTT, int x[]){
	int sl = *w/A[i].tl;
	if(sl > A[i].sl) sl = A[i].sl;
	int j;
	for(j=sl; j>=0; j--){
		*TGT = *TGT + j*A[i].gt;
		*w = *w - j*A[i].tl;
		*CT = *TGT + *w*A[i+1].dg;
		if(*CT > *GTLNTT){
			x[i]=j;
			if(i == n-1){
				if(*TGT > *GTLNTT){
					*GTLNTT=*TGT;
					int k;
					for(k=0; k<n; k++){
						A[k].PA=x[k];
					}
				}
			} else {
				Nhanh_Can(i+1, A, n, w, TGT, CT, GTLNTT, x);
			}
		}
		x[i]=0;
		*TGT = *TGT - j*A[i].gt;
		*w = *w + j*A[i].tl;
	}
}

void Tao_Bang(VatInt A[], int n, int w, int X[][sz], int F[][sz]){
	int v;
	for(v=0; v<=w; v++){
		X[0][v]=v/A[0].tl;
		F[0][v]=X[0][v]*A[0].gt;
	}
	
	int k, xk, yk, Fmax, Xmax;
	for(k=1; k<n; k++){
		for(v=0; v<=w; v++){
			yk=v/A[k].tl;
			Fmax=F[k-1][v];
			Xmax=0;
			for(xk=0; xk<=yk; xk++){
				int Ftam=F[k-1][v-xk*A[k].tl]+xk*A[k].gt;
				if(Ftam > Fmax){
					Fmax=Ftam;
					Xmax=xk;
				}
			}
			if(Xmax > A[k].sl) Xmax = A[k].sl;
			X[k][v]=Xmax;
			F[k][v]=X[k][v]*A[k].gt;
		}
	}
}

void Tra_Bang(VatInt A[], int n, int w, int X[][sz], int F[][sz]){
	int i;
	for(i=n-1; i>=0; i--){
		A[i].PA=X[i][w];
		w=w-A[i].PA*A[i].tl;
	}
}


int main(){
	Vat A[sz];
	int n;
	float w;
	read(A, &n, &w);
	Bubble_Sort(A, n);
	//Tham_An(A, n, w);
	float v=w, TGT=0, CT=0, GTLNTT=0;
	int x[sz];
	Nhanh_Can(0, A, n, &v, &TGT, &CT, &GTLNTT, x);
	In(A, n, w);
	
//	VatInt A[sz];
//	int n, w;
//	readInt(A, &n, &w);
//	
//	int X[sz][sz], F[sz][sz];
//	Tao_Bang(A, n, w, X, F);
//	int i, j;
//	for(i=0; i<n; i++){
//		for(j=0; j<=w; j++){
//			printf("%d %d | ", X[i][j], F[i][j]);
//		}
//		printf("\n");
//	}
//	Tra_Bang(A, n, w, X, F);
//	
//	
//	InInt(A, n, w);
	return 0;
}
