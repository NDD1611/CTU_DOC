#include<stdio.h>
#include<string.h>

#define MaxLength 100

typedef char ElementType;
typedef struct{
	ElementType Elements[MaxLength];
	int Top_idx;
}Stack;

void makenullStack(Stack *pS){
	pS->Top_idx=MaxLength;
}

int emptyStack(Stack S){
	return S.Top_idx==MaxLength;
}

int full(Stack S){
	return S.Top_idx==0;
}

ElementType top(Stack S){
	if(!emptyStack(S))
		return S.Elements[S.Top_idx];
	else printf("Loi! Ngan xep rong");
}

void pop(Stack *pS){
	if(!emptyStack(*pS))
		pS->Top_idx=pS->Top_idx+1;
	else printf("Loi! Ngan xep rong");
}

void push(ElementType x, Stack *pS){
	if(full(*pS))
		printf("Loi! Ngan xep day");
	else{
		pS->Top_idx=pS->Top_idx-1;
		pS->Elements[pS->Top_idx]=x;
	}
}

int mucUutien(char op){
   if (op=='+' || op=='-')
       return 1;
   else if (op=='*' || op=='/')
       return 2;
}

char* chuyenHauto(char A[], char B[]){
	int i, j = 0;
	Stack S;
	makenullStack(&S);
	for(i = 0; i < strlen(A); i++){
		if( ((A[i] >= '0') && (A[i] <= '9')) || ((A[i] >= 'a') && (A[i] <= 'z')) ){
			B[j] = A[i];
			j++;
		}
		else if(A[i] == '('){
			push(A[i], &S);
		}
		else if(A[i] == ')'){
			while(top(S) != '('){
				B[j] = top(S);
				pop(&S);
				j++;
			}
			pop(&S);
		}
		else if( (A[i]=='-') || (A[i]=='+') || (A[i]=='*') || (A[i]=='/') ){
			if(!emptyStack(S)){
				if(mucUutien(A[i])<=mucUutien(top(S))){
					while( (!emptyStack(S)) && (top(S) != '(') ){
						B[j] = top(S);
						j++;
						pop(&S);
					}
					push(A[i], &S);
				}
				else if(mucUutien(A[i]) > mucUutien(top(S)))
					push(A[i], &S);
			}
			else push(A[i], &S);
		}
	}
	while(!emptyStack(S)){
		B[j]=top(S);
		pop(&S);
		j++;
	}
	return B;
}

int main(){
	char trungto[30],hauto[30];
	fgets(trungto,30,stdin);
	if(trungto[strlen(trungto)-1]=='\n'){
    	trungto[strlen(trungto)-1]='\0';
	}
	chuyenHauto(trungto,hauto);
	puts(hauto);
}


