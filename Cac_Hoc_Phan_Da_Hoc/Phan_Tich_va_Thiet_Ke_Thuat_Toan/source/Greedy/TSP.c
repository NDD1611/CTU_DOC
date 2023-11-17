
//Nguyen Dinh Dinh B2007177

#include <stdio.h>

typedef struct {
	float dd;
	int dau, cuoi;
}Canh;

void readData(Canh A[], int *n, int *m){
	FILE* f;
	int i, j;
	int dem=0;
	f=fopen("TSP.txt", "r");
	fscanf(f, "%d", n);
	if(f!=NULL){
		for(i=1; i<=*n; i++){
			float temp;
			for(j=1; j<=i; j++){
				fscanf(f, "%f", &temp);
			}
			for(j=i+1; j<=*n; j++){
				A[dem].dau=i;
				A[dem].cuoi=j;
				fscanf(f, "%f", &A[dem].dd);
				dem++;
			}
		}
		*m=dem;
	} else printf("Loi mo file");
	fclose(f);
}

void swap(Canh *x, Canh *y){
	Canh temp=*x;
	*x=*y; 
	*y=temp;
}
void Bubble (Canh A[], int n){
	int i, j;
	for(i=0; i<n-1; i++){
		for(j=n-1; j>i; j--){
			if(A[j].dd < A[j-1].dd){
				swap(&A[j], &A[j-1]);
			}
		}
	}
}

void Greedy(Canh A[], int n, int m){
	int bac[n+1], nhom[n+1];
	int i, j, scanh;
	for(i=1; i<=n; i++){
		bac[i]=0;
		nhom[i]=i;
	}	
	Canh B[n+1];
	scanh=0;
	j=0; // scanh de dem so canh da duoc chon, bien j chay tu 0->m-1 canh
	do {
		int dau, cuoi;
		dau=A[j].dau;
		cuoi=A[j].cuoi;
		
		if((bac[dau]<2 && bac[cuoi]<2) && (nhom[dau]!=nhom[cuoi])){
			B[scanh]=A[j];
			scanh++;
			bac[dau]++;
			bac[cuoi]++;
			
			int nh = nhom[cuoi];
			for(i=1; i<=n; i++){
				if(nhom[i]==nh){
					nhom[i]=nhom[dau];
				}
			}
			//nhom[cuoi]=nhom[dau];
		} 
		if(scanh == n-1){ // chon canh cuoi cung
			if(bac[dau]==1 && bac[cuoi]==1){
				B[scanh]=A[j];
				scanh++;
				bac[dau]++;
				bac[cuoi]++;			
			}
		}
		j++;
	}while(scanh < n);
	printf("\n\nCac canh duoc chon:\n");
	for(i=0; i<scanh; i++){
		printf("%d %d %.2f\n", B[i].dau, B[i].cuoi, B[i].dd);
	}
}

int main(){
	Canh A[100];
	int n, m;
	readData(A, &n, &m);
	int i;
	Bubble(A, m);
	for(i=0; i<m; i++){
		printf("%d %d %.2f\n", A[i].dau, A[i].cuoi, A[i].dd);
	}
	printf("%d  %d", n, m);
	Greedy(A, n, m);
	return 0;
}
