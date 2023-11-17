#include <stdio.h>
#include <string.h>

int main ()
{
	char s[100],s1[100];
	int n,i,j=0;
	fgets(s,sizeof(s),stdin);
	n=strlen(s);
	if(s[n-1] == '\n')
	{
		n--;
		s[n]='\0';
	}
	for(i=0;i<n;i++)
	{
		if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
		{
			s1[j]=s[i];
			if(s1[j] >= 'A' && s1[j] <= 'Z')
			{
				s1[j] = s1[j]+32;
			}
			j++;
		}
	}
	n=j/2;
	int kt=1;
	for(i=0;i<n;i++)
	{
		if(s1[i] != s1[j-i-1])
		{
			kt=0;
		}
	}
	if(kt == 1)
	{
		printf("\"%s\" doc xuoi va doc nguoc nhu nhau",s);
	}
	else 
	{
		printf("\"%s\" doc xuoi khac doc nguoc",s);
	}
	return 0;
}
