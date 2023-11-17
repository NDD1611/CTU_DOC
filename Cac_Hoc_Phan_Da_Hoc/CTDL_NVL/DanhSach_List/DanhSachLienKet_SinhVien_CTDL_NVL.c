#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char ID[10];
    char Name[50];
    float R1,R2,R3;
}Student;

struct Node
{
    Student Element;
    struct Node* Next;
};
typedef struct Node* Position;
typedef Position List;

List readList();
int append();
void showPassedList();
void printList();
List getList();
List getFailedList();
List locate();

List readList()
{
	int n,i;
	Student s;
	char st[50];
	List L = getList(); // Kh?i t?o danh sách r?ng
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf(" "); //skip some characters
		fgets(st,10,stdin);
		if (st[strlen(st)-1] == '\n')
			st[strlen(st)-1] = '\0';
		strcpy(s.ID, st);
		fgets(st,50,stdin);
		if (st[strlen(st)-1] == '\n')
			st[strlen(st)-1] = '\0';
		strcpy(s.Name, st);
		scanf("%f%f%f",&s.R1,&s.R2,&s.R3);
		// N?u mã sinh viên chua có thì chèn vào danh sách
            	int k;
				k=append(s,&L);
				if(k==0)
				{
				    printf("%s exists\n",s.ID);
				} // doan ma tren else
	}
	return L;
}    

int append (Student s, List *L)// neu ma so sinh vien da co trong danh sach thi ham tra ve 0 nguoc lai them sinh vien vao danh sach va tra ve 1
{
    List P, T;
    P=*L;
    T=(struct Node*)malloc(sizeof(struct Node));
    T=locate(s.ID, *L);
    if(T->Next != NULL)
    {
        return 0;
    }
    else 
    {
        while(P->Next != NULL)
        {
            P=P->Next;
        }
        P->Next = (struct Node*)malloc(sizeof(struct Node));
        P->Next->Element = s;
        P->Next->Next = NULL;
        return 1;
    }
}

void showPassedList(List L)// hien thi cac sinh vien dat
{
	float tb=0, tong = 0;
	List P;
	P=L;
	int i=0;
	while(P->Next != NULL )
	{
		tong=P->Next->Element.R1 + P->Next->Element.R2 + P->Next->Element.R3;
		tb=(float)tong/3;
		if(tb>=4)
		{
			i++;
			printf("%2d - %10s - %50s - %.3f - %.3f - %.3f - %.3f\n",i,P->Next->Element.ID,P->Next->Element.Name,P->Next->Element.R1,P->Next->Element.R2,P->Next->Element.R3,tb);
		}
		P=P->Next;
	}
	printf("%d students in total",i);
}

void printList(List L) // hiem thi danh sach co hien thi diem tb cac mon hoc
{
	List P;
	P=L;
	int i=1;
	float tong=0,tb=0;
	while(P->Next!=NULL)
	{
	tong=P->Next->Element.R1 + P->Next->Element.R2 + P->Next->Element.R3;
	tb=(float)tong/3;
	printf("%2d - %10s - %50s - %.3f - %.3f - %.3f - %.3f\n",i,P->Next->Element.ID,P->Next->Element.Name,P->Next->Element.R1,P->Next->Element.R2,P->Next->Element.R3,tb);
	i++;
	P=P->Next;
	}
}

List getList()// khoi tao mot List rong va tra ve List rong do
{
    List L;
    L=(struct Node*)malloc(sizeof(struct Node));
    L->Next=NULL;
    return L;
}

List getFailedList(List L) // chep cac sinh vien KHONG DAT sang List L1 va tra ve L1
{
	List L1,P;
	P=L;
	L1 = getList();
	float tong=0,tb=0;
	while(P->Next != NULL)
	{
		tong=P->Next->Element.R1 + P->Next->Element.R2 + P->Next->Element.R3;
		tb=(float)tong/3;
		if(tb < 4)
		{
			append(P->Next->Element,&L1);
		}
		P=P->Next;
	}
	return L1;
	// phan trong ham main 
	/*L = getList();
L = readList();
printList(L);
List L1;
L1=getList();
L1 = getFailedList(L);
printList(L1);*/
}

List locate(char S[10], List L)// tra ve vi tri sinh vien co ma S xuat hien dau tien neu khong tra ve vi tri cuoi cung
{
    List P;
    P=L;
    while(P->Next != NULL)
    {
        if(strcmp(S,P->Next->Element.ID) == 0)
        {
            break;
        }
        P=P->Next;
    }
    return P;
}

int main()
{
	List L;
	L = getList();
	L = readList();
	printList(L);
	showPassedList(L);
     return 0;
}
