#include <stdio.h>
#include <stdlib.h>

struct Node {
	int Key;
	struct Node* Left;
	struct Node* Right;
};
typedef struct Node* Tree;

void makenullTree(Tree *T)		// ham khoi tao cay rong
{
	(*T)=NULL;
}

void insertNode(int x, Tree *T) // ham chen khoa x vao cay
{
	if(*T==NULL)
	{
		Tree P;
		P=(struct Node*)malloc(sizeof(struct Node));
		P->Key = x;
		P->Left = NULL;
		P->Right = NULL;
		(*T)=P;
	}
	else if(x < (*T)->Key)
	{
		insertNode(x, &(*T)->Left);
	}
	else if(x > (*T)->Key)
	{
		insertNode(x, &(*T)->Right);
	}
}

int isEmpty (Tree T) // ham kt cay co rong hay khong
{
    if(T == NULL)
    return 1;
    return 0;
}

void deleteNode (int x, Tree *T) // ham xoa mot node trong cay
{
    Tree P;
    P=*T;
    Tree L=P;
    if(x == P->Key) // xoa nut goc
    {
        if(P->Left == NULL) // chi co con phai
        {
            *T=(*T)->Right;
        }
        if(P->Right== NULL) // chi co con trai
        {
            *T=(*T)->Left;
        }
        if(P->Left != NULL && P->Right != NULL)
        {
            if(P->Left->Right == NULL)
            {
                P->Left->Right = P->Right;
                *T=(*T)->Left;
            }else
            {
                Tree max=P->Left;
                Tree Pmax=P->Left;
                while(max->Right != NULL)
                {
                    Pmax=max;
                    max=max->Right;
                }
                P->Key = max->Key;
                Pmax->Right = NULL;
            }
            
        }
    }
    else
        {
        while(P->Key != x && P != NULL)
        {
            if(x < P->Key)
            {
                L=P;
                P=P->Left;
            }
            if(x > P->Key)
            {
                L=P;
                P=P->Right;
            }
            if(x==P->Key)
            {
                if(P->Left == NULL && P->Right == NULL)
                {
                    if(P->Key > L->Key)
                    {
                        L->Right = NULL;
                    }
                    if(P->Key < L->Key)
                    {
                        L->Left = NULL;
                    }
                }
                if (P->Left == NULL && P->Right != NULL)
                {
                    if(P->Key < L->Key )
                    {
                        L->Left = P->Right;
                        free(P);
                    }
                    if(P->Key > L->Key)
                    {
                        L->Right = P->Right;
                        free(P);
                    }
                }
                if (P->Right == NULL && P->Left != NULL)
                {
                    if(P->Key < L->Key )
                    {
                        L->Left = P->Left;
                        free(P);
                    }
                    if(P->Key > L->Key)
                    {
                        L->Right = P->Left;
                        free(P);
                    }
                }
                if (P->Left != NULL && P->Right != NULL)
                {
                    if(P->Left->Right == NULL && P->Key < L->Key)
                    {
                        P->Left->Right = P->Right;
                        L->Left=P->Left;
                    }
                    else if(P->Left->Right == NULL && P->Key > L->Key)
                    {
                        P->Left->Right = P->Right;
                        L->Right=P->Left;
                    }
                }
            }
        }
    }
}

void NLR(Tree T) 			// ham duyet tien tu
{
	if(T != NULL)
	{
		printf("%d ",T->Key);
		NLR(T->Left);
		NLR(T->Right);
	}
}


void LNR(Tree T)  		// ham duyet trung tu
{
	if(T != NULL)
	{
		LNR(T->Left);
		printf("%d ",T->Key);
		LNR(T->Right);
	}
}

void LRN(Tree T)      // ham duyet hau tu
{
	if(T != NULL)
	{
		LRN(T->Left);
		LRN(T->Right);
		printf("%d ",T->Key);
	}
}

Tree rightSibling (int x, Tree T) 	// ham tim anh em ruot phai cua x
{
    Tree P, Brother;
    P=T;
    Brother=NULL;
    while(P != NULL)
    {
        if(P->Key == x && P != Brother)
        {
            return Brother;
        }
        Brother = P->Right;
        if(P->Key < x)
        {
            P=P->Right;
        }
        else
        {
            P=P->Left;
        }
    }
    return NULL;
}

Tree searchNode (int x, Tree T) // tim node co khoa x
{
    Tree P;
    P=T;
    while (P != NULL)
    {
        
        if(x < P->Key)
        {
            P=P->Left;
        }
        else if(x > P->Key)
        {
            P=P->Right;
        }
        else if (P->Key == x)
        {
            break;
        }
    }
    return P;
}


Tree getNext(int x, Tree T) // ham tra ve node dung sau node co khoa x trong cay khi duyet trung tu
{
    Tree P=T;
    Tree maxL=T->Left;
    Tree minR=T->Right;
    Tree Cha=NULL;
    while(maxL->Right != NULL)
    {
        maxL=maxL->Right;
    }
    
    while(minR->Left != NULL)
    {
        minR=minR->Left;
    }
    while(P->Key != x && P != NULL)
    {
        Cha=P;
        if(x < P->Key)
        {
            P=P->Left;
        }
        if(x > P->Key)
        {
            P=P->Right;
        }
    }
    if(P->Key == maxL->Key)
    {
        return T;
    }
    if(P->Key == T->Key)
    {
        return minR;
    }
    if(x > T->Key)
    {
        if(P->Key > Cha->Key)
        {
            return P->Right;
        }
        if(P->Key < Cha->Key)
        
        {
            return Cha;
        }
    }
    if(x < T->Key)
    {
        if(Cha->Key == T->Key && P->Right != NULL)
        {
            return P->Right;
        }
        if(P->Key > Cha->Key)
        {
            return P->Right;
        }
        if(P->Key < Cha->Key)
        {
            return Cha;
        }
    }
    return NULL;
}

Tree getPrevious(int x, Tree T)
{
    Tree P=T;
    Tree minR=T->Right;
    Tree Cha=NULL;
    while(minR->Left != NULL)
    {
        minR=minR->Left;
    }
    while(P->Key != x && P != NULL)
    {
        Cha=P;
        if(x < P->Key)
        {
            P=P->Left;
        }
        if(x > P->Key)
        {
            P=P->Right;
        }
    }
    if(x < T->Key)
    {
        return P->Left;
    }
    if(x > T->Key)
    {
        if(x == minR->Key)
        {
            return T;
        }
        if(P->Key > Cha->Key)
        {
            return Cha;
        }
        if(P->Key < Cha->Key)
        {
            return P->Left;
        }
    }
    return NULL;
}

Tree getParent(int x, Tree T) // tim node cha cua node co khoa x
{
    Tree P=T;
    Tree parent=NULL;
    while(P->Key != x && P != NULL)
    {
        parent=P;
        if(x < P->Key)
        {
            P=P->Left;
        }
        if(x > P->Key)
        {
            P=P->Right;
        }
    }
    return parent;
}

void printPath (int x, Tree T) // tim mot node co khoa la x, khi di qua moi node se in gia tri tai node do
{
    if(T == NULL)
    {
        printf("-> Khong thay");
    } else 
    {
        printf("%d ",T->Key);
        if(x == T->Key)
        {
            printf("-> Tim thay");
        }
        if(x < T->Key)
        {
            printPath(x,T->Left);
        }
        if(x > T->Key)
        {
            printPath(x, T->Right);
        }
    }
}


int getHeight(Tree node) // tim chieu cao cua cay
{
    if (node == NULL)
        return -1;
    else {
        int lDepth = getHeight(node->Left);
        int rDepth = getHeight(node->Right);
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

int dem(Tree T) // dem so node trong cay
{
    if (T == NULL)
       return 0;
  
    int res = 0;
    if  (T != NULL)
       res++;
  
    res += (dem(T->Left) +
            dem(T->Right));
    return res;
}

int tong(Tree T) // tinh tong cac node trong cay
{
    if (T == NULL)
       return 0;
  
    int t = 0;
    if  (T != NULL)
       t=t+T->Key;
  
    t += (tong(T->Left) +
            tong(T->Right));
    return t;
}
float getAverage(Tree T)
{
	int d = dem(T);
	int t = tong(T);
	return (float)t/(float)d;
}
int main()
{	
Tree T=NULL;
Tree p;
int x;

insertNode(10,&T);
insertNode(15,&T);
insertNode(8,&T);
insertNode(4,&T);
insertNode(20,&T);
insertNode(5,&T);
insertNode(1,&T);
insertNode(3,&T);
insertNode(14,&T);
insertNode(15,&T);
NLR(T);
int kq = dem(T);
int t = tong(T);
printf("\n%d %d", kq, t);
float avg = getAverage(T);
printf("\n%.3f ",avg);
	return 0;
}
