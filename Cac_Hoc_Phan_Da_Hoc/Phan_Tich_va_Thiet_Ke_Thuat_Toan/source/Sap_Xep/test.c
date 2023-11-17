#include <stdio.h>

typedef struct{
	int key;
	float b;
}record;

void read(record A[], int *n){
	FILE* f;
	f=fopen("data.txt","r");
	int j=0;
	if(f!=NULL){
		while(!feof(f)){
			fscanf(f, "%d%f", &A[j].key, &A[j].b);
			j++;
		}
	} else printf("Loi mo file");
	*n=j;
}

void in(record A[], int n){
	int i;
	for(i=0; i<n; i++){
		printf("%-5d %-10.2f\n", A[i].key, A[i].b);
	}
}

void swap(record *x, record *y){
	record temp = *x;
	*x=*y;
	*y=temp;
}

void Selection_Sort(record A[], int n){
	printf("\nSelection_Sort:\n");
	int i, j, min, index;
	for(i=0; i<n-1; i++){
		min=A[i].key;
		index=i;
		for(j=i+1; j<n; j++){
			if(A[j].key < min){
				min=A[j].key;
				index=j;
			}
		}
		swap(&A[i], &A[index]);
	}
}

void Insert_Sort(record A[], int n){
	printf("\nInsert_Sort:\n");
	int i, j;
	for(i=1; i<n; i++){
		j=i;
		while(j>0 && A[j].key < A[j-1].key){
			swap(&A[j], &A[j-1]);
			j--;
		}
	}
}

void Bubble_Sort(record A[], int n){
	printf("\nBubble_Sort:\n");
	int i, j;
	for(i=0; i<n-1; i++){
		for(j=n-1; j>i; j--){
			if(A[j].key < A[j-1].key){
				swap(&A[j], &A[j-1]);
			}
		}
	}
}

int Find(record A[], int i, int j){
	int k=i+1;
	while(k<=j && A[k].key == A[i].key) k++;
	if(k>j) return -1;
	if(A[k].key > A[i].key) return k;
	return i;
}
int Parti(record A[], int i, int j, int pivot){
	int L, R;
	L=i;
	R=j;
	while(L<R){
		while(A[L].key < pivot) L++;
		while(A[R].key >= pivot) R--;
		if(L<R){
			swap(&A[L], &A[R]);
		}
	}
	return L;
}
void Quick_Sort(record A[], int i, int j){
	int indexpivot=Find(A, i, j);
	if(indexpivot != -1){
		int pivot = A[indexpivot].key;
		int k = Parti(A, i, j, pivot);
		Quick_Sort(A, i, k-1);
		Quick_Sort(A, k, j);
	}
}

void pushDown(record A[], int first, int last){
	int r=first;
	while(r<=(last-1)/2){
		if(last==r*2+1){
			if(A[r].key < A[last].key){
				swap(&A[r], &A[last]);
			}
			r=last;
		} else if(A[r].key < A[r*2+1].key && A[r*2+1].key >= A[r*2+2].key){
			swap(&A[r], &A[r*2+1]);
			r=r*2+1;
		} else if(A[r].key < A[r*2+2].key && A[r*2+2].key > A[r*2+1].key){
			swap(&A[r], &A[r*2+2]);
			r=r*2+2;
		} else r=last;
	}
}

void Heap_Sort(record A[], int n){
	int i, j;
	for(i=(n-2)/2; i>=0; i--){
		pushDown(A, i, n-1);
	}
	for(i=n-1; i>1; i--){
		swap(&A[0], &A[i]);
		pushDown(A, 0, i-1);
	}
	swap(&A[0], &A[1]);
}

int main(){
	record A[100];
	int n;
	read(A, &n);
	in(A, n);
//	Selection_Sort(A, n);
//	Insert_Sort(A, n);
//	Bubble_Sort(A, n);
//	printf("\nQuic_Sort:\n");
//	Quick_Sort(A, 0, n-1);
//	printf("\nHeap_Sort:\n");
//	Heap_Sort(A, n);
	in(A, n);	
	return 0;
}
