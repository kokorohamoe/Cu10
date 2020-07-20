
#if defined __CUDACC__ 
    #include <cuda_runtime.h>// additional cost $0.01
#endif

class test{
    public:
        int block;
        int thread;
        
        float time;
        
        test(): 
            time (-1),
            block(1),
            thread(1)
        {
            ;
        }
        void run()=0;
    
};