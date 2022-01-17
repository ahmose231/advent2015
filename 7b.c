#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define LINELEN 32
#define NAMELEN 8
#define LINECOUNT 512


struct node {
    int init;
    char *name;
    unsigned short int value;
    struct node* next;
} *root, *temp;


void reset_all();
int all_lines_processed(int *p, int k);
int initialized(char *token);
int process_line(char *original_line);
int all_numbers(char *token);
void create(char *token);
unsigned short int get_value(char *token);
void int_assign(char *token, unsigned short int n);
unsigned short int do_operation(char *token1, char *token2, char *operation);





void main()
{
    root=malloc(sizeof(struct node));
    root->next=NULL;

    char line[LINELEN];
    char input[LINECOUNT][LINELEN];
    int k=0;

    while(fgets(line,LINELEN,stdin)!=NULL)
    {
        if(line[strlen(line)-1]=='\n' || line[strlen(line)-1]==EOF)
            line[strlen(line)-1]='\0';
        if(strlen(line)<2) continue;
        strcpy(input[k++],line);
    }
    
    int *processed=malloc(sizeof(int)*k);
    
    for(int i=0;i<k;i++)
        processed[i]=0;
        
    while(!all_lines_processed(processed, k))
        for(int i=0;i<k;i++)
            if(!processed[i])
                processed[i]=process_line(input[i]);
    
    
    // part 2

    
    int a=get_value("a");
    
    reset_all();
    
    for(int i=0;i<k;i++)
        processed[i]=0;
    
    
    int_assign("b", a);
    
    for(int i=0;i<k;i++)
        if(input[i][strlen(input[i])-1]=='b' && input[i][strlen(input[i])-2]==' ')
        {
            processed[i]=1;
            break;
        }
        
    while(!all_lines_processed(processed, k))
        for(int i=0;i<k;i++)
            if(!processed[i])
                processed[i]=process_line(input[i]);
    
    printf("%hu\n",get_value("a"));
    
    return;
}

void reset_all()
{
    temp=root->next;
    while(temp!=NULL)
    {
        //temp->value=0;
        temp->init=0;
    
        temp=temp->next;
    }
    
    return;
}

int all_lines_processed(int *p, int k)
{
    for(int i=0;i<k;i++)
        if(!p[i])
            return 0;
    return 1;
}
    
    
int process_line(char *original_line)
{
    char *line=malloc(LINELEN);
    strcpy(line, original_line);
    
    char *token, *token2, *token3, *operation;
    int processed=0;
    token=strtok(line," ");
    
    if(strcmp(token,"NOT")==0)
    {
        token=strtok(NULL," ");

        token2=strtok(NULL," ");    // ->
        token2=strtok(NULL," ");

        create(token);
        create(token2);
        if(initialized(token))
        {
            int_assign(token2, ~(get_value(token)));
            processed=1;
        }
    }
    
    else
    {
        
        operation=strtok(NULL," ");
        token2=strtok(NULL," ");
        if(strcmp(operation,"->")==0)
        {
            create(token2);
            if(initialized(token))
            {
                int_assign(token2, get_value(token));
                processed=1;
            }
            return processed;
        }
         

        token3=strtok(NULL," ");    // ->
        token3=strtok(NULL," ");
       
        create(token);
        create(token2);
        create(token3);
        if(initialized(token) && initialized(token2))
        {
            int_assign(token3, do_operation(token, token2, operation));
            processed=1;
        }
    }
    
    free(line);
    return processed;
}


int initialized(char *token)
{
    if(all_numbers(token)) return 1;

    temp=root->next;
    while(temp!=NULL)
    {
        if(strcmp(temp->name, token)==0)
            return temp->init;
        temp=temp->next;
    }
    
    return 0;
}



void create(char *token)
{
    if(all_numbers(token)) return;

    int found=0;
    temp=root->next;

    while(temp!=NULL)
    {
        if(strcmp(token, temp->name)==0)
        {   
            found=1;
            break;
        }
        
        temp=temp->next;
    }
    
    if(found) return;
    
    temp=root;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=malloc(sizeof(struct node));
    temp=temp->next;
    temp->name=malloc(NAMELEN);
    temp->next=NULL;
    temp->init = 0;
    strcpy(temp->name,token);
    temp->value=0;
    
    return;
}


int all_numbers(char *token)
{
    unsigned short int len=strlen(token);
    for(unsigned short int i=0;i<len;i++)
        if(!(token[i]>='0'&&token[i]<='9'))
            return 0;
    
    return 1;
}

void int_assign(char *token, unsigned short int n)
{
    temp=root->next;
    while(temp!=NULL)
    {
        if(strcmp(token,temp->name)==0)
        {   
            temp->value=n;
            temp->init=1;
            break;
        }
        
        temp=temp->next;
    }
    
    return;
}


unsigned short int get_value(char *token)
{
    if(all_numbers(token))
        return atoi(token);
    temp=root->next;
    while(temp!=NULL)
    {
        if(strcmp(token,temp->name)==0)
            return temp->value;
        
        temp=temp->next;
    }
    
    return 0;
}


unsigned short int do_operation(char *token1, char *token2, char *operation)
{

    if(strcmp(operation,"AND")==0)
        return get_value(token1) & get_value(token2);
        
    if(strcmp(operation,"OR")==0)
        return get_value(token1) | get_value(token2);
    
    if(strcmp(operation,"LSHIFT")==0)
        return get_value(token1) << atoi(token2);
    
    if(strcmp(operation,"RSHIFT")==0)
        return get_value(token1) >> atoi(token2);
    
    return 0;
}

