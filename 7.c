#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 32
#define NAMELEN 8

struct node {
    char name[NAMELEN];
    int value;
    struct node* next;
} *root;

int all_numbers(char *token);
void create(char *token);
int get_value(char *token);
void int_assign(char *token, int n);
int do_operation(char *token1, char *token2, char *operation);

void main()
{
    root=malloc(sizeof(struct node));
    root->next=NULL;
    char line[LEN];
    char *token;
    while(fgets(line,LEN,stdin)!=NULL)
    {
        token=strtok(line," ");
        
        if(strcmp(token,"NOT")==0)
        {
            token=strtok(NULL," ");

            char *token2;
            token2=strtok(NULL," ");    // ->
            token2=strtok(NULL," ");

            create(token);
            create(token2);

            int_assign(token, ~get_value(token2));
        }
        
        else
        {
            char *token2, *token3;
            char *operation;
            
            operation=strtok(NULL," ");
            token2=strtok(NULL," ");

            token3=strtok(NULL," ");    // ->
            token3=strtok(NULL," ");
            
            create(token);
            create(token2);
            create(token3);
            
            int_assign(token3, do_operation(token, token2, operation));
        }
        
    }
    
    printf("%d\n",get_value("a"));
    return;
}

    

void create(char *token)
{
    int found=0;
    struct node* temp=root->next;
    while(temp!=NULL)
    {
        if(strcmp(token,temp->name)==0)
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
    temp->next=NULL;
    strcpy(temp->name,token);
    temp->value=0;
    
    return;
}

int all_numbers(char *token)
{
    int len=strlen(token);
    for(int i=0;i<len;i++)
        if(!(token[i]>='0'&&token[i]<='9'))
            return 0;
    
    return 1;
}

void int_assign(char *token, int n)
{
    struct node* temp=root->next;
    while(temp!=NULL)
    {
        if(strcmp(token,temp->name)==0)
        {   
            temp->value=n;
            break;
        }
        
        temp=temp->next;
    }
    
    return;
}


int get_value(char *token)
{
    if(all_numbers(token))
        return atoi(token);
    struct node* temp=root->next;
    while(temp!=NULL)
    {
        if(strcmp(token,temp->name)==0)
            return temp->value;
        
        temp=temp->next;
    }
    
    return 0;
}


int do_operation(char *token1, char *token2, char *operation)
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

