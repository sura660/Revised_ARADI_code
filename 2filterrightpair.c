#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "functions.h"

// Main Function
int main() {
	srand(time(NULL));
	uint32_t Delta[4] = {0x10800010, 0x00000000, 0x00000000, 0x00000000};
	uint32_t Delta1[4] = {0xef7fffef,0xef7fffef, 0xef7fffef, 0xef7fffef};
        
        uint32_t key[8];
	int non_zero[3] = {4,23,28};
	int cntt;
	uint32_t key_d[4] = {0x12345678,0x98765430,0x17359257,0x19263540};
	uint8_t diff_8[6] = {0x5,0x7,0x8,0xa,0xd,0xf};
	uint64_t tcount=0,ncount,ncntt,ntot_cnt=0,count;
        uint32_t p1[4], deltap[4] ;
	uint32_t p2[4] ;
        uint32_t c1[4],c2[4],t1[4],t2[4],c11[4],c22[4], deciphered[4], delta_c[4], delta_cc[4];
	uint32_t out[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
	uint8_t temp[3],temp1[3];
	int col9[9] = {0,3,8,9,14,17,26,27,31};
	int col3[3] = {3,8,27};
	int loop;



	for(loop = 0; loop < (200); loop++){
		count=0;
		ncount=0;
		for(int i = 0; i < 8; i++){
                    key[i] = rand() & 0xffffffff;   
                }
		for(int i=0; i < 4;i++){	
			p1[i] = rand() & 0xffffffff;
			p2[i] = p1[i] ^ Delta[i];     
			}



		printf("\n");

		encryption_ARADI(p1, key, c1);
		encryption_ARADI(p2, key, c2);
			




		for(int i = 0; i < 4; i++){
			c11[i] = c1[i];
			c22[i] = c2[i];
			}


        // Guessing 36 positions of L_{10}^{-1}(k_11)
		
		for(uint64_t gkey = 0 ; gkey < ((uint64_t)(1)<<36) ; gkey++){

			for(int i=0; i < 4;i++) {
				c1[i] = c11[i];
				c2[i] = c22[i];
				}



			c1[0] = linear(2, c1[0]);
		        c1[1] = linear(2, c1[1]);
		        c1[2] = linear(2, c1[2]);
		        c1[3] = linear(2, c1[3]);

			c2[0] = linear(2, c2[0]);
		        c2[1] = linear(2, c2[1]);
		        c2[2] = linear(2, c2[2]);
		        c2[3] = linear(2, c2[3]);


			for(int i=0; i < 4;i++) delta_c[i] = c1[i]^c2[i];


			for(int i=0; i < 4;i++) {
				for(int j = 0; j < 9; j++){
					c1[i] = c1[i] ^ (((gkey >> 9*i+j)&1) << (31-col9[j])); 
					c2[i] = c2[i] ^ (((gkey >> 9*i+j)&1) << (31-col9[j]));
					}
				
				}




	




			sbox_inverse(&c1[0], &c1[1], &c1[2], &c1[3]);
			sbox_inverse(&c2[0], &c2[1], &c2[2], &c2[3]);




			for(int i=0; i < 4;i++) delta_c[i] = c1[i]^c2[i];

			delta_c[0] = linear(1, delta_c[0]);
		        delta_c[1] = linear(1, delta_c[1]);
		        delta_c[2] = linear(1, delta_c[2]);
		        delta_c[3] = linear(1, delta_c[3]);




			int cnt = 0;
			for(int i=0; i < 4;i++){ 
				delta_cc[i] = delta_c[i] & Delta1[i];
				if(delta_cc[i] == 0)
					cnt++;
				}
			if(cnt == 4){
				for(int i = 0; i < 3; i++)
					temp[i] = (((delta_c[0] >> non_zero[i])&1)<<3) ^ (((delta_c[1] >> non_zero[i])&1)<<2) ^ (((delta_c[2] >> non_zero[i])&1)<<1) ^ ((delta_c[3] >> non_zero[i])&1) ;
				cntt = 0;
				for(int i = 0; i < 6; i++){ 
					if(temp[0] == diff_8[i])
						for(int ii = 0; ii < 6; ii++)
							if(temp[1] == diff_8[ii])
								for(int iii = 0; iii < 6; iii++)
									if(temp[2] == diff_8[iii]){
										cntt++;
										break;
										}
 					}
				if(cntt == 1){
					count++;

					// Guessing 12 positions of L_9^{-1}(k_10)
					
					for(uint64_t gkey10 = 0 ; gkey10 < ((uint64_t)(1)<<12) ; gkey10++){
					  for(int i=0;i<4;i++){
                                          t1[i] = c1[i];
                                          t2[i] = c2[i];
                                       }
				  for(int i=0; i < 4;i++) {
				     for(int j = 0; j < 3; j++){
					t1[i] = t1[i] ^ (((gkey10 >> 3*i+j)&1) << (31-col3[j])); 
					t2[i] = t2[i] ^ (((gkey10 >> 3*i+j)&1) << (31-col3[j]));
				     }
				
				  }
				  
				  sbox_inverse(&t1[0], &t1[1], &t1[2], &t1[3]);
			          sbox_inverse(&t2[0], &t2[1], &t2[2], &t2[3]);	
			          
			          for(int i=0; i < 4;i++) delta_c[i] = t1[i]^t2[i];
			          
			          for(int i = 0; i < 3; i++)
			          temp1[i] = (((delta_c[0] >> non_zero[i])&1)<<3) ^ (((delta_c[1] >> non_zero[i])&1)<<2) ^ (((delta_c[2] >> non_zero[i])&1)<<1) ^ ((delta_c[3] >> non_zero[i])&1) ;
			          if(temp1[0] == 8 && temp1[1] == 8 && temp1[2] == 8){
			              ncount++;
			              }
			          
			         
			          
			          
			          }
					}				
				}

			}
		printf("\n\t\tTotal count = %ld \n\n",count);
		printf("\n\t\t Last Total Count = %ld\n\n", ncount);
		tcount = tcount + count;
		ntot_cnt = ntot_cnt + ncount;
		}

	printf("\n\t\tAverage count = %ld \n\n",tcount/loop);
	printf("\n\tAverage  Last count = %f\n\n ",(float)ntot_cnt/loop);


    
    return 0;
}

