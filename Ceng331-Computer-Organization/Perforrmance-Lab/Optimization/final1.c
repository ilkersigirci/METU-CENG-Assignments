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
    {
        for(j = 0; j < dim-8+1; j++)
        {
            dst[j*dim+i] = 0;
            for(k = 0; k < 8; k++)
            {
                for(l = 0; l < 8; l++) 
                {
                    dst[j*dim+i] = dst[j*dim+i] +src[(j+l)*dim+(i+k)]*ker[l*dim+k];
                }
            }
        }
    } 
}
/* 
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */
void convolution1(int dim,int *src, int *ker,int *dst) 
{
    int i,j;

    int ker0  = ker[dim*0+0],ker1  = ker[dim*0+1],ker2  = ker[dim*0+2],ker3  = ker[dim*0+3],ker4  = ker[dim*0+4],ker5  = ker[dim*0+5],ker6  = ker[dim*0+6],ker7  = ker[dim*0+7];
    int ker8  = ker[dim*1+0],ker9 =  ker[dim*1+1],ker10 = ker[dim*1+2],ker11 = ker[dim*1+3],ker12 = ker[dim*1+4],ker13 = ker[dim*1+5],ker14 = ker[dim*1+6],ker15 = ker[dim*1+7];
    int ker16 = ker[dim*2+0],ker17 = ker[dim*2+1],ker18 = ker[dim*2+2],ker19 = ker[dim*2+3],ker20 = ker[dim*2+4],ker21 = ker[dim*2+5],ker22 = ker[dim*2+6],ker23 = ker[dim*2+7];
    int ker24 = ker[dim*3+0],ker25 = ker[dim*3+1],ker26 = ker[dim*3+2],ker27 = ker[dim*3+3],ker28 = ker[dim*3+4],ker29 = ker[dim*3+5],ker30 = ker[dim*3+6],ker31 = ker[dim*3+7];
    int ker32 = ker[dim*4+0],ker33 = ker[dim*4+1],ker34 = ker[dim*4+2],ker35 = ker[dim*4+3],ker36 = ker[dim*4+4],ker37 = ker[dim*4+5],ker38 = ker[dim*4+6],ker39 = ker[dim*4+7];
    int ker40 = ker[dim*5+0],ker41 = ker[dim*5+1],ker42 = ker[dim*5+2],ker43 = ker[dim*5+3],ker44 = ker[dim*5+4],ker45 = ker[dim*5+5],ker46 = ker[dim*5+6],ker47 = ker[dim*5+7];
    int ker48 = ker[dim*6+0],ker49 = ker[dim*6+1],ker50 = ker[dim*6+2],ker51 = ker[dim*6+3],ker52 = ker[dim*6+4],ker53 = ker[dim*6+5],ker54 = ker[dim*6+6],ker55 = ker[dim*6+7];
    int ker56 = ker[dim*7+0],ker57 = ker[dim*7+1],ker58 = ker[dim*7+2],ker59 = ker[dim*7+3],ker60 = ker[dim*7+4],ker61 = ker[dim*7+5],ker62 = ker[dim*7+6],ker63 = ker[dim*7+7];
    
    int x0,x1;
    int y0,y1;
    int * srcjidim;

    for(i = 0; i < dim-8+1; i++)
    {
        for(j = 0; j < dim-8+1; j = j+2)
        {
            //dst[j*dim+i] = 0;
            x0  = 0;x1  = 0;
            y0  = 0,y1  = 0;

            /////////////////////////////////////////
            //dst[j + i*dim] = dst[j + i*dim] +src[(j+k)+(i+l)*dim]*ker[l*dim+k]
            //dst[j + i*dim] = dst[j + i*dim] +src[(j+l)+(i+k)*dim]*ker[l*dim+k]
            srcjidim = src+j+i*dim;

            x0 = x0 + *(srcjidim+0)*ker0;
            x0 = x0 + *(srcjidim+1)*ker1;
            x0 = x0 + *(srcjidim+2)*ker2;
            x0 = x0 + *(srcjidim+3)*ker3;
            x0 = x0 + *(srcjidim+4)*ker4;
            x0 = x0 + *(srcjidim+5)*ker5;
            x0 = x0 + *(srcjidim+6)*ker6;
            x0 = x0 + *(srcjidim+7)*ker7;srcjidim += dim;
            x0 = x0 + *(srcjidim+0)*ker8;
            x0 = x0 + *(srcjidim+1)*ker9;
            x0 = x0 + *(srcjidim+2)*ker10;
            x0 = x0 + *(srcjidim+3)*ker11;
            x0 = x0 + *(srcjidim+4)*ker12;
            x0 = x0 + *(srcjidim+5)*ker13;
            x0 = x0 + *(srcjidim+6)*ker14;
            x0 = x0 + *(srcjidim+7)*ker15;srcjidim += dim;
            x0 = x0 + *(srcjidim+0)*ker16;
            x0 = x0 + *(srcjidim+1)*ker17;
            x0 = x0 + *(srcjidim+2)*ker18;
            x0 = x0 + *(srcjidim+3)*ker19;
            x0 = x0 + *(srcjidim+4)*ker20;
            x0 = x0 + *(srcjidim+5)*ker21;
            x0 = x0 + *(srcjidim+6)*ker22;
            x0 = x0 + *(srcjidim+7)*ker23;srcjidim += dim;
            x0 = x0 + *(srcjidim+0)*ker24;
            x0 = x0 + *(srcjidim+1)*ker25;
            x0 = x0 + *(srcjidim+2)*ker26;
            x0 = x0 + *(srcjidim+3)*ker27;
            x0 = x0 + *(srcjidim+4)*ker28;
            x0 = x0 + *(srcjidim+5)*ker29;
            x0 = x0 + *(srcjidim+6)*ker30;
            x0 = x0 + *(srcjidim+7)*ker31;srcjidim += dim;
            x0 = x0 + *(srcjidim+0)*ker32;
            x0 = x0 + *(srcjidim+1)*ker33;
            x0 = x0 + *(srcjidim+2)*ker34;
            x0 = x0 + *(srcjidim+3)*ker35;
            x0 = x0 + *(srcjidim+4)*ker36;
            x0 = x0 + *(srcjidim+5)*ker37;
            x0 = x0 + *(srcjidim+6)*ker38;
            x0 = x0 + *(srcjidim+7)*ker39;srcjidim += dim;
            x0 = x0 + *(srcjidim+0)*ker40;
            x0 = x0 + *(srcjidim+1)*ker41;
            x0 = x0 + *(srcjidim+2)*ker42;
            x0 = x0 + *(srcjidim+3)*ker43;
            x0 = x0 + *(srcjidim+4)*ker44;
            x0 = x0 + *(srcjidim+5)*ker45;
            x0 = x0 + *(srcjidim+6)*ker46;
            x0 = x0 + *(srcjidim+7)*ker47;srcjidim += dim;
            x0 = x0 + *(srcjidim+0)*ker48;
            x0 = x0 + *(srcjidim+1)*ker49;
            x0 = x0 + *(srcjidim+2)*ker50;
            x0 = x0 + *(srcjidim+3)*ker51;
            x0 = x0 + *(srcjidim+4)*ker52;
            x0 = x0 + *(srcjidim+5)*ker53;
            x0 = x0 + *(srcjidim+6)*ker54;
            x0 = x0 + *(srcjidim+7)*ker55;srcjidim += dim;
            x0 = x0 + *(srcjidim+0)*ker56;
            x0 = x0 + *(srcjidim+1)*ker57;
            x0 = x0 + *(srcjidim+2)*ker58;
            x0 = x0 + *(srcjidim+3)*ker59;
            x0 = x0 + *(srcjidim+4)*ker60;
            x0 = x0 + *(srcjidim+5)*ker61;
            x0 = x0 + *(srcjidim+6)*ker62;
            x0 = x0 + *(srcjidim+7)*ker63;        
            dst[j + i*dim] = x0;
            //////////////////////////////////////
            srcjidim = src+j+1+i*dim;

            x1 = x1 + *(srcjidim+0)*ker0;
            x1 = x1 + *(srcjidim+1)*ker1;
            x1 = x1 + *(srcjidim+2)*ker2;
            x1 = x1 + *(srcjidim+3)*ker3;
            x1 = x1 + *(srcjidim+4)*ker4;
            x1 = x1 + *(srcjidim+5)*ker5;
            x1 = x1 + *(srcjidim+6)*ker6;
            x1 = x1 + *(srcjidim+7)*ker7;srcjidim += dim;
            x1 = x1 + *(srcjidim+0)*ker8;
            x1 = x1 + *(srcjidim+1)*ker9;
            x1 = x1 + *(srcjidim+2)*ker10;
            x1 = x1 + *(srcjidim+3)*ker11;
            x1 = x1 + *(srcjidim+4)*ker12;
            x1 = x1 + *(srcjidim+5)*ker13;
            x1 = x1 + *(srcjidim+6)*ker14;
            x1 = x1 + *(srcjidim+7)*ker15;srcjidim += dim;
            x1 = x1 + *(srcjidim+0)*ker16;
            x1 = x1 + *(srcjidim+1)*ker17;
            x1 = x1 + *(srcjidim+2)*ker18;
            x1 = x1 + *(srcjidim+3)*ker19;
            x1 = x1 + *(srcjidim+4)*ker20;
            x1 = x1 + *(srcjidim+5)*ker21;
            x1 = x1 + *(srcjidim+6)*ker22;
            x1 = x1 + *(srcjidim+7)*ker23;srcjidim += dim;
            x1 = x1 + *(srcjidim+0)*ker24;
            x1 = x1 + *(srcjidim+1)*ker25;
            x1 = x1 + *(srcjidim+2)*ker26;
            x1 = x1 + *(srcjidim+3)*ker27;
            x1 = x1 + *(srcjidim+4)*ker28;
            x1 = x1 + *(srcjidim+5)*ker29;
            x1 = x1 + *(srcjidim+6)*ker30;
            x1 = x1 + *(srcjidim+7)*ker31;srcjidim += dim;
            x1 = x1 + *(srcjidim+0)*ker32;
            x1 = x1 + *(srcjidim+1)*ker33;
            x1 = x1 + *(srcjidim+2)*ker34;
            x1 = x1 + *(srcjidim+3)*ker35;
            x1 = x1 + *(srcjidim+4)*ker36;
            x1 = x1 + *(srcjidim+5)*ker37;
            x1 = x1 + *(srcjidim+6)*ker38;
            x1 = x1 + *(srcjidim+7)*ker39;srcjidim += dim;
            x1 = x1 + *(srcjidim+0)*ker40;
            x1 = x1 + *(srcjidim+1)*ker41;
            x1 = x1 + *(srcjidim+2)*ker42;
            x1 = x1 + *(srcjidim+3)*ker43;
            x1 = x1 + *(srcjidim+4)*ker44;
            x1 = x1 + *(srcjidim+5)*ker45;
            x1 = x1 + *(srcjidim+6)*ker46;
            x1 = x1 + *(srcjidim+7)*ker47;srcjidim += dim;
            x1 = x1 + *(srcjidim+0)*ker48;
            x1 = x1 + *(srcjidim+1)*ker49;
            x1 = x1 + *(srcjidim+2)*ker50;
            x1 = x1 + *(srcjidim+3)*ker51;
            x1 = x1 + *(srcjidim+4)*ker52;
            x1 = x1 + *(srcjidim+5)*ker53;
            x1 = x1 + *(srcjidim+6)*ker54;
            x1 = x1 + *(srcjidim+7)*ker55;srcjidim += dim;
            x1 = x1 + *(srcjidim+0)*ker56;
            x1 = x1 + *(srcjidim+1)*ker57;
            x1 = x1 + *(srcjidim+2)*ker58;
            x1 = x1 + *(srcjidim+3)*ker59;
            x1 = x1 + *(srcjidim+4)*ker60;
            x1 = x1 + *(srcjidim+5)*ker61;
            x1 = x1 + *(srcjidim+6)*ker62;
            x1 = x1 + *(srcjidim+7)*ker63;
            dst[j+1 + i*dim] = x1;            
        }
    }
}


char convolution_descr[] = "Dot product: Current working version";
void convolution(int dim,int *src, int *ker,int *dst) 
{
    //naive_conv(dim,src,ker,dst);
    convolution1(dim,src,ker,dst);
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





void matrix_multiplication1(int dim,int *src, int *src2,int *dst) 
{
    int i,j,k;
    int x0,x1,x2,x3,x4,x5,x6,x7;
    int x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31; 
    int y0,y1,y2,y3,y4,y5,y6,y7;
    int y8,y9,y10,y11,y12,y13,y14,y15,y16,y17,y18,y19,y20,y21,y22,y23,y24,y25,y26,y27,y28,y29,y30,y31; 
    int z0,z1,z2,z3,z4,z5,z6,z7;
    int z8,z9,z10,z11,z12,z13,z14,z15,z16,z17,z18,z19,z20,z21,z22,z23,z24,z25,z26,z27,z28,z29,z30,z31; 
    int t0,t1,t2,t3,t4,t5,t6,t7;
    int t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22,t23,t24,t25,t26,t27,t28,t29,t30,t31; 
    
    //int srckidim0,srckidim1,srckidim2,srckidim3,srckidim4,srckidim5,srckidim6,srckidim7;
    int idim,kdim;
    int sr2cjkdim, sr2cjkdim1, sr2cjkdim2, sr2cjkdim3;
    int * srckidim;  // * dstjidim
    
    for(i = 0; i < dim; i = i+32)
    {
        for(j = 0; j < dim; j = j+4)
        {            
			x0 = 0;x1 = 0;x2 = 0;x3 = 0;x4 = 0;x5 = 0;x6 = 0;x7 = 0;
            x8 = 0;x9 = 0;x10 = 0;x11 = 0;x12 = 0;x13 = 0;x14 = 0;x15 = 0;
            x16 = 0;x17 = 0;x18 = 0;x19 = 0;x20 = 0;x21 = 0;x22 = 0;x23 = 0;
            x24 = 0;x25 = 0;x26 = 0;x27 = 0;x28 = 0;x29 = 0;x30 = 0;x31 = 0;

            y0 = 0;y1 = 0;y2 = 0;y3 = 0;y4 = 0;y5 = 0;y6 = 0;y7 = 0;
            y8 = 0;y9 = 0;y10 = 0;y11 = 0;y12 = 0;y13 = 0;y14 = 0;y15 = 0;
            y16 = 0;y17 = 0;y18 = 0;y19 = 0;y20 = 0;y21 = 0;y22 = 0;y23 = 0;
            y24 = 0;y25 = 0;y26 = 0;y27 = 0;y28 = 0;y29 = 0;y30 = 0;y31 = 0;

            z0 = 0;z1 = 0;z2 = 0;z3 = 0;z4 = 0;z5 = 0;z6 = 0;z7 = 0;
            z8 = 0;z9 = 0;z10 = 0;z11 = 0;z12 = 0;z13 = 0;z14 = 0;z15 = 0;
            z16 = 0;z17 = 0;z18 = 0;z19 = 0;z20 = 0;z21 = 0;z22 = 0;z23 = 0;
            z24 = 0;z25 = 0;z26 = 0;z27 = 0;z28 = 0;z29 = 0;z30 = 0;z31 = 0;

            t0 = 0;t1 = 0;t2 = 0;t3 = 0;t4 = 0;t5 = 0;t6 = 0;t7 = 0;
            t8 = 0;t9 = 0;t10 = 0;t11 = 0;t12 = 0;t13 = 0;t14 = 0;t15 = 0;
            t16 = 0;t17 = 0;t18 = 0;t19 = 0;t20 = 0;t21 = 0;t22 = 0;t23 = 0;
            t24 = 0;t25 = 0;t26 = 0;t27 = 0;t28 = 0;t29 = 0;t30 = 0;t31 = 0;

            idim = i*dim;
            //dstjidim = dst+(j + idim); 
            for(k = 0; k < dim; k++)
            {
                //x0  = x0  + src[k + (i+1)*dim]*src2[j + k*dim];
                kdim = k*dim;
                srckidim = src+(k + idim);
                sr2cjkdim = src2[j + kdim];
                sr2cjkdim1 = src2[j+1 + kdim];
                sr2cjkdim2 = src2[j+2 + kdim];
                sr2cjkdim3 = src2[j+3 + kdim];
                /*
                srckidim0 = *(srckidim);
                srckidim1 = *(srckidim+1*dim);
                srckidim2 = *(srckidim+2*dim);
                srckidim3 = *(srckidim+3*dim);
                srckidim4 = *(srckidim+4*dim);
                srckidim5 = *(srckidim+5*dim);
                srckidim6 = *(srckidim+6*dim);
                srckidim7 = *(srckidim+7*dim);*/

                x0  = x0  + *(srckidim+ 0 *dim)*sr2cjkdim;
                x1  = x1  + *(srckidim+ 1 *dim)*sr2cjkdim;
                x2  = x2  + *(srckidim+ 2 *dim)*sr2cjkdim;
                x3  = x3  + *(srckidim+ 3 *dim)*sr2cjkdim;
                x4  = x4  + *(srckidim+ 4 *dim)*sr2cjkdim;
                x5  = x5  + *(srckidim+ 5 *dim)*sr2cjkdim;
                x6  = x6  + *(srckidim+ 6 *dim)*sr2cjkdim;
                x7  = x7  + *(srckidim+ 7 *dim)*sr2cjkdim;
                x8  = x8  + *(srckidim+ 8 *dim)*sr2cjkdim;
                x9  = x9  + *(srckidim+ 9 *dim)*sr2cjkdim;
                x10 = x10 + *(srckidim+ 10*dim)*sr2cjkdim;
                x11 = x11 + *(srckidim+ 11*dim)*sr2cjkdim;
                x12 = x12 + *(srckidim+ 12*dim)*sr2cjkdim;
                x13 = x13 + *(srckidim+ 13*dim)*sr2cjkdim;
                x14 = x14 + *(srckidim+ 14*dim)*sr2cjkdim;
                x15 = x15 + *(srckidim+ 15*dim)*sr2cjkdim;
                x16 = x16 + *(srckidim+ 16*dim)*sr2cjkdim;
                x17 = x17 + *(srckidim+ 17*dim)*sr2cjkdim;
                x18 = x18 + *(srckidim+ 18*dim)*sr2cjkdim;
                x19 = x19 + *(srckidim+ 19*dim)*sr2cjkdim;
                x20 = x20 + *(srckidim+ 20*dim)*sr2cjkdim;
                x21 = x21 + *(srckidim+ 21*dim)*sr2cjkdim;
                x22 = x22 + *(srckidim+ 22*dim)*sr2cjkdim;
                x23 = x23 + *(srckidim+ 23*dim)*sr2cjkdim;
                x24 = x24 + *(srckidim+ 24*dim)*sr2cjkdim;
                x25 = x25 + *(srckidim+ 25*dim)*sr2cjkdim;
                x26 = x26 + *(srckidim+ 26*dim)*sr2cjkdim;
                x27 = x27 + *(srckidim+ 27*dim)*sr2cjkdim;
                x28 = x28 + *(srckidim+ 28*dim)*sr2cjkdim;
                x29 = x29 + *(srckidim+ 29*dim)*sr2cjkdim;
                x30 = x30 + *(srckidim+ 30*dim)*sr2cjkdim;
                x31 = x31 + *(srckidim+ 31*dim)*sr2cjkdim;

                y0  = y0  + *(srckidim+ 0 *dim)*sr2cjkdim1;
                y1  = y1  + *(srckidim+ 1 *dim)*sr2cjkdim1;
                y2  = y2  + *(srckidim+ 2 *dim)*sr2cjkdim1;
                y3  = y3  + *(srckidim+ 3 *dim)*sr2cjkdim1;
                y4  = y4  + *(srckidim+ 4 *dim)*sr2cjkdim1;
                y5  = y5  + *(srckidim+ 5 *dim)*sr2cjkdim1;
                y6  = y6  + *(srckidim+ 6 *dim)*sr2cjkdim1;
                y7  = y7  + *(srckidim+ 7 *dim)*sr2cjkdim1;
                y8  = y8  + *(srckidim+ 8 *dim)*sr2cjkdim1;
                y9  = y9  + *(srckidim+ 9 *dim)*sr2cjkdim1;
                y10 = y10 + *(srckidim+ 10*dim)*sr2cjkdim1;
                y11 = y11 + *(srckidim+ 11*dim)*sr2cjkdim1;
                y12 = y12 + *(srckidim+ 12*dim)*sr2cjkdim1;
                y13 = y13 + *(srckidim+ 13*dim)*sr2cjkdim1;
                y14 = y14 + *(srckidim+ 14*dim)*sr2cjkdim1;
                y15 = y15 + *(srckidim+ 15*dim)*sr2cjkdim1;
                y16 = y16 + *(srckidim+ 16*dim)*sr2cjkdim1;
                y17 = y17 + *(srckidim+ 17*dim)*sr2cjkdim1;
                y18 = y18 + *(srckidim+ 18*dim)*sr2cjkdim1;
                y19 = y19 + *(srckidim+ 19*dim)*sr2cjkdim1;
                y20 = y20 + *(srckidim+ 20*dim)*sr2cjkdim1;
                y21 = y21 + *(srckidim+ 21*dim)*sr2cjkdim1;
                y22 = y22 + *(srckidim+ 22*dim)*sr2cjkdim1;
                y23 = y23 + *(srckidim+ 23*dim)*sr2cjkdim1;
                y24 = y24 + *(srckidim+ 24*dim)*sr2cjkdim1;
                y25 = y25 + *(srckidim+ 25*dim)*sr2cjkdim1;
                y26 = y26 + *(srckidim+ 26*dim)*sr2cjkdim1;
                y27 = y27 + *(srckidim+ 27*dim)*sr2cjkdim1;
                y28 = y28 + *(srckidim+ 28*dim)*sr2cjkdim1;
                y29 = y29 + *(srckidim+ 29*dim)*sr2cjkdim1;
                y30 = y30 + *(srckidim+ 30*dim)*sr2cjkdim1;
                y31 = y31 + *(srckidim+ 31*dim)*sr2cjkdim1;
                
                z0  = z0  + *(srckidim+ 0 *dim)*sr2cjkdim2;
                z1  = z1  + *(srckidim+ 1 *dim)*sr2cjkdim2;
                z2  = z2  + *(srckidim+ 2 *dim)*sr2cjkdim2;
                z3  = z3  + *(srckidim+ 3 *dim)*sr2cjkdim2;
                z4  = z4  + *(srckidim+ 4 *dim)*sr2cjkdim2;
                z5  = z5  + *(srckidim+ 5 *dim)*sr2cjkdim2;
                z6  = z6  + *(srckidim+ 6 *dim)*sr2cjkdim2;
                z7  = z7  + *(srckidim+ 7 *dim)*sr2cjkdim2;
                z8  = z8  + *(srckidim+ 8 *dim)*sr2cjkdim2;
                z9  = z9  + *(srckidim+ 9 *dim)*sr2cjkdim2;
                z10 = z10 + *(srckidim+ 10*dim)*sr2cjkdim2;
                z11 = z11 + *(srckidim+ 11*dim)*sr2cjkdim2;
                z12 = z12 + *(srckidim+ 12*dim)*sr2cjkdim2;
                z13 = z13 + *(srckidim+ 13*dim)*sr2cjkdim2;
                z14 = z14 + *(srckidim+ 14*dim)*sr2cjkdim2;
                z15 = z15 + *(srckidim+ 15*dim)*sr2cjkdim2;
                z16 = z16 + *(srckidim+ 16*dim)*sr2cjkdim2;
                z17 = z17 + *(srckidim+ 17*dim)*sr2cjkdim2;
                z18 = z18 + *(srckidim+ 18*dim)*sr2cjkdim2;
                z19 = z19 + *(srckidim+ 19*dim)*sr2cjkdim2;
                z20 = z20 + *(srckidim+ 20*dim)*sr2cjkdim2;
                z21 = z21 + *(srckidim+ 21*dim)*sr2cjkdim2;
                z22 = z22 + *(srckidim+ 22*dim)*sr2cjkdim2;
                z23 = z23 + *(srckidim+ 23*dim)*sr2cjkdim2;
                z24 = z24 + *(srckidim+ 24*dim)*sr2cjkdim2;
                z25 = z25 + *(srckidim+ 25*dim)*sr2cjkdim2;
                z26 = z26 + *(srckidim+ 26*dim)*sr2cjkdim2;
                z27 = z27 + *(srckidim+ 27*dim)*sr2cjkdim2;
                z28 = z28 + *(srckidim+ 28*dim)*sr2cjkdim2;
                z29 = z29 + *(srckidim+ 29*dim)*sr2cjkdim2;
                z30 = z30 + *(srckidim+ 30*dim)*sr2cjkdim2;
                z31 = z31 + *(srckidim+ 31*dim)*sr2cjkdim2;

                t0  = t0  + *(srckidim+ 0 *dim)*sr2cjkdim3;
                t1  = t1  + *(srckidim+ 1 *dim)*sr2cjkdim3;
                t2  = t2  + *(srckidim+ 2 *dim)*sr2cjkdim3;
                t3  = t3  + *(srckidim+ 3 *dim)*sr2cjkdim3;
                t4  = t4  + *(srckidim+ 4 *dim)*sr2cjkdim3;
                t5  = t5  + *(srckidim+ 5 *dim)*sr2cjkdim3;
                t6  = t6  + *(srckidim+ 6 *dim)*sr2cjkdim3;
                t7  = t7  + *(srckidim+ 7 *dim)*sr2cjkdim3;
                t8  = t8  + *(srckidim+ 8 *dim)*sr2cjkdim3;
                t9  = t9  + *(srckidim+ 9 *dim)*sr2cjkdim3;
                t10 = t10 + *(srckidim+ 10*dim)*sr2cjkdim3;
                t11 = t11 + *(srckidim+ 11*dim)*sr2cjkdim3;
                t12 = t12 + *(srckidim+ 12*dim)*sr2cjkdim3;
                t13 = t13 + *(srckidim+ 13*dim)*sr2cjkdim3;
                t14 = t14 + *(srckidim+ 14*dim)*sr2cjkdim3;
                t15 = t15 + *(srckidim+ 15*dim)*sr2cjkdim3;
                t16 = t16 + *(srckidim+ 16*dim)*sr2cjkdim3;
                t17 = t17 + *(srckidim+ 17*dim)*sr2cjkdim3;
                t18 = t18 + *(srckidim+ 18*dim)*sr2cjkdim3;
                t19 = t19 + *(srckidim+ 19*dim)*sr2cjkdim3;
                t20 = t20 + *(srckidim+ 20*dim)*sr2cjkdim3;
                t21 = t21 + *(srckidim+ 21*dim)*sr2cjkdim3;
                t22 = t22 + *(srckidim+ 22*dim)*sr2cjkdim3;
                t23 = t23 + *(srckidim+ 23*dim)*sr2cjkdim3;
                t24 = t24 + *(srckidim+ 24*dim)*sr2cjkdim3;
                t25 = t25 + *(srckidim+ 25*dim)*sr2cjkdim3;
                t26 = t26 + *(srckidim+ 26*dim)*sr2cjkdim3;
                t27 = t27 + *(srckidim+ 27*dim)*sr2cjkdim3;
                t28 = t28 + *(srckidim+ 28*dim)*sr2cjkdim3;
                t29 = t29 + *(srckidim+ 29*dim)*sr2cjkdim3;
                t30 = t30 + *(srckidim+ 30*dim)*sr2cjkdim3;
                t31 = t31 + *(srckidim+ 31*dim)*sr2cjkdim3;             
                
            }
            /* *(dstjidim)      = x0;*(dstjidim+1*dim)  = x1;*(dstjidim+2*dim)  = x2;*(dstjidim+3*dim)  = x3;            
            *(dstjidim+4*dim)  = x4;*(dstjidim+5*dim)  = x5;*(dstjidim+6*dim)  = x6;*(dstjidim+7*dim)  = x7; */

            dst[j + idim]       = x0 ;dst[j + idim+1*dim] = x1 ;dst[j + idim+2*dim] = x2 ;dst[j + idim+3*dim] = x3 ;
            dst[j + idim+4*dim] = x4 ;dst[j + idim+5*dim] = x5 ;dst[j + idim+6*dim] = x6 ;dst[j + idim+7*dim] = x7 ;
            dst[j + (i+8 )*dim] = x8 ;dst[j + (i+9 )*dim]  = x9;dst[j + (i+10)*dim] = x10;dst[j + (i+11)*dim] = x11;
            dst[j + (i+12)*dim] = x12;dst[j + (i+13)*dim] = x13;dst[j + (i+14)*dim] = x14;dst[j + (i+15)*dim] = x15;
            dst[j + (i+16)*dim] = x16;dst[j + (i+17)*dim] = x17;dst[j + (i+18)*dim] = x18;dst[j + (i+19)*dim] = x19;
            dst[j + (i+20)*dim] = x20;dst[j + (i+21)*dim] = x21;dst[j + (i+22)*dim] = x22;dst[j + (i+23)*dim] = x23;
            dst[j + (i+24)*dim] = x24;dst[j + (i+25)*dim] = x25;dst[j + (i+26)*dim] = x26;dst[j + (i+27)*dim] = x27;
            dst[j + (i+28)*dim] = x28;dst[j + (i+29)*dim] = x29;dst[j + (i+30)*dim] = x30;dst[j + (i+31)*dim] = x31;j++;
            

            dst[j + idim]       = y0 ;dst[j + idim+1*dim] = y1 ;dst[j + idim+2*dim] = y2 ;dst[j + idim+3*dim] = y3 ;
            dst[j + idim+4*dim] = y4 ;dst[j + idim+5*dim] = y5 ;dst[j + idim+6*dim] = y6 ;dst[j + idim+7*dim] = y7 ;
            dst[j + (i+8 )*dim] = y8 ;dst[j + (i+9 )*dim] = y9 ;dst[j + (i+10)*dim] = y10;dst[j + (i+11)*dim] = y11;
            dst[j + (i+12)*dim] = y12;dst[j + (i+13)*dim] = y13;dst[j + (i+14)*dim] = y14;dst[j + (i+15)*dim] = y15;
            dst[j + (i+16)*dim] = y16;dst[j + (i+17)*dim] = y17;dst[j + (i+18)*dim] = y18;dst[j + (i+19)*dim] = y19;
            dst[j + (i+20)*dim] = y20;dst[j + (i+21)*dim] = y21;dst[j + (i+22)*dim] = y22;dst[j + (i+23)*dim] = y23;
            dst[j + (i+24)*dim] = y24;dst[j + (i+25)*dim] = y25;dst[j + (i+26)*dim] = y26;dst[j + (i+27)*dim] = y27;
            dst[j + (i+28)*dim] = y28;dst[j + (i+29)*dim] = y29;dst[j + (i+30)*dim] = y30;dst[j + (i+31)*dim] = y31;j++;

            dst[j + idim]       = z0 ;dst[j + idim+1*dim] = z1 ;dst[j + idim+2*dim] = z2 ;dst[j + idim+3*dim] = z3 ;
            dst[j + idim+4*dim] = z4 ;dst[j + idim+5*dim] = z5 ;dst[j + idim+6*dim] = z6 ;dst[j + idim+7*dim] = z7 ;
            dst[j + (i+8 )*dim] = z8 ;dst[j + (i+9 )*dim]  = z9;dst[j + (i+10)*dim] = z10;dst[j + (i+11)*dim] = z11;
            dst[j + (i+12)*dim] = z12;dst[j + (i+13)*dim] = z13;dst[j + (i+14)*dim] = z14;dst[j + (i+15)*dim] = z15;
            dst[j + (i+16)*dim] = z16;dst[j + (i+17)*dim] = z17;dst[j + (i+18)*dim] = z18;dst[j + (i+19)*dim] = z19;
            dst[j + (i+20)*dim] = z20;dst[j + (i+21)*dim] = z21;dst[j + (i+22)*dim] = z22;dst[j + (i+23)*dim] = z23;
            dst[j + (i+24)*dim] = z24;dst[j + (i+25)*dim] = z25;dst[j + (i+26)*dim] = z26;dst[j + (i+27)*dim] = z27;
            dst[j + (i+28)*dim] = z28;dst[j + (i+29)*dim] = z29;dst[j + (i+30)*dim] = z30;dst[j + (i+31)*dim] = z31;j++;
            

            dst[j + idim]       = t0 ;dst[j + idim+1*dim] = t1 ;dst[j + idim+2*dim] = t2 ;dst[j + idim+3*dim] = t3 ;
            dst[j + idim+4*dim] = t4 ;dst[j + idim+5*dim] = t5 ;dst[j + idim+6*dim] = t6 ;dst[j + idim+7*dim] = t7 ;
            dst[j + (i+8 )*dim] = t8 ;dst[j + (i+9 )*dim] = t9 ;dst[j + (i+10)*dim] = t10;dst[j + (i+11)*dim] = t11;
            dst[j + (i+12)*dim] = t12;dst[j + (i+13)*dim] = t13;dst[j + (i+14)*dim] = t14;dst[j + (i+15)*dim] = t15;
            dst[j + (i+16)*dim] = t16;dst[j + (i+17)*dim] = t17;dst[j + (i+18)*dim] = t18;dst[j + (i+19)*dim] = t19;
            dst[j + (i+20)*dim] = t20;dst[j + (i+21)*dim] = t21;dst[j + (i+22)*dim] = t22;dst[j + (i+23)*dim] = t23;
            dst[j + (i+24)*dim] = t24;dst[j + (i+25)*dim] = t25;dst[j + (i+26)*dim] = t26;dst[j + (i+27)*dim] = t27;
            dst[j + (i+28)*dim] = t28;dst[j + (i+29)*dim] = t29;dst[j + (i+30)*dim] = t30;dst[j + (i+31)*dim] = t31;j = j-3;


            /*dst[j+1 + idim]      = y0;dst[j+1  + idim+1*dim]  = y1;dst[j+1  + idim+2*dim]  = y2;dst[j+1  + idim+3*dim]  = y3;            
            dst[j+1 + idim+4*dim]  = y4;dst[j+1  + idim+5*dim]  = y5;dst[j+1  + idim+6*dim]  = y6;dst[j+1  + idim+7*dim]  = y7;

            dst[j+2 + idim]      = z0;dst[j+2  + idim+1*dim]  = z1;dst[j+2  + idim+2*dim]  = z2;dst[j+2  + idim+3*dim]  = z3;            
            dst[j+2 + idim+4*dim]  = z4;dst[j+2  + idim+5*dim]  = z5;dst[j+2  + idim+6*dim]  = z6;dst[j+2  + idim+7*dim]  = z7;

            dst[j+3 + idim]      = t0;dst[j+3  + idim+1*dim]  = t1;dst[j+3  + idim+2*dim]  = t2;dst[j+3  + idim+3*dim]  = t3;            
            dst[j+3 + idim+4*dim]  = t4;dst[j+3  + idim+5*dim]  = t5;dst[j+3  + idim+6*dim]  = t6;dst[j+3  + idim+7*dim]  = t7; */

			/* dst[j + i*dim]      = x0;dst[j  + (i+1)*dim]  = x1;dst[j  + (i+2)*dim]  = x2;dst[j  + (i+3)*dim]  = x3;            
            dst[j + (i+4)*dim]  = x4;dst[j  + (i+5)*dim]  = x5;dst[j  + (i+6)*dim]  = x6;dst[j  + (i+7)*dim]  = x7; */
                 
        
        }		
    }
    for(; i < dim; i++)
    {
        for(; j < dim; j++) 
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
char matrix_multiplication_descr[] = "Matrix multiplications: Current working version";
void matrix_multiplication(int dim,int *src, int *src2,int *dst)
{
    //naive_matrix_multiplication(dim,src,src2,dst);
    matrix_multiplication1(dim,src,src2,dst);
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


