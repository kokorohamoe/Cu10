// Cu10 Tensor vs Matrox.cpp if no cuda-dmy code
// Cu09 Tensor vs Matrox.cpp
//
//fork first. If you can , it is your own copy.

/*
t2
./a.out
CUDA matrix tensor test
simple　for copy == 1000
clock : 6.439

simple　for copy 2nd (cpu cache?)  == 1000
clock : 4.309

Support CUDA CC
disabled soft cuda / cuda device count = 1
simple cuda copy == -1
clock : 14.064
*/

#define NN (1000*1000)
#define KERNEL_THREAD_NUM 1000
#define KERNEL_THREAD_NUM_X 1000

#if !defined NOPAIZE
#define __PAIZACC__
#endif
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


#if defined __CUDACC__
    __global__ //cuda keyword
#endif
void kernel3
(
    int *dst,
    int *src
){
#if defined __CUDACC__
            int x = src[blockIdx.x*KERNEL_THREAD_NUM+threadIdx.x];
            dst[blockIdx.x*KERNEL_THREAD_NUM*2+threadIdx.x] = x*x*x+x*x*+x+1;
#endif
}


#define CUDA_ARG void
using func_type = void(*)(int *,int *);

int main( CUDA_ARG ){
    int count ;
    count = -1;
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
    count = 0;
    for(int i=0;i<N;i++){src[i]=115;}
clock_start;
    for(int i=0;i<N;i++){dst[i]=src[i];}
clock_stop;
    for(int i=0;i<N;i++){ if(dst[i]==115) count++;dst[i]=0; /*trick add $0.1*/}
    std::cout <<"simple　CPU for copy == "<<count <<std::endl;
    clock_out;
    std::cout <<std::endl;
    for(int i=0;i<N;i++){src[i]=117;}
clock_start;
    for(int i=0;i<N;i++){dst[i]=src[i];}
clock_stop;
    count = 0;
    for(int i=0;i<N;i++){ if(dst[i]==117) count++;dst[i]=0; /*trick add $0.1*/}
    std::cout <<"simple CPU for copy 2nd (cpu cache?)  == "<<count <<std::endl;
    clock_out;
    std::cout <<std::endl;

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
    
    count =-1;
    for(int i=0;i<N;i++){ if(dst[i]==775) count++;dst[i]=0; /*trick add $0.1*/}
    
    std::cout <<"simple cuda copy == "<<count <<std::endl;
    clock_out;
    std::cout <<std::endl;


    int x3,x;
    x=3;
    
    for(int i=0;i<N;i++){src[i]=x;}
clock_start;
    for(int i=0;i<N;i++){
        volatile int tx = src[i];
        dst[i]=tx*tx*tx+tx*tx+tx+1;
    }
clock_stop;
    for(int i=0;i<N;i++){ if(dst[i]==115) count++;dst[i]=0; /*trick add $0.1*/}
    std::cout <<"simple　CPU for pow x,3 == "<<count <<std::endl;
    clock_out;
    std::cout <<std::endl;



#if defined __CUDACC__
    cudaFree(src_device);
    cudaFree(dst_device);
#endif
   return (int)false;
}


