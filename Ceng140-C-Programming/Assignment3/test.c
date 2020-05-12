#include <stdio.h>
#include <string.h>

int main(){

    char *str[3];
    char * str4;

    str[0]="ilker";
    str[1]="ilker1";
    str[2]="ilker2";

    str4=str[0];       
    printf("%p\n",str[0]);    
    printf("%p\n",str4);    
   

    return 0;
}