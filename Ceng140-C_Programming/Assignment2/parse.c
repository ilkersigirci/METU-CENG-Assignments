  #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void parse(char * moleculeCol,char ** atomCol,int * numCol){
  
  char  * pivMol=moleculeCol;
  /*char  ** pivAtom=atomCol;
  int * pivNum=numCol;  */
  int i=0,j=0,sum=0,coef=0,c=1;

  while(*pivMol){
    printf("%c\n",*pivMol);
    if(*pivMol>='A' && *pivMol<='Z'){
      if((*(pivMol+1)>='A' && *(pivMol+1)<='Z') || !*(pivMol+1) || *(pivMol+1)==')' || *(pivMol+1)=='('){
        for(i=0;atomCol[i];i++){
          if(*pivMol==atomCol[i][0]) numCol[i]+=c;
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
        coef*=c;
        numCol[i]+=coef;
      }
      else if(*(pivMol+1)>='a' && *(pivMol+1)<='z'){
        for(i=0;atomCol[i];i++){
          if(*pivMol==atomCol[i][0] && *(pivMol+1)==atomCol[i][1]) break;
        }
        pivMol++;

        if((*(pivMol+1)>='A' && *(pivMol+1)<='Z') || !*(pivMol+1) || *(pivMol+1)==')' || *(pivMol+1)=='('){
          numCol[i]+=1;
          pivMol++;
        }
        else if(*(pivMol+1)>='1' && *(pivMol+1)<='9'){
          pivMol++;

          while(*pivMol>='1' && *pivMol<='9'){
            sum=10*sum+(*pivMol-'0');
            pivMol++;
          }
          coef=sum;sum=0;
          coef*=c;
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

void allAtoms(char ** atomCol1,char * moleculeCol){

  char * pivMol=moleculeCol;
  char ** atomCol=atomCol1;
  int i=0,j=0,atomSize=0;

  while(*pivMol){
    printf("# %c\n",*pivMol);
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
}

int main()
{
  char ** atomCol;
  char *moleculeCol = "Oz((Ha2)2)3N";
  int i=0,inNumber=1,typeofAtom=10;      /*inNumber=number of moleculeCol*/
  int *numCol;

  atomCol=(char **)malloc(sizeof(char *)*(typeofAtom*(inNumber)+1));
  for(i=0;i<inNumber*typeofAtom;i++){
    atomCol[i]=(char *)malloc(sizeof(char )*3);
  }
  for(i=0;i<inNumber*typeofAtom;i++){
    atomCol[i][0]='1'; atomCol[i][1]='1'; atomCol[i][2]='\0';
  }

  allAtoms(atomCol,moleculeCol);

  typeofAtom=0;
  for(i=0;atomCol[i][0]!='1';) i++;
  typeofAtom=i;    /* printf("%d\n",typeofAtom);  */

  for(i=0;i<inNumber*typeofAt om;i++){
    printf("atomCol[%d]  =  %s\n",i,atomCol[i]);
  }

  numCol=(int *) malloc(typeofAtom*sizeof(int));

  for(i=0;i<typeofAtom;i++) numCol[i]=0;

  parse(moleculeCol,atomCol,numCol);

  for(i=0;i<typeofAtom;i++){
    printf("numCol[%d]  =  %d\n",i,numCol[i]);
  }

  return 0;
}
