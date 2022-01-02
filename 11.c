#include <stdio.h>
#include <stdlib.h>

void increment(char *line)
{
	int rem=0;
	line[7]++;
	for(int i=7;i>=0;i--)
	{
		if(rem)
		{
			line[i]++;
			rem=0;
		}

		if(line[i]>'z')
		{
			line[i]='a';
			rem=1;
		}
	}

	return;
}

int pass_criteria(char *line)
{
	// criteria 1
	for(int i=0;i<8;i++)
		if(line[i]=='i' || line[i]=='l' || line[i]=='o')
			return 0;
	
	//criteria 2
	int count=0;
	int m[8];
	for(int i=0;i<8-1;i++)
	    if(line[i]==line[i+1])
	    {
	        m[count]=line[i];
	        count++;
	    }
	 
	 int flag=0;
	 if(count<2) return 0;
	 for(int i=0;i<count-1;i++)
	    for(int j=1;j<count;j++)
	        if(m[i]!=m[j])
	            flag=1;
    if(!flag) return 0;
	
	
	//criteria 3
	flag=0;
	for(int i=0;i<8-2;i++)
		if(line[i+1]==line[i]+1 && line[i+2]==line[i]+2)
		{
		    flag=1;
		    break;
		}
	
	if(!flag) return 0;

	return 1;
}



int main() {
	// Your code goes here
	char *line=malloc(9);
	fgets(line,9,stdin);
	line[8]='\0';

	increment(line);
	while(!pass_criteria(line))
		increment(line);

	printf("%s\n",line);

	return 0;
}
