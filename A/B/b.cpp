
#include "b.h"
#include "D/d.h"
#include "curand.h"
#include <iostream>
#include <curand_kernel.h>
#include <curand.h>
#include <cufft.h>

void B::greet()
{
    D d;
    d.greet();
    printf("i'm b\n");

    greet_from_kernel();




	cufftHandle plan;
	cufftComplex* data;

#define NX 256 
#define BATCH 10

	cudaMalloc((void**)&data,
		sizeof(cufftComplex) * NX * BATCH);
	/* Create a 1D FFT plan.  */

	cufftPlan1d(&plan, NX, CUFFT_C2C, BATCH);
}


