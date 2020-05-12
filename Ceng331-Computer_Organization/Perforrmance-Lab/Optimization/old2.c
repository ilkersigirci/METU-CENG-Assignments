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
    //int  x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31;
    int idim,kdim;
    int sr2cjkdim;
    int * dstjidim, * srckidim;
    
    for(i = 0; i < dim; i = i+8)
    {
        for(j = 0; j < dim; j++)
        {            
			x0 = 0;x1 = 0;x2 = 0;x3 = 0;x4 = 0;x5 = 0;x6 = 0;x7 = 0;
            /* x8 = 0;x9 = 0;x10 = 0;x11 = 0;x12 = 0;x13 = 0;x14 = 0;x15 = 0;
            x16 = 0;x17 = 0;x18 = 0;x19 = 0;x20 = 0;x21 = 0;x22 = 0;x23 = 0;
            x24 = 0;x25 = 0;x26 = 0;x27 = 0;x28 = 0;x29 = 0;x30 = 0;x31 = 0; */

            idim = i*dim;            
            //dstjidim = dst+(j + idim); 
            for(k = 0; k < dim; k++)
            {
                //dim1 =0;
                kdim = k*dim;
                srckidim = src+(k + idim);
                sr2cjkdim = src2[j + kdim];
                
                /* x0  = x0  + src[k + idim      ]*sr2cjkdim;
                x1  = x1  + src[k + (i+1) *dim]*sr2cjkdim;
                x2  = x2  + src[k + (i+2) *dim]*sr2cjkdim;
                x3  = x3  + src[k + (i+3) *dim]*sr2cjkdim;
                x4  = x4  + src[k + (i+4) *dim]*sr2cjkdim;
                x5  = x5  + src[k + (i+5) *dim]*sr2cjkdim;
                x6  = x6  + src[k + (i+6) *dim]*sr2cjkdim;
                x7  = x7  + src[k + (i+7) *dim]*sr2cjkdim; */

                x0  = x0  + *(srckidim)*sr2cjkdim;
                x1  = x1  + *(srckidim+1*dim)*sr2cjkdim;
                x2  = x2  + *(srckidim+2*dim)*sr2cjkdim;
                x3  = x3  + *(srckidim+3*dim)*sr2cjkdim;
                x4  = x4  + *(srckidim+4*dim)*sr2cjkdim;
                x5  = x5  + *(srckidim+5*dim)*sr2cjkdim;
                x6  = x6  + *(srckidim+6*dim)*sr2cjkdim;
                x7  = x7  + *(srckidim+7*dim)*sr2cjkdim;

                /* x8  = x8  + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x9  = x9  + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x10 = x10 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x11 = x11 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x12 = x12 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x13 = x13 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x14 = x14 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x15 = x15 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x16 = x16 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x17 = x17 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x18 = x18 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x19 = x19 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x20 = x20 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x21 = x21 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x22 = x22 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x23 = x23 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x24 = x24 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x25 = x25 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x26 = x26 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x27 = x27 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x28 = x28 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x29 = x29 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x30 = x30 + src[k + idim + dim1]*src2[j + kdim];dim1 += dim;
                x31 = x31 + src[k + idim + dim1]*src2[j + kdim]; */
                
            }
            /* *(dstjidim)      = x0;*(dstjidim+1*dim)  = x1;*(dstjidim+2*dim)  = x2;*(dstjidim+3*dim)  = x3;            
            *(dstjidim+4*dim)  = x4;*(dstjidim+5*dim)  = x5;*(dstjidim+6*dim)  = x6;*(dstjidim+7*dim)  = x7; */

            dst[j + idim]      = x0;dst[j  + idim+1*dim]  = x1;dst[j  + idim+2*dim]  = x2;dst[j  + idim+3*dim]  = x3;            
            dst[j + idim+4*dim]  = x4;dst[j  + idim+5*dim]  = x5;dst[j  + idim+6*dim]  = x6;dst[j  + idim+7*dim]  = x7;

			/* dst[j + i*dim]      = x0;dst[j  + (i+1)*dim]  = x1;dst[j  + (i+2)*dim]  = x2;dst[j  + (i+3)*dim]  = x3;            
            dst[j + (i+4)*dim]  = x4;dst[j  + (i+5)*dim]  = x5;dst[j  + (i+6)*dim]  = x6;dst[j  + (i+7)*dim]  = x7; */
            /* dst[j + (i+8)*dim]  = x8;dst[j  + (i+9)*dim]  = x9;dst[j  + (i+10)*dim] = x10;dst[j + (i+11)*dim] = x11;
            dst[j + (i+12)*dim] = x12;dst[j + (i+13)*dim] = x13;dst[j + (i+14)*dim] = x14;dst[j + (i+15)*dim] = x15;
            dst[j + (i+16)*dim] = x16;dst[j + (i+17)*dim] = x17;dst[j + (i+18)*dim] = x18;dst[j + (i+19)*dim] = x19;
            dst[j + (i+20)*dim] = x20;dst[j + (i+21)*dim] = x21;dst[j + (i+22)*dim] = x22;dst[j + (i+23)*dim] = x23;
            dst[j + (i+24)*dim] = x24;dst[j + (i+25)*dim] = x25;dst[j + (i+26)*dim] = x26;dst[j + (i+27)*dim] = x27;
            dst[j + (i+28)*dim] = x28;dst[j + (i+29)*dim] = x29;dst[j + (i+30)*dim] = x30;dst[j + (i+31)*dim] = x31; */       
        
        }		
    }
    for(; i < dim; i++)
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
    }

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


