#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long gcd(long a, long b)
{
    
    if (a == 0 || b == 0)
       return 0;
 
    
    if (a == b)
        return a;
 
    
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}

void allAtoms(char ** atomCol1,char * moleculeCol){  /* returns number of atoms */

  char * pivMol=moleculeCol;
  char ** atomCol=atomCol1;
  int i=0,j=0,atomSize=0;

  while(*pivMol){
    atomSize=0; i=0;
    while(!(atomCol[i][0]=='1' && atomCol[i][1]=='1')){
        atomSize++;
        i++;
    } i=0;

    while(*pivMol=='(' || *pivMol==')') pivMol++;
    if(*pivMol>='A' && *pivMol<='Z'){
      if((*(pivMol+1)>='A' && *(pivMol+1)<='Z') || !*(pivMol+1) || *(pivMol+1)=='(' || *(pivMol+1)==')'){
        for(i=0;i<atomSize;i++){
          if(*pivMol==atomCol[i][0] && !atomCol[i][1]) break;
          if(*pivMol!=atomCol[i][0] && !atomCol[i][1]) continue;
        }
        if(i==atomSize){
          atomCol[i][0]=*pivMol;
          atomCol[i][1]='\0';
        }
        pivMol++;
      }

      else if(*(pivMol+1)>='1' && *(pivMol+1)<='9'){
        for(i=0;i<atomSize;i++){
          if(*pivMol==atomCol[i][0] && !atomCol[i][1]) break;
          if(*pivMol!=atomCol[i][0] && !atomCol[i][1]) continue;
        }
        if(i==atomSize){
          atomCol[i][0]=*pivMol;
          atomCol[i][1]='\0';
        }
        pivMol++;
        while(*pivMol>='1' && *pivMol<='9') pivMol++;
      }

      else if(*(pivMol+1)>='a' && *(pivMol+1)<='z'){
        for(i=0;i<atomSize;i++){
          if(*pivMol==atomCol[i][0] && *(pivMol+1)==atomCol[i][1]) break;
          if( atomCol[i][1] && (*pivMol!=atomCol[i][0] || *pivMol!=atomCol[i][1])) continue;
        }
        if(i==atomSize){
          atomCol[i][0]=*pivMol;
          atomCol[i][1]=*(pivMol+1);
          atomCol[i][2]='\0';
        }
        pivMol++;

        if((*(pivMol+1)>='A' && *(pivMol+1)<='Z') || !*(pivMol+1) || *(pivMol+1)=='(' || *(pivMol+1)==')') pivMol++;

        else if(*(pivMol+1)>='1' && *(pivMol+1)<='9'){
          pivMol++;
          while(*pivMol>='1' && *pivMol<='9') pivMol++;
        }
      }
    }
    else if((*pivMol>='1' && *pivMol<='9') || !*pivMol) pivMol++;
  }
  /* return atomSize;  */
}

int endparCoef(char *cp){  /* kapali parantezin pointeri giriyor */
  int sum=0,coef=0;

  cp++;
  if(*cp>='1' && *cp<='9'){
    while(*cp>='1' && *cp<='9'){
      sum=10*sum+(*cp-'0');
      cp++;
    }
    coef=sum;
  }
  else if((*cp>='A' && *cp<='Z') || !*cp || *cp==')' || *cp=='('){
      coef=1;
  }
  return coef;
}

int parCoef(char *cp){      /* parantez sonundaki coefficient bulma */
  int all=0,open=1,closed=0;   /* acik parantezin pointeri giriyor */
  int sum=0,coef=0;
  cp++;  /* acik parantezin bi sonrasinin pointeri*/
  while(open!=closed){
    if(*cp=='('){
      all++;
      open++;
    }
    else if(*cp==')'){
      closed++;
      all--;
    }
    cp++;
  }

  if(*cp>='1' && *cp<='9'){
    while(*cp>='1' && *cp<='9'){
      sum=10*sum+(*cp-'0');
      cp++;
    }
    coef=sum;
  }
  else if((*cp>='A' && *cp<='Z') || !*cp || *cp==')' || *cp=='('){
      coef=1;
  }
  return coef;
}

void parse(char * moleculeCol,char ** atomCol,int * numCol,int side){

  char  * pivMol=moleculeCol;
  /*char  ** pivAtom=atomCol;
  int * pivNum=numCol;  */
  int i=0,j=0,sum=0,coef=0,c=1;

  while(*pivMol){    
   
    if(*pivMol>='A' && *pivMol<='Z'){
      if((*(pivMol+1)>='A' && *(pivMol+1)<='Z') || !*(pivMol+1) || *(pivMol+1)==')' || *(pivMol+1)=='('){
        for(i=0;atomCol[i];i++){
          if(*pivMol==atomCol[i][0] && !atomCol[i][1]) numCol[i]=numCol[i]+c*side;
        }
        pivMol++;
      }
      else if(*(pivMol+1)>='1' && *(pivMol+1)<='9'){
        for(i=0;atomCol[i];i++){
          if(*pivMol==atomCol[i][0]) break;
        }
        pivMol++;

        while(*pivMol>='1' && *pivMol<='9'){
          sum=10*sum+(*pivMol-'0');
          pivMol++;
        }
        coef=sum;sum=0;
        coef=coef*c*side;
        numCol[i]+=coef;
      }
      else if(*(pivMol+1)>='a' && *(pivMol+1)<='z'){
        for(i=0;atomCol[i];i++){
          if(*pivMol==atomCol[i][0] && *(pivMol+1)==atomCol[i][1]) break;
        }
        pivMol++;

        if((*(pivMol+1)>='A' && *(pivMol+1)<='Z') || !*(pivMol+1) || *(pivMol+1)==')' || *(pivMol+1)=='('){
          numCol[i]+=c*side;
          pivMol++;
        }
        else if(*(pivMol+1)>='1' && *(pivMol+1)<='9'){
          pivMol++;

          while(*pivMol>='1' && *pivMol<='9'){
            sum=10*sum+(*pivMol-'0');
            pivMol++;
          }
          coef=sum;sum=0;
          coef=coef*c*side;
          numCol[i]+=coef;
        }
      }
    }
    else if(*pivMol=='('){
      c*=parCoef(pivMol);
      pivMol++;
    }
    else if(*pivMol==')'){
      c/=endparCoef(pivMol);
      pivMol++;
      while(*pivMol>='1' && *pivMol<='9') pivMol++;
    }
  }
}

int ** bareiss(int ** now,int ** next,int row,int col,int pivIndex,int prevPiv){

    int i=0,j=0,k=1,pivot=now[pivIndex][pivIndex],flag=0;
    int * temp1;

    printf("pivIndex %d,pivot %d \n",pivIndex,pivot);  
    if(pivot==0 && pivIndex!=row-1){
        for(i=pivIndex;i<row;i++){
          for(j=0;j<col;j++){
            if(now[i][j]!=0) flag=1;
          }            
        }i=0;j=0;
        if(flag==0){
            return now;
        } 
        while(now[pivIndex+k][pivIndex]==0 && k<col-pivIndex) k++;
        temp1=now[pivIndex];
        now[pivIndex]=now[pivIndex+k];
        now[pivIndex+k]=temp1;
        pivot=now[pivIndex][pivIndex];
    }

    for(i=0;i<row;i++){
        if(i==pivIndex){
            for(j=0;j<col;j++){
            next[i][j]=now[i][j];
            }
            continue;
        }
        for(j=0;j<col;j++){
            next[i][j]=(pivot*now[i][j]
            -now[i][pivIndex]*now[pivIndex][j])/prevPiv;
        }
    } 
    printf("--------------------------------------------\n");
    printf("NOW\n");
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            printf("%d \t",now[i][j]);
        }
        printf("\n");
    }

    printf("Next\n");
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            printf("%d \t",next[i][j]);
        }
        printf("\n");
    } 

    if(pivIndex+1<row){
        bareiss(next,now,row,col,pivIndex+1,now[pivIndex][pivIndex]);
    }
    return next;
}


int main()
{
   char *equation,*equ; /* H3PO4 + (NH4)2MoO4 + HNO3 -> (NH4)3PO4(MoO3)12 + NH4NO3 + H2O */
   char **atomCol;
   char **in,**out,**in1,**out1;
   char *inpp,*outpp;
   int i=0,j=0,k=0,inNumber,outNumber,row,col;
   int typeofAtom=200;  /* dinamik bilinmesi daha iyi olur  */
   int ** matrix,*numCol,**nextMatrix;
   long ** katsayi;
   long x,result;

   equation=(char *)malloc(sizeof(char)*20000);
   in=(char **)malloc(sizeof(char*)*20);
   out=(char **)malloc(sizeof(char*)*20);
   for(i=0;i<20;i++){
     in[i]=(char *)malloc(sizeof(char)*400);
     out[i]=(char *)malloc(sizeof(char)*400);
   }   i=0;

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
     /* printf("in %s\n",in[j]);  */
   }  inNumber=j;
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
     else if(*equ=='\n'){
       break;
     }
     else{
       *outpp++=*equ++;
     }
   }
   i++;
   out[i]=NULL;
  for(j=0;out[j];j++){
  /*  printf("out %s\n",out[j]); */
  }outNumber=j;
  col=inNumber+outNumber;
/*
  printf("---------------------------------------------------------------------\n");
  printf("ATOM COL \n");  */

  atomCol=(char **)malloc(sizeof(char *)*(typeofAtom*inNumber+1));
  for(i=0;i<inNumber*typeofAtom;i++){
    atomCol[i]=(char *)malloc(sizeof(char )*3);
  }
  for(i=0;i<inNumber*typeofAtom;i++){
    atomCol[i][0]='1'; atomCol[i][1]='1'; atomCol[i][2]='\0';
  }

  for(i=0;i<inNumber;i++){
    allAtoms(atomCol,in[i]);
  }

  for(i=0;atomCol[i][0]!='1';) i++;
  row=i;
/*
  for(i=0;i<row;i++){
    printf("atomCol[%d]  =  %s\n",i,atomCol[i]);
  }  

  printf("in %d , out %d ,row %d ,col %d\n",inNumber,outNumber,row,col);
  printf("---------------------------------------------------------------------\n");

  printf("NUM COL \n"); */

  /* H3PO4 + (NH4)2MoO4 + HNO3 -> (NH4)3PO4(MoO3)12 + NH4NO3 + H2O */



  numCol=(int *) malloc(row*sizeof(int));
  for(i=0;i<row;i++) numCol[i]=0;

  matrix=(int **) malloc(row*sizeof(int *));
  for(i=0;i<row;i++){
    matrix[i]=(int *) malloc(col*sizeof(int));
  }
  for(i=0;i<row;i++){
    for(j=0;j<col;j++) matrix[i][j]=0;
  }
/*
  for(i=0;i<row;i++){
      for(j=0;j<col;j++){
          printf("%d \t",matrix[i][j]);
      }
      printf("\n");
  } */
/*
  parse(out[0],atomCol,numCol,1);
  for(k=0;k<row;k++) printf("%d ",numCol[k]);
  printf("\n");  */


  for(i=0;i<inNumber;i++){
    for(k=0;k<row;k++) numCol[k]=0;
    parse(in[i],atomCol,numCol,1);
    for(k=0;k<row;k++){
      matrix[k][i]=numCol[k];
    }
  }
  for(i=inNumber;i<col;i++){
    for(k=0;k<row;k++) numCol[k]=0;
    parse(out[i-inNumber],atomCol,numCol,-1);
    for(k=0;k<row;k++){
      matrix[k][i]=numCol[k];
    }
  }
/*
    parse(out[outNumber-1],atomCol,numCol,-1);
    for(i=0;i<row;i++) printf("%d ",numCol[i]);  */

/*
  for(k=0;k<row;k++) numCol[k]=0;
  parse(out[outNumber-1],atomCol,numCol,-1);
  for(k=0;k<row;k++){
    matrix[k][col-1]=numCol[k];
  }   */

  /* Son Col  Patliyor */

  
/*
  matrix[1][3]=-1;
  matrix[2][3]=-1;  */


/*  printf("\n");  
  for(i=0;i<row;i++){
      for(j=0;j<col;j++){
          printf("%d\t",matrix[i][j]);
      }
      printf("\n");
  }
  printf("---------------------------------------------------------------------\n");

  printf("BAREISS COL \n"); */

  nextMatrix=(int **) malloc(row*sizeof(int *));
  for(i=0;i<row;i++){
    nextMatrix[i]=(int *) malloc(col*sizeof(int));
  }

  for(i=0;i<row;i++){
    for(j=0;j<col;j++) nextMatrix[i][j]=0;
  }


  bareiss(matrix,nextMatrix,row,col,0,1);

  printf("NUM\n");
  for(i=0;i<row;i++){
      for(j=0;j<col;j++){
          printf("%d \t",matrix[i][j]);
      }
      printf("\n");
  }  

   printf("--------------------------------------------\n");
  printf("NEXT\n");
  for(i=0;i<row;i++){
      for(j=0;j<col;j++){
          printf("%d \t",nextMatrix[i][j]);
      }
      printf("\n");
  }

  printf("--------------------------------------------\n");  

  printf("Solving lineeer equations\n");  

  katsayi=(long **) malloc(col*sizeof(long *));
  for(i=0;i<col;i++){
    katsayi[i]=(long *) malloc(2*sizeof(long));
  }
  for(i=0;i<col;i++){
    for(j=0;j<2;j++) katsayi[i][j]=0;
  }

  k=0;
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      if(i==j && nextMatrix[i][j]!=0){
        katsayi[k][0]=(-1)*nextMatrix[i][col-1];
        katsayi[k][1]=nextMatrix[i][j];
        k++;
      }
    }
  }
  for(i=0;i<col;i++){
    if(katsayi[i][0]==0 && katsayi[i][1]==0){
      katsayi[i][0]=1;
      katsayi[i][1]=1;
    }
  }

  for(i=0;i<col;i++){
    for(j=0;j<2;j++) printf("%ld ",katsayi[i][j]);
    printf("\n");
  }

  printf("--------------------------------------------\n");
  printf("ebob alma\n");  

  printf("\n");  

  x=1;
  
  for(i=0;i<col;i++){
    x*=katsayi[i][1];
  }
  printf("%ld\n",x);

  for(i=0;i<col;i++){
    katsayi[i][0]=katsayi[i][0]*(x/katsayi[i][1]);
  }
  
  for(i=0;i<col;i++){
    printf("%ld ",katsayi[i][0]);
  }printf("\n");
 
 
  for(i=0;i<col-1;i++){
    if(i==0){
      result=gcd(katsayi[0][0],katsayi[1][0]);
      printf("result %ld\n",result);
    }
    else{
      result=gcd(result,katsayi[i+1][0]);
    }
  }
  

   for(i=0;i<col;i++){
    katsayi[i][0]/=result;
  }

   for(i=0;i<col;i++){
    printf("%ld ",katsayi[i][0]);
  }

   return 0;
}
