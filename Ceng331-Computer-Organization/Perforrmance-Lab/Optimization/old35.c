/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/* 
 * Please fill in the following student struct 
 */
team_t team = {
    "2171940",              /* Student ID */

    "Ali İlker SIĞIRCI",     /* full name */
    "e2171940@metu.edu.tr",  /* email address */

    "",                   /* leave blank */
    ""                    /* leave blank */
};

/***************
 * CONVOLUTION KERNEL
 ***************/

/******************************************************
 * Your different versions of the convolution functions  go here
 ******************************************************/

/* 
 * naive_conv - The naive baseline version of convolution 
 */
char naive_conv_descr[] = "naive_conv: Naive baseline implementation";
void naive_conv(int dim,int *src, int *ker,int *dst) 
{
    int i,j,k,l;

    for(i = 0; i < dim-8+1; i++)
        for(j = 0; j < dim-8+1; j++) {
            dst[j*dim+i] = 0;
            for(k = 0; k < 8; k++)
                for(l = 0; l < 8; l++) {
                    dst[j*dim+i] = dst[j*dim+i] +src[(j+l)*dim+(i+k)]*ker[l*dim+k];
                }
        }       
}
/* 
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */
char convolution_descr[] = "Dot product: Current working version";
void convolution(int dim,int *src, int *ker,int *dst) 
{
        naive_conv(dim,src,ker,dst);
}

/*********************************************************************
 * register_conv_functions - Register all of your different versions
 *     of the convolution functions  with the driver by calling the
 *     add_conv_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_conv_functions() 
{
    add_conv_function(&naive_conv, naive_conv_descr);   
    add_conv_function(&convolution, convolution_descr);   
    /* ... Register additional test functions here */
}
/***************
 * MATRIX MULTIP KERNEL
 ***************/

/******************************************************
 * Your different versions of the matrix multiplications  go here
 ******************************************************/

/* 
 * naive_matrix_multiplication - The naive baseline version of matrix multiplication 
 */
char naive_matrix_multiplication_descr[] = "Naive_matrix_multiplication: Naive baseline implementation";
void naive_matrix_multiplication(int dim,int *src, int *src2,int *dst) 
{
    int i,j,k;
    for(i = 0; i < dim; i++)
    {
        for(j = 0; j < dim; j++) 
        {

            dst[j*dim+i]=0;
            for(k = 0; k < dim; k++)
            {
                dst[j*dim+i] = dst[j*dim+i] + src[j*dim+k]*src2[i+k*dim];
            }
        }
    }
}


/* 
 * matrix_multiplication - Your current working version of matrix_multiplication
 * IMPORTANT: This is the version you will be graded on
 */





char matrix_multiplication_descr[] = "Matrix multiplications: Current working version";
void matrix_multiplication(int dim,int *src, int *src2,int *dst) 
{
    //matmul_optimized3(dim,src,src2,dst);

    int i,j,k;
    int x0,x1,x2,x3,x4,x5,x6,x7;
    int y0,y1,y2,y3,y4,y5,y6,y7;
    int z0,z1,z2,z3,z4,z5,z6,z7;
    int t0,t1,t2,t3,t4,t5,t6,t7;
    //int  x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31;
    int idim,kdim;
    int sr2cjkdim, sr2ctemp1, sr2ctemp2, sr2ctemp3;
    int * dstjidim, * srckidim;
    
    for(i = 0; i < dim; i = i+8)
    {
        for(j = 0; j < dim; j = j+4)
        {            
			x0 = 0;x1 = 0;x2 = 0;x3 = 0;x4 = 0;x5 = 0;x6 = 0;x7 = 0;
            y0 = 0;y1 = 0;y2 = 0;y3 = 0;y4 = 0;y5 = 0;y6 = 0;y7 = 0;
            z0 = 0;z1 = 0;z2 = 0;z3 = 0;z4 = 0;z5 = 0;z6 = 0;z7 = 0;
            t0 = 0;t1 = 0;t2 = 0;t3 = 0;t4 = 0;t5 = 0;t6 = 0;t7 = 0;
            idim = i*dim;            
            //dstjidim = dst+(j + idim); 
            for(k = 0; k < dim; k++)
            {
                //x0  = x0  + src[k + (i+1)*dim]*src2[j + k*dim];
                kdim = k*dim;
                srckidim = src+(k + idim);
                sr2cjkdim = src2[j + kdim];   
                sr2ctemp1 = src2[j+1 + kdim];
                sr2ctemp2 = src2[j+2 + kdim];
                sr2ctemp3 = src2[j+3 + kdim];

                x0  = x0  + *(srckidim)*sr2cjkdim;
                x1  = x1  + *(srckidim+1*dim)*sr2cjkdim;
                x2  = x2  + *(srckidim+2*dim)*sr2cjkdim;
                x3  = x3  + *(srckidim+3*dim)*sr2cjkdim;
                x4  = x4  + *(srckidim+4*dim)*sr2cjkdim;
                x5  = x5  + *(srckidim+5*dim)*sr2cjkdim;
                x6  = x6  + *(srckidim+6*dim)*sr2cjkdim;
                x7  = x7  + *(srckidim+7*dim)*sr2cjkdim;

                y0  = y0  + *(srckidim)*sr2ctemp1;
                y1  = y1  + *(srckidim+1*dim)*sr2ctemp1;
                y2  = y2  + *(srckidim+2*dim)*sr2ctemp1;
                y3  = y3  + *(srckidim+3*dim)*sr2ctemp1;
                y4  = y4  + *(srckidim+4*dim)*sr2ctemp1;
                y5  = y5  + *(srckidim+5*dim)*sr2ctemp1;
                y6  = y6  + *(srckidim+6*dim)*sr2ctemp1;
                y7  = y7  + *(srckidim+7*dim)*sr2ctemp1;

                z0  = z0  + *(srckidim)*sr2ctemp2;
                z1  = z1  + *(srckidim+1*dim)*sr2ctemp2;
                z2  = z2  + *(srckidim+2*dim)*sr2ctemp2;
                z3  = z3  + *(srckidim+3*dim)*sr2ctemp2;
                z4  = z4  + *(srckidim+4*dim)*sr2ctemp2;
                z5  = z5  + *(srckidim+5*dim)*sr2ctemp2;
                z6  = z6  + *(srckidim+6*dim)*sr2ctemp2;
                z7  = z7  + *(srckidim+7*dim)*sr2ctemp2;

                t0  = t0  + *(srckidim)*sr2ctemp3;
                t1  = t1  + *(srckidim+1*dim)*sr2ctemp3;
                t2  = t2  + *(srckidim+2*dim)*sr2ctemp3;
                t3  = t3  + *(srckidim+3*dim)*sr2ctemp3;
                t4  = t4  + *(srckidim+4*dim)*sr2ctemp3;
                t5  = t5  + *(srckidim+5*dim)*sr2ctemp3;
                t6  = t6  + *(srckidim+6*dim)*sr2ctemp3;
                t7  = t7  + *(srckidim+7*dim)*sr2ctemp3;

             
                
            }
            /* *(dstjidim)      = x0;*(dstjidim+1*dim)  = x1;*(dstjidim+2*dim)  = x2;*(dstjidim+3*dim)  = x3;            
            *(dstjidim+4*dim)  = x4;*(dstjidim+5*dim)  = x5;*(dstjidim+6*dim)  = x6;*(dstjidim+7*dim)  = x7; */

            dst[j + idim]      = x0;dst[j  + idim+1*dim]  = x1;dst[j  + idim+2*dim]  = x2;dst[j  + idim+3*dim]  = x3;            
            dst[j + idim+4*dim]  = x4;dst[j  + idim+5*dim]  = x5;dst[j  + idim+6*dim]  = x6;dst[j  + idim+7*dim]  = x7;

            dst[j+1 + idim]      = y0;dst[j+1  + idim+1*dim]  = y1;dst[j+1  + idim+2*dim]  = y2;dst[j+1  + idim+3*dim]  = y3;            
            dst[j+1 + idim+4*dim]  = y4;dst[j+1  + idim+5*dim]  = y5;dst[j+1  + idim+6*dim]  = y6;dst[j+1  + idim+7*dim]  = y7;

            dst[j+2 + idim]      = z0;dst[j+2  + idim+1*dim]  = z1;dst[j+2  + idim+2*dim]  = z2;dst[j+2  + idim+3*dim]  = z3;            
            dst[j+2 + idim+4*dim]  = z4;dst[j+2  + idim+5*dim]  = z5;dst[j+2  + idim+6*dim]  = z6;dst[j+2  + idim+7*dim]  = z7;

            dst[j+3 + idim]      = t0;dst[j+3  + idim+1*dim]  = t1;dst[j+3  + idim+2*dim]  = t2;dst[j+3  + idim+3*dim]  = t3;            
            dst[j+3 + idim+4*dim]  = t4;dst[j+3  + idim+5*dim]  = t5;dst[j+3  + idim+6*dim]  = t6;dst[j+3  + idim+7*dim]  = t7;

			/* dst[j + i*dim]      = x0;dst[j  + (i+1)*dim]  = x1;dst[j  + (i+2)*dim]  = x2;dst[j  + (i+3)*dim]  = x3;            
            dst[j + (i+4)*dim]  = x4;dst[j  + (i+5)*dim]  = x5;dst[j  + (i+6)*dim]  = x6;dst[j  + (i+7)*dim]  = x7; */
                 
        
        }		
    }
    /* for(; i < dim; i++)
    {
        for(j = 0; j < dim; j++) 
        {            
			x0 = 0;
            for(k = 0; k < dim; k++)
            {
                x0 = x0 + src[k + i*dim]*src2[j + k*dim];                
            }
			dst[j + i*dim] = x0;
        }		
    } */

}


/*********************************************************************
 * register_matrix_multiplication_functions - Register all of your different versions
 *     of the matrix multiplication  with the driver by calling the
 *     add_matrix_multiplication_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_matrix_multiplication_functions() {
    add_matrix_multiplication_function(&naive_matrix_multiplication, naive_matrix_multiplication_descr);   
    add_matrix_multiplication_function(&matrix_multiplication, matrix_multiplication_descr);   
    /* ... Register additional test functions here */
}


