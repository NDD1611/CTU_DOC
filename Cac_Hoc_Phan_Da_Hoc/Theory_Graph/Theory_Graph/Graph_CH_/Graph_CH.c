#include <stdio.h>

typedef struct {
	int data[100][100];
	int n, m;
}Graph;
typedef struct {
	int data[100];
	int size;
}List;

void makeNullList(List *L){
	L->size=0;
}

void pushList(List *L, int x){
	L->data[L->size]=x;
	L->size++;
}
List neighbors(Graph *G, int P){
	List L;
	makeNullList(&L);
	int i;
	for(i=1; i<=G->n; i++){
		if(G->data[P][i] != 0){
			pushList(&L, i);
		}
	}
	return L;
}

int tonTaiDuongDi(Graph *G, int x, int y){	//ham kt co ton tai duong di giua hai dinh x y hay khong
	List dd;
	makeNullList(&dd);
	int mark[G->n];
	int i;
	for(i=1; i<=G->n;i++){
		mark[i]=0;
	}
	pushList(&dd, x);
	while(!(dd.size==0)){
		int P;
		P=dd.data[dd.size-1];
		dd.size--;
		
		if(mark[P]!=0) continue;
		
		mark[P]=1;
		List L;
		L=neighbors(G, P);
		
		for(i=0; i<L.size;i++){
			pushList(&dd, L.data[i]);
		}
	}
	if(mark[y]!=0) return 1;
	
	return 0;
}

// tim duong di ngan nhat cho do thi co huong
void Moore_Dijkstra_CH(Graph *G, int x, int n){
	List dd;			// danh sach cac phan tu doi duyet
	int parent[G->n+1];	// chua cha cua cac phan tu
	int cs[G->n+1];		// chi so duong di ngan nhat toi dinh
	int mark[G->n+1];		// cho biet dinh da duoc chon hay chua
	int i, j;
	for(i=1; i<=G->n; i++){
		parent[i]=0;
		cs[i]=0;
		mark[i]=0;
	}
	makeNullList(&dd);
	pushList(&dd, x);
	
	while(!(dd.size==0)){
		int P, ptmin, minindex;
		ptmin=dd.data[0];
		minindex=0;
		// tim phan tu co chi so duong di ngan nhat de chon ra
		for(i=0; i<dd.size; i++){
			if(cs[dd.data[i]]<cs[ptmin]){
				ptmin=dd.data[i];
				minindex=i;
			}
		}
		// gan phan tu co chi so ngan nhat cho P
		P=ptmin;
		
		// xoa phan tu vua chon ra khoi danh sach dd bang cach don dan sach lai
		for(i=minindex; i<dd.size-1;i++){
			dd.data[i]=dd.data[i+1];
		}
		dd.size--;
		
		mark[P]=1; // danh dau la da duyet
		
		List L;
		L=neighbors(G, P); 	// danh sach hang xom cua P
		
		for(i=0; i<L.size; i++){	// dua cac phan tu vao danh sach dd
			int kt=0, cstam;
			int H;
			H=L.data[i];
			for(j=0; j<dd.size; j++){
				if(dd.data[j] == H){
					kt=1;
				}
			}
			cstam=cs[P]+G->data[P][H];
			if(kt==1){
				if(cstam<cs[H]){
					cs[H]=cstam;
					parent[H]=P;
				}
			} else { 
				if(mark[H]==0){
				pushList(&dd, H);
				cs[H]=cstam;
				parent[H]=P;
				}
			}
		}
	}	
	for(i=1; i<=G->n;i++){
		printf("%d: %d %d\n", i, parent[i], cs[i]);
	}
}

// giai thuat xep hang cho do thi Co Huong, khong co chu trinh
void XH(Graph *G){
	int hang[G->n];
	List dd;
	makeNullList(&dd);
	int i, j;
	for(i=1; i<=G->n; i++){
		hang[i]=0;
	}
	int kt;
	for(i=1; i<=G->n; i++){
		kt=0;
		for(j=1; j<=G->n;j++){
			if(G->data[j][i]!=0){
				kt=1;
				continue;
			}
		}
		if(kt==0) break;
	}
	pushList(&dd, i);
	
	while(!(dd.size==0)){
		int P;
		P=dd.data[dd.size-1];
		dd.size--;
		List L;
		L = neighbors(G, P);
		
		for(i=0; i<L.size;i++){
			int H;
			H=L.data[i];
			int hTam;
			hTam=hang[P]+1;
			int kt=0;
			for(j=0; j<dd.size; j++){
				if(dd.data[j]==H){
					kt=1;
				}
			}
			if(kt==1){
				if(hang[H]<hTam){
					hang[H]=hTam;
				}
			} else {
				if(hang[H]<hTam){
					hang[H]=hTam;
				}
				pushList(&dd, H);
			}
		}
	}
	for(i=1; i<=G->n; i++){
		printf("%d: %d\n", i, hang[i]);
	}
	
	//start dung cho bai toan can da tren else
//	for(i=0; i<=G->n; i++){
//		for(j=1; j<=G->n; j++){
//			if(hang[j]==i){
//				printf("%d ", j);
//			}
//		}
//	}
	// end dung cho bai toan can da tren else
	
	
	//start chia keo tren else
	int hMax=-1;
	for(i=1; i<=G->n;i++){
		if(hang[i]> hMax){
			hMax=hang[i];
		}
	}
	int skln=hMax+1; // so keo lon nhat
	int sKeo[G->n];
	for(i=1; i<=G->n;i++){
		sKeo[i]=skln-hang[i];
	}
	for(i=1; i<=G->n;i++){
		printf("%d\n", sKeo[i]);
	}
	// end chia keo tren else
}
int main(){
	
	Graph G;
	scanf("%d%d", &G.n, &G.m);
	int i, j, u, v, w;
	for(i=1; i<=G.n;i++){
		for(j=1; j<=G.n;j++){
			G.data[i][j]=0;
		}
	}
	
	// sd cho do thi co trong so cua cung
//	for(i=1; i<=G.m; i++){
//		scanf("%d%d%d", &u, &v, &w);
//		G.data[u][v]=w;	
//	}
	
	// sd cho do thi khong co trong so
	for(i=1; i<=G.m; i++){
		scanf("%d%d", &u, &v);
		G.data[u][v]=1;
	}
	
	printf("\n\n");
	for(i=1; i<=G.n;i++){
		for(j=1; j<=G.n;j++){
			printf("%d ", G.data[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	
	//tim duong di ngan nhat 
	//Moore_Dijkstra_CH(&G, 1, 1);
	
	// start kt do thi co lien thong manh hay khong
//	int kt=1;
//	for(i=1; i<=G.n;i++){
//		for(j=1; j<=G.n; j++){
//			if(i!=j){
//				int tontai;
//				tontai=tonTaiDuongDi(&G, i, j);
//				if(tontai==0){
//					kt=0;
//					break;
//				}
//			}
//		}		
//	}
//	if(kt==1){
//		printf("strong connected");
//	} else {
//		printf("unconnected");
//	}
	//end kt do thi co lien thong manh hay khong
	
	// start xep hang cho cac dinh trong do thi
	XH(&G);
	// end xep hang cho cac dinh trong do thi
	return 0;
}
/* co huong
7 12
1 2 7
1 3 1
2 4 4
2 5 2
2 6 3
3 2 5
3 6 7
3 5 2
4 7 4
5 7 10
6 4 5
6 5 3
*/
