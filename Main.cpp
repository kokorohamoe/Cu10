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
    #include "Cuda_dmy.h"
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

#if defined __CUDACC__
    dim3 block(10,10,10);
    dim3 thread(10,10,10);
#endif

    int *dst =new int[NN];
    int *src =new int[NN];;
    
    volatile int *cuda_dst=NULL;
    volatile int *cuda_src=NULL;

#if defined __CUDACC__
    cudaMalloc((void**)&cuda_src,N*sizeof(int));
    cudaMalloc((void**)&cuda_dst,N*sizeof(int));
#endif    

    for(int i=0;i<NN;i++) src[i] = 775;
#if defined __CUDACC__
    cudaMemcpy(cuda_src,src,sizeof(int)*N,cudaMemcpyHostToDevice);
#endif    

#if defined __CUDACC__
    //cuda dmy for g++/clang++
    kernel<<<block,thread>>>(cuda_dst,cuda_src);
#endif    
//return 0;
#if defined __CUDACC__
    cudaMemcpy(dst,cuda_dst,sizeof(int)*N,cudaMemcpyDeviceToHsot);
    cudaDeviceSynchronize();
#endif    
    std::cout <<"cudaDeviceSynchronize fin "<<std::endl;

    std::cout <<"unused N "<<N<<std::endl;

    int count = 0; 
    for(int i=0;i<N;i++) if (dst[i] == 775) count++;
    
#if defined __CUDACC__
    cudaFree((void*)cuda_src,N);
    cudaFree((void*)cuda_dst,N);
#endif    
    
    
    return (int)false;
}




/*


//#if defined CUDA
//int main() //$0.1
//#else
//int main(int argc,char **argv)//additional cost $0
//#endif
{
    Block test(1,1,1);
//    const int N = 1024*1024;
    const int N = 1000*2000;
;
    int *mem1 = new int[N];
    int *mem2 = new int[N];
    int *gpu1,*gpu2;
    cudaMalloc((void**)&gpu1,N*sizeof(int));
    cudaMalloc((void**)&gpu2,N*sizeof(int));
    for(int i=0;i<N;i++) mem1[i] = 775;
//return 0;
    cudaMemcpy(gpu1,mem1,sizeof(int)*N,cudaMemcpyHostToDevice);
    


#define KERNEL_NAME kernel
//#define KERNEL_BLOCK_NUM 3
#define KERNEL_PARAM gpu2,gpu1
   //    ↓↓↓↓↓↓↓se
    CUDA_KERNAL_CALL_HERE;

    cudaDeviceSynchronize();
    cudaMemcpy(mem2,gpu2,sizeof(int)*N,cudaMemcpyDeviceToHost);
    cudaDeviceSynchronize();
    
    int c=0;
    int d=0;
    int e=0;
    for(int i=0;i<N;i++) if(mem2[i]==mem1[i]){c++;}else if(mem1[i]==775){e++;}else{d++;}

    std::cout << "c=" << c << "    d=" << d<< "    e=" << e<<std::endl;
    std::cout << "0 is not support cuda and no soft emu"  <<std::endl;
    std::cout << "KERNEL_BLOCK_NUM=" << KERNEL_BLOCK_NUM <<std::endl;
    std::cout << "KERNEL_PARAM=" << KERNEL_THREAD_NUM <<std::endl;
    
#if !defined CUDA
    std::cout << "enabled soft cuda emu code" << std::endl;
#else
    cudaGetDeviceCount(&c);
    std::cout << "disabled soft cuda / cuda device count = "<< c << std::endl;
#endif

   cudaFree(mem2);
    cudaFree(mem1);

    return (int)false;
}


*/



#endif