#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100
#define ITERATION 100

void process(int, int);

int grid[SIZE][SIZE];
int grid2[SIZE][SIZE];

void main()
{
    int len;
    char line[SIZE+2];
    int k=0;
    while(fgets(line,SIZE+2,stdin)!=NULL)
    {
        len=strlen(line);
        if(line<2) continue;
        for(int i=0;i<len;i++)
        {
            if(line[i]=='#')
                grid[k][i]=1;
            if(line[i]=='.')
                grid[k][i]=0;
        }
        
        k++;
    }
    

    int iterate=ITERATION;
    while(iterate--)
    {
        for(int i=0;i<SIZE;i++)
            for(int j=0;j<SIZE;j++)
                process(i,j);
        
        for(int i=0;i<SIZE;i++)
            for(int j=0;j<SIZE;j++)   
                grid[i][j] = grid2[i][j];
       

    }
   
    int count=0;
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            if(grid[i][j])
                count++;
    printf("%d\n",count);
    
    
    
    return;   
}


void process(int a, int b)
{
    int count=0;
    
    if(a==0 || b==0 || a==SIZE-1 || b==SIZE-1)
    {
        if(a==0 && b==0)
            count=grid[0][1]+grid[1][0]+grid[1][1];
        else if(a==0 && b==SIZE-1)
            count=grid[0][SIZE-2]+grid[1][SIZE-1]+grid[1][SIZE-2];
        else if(a==SIZE-1 && b==0)
            count=grid[SIZE-2][0]+grid[SIZE-1][1]+grid[SIZE-1][1];
        else if(a==SIZE-1 && b==SIZE-1)
            count=grid[SIZE-2][SIZE-1]+grid[SIZE-1][SIZE-2]+grid[SIZE-2][SIZE-2];
        
        else if(a==0)
        {
            for(int i=b-1;i<b+2;i++)
                if(grid[1][i])
                    count++;
            count += grid[0][b-1]+grid[0][b+1];
        }
        
        else if(b==0)
        {
            for(int i=a-1;i<a+2;i++)
                if(grid[i][1])
                    count++;
            count += grid[a-1][0]+grid[a+1][0];
        }
        
        else if(a==SIZE-1)
        {
            for(int i=b-1;i<b+2;i++)
                if(grid[a-1][i])
                    count++;
            count += grid[a][b-1]+grid[a][b+1];
        }
        
        else if(b==SIZE-1)
        {
            for(int i=a-1;i<a+2;i++)
                if(grid[i][b-1])
                    count++;
            count += grid[a-1][b]+grid[a+1][b];
        }
    
    }
    else
    {
        for(int i=a-1;i<a+2;i++)
            for(int j=b-1;j<b+2;j++)
                if(grid[i][j] && !(i==a && j==b))
                    count++;
    }                    
    
                        
    if(grid[a][b])
    {
        if(count == 2 || count == 3)
            grid2[a][b]=1;
        else
            grid2[a][b]=0;
    }
    else
    {
        if(count == 3)
            grid2[a][b]=1;
        else
            grid2[a][b]=0;        
    }
    
    return;
}
            
            
