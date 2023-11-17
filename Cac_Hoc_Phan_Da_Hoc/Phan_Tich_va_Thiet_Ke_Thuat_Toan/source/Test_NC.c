#include <stdio.h>
#define sz 50

typedef struct{
	int d, c, mark;
	float dd;
}canh;

void read(canh A[][sz], int *n){
	FILE* f=fopen("TSP_1.txt","r");
	if(f!=NULL){
		fscanf(f, "%d", n);
		int i, j;
		for(i=1; i<=*n; i++){
			for(j=1; j<=*n; j++){
				fscanf(f, "%f", &A[i][j].dd);
				A[i][j].d=i;
				A[i][j].c=j;
				A[i][j].mark=0;
			}
		}
	} else printf("Loi mo file");
	fclose(f);
}

void In(canh A[][sz], int n){
	int i, j;
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			printf("%c%c=%5.2f ", i+96, j+96, A[i][j].dd);
		}
		printf("\n");
	}
}

int CO_CT(canh x[], int sl, int j){
	int i, kt=0;
	for(i=0; i<sl; i++){
		if(x[i].d == j){
			kt=1;
			return kt;
		}
	}
	return kt;
}

float Canh_NN(canh A[][sz], int n){
	float min=99999;
	int i, j;
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			if(A[i][j].dd < min && i != j && A[i][j].mark == 0){
				min=A[i][j].dd;
			}
		}
	}
	return min;
}

void Nhanh_Can(canh A[][sz], int n, int sl, int xp, float *TGT, float *CD, float *GTNNTT, canh x[], canh PA[]){
	int j;
	for(j=1; j<=n; j++){
		if(j != xp && A[xp][j].mark==0 && !CO_CT(x, sl, j)){
			*TGT = *TGT + A[xp][j].dd;
			*CD = *TGT + (n-(sl+1)*Canh_NN(A, n));
			if(*CD < *GTNNTT){
				x[sl]=A[xp][j];
				A[xp][j].mark=1;
				A[j][xp].mark=1;
				if(sl==n-2){
					x[n-1]=A[x[n-2].c][x[0].d];
					*TGT=*TGT + x[n-1].dd;
					if(*TGT < *GTNNTT){
						*GTNNTT = *TGT;
						int k;
						for(k=0; k<n; k++){
							PA[k]=x[k];
						}
					}
					*TGT=*TGT - x[n-1].dd;
				} else {
					Nhanh_Can(A, n, sl+1, j, TGT, CD, GTNNTT, x, PA);
				}
				
			}
			*TGT = *TGT - A[xp][j].dd;
			A[xp][j].mark=0;
			A[j][xp].mark=0;
		}
	}
}

int main(){
	canh A[sz][sz];
	int n;
	read(A, &n);
	In(A, n);	
	
	char tpxp;
	while(1){
		fflush(stdin);
		printf("Nhap thanh pho xuat phat:");
		scanf("%c", &tpxp);
		float TGT=0, CD=0, GTNNTT=99999;
		canh x[sz], PA[sz];
		Nhanh_Can(A, n, 0, tpxp-96, &TGT, &CD, &GTNNTT, x, PA);
		int i;
		float tong=0;
		for(i=0; i<n; i++){
			tong += PA[i].dd;
			printf("%c-%c=%.2f\n", PA[i].d+96, PA[i].c+96, PA[i].dd);
		}
		for(i=0; i<n; i++){
			printf("%c -> ", PA[i].d+96);
		}
		printf("%c", PA[0].d+96);
		fflush(stdin);
		printf("\nTong GT: %.2f", tong);
		printf("\nnhap q de tiep tuc va phim bat ki de thoat:");
		char kt;
		scanf("%c", &kt);
		if(kt == 'q') break;
		int j;
		for(i=1; i<=n; i++){
			for(j=1; j<=n; j++){
				A[i][j].mark=0;
			}
		}
	}
	return 0;
}
