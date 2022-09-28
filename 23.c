#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 32


int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("need filename as parameter\n");
		return 0;
	}
	FILE *fp;
	fp=fopen(argv[1],"r");

	int linecount=0;
	char *line=malloc(LEN);
	int len;

	while(fgets(line,LEN,fp)!=NULL)
	{
		if(strlen(line)<2) continue;
		linecount++;
	}

	char lines[linecount][LEN];

	int k=0;
	rewind(fp);

	while(fgets(line,LEN,fp)!=NULL)
	{
		len=strlen(line);
		if(len<2) continue;
		if(line[len-1]=='\n' || line[len-1]==EOF)
			line[len-1]='\0';
		strcpy(lines[k++], line);
	}

	fclose(fp);


	int index=0;
	char *instruction;
	char *rest;
	int myregs[2]={0,0};
	int sign;
	int value;
	
	while(index>=0 && index<linecount)
	{
		strcpy(line, lines[index]);
		instruction=strtok(line, " ");
		rest=strtok(NULL, " ");
		
		if(strcmp(instruction, "hlf")==0)
			myregs[rest[0]-'a'] /= 2;
		
		
		if(strcmp(instruction, "tpl")==0)
			myregs[rest[0]-'a'] *= 3;

		if(strcmp(instruction, "inc")==0)
			myregs[rest[0]-'a'] += 1;
		
		if(strcmp(instruction, "jmp")==0)
		{
			sign=rest[0];
			rest[0]='0';
			value=atoi(rest);
			
			if(sign=='-')
				index=index-value;
			else
				index=index+value;
			
			index--;
		}
		
		if(strcmp(instruction, "jie")==0)
		{	
			if(myregs[rest[0]-'a'] % 2 == 0)
			{		
				sign=rest[3];
				rest[0]=rest[1]=rest[2]=rest[3]='0';
				value=atoi(rest);
				
				if(sign=='-')
					index=index-value;
				else
					index=index+value;
				
				index--;			
			}
		}				
		
		if(strcmp(instruction, "jio")==0)
		{	
			if(myregs[rest[0]-'a'] == 1)
			{		
				sign=rest[3];
				rest[0]=rest[1]=rest[2]=rest[3]='0';
				value=atoi(rest);
				
				if(sign=='-')
					index=index-value;
				else
					index=index+value;
				
				index--;	
			}				
		}	
		
		
		index++;
	}
	

	printf("%d\n", myregs[1]);

	return 0;

}
