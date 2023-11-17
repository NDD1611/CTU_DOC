#include <stdio.h>
#include <string.h>


typedef struct 
{
    char MSSV[10];
    char HoTen[50];
    float DiemLT, DiemTH1, DiemTH2;
} SinhVien;

typedef struct 
{
    SinhVien A[40];
    int n;
} DanhSach;

DanhSach dsRong()
{
    DanhSach L;
    L.n=0;
    return L;
}

void chenCuoi (struct SinhVien s, DanhSach *L)// chen sinh vien vao cuoi danh sach neu danh sach van chua day
{
    if(L->n < 40)
    {
        L->A[L->n] = s;
        L->n++;
    }
    else
    {
        printf("Loi! Danh sach day!");
    }
}

DanhSach chepKhongDat(DanhSach L)// chep nhung sinh vien khong dat sang 1 danh sach L1 va tra ve danh Sach L1
{
    DanhSach L1;
    int n1=0;
    int i;
    float tong=0;
    for(i=0;i<L.n;i++)
    {
        tong=L.A[i].DiemLT + L.A[i].DiemTH1 + L.A[i].DiemTH2;
        if(tong < 4)
        {
            L1.A[n1] = L.A[i];
            n1++;
        }
    }
    L1.n=n1;
    return L1;
}

void xoaSinhVien(char x[10],DanhSach *L)// xoa sinh vien co ma so cho truoc
{
    int p;
    p=tim(x,*L);
    if(p<=L->n)
    {
        xoaTai(p,&*L);
    }
}

void xoaTai(int p, DanhSach *L)// ham xoa sinh vien tai vi tri p
{
    int i;
    if(p>0 && p<=L->n)
    {
        for(i=p-1;i<L->n;i++)
        {
            L->A[i] = L->A[i+1];
        }
    }
    L->n--;
}

int tim(char x[10], DanhSach L)//tim 1 sinh vien co ma so cho truoc
{
    int i, kq;
    kq=L.n+1;
    for(i=0;i<L.n;i++)
    {
        if(strcmp(L.A[i].MSSV,x)==0)
        {
            kq=i+1;
            break;
        }
    }
    return kq;
}

void hienthiDat(DanhSach L)// hien thi sinh vien DAT trong danh sach 
{
    float tong;
    int i; 
    for(i=0;i<L.n;i++)
    {
        tong=(L.A[i].DiemLT+L.A[i].DiemTH1+L.A[i].DiemTH2);
        if(tong>=4)
        {
             printf("%s - %s - %.2f - %.2f - %.2f - %.2f\n",L.A[i].MSSV,L.A[i].HoTen,L.A[i].DiemLT,L.A[i].DiemTH1,L.A[i].DiemTH2,tong);
        }
    }
}

void hienthi(DanhSach L)// hien thi mot danh sach sinh vien
{
    int i;
    float tong=0;
    for(i=0;i<L.n;i++)
    {
        tong=L.A[i].DiemLT+L.A[i].DiemTH1+L.A[i].DiemTH2;
        printf("%s - %s - %.2f - %.2f - %.2f - %.2f\n",L.A[i].MSSV,L.A[i].HoTen,L.A[i].DiemLT,L.A[i].DiemTH1,L.A[i].DiemTH2,tong);
    }
}

DanhSach nhap()// nhap mot danh sach sinh vien
{
    DanhSach L;
    int l,n;
	struct SinhVien S;
	L = dsRong();
    scanf("%d",&n);
    int i;
    for(i=0;i<n;i++)
    {
        scanf(" ");
        fgets(S.MSSV, sizeof(S.MSSV), stdin);
        l=strlen(S.MSSV);
        if(S.MSSV[l-1]=='\n')
        {
            S.MSSV[l-1]='\0';
        }
        
        if(tim(S.MSSV,L)>L.n)
        {
            fgets(S.HoTen, sizeof(S.HoTen),stdin);
            l=strlen(S.HoTen);
            if(S.HoTen[l-1]=='\n')
            {
               S.HoTen[l-1]='\0';
            }
            scanf("%f %f %f",&S.DiemLT,&S.DiemTH1,&S.DiemTH2);
            chenCuoi(S,&L);
        }
    }
    return L;
}

//start chuong trinh nhap va hien thi danh sach sinh vien sau do nhap vao mot sinh vien va tim sinh vien do neu tim gap thi xoa
{// dau ngoac khoi
#include <stdio.h>
#include "AStudentListLib.c"
void nhap(List *L)
{
    int i, l;
    scanf("%d",&L->Last);
    for(i=0;i<L->Last;i++)
    {
        scanf(" ");
        fgets(L->Elements[i].MSSV, sizeof(L->Elements[i].MSSV), stdin);
        l=strlen(L->Elements[i].MSSV);
        if(L->Elements[i].MSSV[l-1]=='\n')
        {
            L->Elements[i].MSSV[l-1]='\0';
        }
        fgets(L->Elements[i].HoTen, sizeof(L->Elements[i].HoTen), stdin);
        l=strlen(L->Elements[i].HoTen);
        if(L->Elements[i].HoTen[l-1]=='\n')
        {
            L->Elements[i].HoTen[l-1]='\0';
        }
        scanf("%f%f%f",&L->Elements[i].DiemLT,&L->Elements[i].DiemTH1,&L->Elements[i].DiemTH2);
    }
}

void print(List L)
{
    int i;
    for(i=0;i<L.Last;i++)
    {
        printf("%s - %s - %.2f - %.2f - %.2f\n",L.Elements[i].MSSV,L.Elements[i].HoTen,L.Elements[i].DiemLT,L.Elements[i].DiemTH1,L.Elements[i].DiemTH2);
    }
}

int main()
{
    List L;
    char x[10];
    makenullList(&L);
    nhap(&L);
    scanf(" ");
    fgets(x,sizeof(x), stdin);
    int l;
    l=strlen(x);
    if(x[l-1]=='\n')
    {
        x[l-1]='\0';
    }
    print(L);
    int i, kt=0, p=0;
    for(i=0;i<L.Last;i++)
    {
        if(strcmp(x,L.Elements[i].MSSV)==0)
        {
            kt=1;
            p=i;
            break;
        }
    }
    if(kt==1)
    {
            printf("Tim thay sinh vien %s. Thong tin sinh vien:\n%s - %s - %.2f - %.2f - %.2f",x,L.Elements[p].MSSV,L.Elements[p].HoTen,L.Elements[p].DiemLT,L.Elements[i].DiemTH1,L.Elements[i].DiemTH2);
    }
    else
    {
        printf("Khong tim thay sinh vien %s",x);
    }
}
}// dau ngoac khoi
//end chuong trinh


//start chuong trinh nhap va hien thi danh sach sinh vien sau do hien thi ra cac sinh vien DAT
#include "AStudentListLib.c"
{// dau ngoac khoi

#include <stdio.h>
#include "AStudentListLib.c"
void nhap(List *L)
{
    scanf("%d",&L->Last);
    int l, i;
    for(i=0;i<L->Last;i++)
    {
        scanf(" ");
        fgets(L->Elements[i].MSSV,sizeof(L->Elements[i].MSSV), stdin);
        l= strlen(L->Elements[i].MSSV);
        if(L->Elements[i].MSSV[l-1]=='\n')
        {
            L->Elements[i].MSSV[l-1]='\0';
        }
        fgets(L->Elements[i].HoTen,sizeof(L->Elements[i].HoTen), stdin);
        l= strlen(L->Elements[i].HoTen);
        if(L->Elements[i].HoTen[l-1]=='\n')
        {
            L->Elements[i].HoTen[l-1]='\0';
        }
        scanf("%f%f%f",&L->Elements[i].DiemLT,&L->Elements[i].DiemTH1,&L->Elements[i].DiemTH2);
    }
}

void hienthi(List L)
{
    int i;
    for(i=0;i<L.Last;i++)
    {
        printf("%s - %s - %.2f - %.2f - %.2f\n",L.Elements[i].MSSV,L.Elements[i].HoTen,L.Elements[i].DiemLT,L.Elements[i].DiemTH1,L.Elements[i].DiemTH2);
    }
}

void dat(List L)
{
    float tong;
    int i; 
    for(i=0;i<L.Last;i++)
    {
        tong=(L.Elements[i].DiemLT+L.Elements[i].DiemTH1+L.Elements[i].DiemTH2);
        if(tong>=4)
        {
             printf("%s - %s - %.2f - %.2f - %.2f\n",L.Elements[i].MSSV,L.Elements[i].HoTen,L.Elements[i].DiemLT,L.Elements[i].DiemTH1,L.Elements[i].DiemTH2);
        }
    }
}

int main ()
{
    List L;
    makenullList(&L);
    nhap(&L);
    hienthi(L);
    printf("Sinh vien DAT\n");
    dat(L);
    return 0;
}
}// dau ngoac khoi
//end chuong trinh
//

//start chuong trinh nhap va hien thi danh sach sinh vien sau do hien thi ra cac sinh vien KHONG DAT
{// dau ngoac khoi
#include <stdio.h>
#include "AStudentListLib.c"
void nhap(List *L)
{
    scanf("%d",&L->Last);
    int l, i;
    for(i=0;i<L->Last;i++)
    {
        scanf(" ");
        fgets(L->Elements[i].MSSV,sizeof(L->Elements[i].MSSV), stdin);
        l= strlen(L->Elements[i].MSSV);
        if(L->Elements[i].MSSV[l-1]=='\n')
        {
            L->Elements[i].MSSV[l-1]='\0';
        }
        fgets(L->Elements[i].HoTen,sizeof(L->Elements[i].HoTen), stdin);
        l= strlen(L->Elements[i].HoTen);
        if(L->Elements[i].HoTen[l-1]=='\n')
        {
            L->Elements[i].HoTen[l-1]='\0';
        }
        scanf("%f%f%f",&L->Elements[i].DiemLT,&L->Elements[i].DiemTH1,&L->Elements[i].DiemTH2);
    }
}

void hienthi(List L)
{
    int i;
    for(i=0;i<L.Last;i++)
    {
        printf("%s - %s - %.2f - %.2f - %.2f\n",L.Elements[i].MSSV,L.Elements[i].HoTen,L.Elements[i].DiemLT,L.Elements[i].DiemTH1,L.Elements[i].DiemTH2);
    }
}

void khongdat(List L)
{
    float tong;
    int i; 
    for(i=0;i<L.Last;i++)
    {
        tong=(L.Elements[i].DiemLT+L.Elements[i].DiemTH1+L.Elements[i].DiemTH2);
        if(tong < 4)
        {
             printf("%s - %s - %.2f - %.2f - %.2f\n",L.Elements[i].MSSV,L.Elements[i].HoTen,L.Elements[i].DiemLT,L.Elements[i].DiemTH1,L.Elements[i].DiemTH2);
        }
    }
}

int main ()
{
    List L;
    makenullList(&L);
    nhap(&L);
    hienthi(L);
    printf("Sinh vien KHONG DAT\n");
    khongdat(L);
    return 0;
}	
}// dau ngoac khoi
//end chuong trinh



