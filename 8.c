#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 128

void main()
{
    char line[LEN];
    int len;
    int sum=0;
    int k;
    while(fgets(line,LEN,stdin)!=NULL)
    {
        len=strlen(line);
        if(len<2) continue;
        if(line[len-1]=='\n' || line[len-1]==EOF)
        {
            line[len-1]='\0';
            len--;
        }
        k=-2;
        for(int i=0;i<len;i++)
        {
            k++;
            if(line[i]=='\\')
            {
                if(line[i+1]=='x')
                    i=i+3;
                else
                    i++;
            }
        }

        sum += len - k;
    }
    
    printf("%d\n",sum);
    return;
}
                    
            
    
    
    
    
    
