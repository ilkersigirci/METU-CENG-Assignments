#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void int2String(char str[], int number)
{
    int i = 0, length = 0, n = number, index =  0, tempNum, tempChar;
    while (n != 0)
    {
        n /= 10;
        length++;
    }
    for (i = 0; i < length; i++)
    {
        tempNum = number % 10;
        tempChar = tempNum + '0';
        index = length - (i + 1);
        str[index] = tempChar;
        number /= 10;
    }
    str[length] = '\0';
}


int main(int argc, char *argv[]){

    int n; // to keep track of num bytes read
    char buffer[2]; // buffer to hold text read/written
    int N = atoi(argv[1]);
    int i,j,c,line = 0,whichMapper;
    int pm[N][2],mr[N][2],rr[N-1][2];
    int ppid = getpid(),pid;
    int mapper[N];
    char str[2];
    char *mapperID[N],*reducerID[N];
    
    if(argc == 3)    // Mapper Model
    {
        for(i =0;i<N;i++)
        {
            if (pipe(pm[i]) < 0) perror("pipe error\n");
        }

        for(i =0;i<N;i++)
        {
            if ((pid = fork()) < 0)  perror("fork error\n");
            
            else if(pid > 0) continue; // parent

            else // child_i
            {
                mapper[i] = getpid();
                int2String(str, i);
                mapperID[i] = str;
                dup2(pm[i][0], 0);
                for(j=0;j<N;j++) // close all except pm[i][0]
                {
                    //if(j != i ) 
                    close(pm[j][0]);
                    close(pm[j][1]);
                }
                execl(argv[2],argv[2],mapperID[i],(char *)0);
            }
            
        }

        if (ppid == getpid()) //parent
        {
            for(j =0;j<N;j++) close(pm[j][0]); // close all reads of parent

            while(read(0, buffer, 1))
            {
                //printf("%c",buffer[0]);
                if(buffer[0] == '\n') 
                {
                    whichMapper = (line%N);                
                    write(pm[whichMapper][1], buffer, 1);
                    line++;
                    continue;
                }
                whichMapper = (line%N);                
                write(pm[whichMapper][1], buffer, 1);
                
            }
            for(j =0;j<N;j++) close(pm[j][1]); // close all writes of parent
            for(j =0;j<N;j++)
            {
                wait(&c);
            }
        }
    }

    else if(argc == 4) // MapReduce Model
    {
        for(i =0;i<N;i++) // pipes
        {
            if (pipe(pm[i]) < 0) perror("pipe error\n");
            if (pipe(mr[i]) < 0) perror("pipe error\n");
            if(i == N-1) continue;
            if (pipe(rr[i]) < 0) perror("pipe error\n");
        }
        for(i =0;i<N;i++) // mapper
        {
            if ((pid = fork()) < 0)  perror("fork error\n");
            
            else if(pid > 0) continue; // parent

            else // mapper_i
            {
                int2String(str, i);
                mapperID[i] = str;
                dup2(pm[i][0], 0);
                dup2(mr[i][1],1);
                for(j=0;j<N;j++) // close all read and write ends of mapper
                {
                    close(pm[j][0]);close(pm[j][1]);
                    close(mr[j][0]);close(mr[j][1]);
                    if(j == N-1) continue;
                    close(rr[j][0]);close(rr[j][1]);
                }
                execl(argv[2],argv[2],mapperID[i],(char *)0);
            }
            
        }
        if (ppid == getpid()) // Only parent create reducer
        {
            for(i = 0;i < N;i++) // reducer
            {
                if ((pid = fork()) < 0)  perror("fork error\n");
                
                else if(pid > 0) continue; // parent

                else // reducer_i
                {
                    int2String(str, i);
                    reducerID[i] = str;
                    dup2(mr[i][0], 0);

                    if(i == 0) dup2(rr[i][1], 1);  //first reducer

                    else if(i == N-1)  dup2(rr[i-1][0],2); //last reducer

                    else  // other reducer
                    {   
                        dup2(rr[i][1], 1);
                        dup2(rr[i-1][0],2);                        
                    }
                    for(j=0;j<N;j++) 
                    {
                        close(pm[j][0]);close(pm[j][1]);
                        close(mr[j][0]);close(mr[j][1]);
                        if(j == N-1) continue;
                        close(rr[j][0]);close(rr[j][1]);
                    }
                    execl(argv[3],argv[3],reducerID[i],(char *)0);
                }
                
            }
        }
        if (ppid == getpid()) //parent
        {
            while(read(0, buffer, 1))
            {
                if(buffer[0] == '\n') 
                {
                    whichMapper = (line%N);                
                    write(pm[whichMapper][1], buffer, 1);
                    line++;
                    continue;
                }
                whichMapper = (line%N);                
                write(pm[whichMapper][1], buffer, 1);
                
            }
            for(j =0;j<N;j++) 
            {
                close(pm[j][0]);close(pm[j][1]); // close all writes of parent
                close(mr[j][0]);close(mr[j][1]);
                if(j == N-1) continue;
                close(rr[j][0]);close(rr[j][1]);

            }
            for(j =0;j<3*N-1;j++) wait(&c);
        }    
    }
    else;    
    exit(0);
}