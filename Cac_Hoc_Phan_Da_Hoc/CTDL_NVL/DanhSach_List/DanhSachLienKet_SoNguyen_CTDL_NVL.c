#include <stdio.h>
#include <stdlib.h>


typedef int ElementType;

struct Node
{
ElementType Element;
struct Node* Next;
};
typedef struct Node* Position;
typedef Position List;

void makenullList();//32 /<stdlib.h>
List intersection();//38 /makenullList
void append();//53  
List readSet();//72 /member, addFirst
void readList();//89 /makenullList
void addFirst();//112 /
Position locate();//121 
int member();//136
void deleteList();//152
List difference();//160 /makenullList
void erase();//177 /locate, deleteList
float getAvg();//191
void removeAll();//214 /locate, deleteList
void printList();//228
void loc_so_chan();//240
void loc_so_le();//265
void normalize();
void printOddNumbers();
List unionSet();

void makenullList(List *L) // ham khoi tao danh sach rong
{
    *L=(struct Node*)malloc(sizeof(struct Node));
    (*L)->Next=NULL;
}

List intersection(List L1, List L2)//ham tim tap hop giao cua 2 danh sach L1 va L2 /makenullList, member, append
{
    List L;
    makenullList(&L);
    while(L1->Next != NULL)
    {
        if(member(L1->Next->Element,L2))
        {
            append(L1->Next->Element, &L);
        }
        L1=L1->Next;
    }
    return L;
}

void append(int x, List *L)// ham noi phan tu x vao danh sach 
{
    Position P;
    P=*L;
    Position T;
    T=(struct Node*)malloc(sizeof(struct Node));
    T->Element=x;
    T->Next=NULL;
    while(P->Next != NULL)
    {
         P=P->Next;
    }
    if(P->Next==NULL)
    {
        P->Next = T;
    }
    
}

List readSet ()// ham nhap danh sach da duoc chuan hoa
{
    List L;
    makenullList(&L);
    int x, i, n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        if(member(x,L)==0)
        {
            addFirst(x,&L);
        }
    }
    return L;
}

void readList (List *L)// ham nhap danh sach
{
    int n, i;
    makenullList(&*L);
    Position P;
    P=*L;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        if(P->Next != NULL)
        {
            while(P->Next != NULL)
            {
                P=P->Next;
            } 
        }  
        P->Next=(struct Node*)malloc(sizeof(struct Node));
        scanf("%d",&P->Next->Element);
        P->Next->Next=NULL;
    }
    return ;
}

void addFirst(int x, List *L)// ham chen x vao dau danh sach
{
    Position T;
    T=(struct Node*)malloc(sizeof(struct Node));
    T->Element=x;
    T->Next=(*L)->Next;
    (*L)->Next=T;
}

Position locate(ElementType x, List L)//tra ve vi tri xuat hien dau tien cua x trong danh sach L
{
    Position P;
    P=L;
    while(P->Next != NULL)
    {
        if(P->Next->Element==x)
        {
            break;
        }
        P=P->Next;
    }
    return P;
}

int member(ElementType x, List L)// kt phan tu x co trong danh sach hay khong
{
	Position P;
	P=L;
	int result=0;
	while(P->Next != NULL)
	{
		if(P->Next->Element == x)
		{
			result = 1;
		}
		P=P->Next;
	}
	return result;
}

void deleteList(Position P, List *L)// ham xoa mot Node trong List
{
    Position T;
    T=P->Next;
    P->Next=P->Next->Next;
    free(T);
}

List difference(List L1, List L2)// tap hop hieu cua 2 danh sach
{
    List L;
    makenullList(&L);
    Position P;
    P=L1;
    while(P->Next != NULL)
    {
        if(member(P->Next->Element, L2) == 0)
        {
            append(P->Next->Element, &L);
        }
        P=P->Next;
    }
    return L;
}

void erase(int x, List *L)// xoa phan tu xuat hien dau tien co gia tri x trong danh sach
{
    Position P;
    P=locate(x,*L);
    if(P->Next != NULL)
    {
        deleteList(P,&*L);
    }
    else
    {
        printf("Not found %d\n",x);
    }
}

float getAvg(List L)// tra ve gia tri trung binh cac phan tu trong danh sach neu khong co phan tu thi tra ve -10000
{
    Position P;
    P=L;
    float tong=0;
    int i=0;
    while(P->Next != NULL)
    {
        tong=tong+P->Next->Element;
        i++;
        P=P->Next;
    }
    if(tong!=0)
    {
        tong=(float)tong/i;
    }
    if(tong==0)
    {
        tong=-10000;
    }
    return tong;
}

void removeAll (int x, List *L)// ham xoa tat ca cac phan tu co gia tri bang x
{
    Position P;
    P=*L;
    while(P->Next != NULL)
    {
        P=locate(x,*L);
        if(P->Next != NULL)
        {
             deleteList(P,&*L);   
        } 
    }
}

void printList(List L)// ham in danh sach
{
	Position P;
	P=L;
	while(P->Next != NULL)
	{
		printf("%d ",P->Next->Element);
		P=P->Next;
	}
	printf("\n");
}

void loc_so_chan (List *L1, List L)//ham loc so chan tu danh sach L
{
	makenullList(&*L1);
	Position P1,P;
	P1=*L1;
	P=L;
	while(P->Next != NULL)
	{
		if(P->Next->Element%2 == 0)
		{
			while(P1->Next != NULL)
			{
				P1=P1->Next;
			}
			if(P1->Next == NULL)
			{
				P1->Next = (struct Node*)malloc(sizeof(struct Node));
			}
			P1->Next->Element = P->Next->Element;
			P1->Next->Next=NULL;
		}
		P=P->Next;
	}
}

void loc_so_le (List *L1, List L)//ham loc so le tu danh sach L
{
	makenullList(&*L1);
	Position P1,P;
	P1=*L1;
	P=L;
	while(P->Next != NULL)
	{
		if(P->Next->Element%2 != 0)
		{
			while(P1->Next != NULL)
			{
				P1=P1->Next;
			}
			if(P1->Next == NULL)
			{
				P1->Next = (struct Node*)malloc(sizeof(struct Node));
			}
			P1->Next->Element = P->Next->Element;
			P1->Next->Next=NULL;
		}
		P=P->Next;
	}
}

void normalize(List *L)// xoa cac phan tu trung nhau trong danh sach
{
    Position P,T;
    P=*L;
    while(P->Next != NULL)
    {
        T=P->Next;
        while(T->Next != NULL)
        {
            if(P->Next->Element == T->Next->Element)
            {
                deleteList(T,&*L);
                T=P->Next;
            }
            else
            {
                T=T->Next; 
            }
        }
        P=P->Next;
    }
}

void printOddNumbers (List L)//ham hien thi so le tu danh sach L
{
    Position P;
    P=L;
	while(P->Next != NULL)
	{
		if(P->Next->Element%2 != 0)
		{
			printf("%d ",P->Next->Element);
		}
		P=P->Next;
	}
}

List unionSet(List L1, List L2)
{
    List L;
    makenullList(&L);
    Position P,T;
    P=L1;
    T=L2;
    while (P->Next != NULL)
    {
        append(P->Next->Element, &L);
        P=P->Next;
    }
    while(T->Next != NULL)
    {
        if(member(T->Next->Element,L) == 0)
        {
            append(T->Next->Element,&L);
        }
        T=T->Next;
    }
    return L;
}

void SapXep(List *L)// sap xep danh sach
{
    int A[100];
    int i;
    Position P;
    P=*L;
    i=0;
    while(P->Next != NULL)
    {
        A[i]=P->Next->Element;
        i++;
        P=P->Next;
    }
    int n;
    n=i;
    int j, doi=0;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(A[i]>A[j])
            {
                doi=A[i];
                A[i]=A[j];
                A[j]=doi;
            }
        }
    }
    P=*L;
    i=0;
    while(P->Next != NULL)
    {
        P->Next->Element = A[i];
        i++;
        P=P->Next;
    }
}

int main ()
{
	List L;
	readList(&L);
	SapXep(&L);
	printList(L);
	
	return 0;
}
