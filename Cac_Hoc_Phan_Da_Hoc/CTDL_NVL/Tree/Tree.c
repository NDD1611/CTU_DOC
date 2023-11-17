
Tree findElement( char x, Tree T) // tim phan tu tren Tree
{
    if(T==NULL || T->Data == x)
    return T;
    Tree found = findElement(x, T->Left);
    if(found != NULL) return found;
    return findElement(x, T->Right);
}


int isMirrors(Tree T1, Tree T2) // kiem tra cay co phai la phan chieu hay khong
{ 
    if (T1==NULL && T2==NULL) 
        return true; 
    if (T1==NULL || T2 == NULL) 
        return false; 
    return  T1->Data == T2->Data && 
            isMirrors(T1->Left, T2->Right) && 
            isMirrors(T1->Right, T2->Left); 
} 


int findMax(Tree T) // tim gia tri lon nhat tren Tree
{
    if (T == NULL)
        return 1;
 
    int max = T->Data;
    int maxl = findMax(T->Left);
    int maxr = findMax(T->Right);
    if (maxl > max)
        max = maxl;
    if (maxr > max)
        max = maxr;
    return max;
}

int getFullNodes(Tree T) // dem so node du 2 con
{
    if (T == NULL)
       return 0;
  
    int res = 0;
    if  (T->Left && T->Right)
       res++;
  
    res += (getFullNodes(T->Left) +
            getFullNodes(T->Right));
    return res;
}

Tree convertTree(Tree T) // chuyen cay nhi phan T thanh cay phan chieu cua no
{
  if (T==NULL)
    return T; 
  else
  {
    Tree temp;
    convertTree(T->Left);
    convertTree(T->Right);
 
    temp = T->Left;
    T->Left  = T->Right;
    T->Right = temp;
  }
  return T;
}

int preIndex = 0; // ham tao cay tu 2 danh sach duyet trung tu va tien tu khai bao bien toan cuc
Tree createTree (DataType pre[], DataType in[], int Start, int End)
{
    Tree N=NULL;
    if(Start <= End){
    N=(struct Node*)malloc(sizeof(struct Node));
    N->Data = pre[preIndex];
    (preIndex)++;
    int Middle = findIndex(N->Data, in, Start, End);
    N->Left = createTree(pre, in, Start, Middle-1);
    N->Right = createTree(pre, in, Middle+1, End);
    }
    return N;
}
