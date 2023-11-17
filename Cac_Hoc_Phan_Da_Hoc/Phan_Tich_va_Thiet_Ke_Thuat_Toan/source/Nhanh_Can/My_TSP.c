#include <stdio.h>
#define size 100

typedef struct{
	int d, c, mark;
	float dd;
}canh;

void read_data(canh A[][size], int *n){
	FILE* f = fopen("TSP_1.txt", "r");
	if(f != NULL){
		fscanf(f, "%d", n);
		int i, j;
		for(i=1; i<=*n; i++){
			for(j=1; j<=*n; j++){
				fscanf(f, "%f",&A[i][j].dd);
				A[i][j].d=i;
				A[i][j].c=j;
				A[i][j].mark=0;
			}
		}
		
	} else printf("Loi mo file");
	close(f);
	
}

int Co_CT(canh x[], int sl, int i){
	int j, kt=0;
	for(j=0; j<sl; j++){
		if(x[j].d==i) {
			kt=1;
			return kt;
		}
	}
	return kt;
}

float canh_NN(canh A[][size], int n){
	int i, j;
	float min=9999999;
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			if(i!=j && A[i][j].dd<min && A[i][j].mark==0){
				min=A[i][j].dd;
			}
		}
	}
	return min;
}

void Nhanh_Can(canh A[][size], int n, int sl, int xp, float *TGT, float *CD, float *GTNNTT, canh x[], canh PA[]){
	int i;
	for(i=1; i<=n; i++){
		if(xp != i && !A[xp][i].mark && !Co_CT(x, sl, i)){
			*TGT = *TGT + A[xp][i].dd;
			*CD = *TGT + (n-(sl+1))*(canh_NN(A, n));
			if(*CD < *GTNNTT){
				x[sl]=A[xp][i];
				A[xp][i].mark=1;
				A[i][xp].mark=1;
				if(sl == n-2){
					x[n-1]=A[x[n-2].c][x[0].d];
					*TGT = *TGT + x[n-1].dd;
					if(*TGT < *GTNNTT){
						*GTNNTT = *TGT;
						int k;
						for(k=0; k<n; k++){
							PA[k]=x[k];
						}
					}
					*TGT = *TGT - x[n-1].dd;
				} else {
					Nhanh_Can(A, n, sl+1, i, TGT, CD, GTNNTT, x, PA);
				}
				
			}
			*TGT = *TGT - A[xp][i].dd;
			A[xp][i].mark=0;
			A[i][xp].mark=0;
		}
	}
}

int main(){
	canh A[size][size];
	canh x[size], PA[size];
	int n;
	read_data(A, &n);
	int i, j;
	char tpxp;
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			printf("%c%c=%.2f ", i+96, j+96, A[i][j].dd);
		}
		printf("\n");
	}
	printf("Chon thanh pho xuat phat tu a-%c: ", n+96);
	scanf("%c", &tpxp);
	float TGT=0, CD=0, GTNNTT=999999999;
	Nhanh_Can(A, n, 0, tpxp-96, &TGT, &CD, &GTNNTT, x, PA);
	float sum=0;
	for(i=0; i<n; i++){
		printf("%c-%c=%.2f\n", PA[i].d+96, PA[i].c+96, PA[i].dd);
		sum += PA[i].dd;
	}
	for(i=0; i<n; i++){
		printf("%c -> ", PA[i].d+96);
	}
	printf("%c", PA[0].d+96);
	printf("\nTGT: %.2f", sum);
	return 0;
}
