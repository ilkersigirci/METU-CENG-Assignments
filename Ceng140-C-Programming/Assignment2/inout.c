dsf#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
   char *equation,*equ; /* Ba3N2 + H2O ->  Ba(OH)2 + NH3 */
   char **in,**out,**in1,**out1;
   char *inpp,*outpp;
   int i=0,j=0;

   equation=(char *)malloc(sizeof(char)*20000);
   in=(char **)malloc(sizeof(char*)*20);
   out=(char **)malloc(sizeof(char*)*20);
   for(i=0;i<20;i++){
     in[i]=(char *)malloc(sizeof(char)*400);
     out[i]=(char *)malloc(sizeof(char)*400);
   }
   i=0;

   fgets(equation, 20000, stdin);
   equ=equation;  in1=in;  out1=out;

    inpp=in1[i];
    while(1){
      while(*equ==' ') equ++;
      if(*equ=='+'){
        equ++;
        *inpp='\0';
        i++;
        inpp=in1[i];
        continue;
      }
      else if(*equ=='-'){
        equ++;
        break;
      }
      else{
        *inpp++=*equ++;
      }
    }
    i++;
    in[i]=NULL;
   for(j=0;in[j];j++){
     printf("in %s\n",in[j]);
   }
   i=0; j=0;equ++;

   outpp=out1[i];
   while(1){
     while(*equ==' ') equ++;
     if(*equ=='+'){
       equ++;
       *outpp='\0';
       i++;
       outpp=out1[i];
       continue;
     }
     else if(*equ=='\0'){
       break;
     }
     else{
       *outpp++=*equ++;
     }
   }
   i++;
   out[i]=NULL;
  for(j=0;out[j];j++){
    printf("out %s\n",out[j]);
  }

  












   return 0;
}

