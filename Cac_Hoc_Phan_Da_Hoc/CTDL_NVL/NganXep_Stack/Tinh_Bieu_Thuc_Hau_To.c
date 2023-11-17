#include <stdio.h>
#include <string.h>

#define MaxLength 100
typedef char ElementType;// mac dinh la float
typedef struct 
{
	ElementType Elements[MaxLength];
	int Top_idx;
} Stack;

void makenullStack();
void pop();
int emptyStack();
int fullStack();
ElementType top();
void printBinary();
void delete_space();
float Suffixes();

void push(ElementType x, Stack *S)// them phan tu x vao Stack
{
	if (fullStack(*S))
	{	
		printf ("Stack day");
	}
	else
	{
		S->Top_idx--;
		S->Elements[S->Top_idx]=x;
	}
}

void makenullStack(Stack *S)// khoi tao mot Stack rong
{
	S->Top_idx = MaxLength;
}

void pop(Stack *S)// xoa mot phan tu trong Stack
{
	S->Top_idx++;
}

int emptyStack(Stack S)// kt Stack co rong hay khong neu co rong thi tra ve 1, khong rong thi tra ve 0
{
	int result=0;
	if(S.Top_idx==MaxLength)
	{
		result =1;
	}
	return result;
}

int fullStack(Stack S)// kt Stack co day khong
{
	return S.Top_idx==0;
}

ElementType top(Stack S) // tra ve phan tu tai dinh Stack
{
	return S.Elements[S.Top_idx];
}

void delete_space(char s[])// xoa khoang trang trong chuoi
{
	char s1[100];
	int n, i, j=0;
	n= strlen(s);
	for(i=0;i<=n;i++)
	{
		if(s[i] != ' ')
		{
			s1[j]=s[i];
			j++;
		}
	}
	for(i=0;i<=j;i++)
	{
		s[i]=s1[i];
	}
}

void printBinary(int n)//in ma nhi phan cua mot so nguyen / phai doi ElementType thanh kieu so nguyen
{
	if (n==0) 
	{
		printf("0");
	}
	else
	{
		Stack S;
		makenullStack(&S);
		while (n!=0)
		{
			push(n%2, &S);
			n=n/2;
		}
		while (!emptyStack(S)) 
		{
			printf("%d", top(S));
			pop(&S); 
		}
	}
} 

float Suffixes(char s[])// tinh gia tri cua chuoi so o dang hau to
{
	Stack S;
	makenullStack(&S);
	float result;
	int n, i;
	float x,a,b,kq;
	n = strlen(s);
	for(i=0;i<n;i++)
	{
		if(s[i] != ' ')
		{	
			if(s[i] >= '0' && s[i] <= '9')
			{
				x = (float)(s[i]-'0');
				push(x,&S);
			}
			else
			{
				switch (s[i])
				{
					case '+':
						a =(float) top(S);
						pop(&S);
						b = (float)top(S);
						pop(&S);
						kq=a+b;
						push(kq,&S);
						break;
						
					case '-':
						a = (float)top(S);
						pop(&S);
						b = (float)top(S);
						pop(&S);
						kq=b-a;
						push(kq,&S);
						break;
						
					case '*':
						a = (float)top(S);
						pop(&S);
						b = (float)top(S);
						pop(&S);
						kq=a*b;
						push(kq,&S);
						break;
						
					case '/':
						a = (float)top(S);
						pop(&S);
						b = (float)top(S);
						pop(&S);
						kq=b/a;
						push(kq,&S);
						break;	
					case '%':
						a = (float)top(S);
						pop(&S);
						b = (float)top(S);
						pop(&S);
						kq=(int)b%(int)a;
						push((float)kq,&S);
						break;
				}
			}
		}
	}
	result = kq;
	return result;
}

int value(char c)
{
	if(c == '+' || c == '-')
	{
		return 1;
	}
	else if (c == '*' || c == '/' || c == '%')
	{
		return 2;
	}
	else if (c == '(' || c == ')')
	{
		return 0;
	}
}

void trungtosanghauto(char s[])// chuyen chuoi tu trung to sang hau to /can chuyen doi ElementType sang kieu char
{
	Stack S;
	makenullStack(&S);
	char result[MaxLength];
	char c;
	int i, n, j=0;
	n = strlen(s);
	for(i=0; i<n; i++)
	{
		c=s[i];
		if(c == '(')
		{
			push(c,&S);
		} 
		else if (c >= '0' && c <='9')
		{
			result[j]=c;
			j++;
		}
		else if(c == ')')
		{
			while(S.Elements[S.Top_idx] != '(')
			{
				result[j]=S.Elements[S.Top_idx];
				j++;
				pop(&S);
			}
			pop(&S);
		}
		else if( c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
		{
			if(emptyStack(S) == 0)
			{
				while(value(c) <= value(S.Elements[S.Top_idx]) && emptyStack(S) == 0)
				{
					result[j]=S.Elements[S.Top_idx];
					j++;
					pop(&S);
				}
				push(c,&S);
			}
			else 
			{
				push(c,&S);
			}
		}
	}
	while(emptyStack(S) != 1)
	{
		result[j]=S.Elements[S.Top_idx];
		j++;
		pop(&S);
	}
	for(i=0;i<j;i++)
	{
		printf("%c ",result[i]);
	}
	//tinh gia tri cua bieu thuc hau to
	float kq;
	kq = Suffixes(result);
	printf("\n%.2f",kq);
}
//(7+5)*(8-4)/5
//(7% (6-3) + 4*(5+9))/ (8-6*3 +2)
//(7%(6-3)+4*(5+9))/(8-6*3+2)
//763-%459+*+863*-2+/
int main()
{
	char s[MaxLength];
	char result[MaxLength];
	fgets(s,sizeof(s),stdin);
	float kq;
	kq = Suffixes(s);
	printf("%f",kq);
	return 0;
}
