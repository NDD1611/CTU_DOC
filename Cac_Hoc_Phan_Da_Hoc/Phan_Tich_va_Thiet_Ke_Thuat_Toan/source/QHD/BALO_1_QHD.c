#include <stdio.h>

typedef struct{
	char ten[50];
	int tl, gt, PA;
}Vat;

void read_data(Vat A[], int *n, int *w){
	FILE* f=fopen("data_Balo_1_QHD.txt", "r");
	if(f!=NULL){
		fscanf(f, "%d", w);
		int i=0;
		while(!feof(f)){
			fscanf(f, "%d%d%[^\n]", &A[i].tl, &A[i].gt, &A[i].ten);
			i++;
		}
		*n=i;
	} else printf("loi mo file");
	close(f);
}

void Tao_Bang(Vat A[], int n, int w, int X[][50], int F[][50]){
	// dien dong dau tien cho bang
	int k, v, xk, yk, Fmax, Xmax;
	for(v=0; v<=w; v++){
		X[0][v]= v/A[0].tl;
		F[0][v]=X[0][v]*A[0].gt;
	}
	
	// dien cac dong con lai
	for(k=1; k<n; k++){
		for(v=0; v<=w; v++){
			yk=v/A[k].tl;
			Fmax=F[k-1][v];
			Xmax=0;
			for(xk=0; xk<=yk; xk++){
				int Ftam = F[k-1][v-xk*A[k].tl] + xk*A[k].gt;
				if(Ftam > Fmax){
					Fmax = Ftam;
					Xmax = xk;
				}
			}
			F[k][v]=Fmax;
			X[k][v]=Xmax;
		}
	}
}

void In_Bang(int n, int w, int F[][50], int X[][50]){
	int k, v;
	for(k=0; k<n; k++){
		for(v=0; v<=w; v++){
			printf("%2d %2d| ", F[k][v], X[k][v]);
		}
		printf("\n");
	}
}

void Tra_Bang(Vat A[], int n, int w, int F[][50], int X[][50]){
	int v=w;
	int k;
	for(k=n-1; k>=0; k--){
		A[k].PA=X[k][v];
		v=v-A[k].PA*A[k].tl;
	}
}

int main(){
	Vat A[100];
	int n;
	int w;
	int F[50][50], X[50][50];
	read_data(A, &n, &w);
	int i;
	Tao_Bang(A, n, w, X, F);
	In_Bang(n, w, F, X);
	Tra_Bang(A, n, w, F, X);
		printf("\n\nTrong Luong   Gia Tri 	Ten 		Phuong an\n");
	for(i=0; i<n; i++){
		printf("%10d %10d %-20s %5d\n", A[i].tl, A[i].gt, A[i].ten, A[i].PA);
	}
	int tongTL=0, tongGT=0;
	for(i=0; i<n; i++){
		tongTL += A[i].PA*A[i].tl;
		tongGT += A[i].PA*A[i].gt;
	}
	printf("\nTong trong luong cua ba lo la: %d", tongTL);
	printf("\nTong gia tri cua ba lo la: %d", tongGT);
	return 0;
}
