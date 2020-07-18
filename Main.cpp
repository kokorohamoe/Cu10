// Cu10 Tensor vs Matrox.cpp
// Cu09 Tensor vs Matrox.cpp
//
//

#define NN (1000*1000)
#define THREADperBLOCK 1000

#if !defined NOPAIZE
#define __PAIZACC__
#endif
#include <iostream>
#include <string.h>
#include <vector>


#if defined __CUDACC__ 
    #include <cuddea_runtime.h>// additional cost $0.01
#elif defined __PAIZACC__
//    #include <cuddea_runtime.h>
//      use dmy code include 
//    #include "Cuda_dmy.h"
#elif defined __clang__ 
    #include <cuda_runtime.h>
#elif defined __GNUC_
    #include <cuda_runtim.h>
#else
#endif

    //#include "Cuda_dmy.h"
#if defined __PAIZACC__
    const int N=(1000);
#else
    const int N=(1000*1000);
#endif


#if 0

//Cuda compile $0.0 this code for cuda native
//gcc support x1.5-x3,0 compile and easy dummy 
//clang ask 
//vcc
//intel cc

//Main.cpp:53:5: note: suggested alternative: ‘__sync_synchronize’
#if defined __CUDACC__
    __global__ //cuda keyword
#endif
void kernel
(
    int *dst,
    int *src
){
#if defined __CUDACC__
            dst[blockIdx.x*KERNEL_THREAD_NUM*2+threadIdx.x] = src[blockIdx.x*KERNEL_THREAD_NUM+threadIdx.x];
#endif
}


#define CUDA_ARG void
using func_type = void(*)(int *,int *);

int main( CUDA_ARG ){
    std::cout <<"CUDA matrix tensor test\n"<<std::flush;
    return (int)false;
}