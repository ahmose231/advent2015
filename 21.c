#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define LEN 128
#define WLEN 16

void parse_line(char *line,  char **token);
int fightboss(int mydmg, int myarmor);

struct proto_boss {
    int hp;
    int damage;
    int armor;
} boss;


void main()
{
    
    boss.hp=104;
    boss.damage=8;
    boss.armor=1;
    
    struct item {
        char name[WLEN];
        int cost;
        int damage;
        int armor;
    } weapon[5], armor[6], ring[8];
    
    strcpy(armor[0].name, "empty");
    armor[0].cost=0;
    armor[0].damage=0;
    armor[0].armor=0;
    
    for(int i=0;i<2;i++)
    {
        strcpy(ring[i].name, "empty");
        ring[i].cost=0;
        ring[i].damage=0;
        ring[i].armor=0;
    }
    
    int len;
    char line[LEN];
    char **token;
    token=malloc(sizeof(char*)*4);
    for(int i=0;i<4;i++)
        token[i]=malloc(WLEN);
        
    while(fgets(line,LEN,stdin)!=NULL)
    {
        for(int i=0;i<5;i++)
        {
            fgets(line,LEN,stdin);
            parse_line(line, token);

            strcpy(weapon[i].name, token[0]);
            weapon[i].cost  =   atoi(token[1]);
            weapon[i].damage=   atoi(token[2]);
            weapon[i].armor =   atoi(token[3]);
            
        }
        
        fgets(line,LEN,stdin);
        fgets(line,LEN,stdin);

        for(int i=1;i<6;i++)
        {
            fgets(line,LEN,stdin);
            parse_line(line, token);

            strcpy(armor[i].name, token[0]);
            armor[i].cost   =   atoi(token[1]);
            armor[i].damage =   atoi(token[2]);
            armor[i].armor  =   atoi(token[3]);
            
        }
        
        fgets(line,LEN,stdin);
        fgets(line,LEN,stdin);

        for(int i=2;i<8;i++)
        {
            fgets(line,LEN,stdin);
            parse_line(line, token);

            strcpy(ring[i].name, token[0]);
            ring[i].cost    =   atoi(token[1]);
            ring[i].damage  =   atoi(token[2]);
            ring[i].armor   =   atoi(token[3]);
            
            
        }    
    }
    

    int myarmor;
    int mydmg; 
    int gold;
    int mingold=INT_MAX;
    for(int w=0;w<5;w++)
    {

        for(int a=0;a<6;a++)
        {

            for(int r=0;r<8;r++)
            {
                mydmg = weapon[w].damage + ring[r].damage;
                myarmor = armor[a].armor + ring[r].armor;
                gold = weapon[w].cost + armor[a].cost + ring[r].cost;
                
                if(fightboss(mydmg, myarmor))
                    if(mingold>gold)
                        mingold=gold;
                        
                
            }
        }
    }
    
    printf("%d\n",mingold);
                                    
    return;
}

int fightboss(int mydmg, int myarmor)
{
    int myhp=100;
    int bosshp=boss.hp;
    int bossdmg=boss.damage;
    int bossarmor=boss.armor;

    while(1)
    {
        if(mydmg<=bossarmor)
            bosshp--;
        else
            bosshp -= mydmg-bossarmor;
        
        if(bosshp<=0)
            return 1;
            
        if(bossdmg<=myarmor)
            myhp--;
        else
            myhp -= bossdmg-myarmor;

        if(myhp<=0)
            return 0;
    }
    
    return 0;
}

void parse_line(char *line,  char **token)
{
    char word[WLEN];
    int l=0;
    int w;
    for(int i=0;i<3;i++)
    {
        w=0;
        while(line[l]!=' ')
            word[w++]=line[l++];
        word[w]='\0';
        strcpy(token[i], word);

        while(line[l]==' ')
            l++;
    }
    

    w=0;
    while(line[l]!='\n' && line[l]!=EOF)
        word[w++]=line[l++];
    word[w]='\0';
    strcpy(token[3], word);
    
    return;
}
