#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 512000
#define REPEAT 40

void main(int argc, char *argv[])
{
    char line1[LEN];
    char line2[LEN];
    
    if(argc!=2) return;
    strcpy(line1, argv[1]);
    int k;
    int len;
    int count;
    int t=0;
    for(int i=0;i<REPEAT;i++)
    {
        k=0;
        len=strlen(line1);
        for(int j=0; j<len; j=j+count)
        {
            count=0;
 
            for(int m=j;m<len;m++)
                if(line1[j]==line1[m])
                    count++;
                else
                    break;
                    
            line2[k++]=count+'0';
            line2[k++]=line1[j];
        }
        line2[k]='\0';
        printf("%d: %d\n",++t,strlen(line2));
        strcpy(line1,line2);
     }
     
     return;
}
     
