
#include <stdio.h>

//Do dai cua danh sach

#define Maxlength 300

typedef int ElementType;

typedef int Position; 


typedef struct {
	ElementType Elements[Maxlength];
	Position Last; 
  } List; 


void makenullList(List *L) {
	L->Last=0;
}


int emptyList(List L){
	return L.Last==0;
} 

int fullList(List L){
	return L.Last==Maxlength;
}

Position first(List L){
	return 1;
}


Position endList(List L){
	return L.Last+1;
}


ElementType retrieve(Position P, List L){
	return L.Elements[P-1];
}

Position next(Position P, List L){
	return P+1;
} 

Position previous(Position P, List L){
	return P-1;
} 


void insertList(ElementType X,Position P, List *L){
	 if (L->Last==Maxlength)
		printf("Danh sach day\n");	
  	 else if (P<1 || P>L->Last+1)
	    printf("Vi tri khong hop le\n");
	 else {
	    Position Q;
	    for(Q=L->Last;Q>=P;Q--)
		   L->Elements[Q]=L->Elements[Q-1];
	    L->Last++;
	    L->Elements[P-1]=X;
	 }
} 
 
 
void deleteList(Position P,List *L){ 
  if ((P<1) || (P>L->Last))
	    printf("Vi tri khong hop le");
  else if (L->Last==0)
	    printf("Danh sach rong!");
  else{
      Position Q;
 		for(Q=P;Q<L->Last;Q++)
		   L->Elements[Q-1]=L->Elements[Q];
		L->Last--;
  }
} 
 

Position locate(ElementType X, List L){
    int Found = 0;
	Position P = first(L), E=endList(L); 
	while (P != E && !Found)
		if (retrieve(P,L) == X) Found = 1;
		else P = next(P, L);
	return P;
} 


void readList (List *L)// nhap danh sach chua duoc chuan hoa /makenullLits
{
	makenullList(&*L);
    int n,i,x;
    scanf("%d",&n);
    L->Last=n;
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        L->Elements[i]=x;
    }
}


void printList (List L)// in danh sach 
{
    int i;
    for (i=0; i<L.Last; i++)
    {
        printf("%d ",L.Elements[i]);
    }
    printf("\n");
}

int main ()
{
	List L;
	readList(&L);
	printList(L);
	return 0;
}








