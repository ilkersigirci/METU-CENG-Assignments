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

    int ker0  = ker[0 ],ker1  = ker[1 ],ker2  = ker[2 ],ker3  = ker[3 ],ker4  = ker[4 ],ker5  = ker[5 ],ker6  = ker[6 ],ker7  = ker[7 ],ker8  = ker[8 ],ker9 =  ker[9 ],ker10 = ker[10],ker11 = ker[11],ker12 = ker[12],ker13 = ker[13],ker14 = ker[14],ker15 = ker[15];
    int ker16 = ker[16],ker17 = ker[17],ker18 = ker[18],ker19 = ker[19],ker20 = ker[20],ker21 = ker[21],ker22 = ker[22],ker23 = ker[23],ker24 = ker[24],ker25 = ker[25],ker26 = ker[26],ker27 = ker[27],ker28 = ker[28],ker29 = ker[29],ker30 = ker[30],ker31 = ker[31];
    int ker32 = ker[32],ker33 = ker[33],ker34 = ker[34],ker35 = ker[35],ker36 = ker[36],ker37 = ker[37],ker38 = ker[38],ker39 = ker[39],ker40 = ker[40],ker41 = ker[41],ker42 = ker[42],ker43 = ker[43],ker44 = ker[44],ker45 = ker[45],ker46 = ker[46],ker47 = ker[47];
    int ker48 = ker[48],ker49 = ker[49],ker50 = ker[50],ker51 = ker[51],ker52 = ker[52],ker53 = ker[53],ker54 = ker[54],ker55 = ker[55],ker56 = ker[56],ker57 = ker[57],ker58 = ker[58],ker59 = ker[59],ker60 = ker[60],ker61 = ker[61],ker62 = ker[62],ker63 = ker[63];
    
    int x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31;
    int x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,x54,x55,x56,x57,x58,x59,x60,x61,x62,x63;

    for(i = 0; i < dim-8+1; i++)
    {
        for(j = 0; j < dim-8+1; j++)
        {
            //dst[j*dim+i] = 0;
            x0  = 0;x1  = 0;x2  = 0;x3  = 0;x4  = 0;x5  = 0;x6  = 0;x7  = 0;
            x8  = 0;x9  = 0;x10 = 0;x11 = 0;x12 = 0;x13 = 0;x14 = 0;x15 = 0;
            x16 = 0;x17 = 0;x18 = 0;x19 = 0;x20 = 0;x21 = 0;x22 = 0;x23 = 0;
            x24 = 0;x25 = 0;x26 = 0;x27 = 0;x28 = 0;x29 = 0;x30 = 0;x31 = 0;
            x32 = 0;x33 = 0;x34 = 0;x35 = 0;x36 = 0;x37 = 0;x38 = 0;x39 = 0;
            x40 = 0;x41 = 0;x42 = 0;x43 = 0;x44 = 0;x45 = 0;x46 = 0;x47 = 0;
            x48 = 0;x49 = 0;x50 = 0;x51 = 0;x52 = 0;x53 = 0;x54 = 0;x55 = 0;
            x56 = 0;x57 = 0;x58 = 0;x59 = 0;x60 = 0;x61 = 0;x62 = 0;x63 = 0;

            /////////////////////////////////////////
            //dst[j + i*dim] = dst[j + i*dim] +src[(j+k)+(i+l)*dim]*ker[l*dim+k]
            x0  = x0  + src[(j+0)+(i+0)*dim]*ker0;
            x1  = x1  + src[(j+1)+(i+0)*dim]*ker1;
            x2  = x2  + src[(j+2)+(i+0)*dim]*ker2;
            x3  = x3  + src[(j+3)+(i+0)*dim]*ker3;
            x4  = x4  + src[(j+4)+(i+0)*dim]*ker4;
            x5  = x5  + src[(j+5)+(i+0)*dim]*ker5;
            x6  = x6  + src[(j+6)+(i+0)*dim]*ker6;
            x7  = x7  + src[(j+7)+(i+0)*dim]*ker7;
            x8  = x8  + src[(j+0)+(i+1)*dim]*ker8;
            x9  = x9  + src[(j+1)+(i+1)*dim]*ker9;
            x10 = x10 + src[(j+2)+(i+1)*dim]*ker10;
            x11 = x11 + src[(j+3)+(i+1)*dim]*ker11;
            x12 = x12 + src[(j+4)+(i+1)*dim]*ker12;
            x13 = x13 + src[(j+5)+(i+1)*dim]*ker13;
            x14 = x14 + src[(j+6)+(i+1)*dim]*ker14;
            x15 = x15 + src[(j+7)+(i+1)*dim]*ker15;
            x16 = x16 + src[(j+0)+(i+2)*dim]*ker16;
            x17 = x17 + src[(j+1)+(i+2)*dim]*ker17;
            x18 = x18 + src[(j+2)+(i+2)*dim]*ker18;
            x19 = x19 + src[(j+3)+(i+2)*dim]*ker19;
            x20 = x20 + src[(j+4)+(i+2)*dim]*ker20;
            x21 = x21 + src[(j+5)+(i+2)*dim]*ker21;
            x22 = x22 + src[(j+6)+(i+2)*dim]*ker22;
            x23 = x23 + src[(j+7)+(i+2)*dim]*ker23;
            x24 = x24 + src[(j+0)+(i+3)*dim]*ker24;
            x25 = x25 + src[(j+1)+(i+3)*dim]*ker25;
            x26 = x26 + src[(j+2)+(i+3)*dim]*ker26;
            x27 = x27 + src[(j+3)+(i+3)*dim]*ker27;
            x28 = x28 + src[(j+4)+(i+3)*dim]*ker28;
            x29 = x29 + src[(j+5)+(i+3)*dim]*ker29;
            x30 = x30 + src[(j+6)+(i+3)*dim]*ker30;
            x31 = x31 + src[(j+7)+(i+3)*dim]*ker31;
            x32 = x32 + src[(j+0)+(i+4)*dim]*ker32;
            x33 = x33 + src[(j+1)+(i+4)*dim]*ker33;
            x34 = x34 + src[(j+2)+(i+4)*dim]*ker34;
            x35 = x35 + src[(j+3)+(i+4)*dim]*ker35;
            x36 = x36 + src[(j+4)+(i+4)*dim]*ker36;
            x37 = x37 + src[(j+5)+(i+4)*dim]*ker37;
            x38 = x38 + src[(j+6)+(i+4)*dim]*ker38;
            x39 = x39 + src[(j+7)+(i+4)*dim]*ker39;
            x40 = x40 + src[(j+0)+(i+5)*dim]*ker40;
            x41 = x41 + src[(j+1)+(i+5)*dim]*ker41;
            x42 = x42 + src[(j+2)+(i+5)*dim]*ker42;
            x43 = x43 + src[(j+3)+(i+5)*dim]*ker43;
            x44 = x44 + src[(j+4)+(i+5)*dim]*ker44;
            x45 = x45 + src[(j+5)+(i+5)*dim]*ker45;
            x46 = x46 + src[(j+6)+(i+5)*dim]*ker46;
            x47 = x47 + src[(j+7)+(i+5)*dim]*ker47;
            x48 = x48 + src[(j+0)+(i+6)*dim]*ker48;
            x49 = x49 + src[(j+1)+(i+6)*dim]*ker49;
            x50 = x50 + src[(j+2)+(i+6)*dim]*ker50;
            x51 = x51 + src[(j+3)+(i+6)*dim]*ker51;
            x52 = x52 + src[(j+4)+(i+6)*dim]*ker52;
            x53 = x53 + src[(j+5)+(i+6)*dim]*ker53;
            x54 = x54 + src[(j+6)+(i+6)*dim]*ker54;
            x55 = x55 + src[(j+7)+(i+6)*dim]*ker55;
            x56 = x56 + src[(j+0)+(i+7)*dim]*ker56;
            x57 = x57 + src[(j+1)+(i+7)*dim]*ker57;
            x58 = x58 + src[(j+2)+(i+7)*dim]*ker58;
            x59 = x59 + src[(j+3)+(i+7)*dim]*ker59;
            x60 = x60 + src[(j+4)+(i+7)*dim]*ker60;
            x61 = x61 + src[(j+5)+(i+7)*dim]*ker61;
            x62 = x62 + src[(j+6)+(i+7)*dim]*ker62;
            x63 = x63 + src[(j+7)+(i+7)*dim]*ker63;
            /////////////////////////////////////////
            /* for(k = 0; k < 8; k++)
            {
                for(l = 0; l < 8; l++) 
                {
                    //x0 = x0 +src[(i+l)*dim+(j+k)]*ker[l*dim+k];                    
                }
            } */
            /////////////////////////////////////////
            dst[j + i*dim] = x0;
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


