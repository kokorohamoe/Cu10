// Cu10 Tensor vs Matrox.cpp if no cuda dmy code
// Cu09 Tensor vs Matrox.cpp
//
//

#define NN (1000*1000)
#define KERNEL_THREAD_NUM 1000
#define KERNEL_THREAD_NUM_X 1000

#if !defined NOPAIZE
#define __PAIZACC__
#endif
#include <iostream>
#include <string.h>
#include <vector>

       #include <sys/time.h>
       #include <sys/resource.h>
struct timespec ts_res;
struct timespec ts_start;
struct timespec ts_stop;
#define CLOCKID CLOCK_REALTIME
float operator - (struct timespec &tv_stop,struct timespec &tv_start){
    float r1;
    float r2;
    r1 = tv_stop.tv_sec - tv_start.tv_sec;
    r2 = tv_stop.tv_nsec - tv_start.tv_nsec;
    r1 *= (1000*1000);
    r2 /= 1000;
    return r1+r2;
}

#define clock_stop     ::clock_gettime(CLOCKID ,&ts_stop)
#define clock_start     ::clock_gettime(CLOCKID ,&ts_start)
#define clock_out       std::cout <<"clock : "<<(ts_stop -ts_start)<<std::endl;
#define clock_save(x)       x = (ts_stop -(ts_start))


#if defined __CUDACC__ 
    #include <cuda_runtime.h>// additional cost $0.01
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
    dim3 thread(1000,2);
#endif

    int *dst = new int[N];
    int *src = new int[N];
    int *dst_device=NULL;
    int *src_device=NULL;

#if defined __CUDACC__
    cudaMalloc(&dst_device,sizeof(int)*N);
    cudaMalloc(&src_device,sizeof(int)*N);
#endif
    for(int i=0;i<N;i++){src[i]=775;}

#if defined __CUDACC__ && defined __CUDA_ARCH__
    std::cout <<"Support CUDA CC "<<__CUDA_ARCH__ <<std::endl;
#elif defined __CUDACC__ && !defined __CUDA_ARCH__
    std::cout <<"Support CUDA CC " <<std::endl;
#else
    std::cout <<"disable CUDA CC"<<std::endl;
#endif

clock_start;

    kernel
#if defined __CUDACC__
    <<<block,
        thread>>>
#endif
    (dst,src);

#if defined __CUDACC__
    cudaDeviceSynchronize();
#endif
    clock_stop;

#if defined __CUDACC__
    int c=0;
    cudaGetDeviceCount(&c);
    std::cout << "disabled soft cuda / cuda device count = "<< c << std::endl;
#endif
//    clock_out;
    
    int count =-1;
    for(int i=0;i<N;i++){ if(dst[i]==775) count++;dst[i]=0; /*trick add $0.1*/}
    
    std::cout <<"simple cuda copy == "<<count <<std::endl;
    clock_out;
    std::cout <<std::endl;

#if defined __CUDACC__
    cudaFree(src_device);
    cudaFree(dst_device);
#endif
   return (int)false;
}


