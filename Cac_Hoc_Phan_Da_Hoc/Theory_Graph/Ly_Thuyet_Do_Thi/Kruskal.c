#include <stdio.h>
#define sz 50

typedef struct{
	int u, v, w;
}cung;

void Bubble_Sort(cung A[], int n, int m){
	int i, j;
	for(i=0; i<m-1; i++){
		for(j=m-1; j>i; j--){
			if(A[j].w < A[j-1].w){
				cung temp = A[j];
				A[j]=A[j-1];
				A[j-1]=temp;
			}
		}
	}
}

void Kruskal(cung A[], int n, int m){
	int nhom[sz];
	int i;
	for(i=1; i<=n; i++){
		nhom[i]=i;
	}
	cung B[sz];
	int sl=0;
	int tong=0;
	for(i=0; i<m; i++){
		int u, v;
		u=A[i].u;
		v=A[i].v;
		if(nhom[u] != nhom[v]){
			tong += A[i].w;
			B[sl]=A[i];
			sl++;
			int k;
			int nhomU=nhom[u];
			int nhomV=nhom[v];
			for(k=1; k<=n; k++){
				if(nhom[i]==nhomV){
					nhom[i]=nhomU;
				}
			}
		}
		if(sl==n-1) break;
	}
	
	printf("\n%d\n", tong);
	for(i=0; i<sl; i++){
		if(A[i].u > A[i].v){
			int temp=A[i].u;
			A[i].u=A[i].v;
			A[i].v=temp;
		}
		printf("%d %d %d\n", A[i].u, A[i].v, A[i].w);
	}
}

int main(){
	cung A[sz];
	int n, m;
	scanf("%d%d", &n, &m);
	int i;
	for(i=0; i<m; i++){
		scanf("%d%d%d", &A[i].u, &A[i].v, &A[i].w);
	}
	Bubble_Sort(A, n, m);
	Kruskal(A, n, m);
	return 0;
}
