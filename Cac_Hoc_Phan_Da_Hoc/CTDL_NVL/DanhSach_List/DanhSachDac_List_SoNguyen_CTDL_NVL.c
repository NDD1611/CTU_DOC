#include <stdio.h>

void deleteList();
int locate();
void makenullList();
void normalize();
void erase();
void printList();
void readList();
float getAvg();
void insertSet();
void unionSet();
void difference();
int member();
void Hop();
void copyEvenNumbers();
void printOddNumbers();
int locate();
void insertList();

typedef struct 
{
	int Elements[100];
	int Last;	
} List;

void deleteList(int p,List *L)// xoa phan tu tai vi tri p trong danh sach l
{	
	int i;
	if(p > 0 && p <= L->Last)
	{
    	for(i=p-1;i<L->Last;i++)
    	{
    		L->Elements[i] = L->Elements[i+1];
    	}
    	L->Last--;
	}
	else
	{
	    printf("Vi tri khong hop le\n");
	}
}

int locate(int x,List L)// tra ve vi tri xuat hien dau tien cua x trong danh sach L
{
	int i;
	for(i=0;i<L.Last;i++)
	{
		if(L.Elements[i] == x)
		{
			return i+1;
		}
	}
	return L.Last+1;
}

void normalize (List *L)// ham chuan hoa danh sach /deleteList
{
    int i, j;
    for(i=0;i<L->Last;i++)
    {
        for(j=i+1;j<L->Last;j++)
        {
            if(L->Elements[i] == L->Elements[j])
            {
                deleteList(j+1,&*L);
                j--;
            }
        }
    }
}

void erase (int x, List *L)//xoa phan tu co vi tri xuat hien dau tien trong danh sach /locate,deleteList
{
    int p;
    p = locate(x,*L);
    if(p>0 && p <= L->Last)
    {
        deleteList(p,&*L);
    }
}

void sort (List *L)//sap xep danh sach theo thu tu tang dan
{
    int i,j,b;
    for(i=0;i<L->Last;i++)
    {
        for(j=i+1;j<L->Last;j++)
        {
            if(L->Elements[i] > L->Elements[j])
            {
                b=L->Elements[i];
                L->Elements[i]=L->Elements[j];
                L->Elements[j]=b;
            }
        }
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

void readSet(List *L)//nhap danh sach da duoc chuan hoa /makenullLits, member, insertSet
{
	makenullList(&*L);
    int n, i, x;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        if(member(x,*L) == 0)
        {
            insertSet(x,&*L);
        }
    }
}

float getAvg(List L)// tinh gia tri trung binh cac phan tu trong mang
{
    int i;
    float result=0, total=0;
    for(i=0; i<L.Last; i++)
    {
        total=total+L.Elements[i];
    }
    if(L.Last==0)
    {
        result=(float)-10000;
    }
    else
    {
        result=(float)total/L.Last;
    }
    return result;
}

void insertSet (int x, List *L)// chen x voa vi tri cuoi cua danh sach 
{
    L->Elements[L->Last]=x;
    L->Last++;
}

void unionSet (List L1, List L2, List *L)// tinh tap hop cua 2 danh sach /makenullList, insertSet, member
{
    makenullList(&*L);
    int i;
    for(i=0; i<L1.Last; i++)
    {
        insertSet(L1.Elements[i],&*L);
    }
    for(i=0;i<L2.Last;i++)
    {
        if(member(L2.Elements[i],*L)==0)
        {
            insertSet(L2.Elements[i],&*L);
        }
    }
}

void difference (List L1, List L2, List *L)// tap hop HIEU cua 2 danh sach /makenullList, member, insertSet
{
    int i;
    makenullList(&*L);
    for(i=0;i<L1.Last;i++)
    {
        if (member(L1.Elements[i],L2)==0)
        {
            insertSet(L1.Elements[i],&*L);
        }
    }
}

int member(int x, List L)// kiem tra x co xuat hien trong danh sach L hay khong
{
    int i,result=0;
    for(i=0;i<L.Last;i++)
    {
        if(L.Elements[i] == x)
        {
            result=1;
        }
    }
    return result;
}

void makenullList (List *L)//khoi tao danh sach rong
{
	L->Last = 0;
}

void intersection (List L1, List L2, List *L)// tim tap GIAO cua 2 danh sach / insertSet
{
	makenullList(&*L);
    int i;
    for(i=0;i<L1.Last;i++)
    {
        if(member(L1.Elements[i],L2)==1)
        {
            insertSet(L1.Elements[i],&*L);
        }
    }
}

void copyEvenNumbers (List L1, List *L)// copy cac so chan tu danh sach L1 sang L /makenullList
{
    makenullList(&*L);
    int i;
    for(i=0;i<L1.Last;i++)
    {
        if(L1.Elements[i]%2 == 0)
        {
            L->Elements[L->Last] = L1.Elements[i];
            L->Last++;
        }
    }
}

void printOddNumbers(List L)// liet ke cac so le trong danh sach
{
    int i;
    for(i=0;i<L.Last;i++)
    {
        if(L.Elements[i]%2 != 0)
        {
            printf("%d ",L.Elements[i]);
        }
    }
}

void  insertList(int x, int p, List *L)// ham chen phan tu x vao vi tri p neu vi tri p hop le
{
    int i;
    if(p > 0 && p <= L->Last)
    {
        for(i=L->Last;i>=p;i++)
        {
            L->Elements[i]=L->Elements[i-1];
        }
    }
    L->Elements[p-1]=x;
    L->Last++;
}

void removeAll (int x, List *L)// xoa tat ca cac phan tu co gia tri x trong danh sach L /locate, deletelist
{
    int i,p;
    for(i=0;i<L->Last;i++)
    {
        p=locate(x,*L);
        if(p>0 && p<=L->Last)
        {
            deleteList(p,&*L);
        }
    }
}

int main ()
{
	List L;
	readSet(&L);
	printList(L);
	return 0;
}
