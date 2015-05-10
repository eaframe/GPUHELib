#ifndef _GPU_H_
#define _GPU_H_

cudaStream_t *stream;
int num_streams = 0;
long *vector_A = NULL;
long length_A = 0;
long *vector_B1 = NULL;
long length_B1 = 0;
long *vector_B2 = NULL;
long length_B2 = 0;
long *vector_C = NULL;
long length_C = 0;

long *ithPrimes = NULL;
long length_ithPrimes = 0;

long *ns = NULL;
long length_ns = 0; 

#endif
