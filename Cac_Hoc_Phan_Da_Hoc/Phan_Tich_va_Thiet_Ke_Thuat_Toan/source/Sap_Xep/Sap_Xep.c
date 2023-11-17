#include <stdio.h>

typedef struct{
	int key;
	float orther;
}record;

void swap (record *x, record *y){
	record temp;
	temp = *y;
	*y = *x;
	*x = temp;
}

void SelectSort(record A[], int n){
	int i, j;
	int min, minindex;
	for(i=0; i<n-1; i++){
		min=A[i].key;
		minindex=i;
		for(j=i+1; j<n; j++){
			if(A[j].key < min){
				min=A[j].key;
				minindex=j;
			}
		}
		swap(&A[i], &A[minindex]);
	}
}

void InsertSort(record A[], int n){
	int i, j;
	for(i=1; i<n; i++){
		j=i;
		while(j>0 && A[j].key<A[j-1].key){
			swap(&A[j], &A[j-1]);
			j--;
		}
	}
}

void BubbleSort(record A[], int n){
	int i, j;
	for(i=0; i<n-1; i++){
		for(j=n-1; j>=i+1; j--){
			if(A[j].key < A[j-1].key){
				swap(&A[j], &A[j-1]);
			}
		}
	}
}

int FindPivot(record A[], int i, int j){
	int k;
	int firstkey;
	firstkey=i;
	k=i+1;
	while(k<=j && A[firstkey].key == A[k].key) k++;
	if(k>j) return -1;
	if(A[k].key > A[firstkey].key) return k;
	return firstkey;
}

int Partition (record A[], int i, int j, int pivot){
	int L, R;
	L=i;
	R=j;
	while(L<=R){
		while(A[L].key<pivot) L++;
		while(A[R].key>=pivot) R--;
		if(L<R) swap(&A[L], &A[R]);
	}
	return L;
}

void QuickSort(record A[], int i, int j){
	int pivotindex, k;
	pivotindex=FindPivot(A, i, j);
	int pivot;
	if(pivotindex != -1){
		pivot=A[pivotindex].key;
		k=Partition(A, i, j, pivot);
		QuickSort(A, i, k-1);
		QuickSort(A, k, j);
	}
}

void PushDown(record A[], int first, int last){
	int r; 
	r=first;
	while(r<=(last-1)/2){
		if(last == 2*r+1){
			if(A[r].key < A[last].key){
				swap(&A[r], &A[last]);
			}
			r=last;
		} else if((A[r].key > A[2*r+1].key) && (A[2*r+1].key <= A[2*r+2].key)){
			swap(&A[r], &A[2*r+1]);
			r=2*r+1;
		} else if((A[r].key > A[r*2+2].key) && (A[r*2+2].key < A[r*2+1].key)){
			swap(&A[r],&A[r*2+2]);
			r=2*r+2;
		} else {
			r=last;
		}
	}
}

void HeapSort(record A[], int n){
	int i;
	for(i=(n-2)/2; i>=0; i--){
		PushDown(A, i, n-1);
	}
	for(i=n-1; i>=2; i--){
		swap(&A[0], &A[i]);
		PushDown(A, 0, i-1);
	}
	swap(&A[0], &A[1]);
}

int main(){
	FILE* f;
	record A[100];
	int i, n;
	n=0;
	f = fopen("data.txt", "r");
	if(f!=NULL){
		while(!feof(f)){
			fscanf(f, "%d%f", &A[n].key, &A[n].orther);
			n++;
		} 
	}else printf("khong mo duoc file");
	fclose(f);
	
	for(i=0; i<n; i++){
		printf("%d %.2f\n", A[i].key, A[i].orther);
	}
	
	//SelectSort(A, n);
	//InsertSort(A, n);
	//BubbleSort(A, n);  
	//QuickSort(A,0, n-1);
	HeapSort(A, n);
	printf("\n\n");
	for(i=0; i<n; i++){
		printf("%d %.2f\n", A[i].key, A[i].orther);
	}
	return 0;
}
