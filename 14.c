#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 128
#define TIME 2503

void main(int argc, char *argv[])
{
	if(argc!=2) return;
	char line[LEN];
	FILE* fp=fopen(argv[1],"r");
	if(fp==NULL) return;
	int linecount=0;
	while(fgets(line,LEN,fp)!=NULL)
	{
		if(strlen(line)<2) continue;
		linecount++;
	}
	rewind(fp);
	
	int distance[linecount];
	int speed[linecount];
	int seconds[linecount];
	int rest[linecount];
	int k=0;
	char name[16];
	while(fgets(line,LEN,fp)!=NULL)
	{
		sscanf(line,"%s can fly %d km/s for %d seconds, but then must rest for %d seconds.",
				&name[0],&speed[k], &seconds[k], &rest[k]);
		k++;
	}
	
	fclose(fp);
	
	
	int counter;
	int state;	// 1 for motion, 0 for rest
	for(int i=0;i<linecount;i++)
	{	
		distance[i]=0;
		state=1;
		counter=0;
		for(int t=0;t<TIME;t++)
		{
			if(state)
			{
				counter++;
				distance[i]+=speed[i];
				if(counter==seconds[i])
				{
					state=0;
					counter=0;
				}
			}
			else
			{
				counter++;
				if(counter==rest[i])
				{
					state=1;
					counter=0;
				}				
			}
		}
	}

	int max=0;
	for(int i=0;i<linecount;i++)
		if(max<distance[i])
			max=distance[i];
		
	printf("%d\n",max);
	
	return;
}
		
