#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double f(double x),arr[2000],begin,end,eps,root,h=1e-5,div,deriv;
    int count=0,i,flag;
    scanf("%lf %lf %lf",&begin,&end,&eps);

    for(;begin<=end;begin+=eps)
    {
        flag=0;
        root=begin;
        deriv=((f(root+h)-f(root-h))/(2*h));
        if(!deriv) continue;
        div=f(root)/deriv;
        root=root-div;

        if(div<eps && div>-eps){
              for(i=0;i<count;i++){
                if(root<=arr[i]+2*eps && root>=arr[i]-2*eps){
                    flag=1;
                    break;
                }
            }
            if(flag) continue;

            arr[count]=root;
            printf("%f ",arr[count]);
            count++;
        }
    }
    return 0;
}
