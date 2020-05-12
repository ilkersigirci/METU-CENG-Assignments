#include <stdio.h>
#include <math.h>


int main()
{
    double f(double x),arr[2000],begin,end,eps,root,h=1e-5,div,deriv,temp;
    int count=0,i,j,flag;

    scanf("%lf %lf %lf",&begin,&end,&eps);

    for(;begin<=end;begin+=10*eps)
    {
        flag=0;
        root=begin;
        deriv=((f(root+h)-f(root-h))/(2*h));
        div=f(root)/deriv;

        if(!deriv || deriv!=deriv){continue;}

        while(!(div<eps && div>-eps)){
            deriv=((f(root+h)-f(root-h))/(2*h));
            div=f(root)/deriv;
            root=root-div;
        }
        if(root>=begin && root<=end){
            for(i=0;i<count;i++){
                if(root<=arr[i]+2*eps && root>=arr[i]-2*eps){
                    flag=1;
                    break;
                }
            }
            if(flag) {continue;}
            arr[count]=root;
            count++;
            }
         else continue;
    }
    count--;

    for(i=0;i<count;i++){
        for (j = 0; j < count-i; j++){
            if (arr[j] > arr[j+1]){
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

    for(i=0;i<count+1;i++){
        printf("%f ",arr[i]);
    }

    return 0;
}
