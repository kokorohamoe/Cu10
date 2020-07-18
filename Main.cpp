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
#if defined __CUDACC__
    dim3 block(1000);
    dim3 thread(1000,2)
#endif

    int *dst = new int[N];
    int *src = new int[N];

    for(int i=0;i<N;i++){src[i]=775;}

#if defined __CUDACC__
    std::cout <<"Support CUDA CC "<<__CUDA_ARCH__ <<std::endl;
#else
    std::cout <<"disable CUDA CC"<<std::endl;
#endif

    kernel
#if defined __CUDACC__
    <<<block,
        thread>>>
#endif
    (dst,src);
    

   return (int)false;
}