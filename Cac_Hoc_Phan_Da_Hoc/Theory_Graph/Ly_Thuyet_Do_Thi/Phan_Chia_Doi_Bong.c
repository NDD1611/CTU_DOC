#include <stdio.h>
#define sz 50
typedef struct{
	int u, v;
}cung;

int main(){
	
	cung A[sz];
	int n, m;
	scanf("%d%d", &n, &m);
	int i;
	for(i=0; i<m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		A[i].u=u;
		A[i].v=v;
	}
	
	int nhom[sz];
	for(i=1; i<=n; i++){
		nhom[i]=0;
	}
	
	int kt=1;
	for(i=0; i<m; i++){
		int u, v; 
		u=A[i].u;
		v=A[i].v;
		if(nhom[u]==0 && nhom[v]==0){
			nhom[u]=1;
			nhom[v]=2;
		} else if(nhom[u]==1 && nhom[v]==0){
			nhom[v]=2;
		} else if(nhom[u]==2 && nhom[v]==0){
			nhom[v]=1;
		} else if(nhom[u]==nhom[v]){
			kt=0;
		}
	}
	
	if(kt==0){
		printf("IMPOSSIBLE");
	} else {
		for(i=1; i<=n; i++){
			if(nhom[i]==1){
				printf("%d ", i);
			}
		}
		printf("\n");
		for(i=1; i<=n; i++){
			if(nhom[i]==2){
				printf("%d ", i);
			}
		}
	}
	
	return 0;
}
