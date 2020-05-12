char matmul_optimized3_descr[] = "matmul_optimized3";
void matmul_optimized3(int n, int *src1, int *src2, int *dst) {
    if (n != 32) {
        int nd = n >> 3;
        int *src2c = malloc(n*n*sizeof(int));
        
        int *src2i   = src2;
        int *src2cik = src2c;
        for (int i = n; i--; ) {
            int *src2cikj = src2cik;
            int *src2ij   = src2i;
            for (int j = nd; j--; ) 
            {
                int t0  = src2ij[0];
                int t1  = src2ij[1];
                int t2  = src2ij[2];
                int t3  = src2ij[3];
                int t4  = src2ij[4];
                int t5  = src2ij[5];
                int t6  = src2ij[6];
                int t7  = src2ij[7];

                *src2cikj = t0;
                src2cikj += n;

                *src2cikj = t1;
                src2cikj += n;

                *src2cikj = t2;
                src2cikj += n;

                *src2cikj = t3;
                src2cikj += n;

                *src2cikj = t4;
                src2cikj += n;

                *src2cikj = t5;
                src2cikj += n;

                *src2cikj = t6;
                src2cikj += n;

                *src2cikj = t7;
                src2cikj += n;

                src2ij += 8;

            }
            src2i += n;
            src2cik++;
        }    

        nd = n >> 5;
        dst += n-1;
        src2c += n*(n-1);
        for (int i = n; i--; ) {
            int *src2cj = src2c;
            int *dstij  = dst;
            for (int j = n; j--; ) {
                int acc0 = 0;
                int *src1ik  = src1;
                int *src2cjk = src2cj;
                for (int k = nd; k--; ) 
                {
                    acc0 += src1ik[0]*src2cjk[0];
                    acc0 += src1ik[1]*src2cjk[1];
                    acc0 += src1ik[2]*src2cjk[2];
                    acc0 += src1ik[3]*src2cjk[3];
                    acc0 += src1ik[4]*src2cjk[4];
                    acc0 += src1ik[5]*src2cjk[5];
                    acc0 += src1ik[6]*src2cjk[6];
                    acc0 += src1ik[7]*src2cjk[7];
                    acc0 += src1ik[8]*src2cjk[8];
                    acc0 += src1ik[9]*src2cjk[9];
                    acc0 += src1ik[10]*src2cjk[10];
                    acc0 += src1ik[11]*src2cjk[11];
                    acc0 += src1ik[12]*src2cjk[12];
                    acc0 += src1ik[13]*src2cjk[13];
                    acc0 += src1ik[14]*src2cjk[14];
                    acc0 += src1ik[15]*src2cjk[15];
                    acc0 += src1ik[16]*src2cjk[16];
                    acc0 += src1ik[17]*src2cjk[17];
                    acc0 += src1ik[18]*src2cjk[18];
                    acc0 += src1ik[19]*src2cjk[19];
                    acc0 += src1ik[20]*src2cjk[20];
                    acc0 += src1ik[21]*src2cjk[21];
                    acc0 += src1ik[22]*src2cjk[22];
                    acc0 += src1ik[23]*src2cjk[23];
                    acc0 += src1ik[24]*src2cjk[24];
                    acc0 += src1ik[25]*src2cjk[25];
                    acc0 += src1ik[26]*src2cjk[26];
                    acc0 += src1ik[27]*src2cjk[27];
                    acc0 += src1ik[28]*src2cjk[28];
                    acc0 += src1ik[29]*src2cjk[29];
                    acc0 += src1ik[30]*src2cjk[30];
                    acc0 += src1ik[31]*src2cjk[31];

                    src1ik  += 32;
                    src2cjk += 32;
                }

                *dstij-- = acc0;

                src2cj -= n;
            }
            src1 += n;
            dst  += n;
        }
    }
    
    else {
        int in = 0;
        for (int i = 32; i-- ; ) 
        {
            int r  = src1[in];
            int *dstij  = dst+in;
            
            dstij[0 ] = r * src2[0 ];
            dstij[1 ] = r * src2[1 ];
            dstij[2 ] = r * src2[2 ];
            dstij[3 ] = r * src2[3 ];
            dstij[4 ] = r * src2[4 ];
            dstij[5 ] = r * src2[5 ];
            dstij[6 ] = r * src2[6 ];
            dstij[7 ] = r * src2[7 ];
            dstij[8 ] = r * src2[8 ];
            dstij[9 ] = r * src2[9 ];
            dstij[10] = r * src2[10];
            dstij[11] = r * src2[11];
            dstij[12] = r * src2[12];
            dstij[13] = r * src2[13];
            dstij[14] = r * src2[14];
            dstij[15] = r * src2[15];
            dstij[16] = r * src2[16];
            dstij[17] = r * src2[17];
            dstij[18] = r * src2[18];
            dstij[19] = r * src2[19];
            dstij[20] = r * src2[20];
            dstij[21] = r * src2[21];
            dstij[22] = r * src2[22];
            dstij[23] = r * src2[23];
            dstij[24] = r * src2[24];
            dstij[25] = r * src2[25];
            dstij[26] = r * src2[26];
            dstij[27] = r * src2[27];
            dstij[28] = r * src2[28];
            dstij[29] = r * src2[29];
            dstij[30] = r * src2[30];
            dstij[31] = r * src2[31];

            in += 32;
        }

        int kn = 32;
        for (int k = 1; k < 32; k++) {
            int in = 0;
            int *src2i = src2 + kn;
            for (int i = 32; i--;) {
                int r  = src1[in+k];
                int *dstij  = dst+in;
                
                dstij[0 ] += r * src2i[0 ];
                dstij[1 ] += r * src2i[1 ];
                dstij[2 ] += r * src2i[2 ];
                dstij[3 ] += r * src2i[3 ];
                dstij[4 ] += r * src2i[4 ];
                dstij[5 ] += r * src2i[5 ];
                dstij[6 ] += r * src2i[6 ];
                dstij[7 ] += r * src2i[7 ];
                dstij[8 ] += r * src2i[8 ];
                dstij[9 ] += r * src2i[9 ];
                dstij[10] += r * src2i[10];
                dstij[11] += r * src2i[11];
                dstij[12] += r * src2i[12];
                dstij[13] += r * src2i[13];
                dstij[14] += r * src2i[14];
                dstij[15] += r * src2i[15];
                dstij[16] += r * src2i[16];
                dstij[17] += r * src2i[17];
                dstij[18] += r * src2i[18];
                dstij[19] += r * src2i[19];
                dstij[20] += r * src2i[20];
                dstij[21] += r * src2i[21];
                dstij[22] += r * src2i[22];
                dstij[23] += r * src2i[23];
                dstij[24] += r * src2i[24];
                dstij[25] += r * src2i[25];
                dstij[26] += r * src2i[26];
                dstij[27] += r * src2i[27];
                dstij[28] += r * src2i[28];
                dstij[29] += r * src2i[29];
                dstij[30] += r * src2i[30];
                dstij[31] += r * src2i[31];

                in += 32;
            }
            kn += 32;
        }
    }
}