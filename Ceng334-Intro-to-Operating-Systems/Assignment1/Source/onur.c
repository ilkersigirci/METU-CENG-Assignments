/* parent master -> child slave (bc -q, a simple calculator)
   two pipes one for parent to child, other from child to parent
   parent -> 3+4, 5*6 * ... child bc -q results -> parent
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    int forkCount = atoi(argv[1]);
    int mapIndex;
    int redIndex;
    int lineCount = 0;
	int mmfd[forkCount][2];  
    int ret =1;
    int i;
	int flag =0 ;// 0 parent 1 mapper 2 reducer
	
	
    

    if (argv[3] == NULL) {
       for(i = 0; i < forkCount; i++)
	{
		pipe(mmfd[i]);

	}
        for( i = 0; (i < forkCount) && ret; i++)
        {
			
			ret = fork();
            mapIndex = i;
			

        }
		if (ret) {
			printf("parent\n");
				for(int j = 0; j < forkCount; j++)
				{
					
					close(mmfd[j][0]);
					
				}

				char buffer[1024];
				//printf("a\n");
				//buffer[0] = read(0,buffer,1);
				//printf("a\n");
				i = 0;
    			while(fgets(buffer,1024,stdin))
    			{
					//printf("b\n");
					//printf("%s\n", buffer);
					write(mmfd[i%forkCount][1],buffer,strlen(buffer));
					i++;

        			
    			}

				for(int j = 0; j < forkCount; j++)
				{
					
					close(mmfd[j][1]);
					
				}
				for(i = 0;i < forkCount;i++)
				{
					wait(NULL);
				}
			}
			else
			{
				printf("%d\n", mapIndex);
				for(int j = 0; j < forkCount; j++)
				{
					if (mapIndex!=j) {
						close(mmfd[j][0]);
					}
					close(mmfd[j][1]);
				}
  				char mapstr[10];
  				sprintf(mapstr, "%d", mapIndex);
				dup2(mmfd[mapIndex][0],0);
				close(mmfd[mapIndex][0]);//string mapind
				execl(argv[2],argv[2],mapstr,(char *)0);
				
			}
		
    
	
	}
	else // mapreduce model
	{
		int mrfd[forkCount][2];
		int rrfd[forkCount-1][2];
		for(i = 0; i < forkCount; i++)//pipe olustur
		{
			pipe(mmfd[i]);
			pipe(mrfd[i]);
			

		}
		for(i = 0; i < forkCount-1; i++)//pipe olustur
		{
			pipe(rrfd[i]);
			

		}
		for( i = 0; (i < forkCount) && ret; i++)//mapper forkla
        {
			
			ret = fork();
            mapIndex = i;
			if (!ret) {
				flag = 1;
			}
			
			

        }
		for( i = 0; (i < forkCount) && ret; i++)//reducer forkla
        {
			
			ret = fork();
            redIndex = i;
			if (!ret) {
				flag = 2;
			}

        }
		//printf("asd:%d \n",mapIndex);
		if (!flag) { // parent bolusturma islemi yapar
				for(int j = 0; j < forkCount; j++)
				{
					
					close(mmfd[j][0]);
					close(mrfd[j][1]);
					close(mrfd[j][0]);
					
				}
				for(int j = 0; j < forkCount-1; j++)
				{
					
					
					close(rrfd[j][0]);
					close(rrfd[j][1]);
					
				}
				// close(stdout); sor bunu

				char buffer[1024];
    			i = 0;
    			while(fgets(buffer,1024,stdin))
    			{
					//printf("b\n");
					//printf("%s\n", buffer);
					write(mmfd[i%forkCount][1],buffer,strlen(buffer));
					i++;

        			
    			}
				//printf("c\n");
				for(int i = 0;i < forkCount;i++)
					{
						close(mmfd[i][1]);
					}
				for(i = 0;i < forkCount;i++)
				{
					wait(NULL);
				}
				for(i = 0;i < forkCount;i++)
				{
					wait(NULL);
				}

			
			}
			else if (flag == 1)// data masterdan alinacak islenip reducerlara atilacak
			{
				
				for(int j = 0; j < forkCount; j++)
				{
					if (mapIndex!=j) {
						close(mrfd[j][1]);
						close(mmfd[j][0]);	
					}
					close(mmfd[j][1]);
					
					close(mrfd[j][1]);

					
					
				}
				for(int j = 0;j < forkCount-1;j++)
				{
					close(rrfd[j][0]);
					close(rrfd[j][1]);
				}
				dup2(mmfd[mapIndex][0],0);
				dup2(mrfd[mapIndex][1],1);
				close(mmfd[mapIndex][0]);
				close(mrfd[mapIndex][1]);
				for(int j = 0;j < forkCount;j++)
				{
					close(mrfd[redIndex][1]);
					close(mrfd[redIndex][0]);
					
					close(mmfd[redIndex][0]);
					close(mmfd[redIndex][1]);
				}
				for(int j = 0;j < forkCount -1;j++)
				{
					close(rrfd[redIndex][0]);
					close(rrfd[redIndex][1]);

				}
				char mapstr[10];
  				sprintf(mapstr, "%d", mapIndex);
				dup2(mmfd[mapIndex][0],0);
				execl(argv[2],argv[2],mapstr,(char *)0);
			}
			else{ // reducer
				printf("redin: %d \n", redIndex);
				for(int j = 0;j < forkCount-1;j++)
				{
					if (redIndex!=j) {
						close(rrfd[j][1]);
						if(j)close(rrfd[j-1][0]);
					}
				}
				if (redIndex == 0)
				{
					dup2(mrfd[redIndex][0],0);
					dup2(rrfd[redIndex][1],1);

				}
				else if(redIndex == forkCount-1)
				{
					dup2(mrfd[redIndex][0],0);
					dup2(rrfd[redIndex-1][0],2);
				}
				else
				{
					dup2(mrfd[redIndex][0],0);
					dup2(rrfd[redIndex-1][0],2);
					dup2(rrfd[redIndex][1],1);
					
				}
				for(int j = 0;j < forkCount;j++)
				{
					close(mrfd[redIndex][1]);
					close(mrfd[redIndex][0]);
					
					close(mmfd[redIndex][0]);
					close(mmfd[redIndex][1]);
				}
				for(int j = 0;j < forkCount -1;j++)
				{
					close(rrfd[redIndex][0]);
					close(rrfd[redIndex][1]);

				}
				char redstr[10];
  				sprintf(redstr, "%d", redIndex);
				dup2(mmfd[redIndex][0],0);
				printf("asd %d \n",redIndex);
				execl(argv[3],argv[3],redstr,(char *)0);
				printf("dsa\n");
			}
	}
	
    


	return 0;
}