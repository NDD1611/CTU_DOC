typedef int KeyType;
struct Node {
    KeyType Key;
    int Height;
    struct Node *Left, *Right;
};
typedef struct Node* AVLTree; 


int getHeight(AVLTree T) // ham tra ve chieu cao cua node
{
    if(T == NULL)
    return -1;
    else
    return T->Height;
}

void printNLR (AVLTree T) // duyet tien tu cay AVL co in chieu cao
{
    if(T != NULL)
    {
        printf("(%d - %d); ",T->Key, T->Height);
        printNLR(T->Left);
        printNLR(T->Right);
    }
}

void printLRN (AVLTree T) // ham duyet hau tu cay AVL
{
    if(T != NULL)
    {
        printLRN(T->Left);
        printLRN(T->Right);
        printf("(%d - %d); ",T->Key,T->Height);
    }
}

int getBalance(AVLTree N) // ham tinh he so can bang cua node tren cay AVL
{
    if (N == NULL)
        return 0;
    return getHeight(N->Left) - getHeight(N->Right);
}


AVLTree rightRotate(AVLTree N) // quay don sang phai cho truong hop mat can bang ben trai cua con trai
{
    AVLTree x = (N)->Left;
    AVLTree T2 = x->Right;
    x->Right = N;
    (N)->Left = T2;
    (N)->Height = max(getHeight((N)->Left), getHeight((N)->Right))+1;
    x->Height = max(getHeight(x->Left), getHeight(x->Right))+1;
    return x;
}

AVLTree leftRotate(AVLTree N) // quay don sang phai trong truong hop mat can bang ben phai cua con phai
{
    AVLTree x = N->Right;
    AVLTree T2 = x->Left;
    x->Left = N;
    N->Right = T2;
    N->Height = max(getHeight(N->Right), getHeight(N->Left))+1;
    x->Height = max(getHeight(x->Right), getHeight(x->Left))+1;
    return x;
}

AVLTree leftrightRotate(AVLTree N) // xu ly khi mat can bang ben phai cua con trai
{
    AVLTree P = N->Left;
    AVLTree x = P->Right;
    AVLTree T2 = x->Left;
    x->Left = P;
    P->Right = T2;
    N->Left = x;
    P->Height = max(getHeight(P->Right), getHeight(P->Left))+1;
    x->Height = max(getHeight(x->Right), getHeight(x->Left))+1;
    N->Height = max(getHeight(N->Right), getHeight(N->Left))+1;
    AVLTree y = N->Left;
    AVLTree T3 = y->Right;
    N->Left = T3;
    y->Right = N;
    N->Height = max(getHeight(N->Right), getHeight(N->Left))+1;
    y->Height = max(getHeight(y->Right), getHeight(y->Left))+1;
    return y;
}

AVLTree rightleftRotate(AVLTree N) // xu ly mat can bang ben trai cua con phai
{
    AVLTree P = N->Right;
    AVLTree x = P->Left;
    AVLTree T2 = x->Right;
    x->Right = P;
    P->Left = T2;
    N->Right = x;
    P->Height = max(getHeight(P->Right), getHeight(P->Left))+1;
    x->Height = max(getHeight(x->Right), getHeight(x->Left))+1;
    N->Height = max(getHeight(N->Right), getHeight(N->Left))+1;
    AVLTree y = N->Right;
    AVLTree T3 = y->Left;
    N->Right = T3;
    y->Left = N;
    N->Height = max(getHeight(N->Right), getHeight(N->Left))+1;
    y->Height = max(getHeight(y->Right), getHeight(y->Left))+1;
    return y;
}

AVLTree insertNode(int key, AVLTree T) // them mot node co gia tri bang key vao AVL
{
    if (T == NULL)
    {
        AVLTree P;
        P = (struct Node*)malloc(sizeof(struct Node));
        P->Key = key;
        P->Left = NULL;
        P->Right = NULL;
        return P;
    }
 
    if (key < T->Key)
        T->Left  = insertNode(key, T->Left);
    else if (key > T->Key)
        T->Right = insertNode(key, T->Right);
    else 
        return T;
 
    T->Height = 1 + max(getHeight(T->Left),
                           getHeight(T->Right));
 
    int balance = getBalance(T);
    if (balance > 1 && key < T->Left->Key)
        return rightRotate(T);
    if (balance < -1 && key > T->Right->Key)
        return leftRotate(T);
    if (balance > 1 && key > T->Left->Key)
    {
        T->Left =  leftRotate(T->Left);
        return rightRotate(T);
    }
    if (balance < -1 && key < T->Right->Key)
    {
        T->Right = rightRotate(T->Right);
        return leftRotate(T);
    }
 
    return T;
}

AVLTree search(int k, AVLTree N) // tim kiem mot node va tra ve node do
{
    if(N==NULL || N->Key == k)
    {
        return N;
    }
    if(k < N->Key)
        return search(k, N->Left);
       
    return search(k, N->Right);
}

void printHeight(int h, AVLTree T) // in cac node co cung chieu cao la h
{
    if(T!= NULL)
    {
        if(T->Height == h)
        {
            printf("%d ",T->Key);
        }
        printHeight(h, T->Left);
        printHeight(h, T->Right);
    }
}


bool isAVL(AVLTree root) { // kiem tra cay co phai la cay AVL hay khong neu co tra ve 1 khong co tra ve 0
   int lh;
   int rh;
   if(root == NULL)
      return 1;
   lh = getHeight(root->Left);
   rh = getHeight(root->Right);
   if(abs(lh-rh) <= 1 && isAVL(root->Left) && isAVL(root->Right)) return 1;
   return 0;
}


void printLeaves (AVLTree T) // in cac node la trong cay AVL
{
    if (T != NULL) 
    {
        printLeaves(T->Left);
        printLeaves(T->Right);
        if(T->Left == NULL && T->Right == NULL)
        {
            printf("%d ",T->Key);
        }
    }
}

