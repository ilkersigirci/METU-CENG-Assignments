#include <stdio.h>

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

int main(){

    char * cp="ilker)5345";

    int x=0;

    x=endparCoef(cp+5);

    printf("%d\n",x);
        

    return 0;
}