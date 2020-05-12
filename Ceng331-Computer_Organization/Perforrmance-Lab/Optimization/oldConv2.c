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
    int i,j,k,l;

    int ker0  = ker[dim*0+0],ker1  = ker[dim*0+1],ker2  = ker[dim*0+2],ker3  = ker[dim*0+3],ker4  = ker[dim*0+4],ker5  = ker[dim*0+5],ker6  = ker[dim*0+6],ker7  = ker[dim*0+7];
    int ker8  = ker[dim*1+0],ker9 =  ker[dim*1+1],ker10 = ker[dim*1+2],ker11 = ker[dim*1+3],ker12 = ker[dim*1+4],ker13 = ker[dim*1+5],ker14 = ker[dim*1+6],ker15 = ker[dim*1+7];
    int ker16 = ker[dim*2+0],ker17 = ker[dim*2+1],ker18 = ker[dim*2+2],ker19 = ker[dim*2+3],ker20 = ker[dim*2+4],ker21 = ker[dim*2+5],ker22 = ker[dim*2+6],ker23 = ker[dim*2+7];
    int ker24 = ker[dim*3+0],ker25 = ker[dim*3+1],ker26 = ker[dim*3+2],ker27 = ker[dim*3+3],ker28 = ker[dim*3+4],ker29 = ker[dim*3+5],ker30 = ker[dim*3+6],ker31 = ker[dim*3+7];
    int ker32 = ker[dim*4+0],ker33 = ker[dim*4+1],ker34 = ker[dim*4+2],ker35 = ker[dim*4+3],ker36 = ker[dim*4+4],ker37 = ker[dim*4+5],ker38 = ker[dim*4+6],ker39 = ker[dim*4+7];
    int ker40 = ker[dim*5+0],ker41 = ker[dim*5+1],ker42 = ker[dim*5+2],ker43 = ker[dim*5+3],ker44 = ker[dim*5+4],ker45 = ker[dim*5+5],ker46 = ker[dim*5+6],ker47 = ker[dim*5+7];
    int ker48 = ker[dim*6+0],ker49 = ker[dim*6+1],ker50 = ker[dim*6+2],ker51 = ker[dim*6+3],ker52 = ker[dim*6+4],ker53 = ker[dim*6+5],ker54 = ker[dim*6+6],ker55 = ker[dim*6+7];
    int ker56 = ker[dim*7+0],ker57 = ker[dim*7+1],ker58 = ker[dim*7+2],ker59 = ker[dim*7+3],ker60 = ker[dim*7+4],ker61 = ker[dim*7+5],ker62 = ker[dim*7+6],ker63 = ker[dim*7+7];
    
    int x0,x1,x2,x3,x4;/*x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31;
    int x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,x54,x55,x56,x57,x58,x59,x60,x61,x62,x63; */
    int * srcjidim;

    for(i = 0; i < dim-8+1; i++)
    {
        for(j = 0; j < dim-8+1; j = j+2)
        {
            //dst[j*dim+i] = 0;
            x0  = 0;x1  = 0;x2  = 0;x3  = 0,x4  = 0;/*x5  = 0;x6  = 0;x7  = 0;
            x8  = 0;x9  = 0;x10 = 0;x11 = 0;x12 = 0;x13 = 0;x14 = 0;x15 = 0;
            x16 = 0;x17 = 0;x18 = 0;x19 = 0;x20 = 0;x21 = 0;x22 = 0;x23 = 0;
            x24 = 0;x25 = 0;x26 = 0;x27 = 0;x28 = 0;x29 = 0;x30 = 0;x31 = 0;
            x32 = 0;x33 = 0;x34 = 0;x35 = 0;x36 = 0;x37 = 0;x38 = 0;x39 = 0;
            x40 = 0;x41 = 0;x42 = 0;x43 = 0;x44 = 0;x45 = 0;x46 = 0;x47 = 0;
            x48 = 0;x49 = 0;x50 = 0;x51 = 0;x52 = 0;x53 = 0;x54 = 0;x55 = 0;
            x56 = 0;x57 = 0;x58 = 0;x59 = 0;x60 = 0;x61 = 0;x62 = 0;x63 = 0; */

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
    //matmul_optimized3(dim,src,src2,dst);

    int i,j,k;
    int x0,x1,x2,x3,x4,x5,x6,x7;
    int y0,y1,y2,y3,y4,y5,y6,y7;
    int z0,z1,z2,z3,z4,z5,z6,z7;
    int t0,t1,t2,t3,t4,t5,t6,t7;
    int srckidim0,srckidim1,srckidim2,srckidim3,srckidim4,srckidim5,srckidim6,srckidim7;
    //int  x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31;
    int idim,kdim;
    int sr2cjkdim, sr2ctemp1, sr2ctemp2, sr2ctemp3;
    int * srckidim;  // * dstjidim
    
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

                srckidim0 = *(srckidim);
                srckidim1 = *(srckidim+1*dim);
                srckidim2 = *(srckidim+2*dim);
                srckidim3 = *(srckidim+3*dim);
                srckidim4 = *(srckidim+4*dim);
                srckidim5 = *(srckidim+5*dim);
                srckidim6 = *(srckidim+6*dim);
                srckidim7 = *(srckidim+7*dim);

                x0  = x0  + srckidim0*sr2cjkdim;
                x1  = x1  + srckidim1*sr2cjkdim;
                x2  = x2  + srckidim2*sr2cjkdim;
                x3  = x3  + srckidim3*sr2cjkdim;
                x4  = x4  + srckidim4*sr2cjkdim;
                x5  = x5  + srckidim5*sr2cjkdim;
                x6  = x6  + srckidim6*sr2cjkdim;
                x7  = x7  + srckidim7*sr2cjkdim;

                y0  = y0  + srckidim0*sr2ctemp1;
                y1  = y1  + srckidim1*sr2ctemp1;
                y2  = y2  + srckidim2*sr2ctemp1;
                y3  = y3  + srckidim3*sr2ctemp1;
                y4  = y4  + srckidim4*sr2ctemp1;
                y5  = y5  + srckidim5*sr2ctemp1;
                y6  = y6  + srckidim6*sr2ctemp1;
                y7  = y7  + srckidim7*sr2ctemp1;

                z0  = z0  + srckidim0*sr2ctemp2;
                z1  = z1  + srckidim1*sr2ctemp2;
                z2  = z2  + srckidim2*sr2ctemp2;
                z3  = z3  + srckidim3*sr2ctemp2;
                z4  = z4  + srckidim4*sr2ctemp2;
                z5  = z5  + srckidim5*sr2ctemp2;
                z6  = z6  + srckidim6*sr2ctemp2;
                z7  = z7  + srckidim7*sr2ctemp2;

                t0  = t0  + srckidim0*sr2ctemp3;
                t1  = t1  + srckidim1*sr2ctemp3;
                t2  = t2  + srckidim2*sr2ctemp3;
                t3  = t3  + srckidim3*sr2ctemp3;
                t4  = t4  + srckidim4*sr2ctemp3;
                t5  = t5  + srckidim5*sr2ctemp3;
                t6  = t6  + srckidim6*sr2ctemp3;
                t7  = t7  + srckidim7*sr2ctemp3;

             
                
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
char matrix_multiplication_descr[] = "Matrix multiplications: Current working version";
void matrix_multiplication(int dim,int *src, int *src2,int *dst)
{
    naive_matrix_multiplication(dim,src,src2,dst);
    //matrix_multiplication1(dim,src,src2,dst);
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


