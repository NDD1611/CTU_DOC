#include <stdio.h>

#define MAX_Vertices 20 // so luong dinh toi da
#define MAX_Length 20 

// khai bao cau truc do thi
typedef struct {
	int A[MAX_Vertices][MAX_Vertices];
	int n; // so luong dinh  cua do thi
}Graph;

// khai bao cau truc List
typedef struct {
	int data[MAX_Length];
	int size;
} List;

// ham khoi tao danh sach rong
void make_null(List *L) {
	L->size = 0;
}

// ham them 1 phan tu (dinh) vao danh sach
void push_back (List *L, int x) {
	L->data[L->size] = x;
	L->size++;
}

// ham lay mot phan tu (dinh) trong danh sach tai vi tri i
int element_at(List *L, int i){
	return L->data[i];
}

// ham khoi tao do thi
void init_Graph (Graph *G, int n) {
	G->n = n;
	int i, j;
	for(i=1; i<= G->n; i++) {
		for(j=1; j<=G->n; j++) {
			G->A[i][j] = 0;
		}
	}
}

// ham them cung vao do thi
void add_edge(Graph *G, int x, int y) {
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}

// ham kiem tra dinh x va dinh y co phai la lang gieng cua nhau hay khong
int adjacent (Graph *G, int x, int y) {
	return G->A[x][y];
}

// ham tinh bac cua 1 dinh bat  ky
int degree (Graph *G, int x) {
	int i, result = 0;
	for(i=1; i<=G->n; i++) {
		if(G->A[i][x] == 1) {
			result++;
		}
	}
	return result;
}

// ham tim tat ca lang gieng cua mot dinh
List neightbors (Graph *G, int x) {
	int i;
	List L;
	make_null(&L);
	for(i=1; i<=G->n; i++){
		if(G->A[i][x] == 1) {
			L.data[L.size] = i;
			L.size++;
		}
	}
	return L;
}

int main () {
	Graph G;
	int i, j, k;
	// doc du lieu tu file
	FILE* file = fopen("Graph.txt", "r");// lenh mo file
	int n, m; // n so luong dinh, m so kuong cung
	fscanf(file, "%d%d", &n, &m); // doc so dinh va cung tu file
	init_Graph(&G, n); // khoi tao do thi
	int u,  v; // u dinh dau, v la dinh ket thuc
	for(i=1; i<=m; i++) {
		fscanf(file, "%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	fclose(file); // sau khi doc du lieu xong phai dong file lai
	
	//in ma tran ra man hinh
	printf("\n%d\n",G.n);
	for(i=1; i<= G.n; i++) {
		for(j=1; j<=G.n; j++) {
			printf("%d ",G.A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	// in ra bac cua cac dinh
	for(i=1;i<=G.n;i++) {
		printf("bac cua dinh %d la: %d\n",i, degree(&G, i));
	}
	printf("\n");
	
	//tim lang gieng cua tat ca cac dinh (cach 1)
//	List L;
//	for(i=1; i<=G.n; i++){
//	make_null(&L);
//		for(j=1; j<=G.n; j++){
//			if(G.A[i][j] == 1) {
//				push_back(&L, j);
//			}
//		}
//		printf("lang gieng cua dinh %d la: ", i);
//		for(k=0; k<L.size; k++) {
//			printf("%d ", L.data[k]);
//		}
//		printf("\n");
//	}	


	// tim lang gieng cua tat ca cac dinh (cach 2)
	List L;
	for(i=1; i<=G.n; i++){
		make_null(&L);
		L = neightbors(&G, i);
		printf("lang gieng cua dinh %d la: ",i);
		for(j=0; j<L.size; j++){
			printf("%d ", L.data[j]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}
