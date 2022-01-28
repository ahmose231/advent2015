#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 128
#define WORDLEN 16

void main(int argc, char *argv[])
{
    if(argc!=3)
    {
        printf("usage: %s <suelist> <mycard>\n",argv[0]);
        exit(0);
    }
    FILE *suelist;
    FILE *mycard;

    char line[LEN];
    char linecount=0;
    mycard=fopen(argv[2],"r");
    while(fgets(line,LEN,mycard)!=NULL)
    {
        if(strlen(line)<2) continue;
        linecount++;
    }

    struct proto_mycard {
        char name[WORDLEN];
        int value;
    } card[linecount];

    int k=0;
    char *token;
    rewind(mycard);
    while(fgets(line,LEN,mycard)!=NULL)
    {
        if(strlen(line)<2) continue;
        token=strtok(line," ");
        strcpy(card[k].name, token);
        
        token=strtok(NULL," ");
        card[k].value=atoi(token);
        k++;
    }

    fclose(mycard);
    suelist=fopen(argv[1],"r");
    int suenumber;
    int match;
    int n;
    char word[WORDLEN];
    while(fgets(line,LEN,suelist)!=NULL)
    {
        token=strtok(line," "); //"sue"
        token=strtok(NULL," "); //number:
        suenumber=atoi(token);
        
        match=1;
        
        token=(strtok(NULL," "));
        strcpy(word, token);
        token=(strtok(NULL," "));
        n=atoi(token);
        
        for(int i=0;i<linecount;i++)
            if(strcmp(word, card[i].name)==0)
            {
                if(strcmp(word,"cat:")==0 || strcmp(word,"trees:")==0)
                {
                    if(n <= card[i].value)
                        match=0;
                }
                
                else if(strcmp(word,"pomeranians:")==0 || strcmp(word,"goldfish:")==0)
                {
                    if(n >= card[i].value)
                        match=0;
                }               
                else if(n != card[i].value)
                    match=0;
            }
            
        token=(strtok(NULL," "));
        strcpy(word, token);
        token=(strtok(NULL," "));
        n=atoi(token);
        
        for(int i=0;i<linecount;i++)
            if(strcmp(word, card[i].name)==0)
            {
                if(strcmp(word,"cat:")==0 || strcmp(word,"trees:")==0)
                {
                    if(n <= card[i].value)
                        match=0;
                }
                
                else if(strcmp(word,"pomeranians:")==0 || strcmp(word,"goldfish:")==0)
                {
                    if(n >= card[i].value)
                        match=0;
                }               
                else if(n != card[i].value)
                    match=0;
            }
            
                    
        token=(strtok(NULL," "));
        strcpy(word, token);
        token=(strtok(NULL," "));
        n=atoi(token);

        for(int i=0;i<linecount;i++)
            if(strcmp(word, card[i].name)==0)
            {
                if(strcmp(word,"cat:")==0 || strcmp(word,"trees:")==0)
                {
                    if(n <= card[i].value)
                        match=0;
                }
                
                else if(strcmp(word,"pomeranians:")==0 || strcmp(word,"goldfish:")==0)
                {
                    if(n >= card[i].value)
                        match=0;
                }               
                else if(n != card[i].value)
                    match=0;
            }
            
        
                                                          
        if(match)
        {
            printf("%d\n",suenumber);
            break;
        }
    }
    
    fclose(suelist);
    
    return;
}

