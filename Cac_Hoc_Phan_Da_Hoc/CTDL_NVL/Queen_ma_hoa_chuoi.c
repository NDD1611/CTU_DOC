#include <stdio.h>
#include <string.h>

int main ()
{
	char s1[10000],s2[10000];
	int number[1000];
	int n1,n2,i,num=0;
	fgets(s1,sizeof(s1),stdin);
	n1=strlen(s1);
	if(s1[n1-1] == '\n')
	{
		s1[n1-1]='\0';
		n1--;
	}
	fgets(s2,sizeof(s2),stdin);
	n2=strlen(s2);
	if(s2[n2-1] == '\n')
	{
		s2[n2-1]='\0';
		n2--;
	}
	for(i=0;i<n2;i++)
	{
		number[num] = s2[i] - '0';
		num++;
	}
	int j=0;
	for(i=0;i<n1;i++)
	{
		if(j == num)
		{
			j=0;
		}
		s1[i]=s1[i]+number[j];
		j++;
	}
	printf("%s",s1);
	return 0;
}
