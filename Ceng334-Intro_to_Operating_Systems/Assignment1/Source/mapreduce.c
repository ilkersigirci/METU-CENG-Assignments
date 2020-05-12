#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>

int main( int argc, char *argv[] )  {
	int n,c,k;
	pid_t pids[atoi(argv[1])];
	pid_t pidsr[atoi(argv[1])];
	int fd[atoi(argv[1])][2];
	int fdr[atoi(argv[1])][2];
	int frr[atoi(argv[1])-1][2];
	int p,q;
	int v=0;
	pid_t parent_pid;
	char d[1];
	char id[3];

	n = atoi(argv[1]);
	if( argc == 3 ) { // mapper
		parent_pid = getpid();

		for(int i=0; i<n; i++){
			if(pipe(fd[i])<0){
				perror("pipe error");
			}		
		}

		for(int i=0;i<n;i++){
			if(parent_pid == getpid()){				
				if((p=fork())<0){
					perror("fork error");
				}
				else if(p==0){
					pids[i] = getpid();

					for(int k=0; k<n; k++){
						if(k==i){
							close(fd[i][1]);
							dup2(fd[i][0],0);
							close(fd[i][0]);
						}
						else{
							close(fd[k][1]);
							close(fd[k][0]);
						}
					}
				}
			}
		}

		if(getpid()==parent_pid){
			for(int i=0;i<n;i++){
				close(fd[i][0]);
			}
		}

		for(int i=0;i<n;i++){
			if(pids[i]==getpid()){
				if(i<=9){
					id[0] = i+'0';
					id[1] = '\0';
				}
				else{
					id[0] = (i/10)+'0';
					id[1] = (i%10)+'0';
					id[2] = '\0';
				}
				execl(argv[2],argv[2],id,(char*) NULL);
			}
		}


		if(parent_pid==getpid()){
			v=0;
			while(read(0,d,1)){
				write(fd[v%n][1],d, 1);
				if(d[0]=='\n'){
					write(fd[v%n][1],d, 1);					
					v++;
					continue;
				}
			}
		}

		for(int i=0;i<n;i++){
			if(pids[i]==getpid()){
				close(fd[i][1]);
			}
		}

		for(int i=0;i<((3*n)-1);i++){
			wait(&c);
		}

	}
	else if( argc = 4 ) { // mapper + reducer
		parent_pid = getpid();

		for(int i=0; i<n; i++){
			if(pipe(fd[i])<0){
				perror("pipe error");
			}		
		}

		for(int i=0; i<n; i++){
			if(pipe(fdr[i])<0){
				perror("pipe error");
			}	
		}

		for(int i=0; i<n-1; i++){
			if(pipe(frr[i])<0){
				perror("pipe error");
			}	
		}


		for(int i=0;i<n;i++){
			if(parent_pid == getpid()){				
				if((p=fork())<0){
					perror("fork error");
				}
				else if(p==0){
					pids[i] = getpid();
					for(int k=0; k<n; k++){
						if(k==i){
							close(fdr[i][0]);
							dup2(fdr[i][1],1);
							close(fdr[i][1]);
						}
						else{
							close(fdr[k][1]);
							close(fdr[k][0]);
						}
					}
					for(int k=0; k<n-1; k++){
						close(frr[k][1]);
						close(frr[k][0]);
					}
					for(int k=0; k<n; k++){
						if(k==i){
							close(fd[i][1]);
							dup2(fd[i][0],0);
							close(fd[i][0]);
						}
						else{
							close(fd[k][1]);
							close(fd[k][0]);
						}
					}
				}
			}
		}

		for(int i=0;i<n;i++){
			if(parent_pid == getpid()){				
				if((p=fork())<0){
					perror("fork error");
				}
				else if(p==0){
					pidsr[i] = getpid();
					for(int k=0; k<n; k++){
						close(fd[k][1]);
						close(fd[k][0]);
					}
					for(int k=0; k<n; k++){
						if(k==i){
							if(k==0){
								close(frr[k][0]);
								dup2(frr[k][1],1);
								close(frr[k][1]);
							}
							else if(k==n-1){
								close(frr[k-1][1]);
								dup2(frr[k-1][0],2);
								close(frr[k-1][0]);
							}
							else{
								dup2(frr[k][0],2);
								close(frr[k][0]);
								dup2(frr[k][1],1);
								close(frr[k][1]);
							}							
						}
						else{
							if(k==n-1){
								continue;
							}
							else{
								close(frr[k][1]);
								close(frr[k][0]);
							}
						}
					}
					for(int k=0; k<n; k++){
						if(k==i){
							close(fdr[i][1]);
							dup2(fdr[i][0],0);
							close(fdr[i][0]);
						}
						else{
							close(fdr[k][1]);
							close(fdr[k][0]);
						}
					}
				}
			}
		}

		if(getpid()==parent_pid){
			for(int i=0;i<n;i++){
				close(fdr[i][0]);
				close(fdr[i][1]);

				close(fd[i][0]);
			}
			for(int i=0;i<n-1;i++){
				close(frr[i][1]);
				close(frr[i][0]);	
			}

		}

		for(int i=0;i<n;i++){
			if(pids[i]==getpid()){
				if(i<=9){
					id[0] = i+'0';
					id[1] = '\0';
				}
				else{
					id[0] = (i/10)+'0';
					id[1] = (i%10)+'0';
					id[2] = '\0';
				}
				execl(argv[2],argv[2],id,(char*) NULL);
			}
		}

		for(int i=0;i<n;i++){
			if(pidsr[i]==getpid()){
				if(i<=9){
					id[0] = i+'0';
					id[1] = '\0';
				}
				else{
					id[0] = (i/10)+'0';
					id[1] = (i%10)+'0';
					id[2] = '\0';
				}
				execl(argv[3],argv[3],id,(char*) NULL);
			}
		}

		if(parent_pid==getpid()){
			v=0;
			while(read(0,d,1)){
				write(fd[v%n][1],d, 1);
				if(d[0]=='\n'){
					write(fd[v%n][1],d, 1);					
					v++;
					continue;
				}
			}
		}

		for(int i=0;i<n;i++){
			if(pidsr[i]==getpid()){
				close(fd[i][1]);
			}
		}

		for(int i=0;i<((3*n)-1);i++){
			wait(&c);
		}

	}
}