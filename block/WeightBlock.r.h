#ifndef WEIGHTBLOCK_R_H
#define WEIGHTBLOCK_R_H

#include "Block.r.h"

#ifdef __cplusplus
extern 'C'
{
#endif

    extern const fn_t weightblockLC;

    typedef struct WeightBlockClass *WeightBlockClass_t;
    typedef struct WeightBlockClass WeightBlockClass_st;
    typedef struct WeightBlock WeightBlock_st;
    struct WeightBlockClass
    {
        BlockClass_st _;
        // other members go here
    };
    struct WeightBlock
    {
        const Block_st _;
        // other members go here
        const void **kerns;
        const char *isTrainable;
        const int noOfKerns;
    };
    /*--------------------------------*/
    static inline void setKerns(WeightBlock_t v, void *list, int n)
    {
        if (v->noOfKerns)
        {
            fatalErr("%s: kernel is set already, instead call setKernI()\n", "WeightBlock");
        }
        if (n > 1)
        {
            v->kerns = list;
            v->isTrainable = malloc(n * sizeof(char));
            memset(v->isTrainable, 0, n);
        }
        *(int *)&v->noOfKerns = n;
    }
    static inline void initKerns(WeightBlock_t v, int n)
    {
        if (n > 1)
            return setKerns(v, malloc(n * sizeof(void *)), n);
        else
            return setKerns(v, 0, n);
    }
    static inline void brkKerns(WeightBlock_t w)
    {
        if (!w->noOfKerns)
            return;
        else if (w->noOfKerns > 1)
        {
            for (int i = 0; i < w->noOfKerns; i++)
            {
                if (!w->kerns[i])
                    continue;
                detach(w->kerns[i]);
                del(w->kerns[i]);
            }
            free(w->kerns);
            free(w->isTrainable);
        }
        else
        {
            detach(w->kerns);
            del(w->kerns);
        }
    }
    static inline void *kernI(WeightBlock_t b, int i)
    {
        if (b->noOfKerns == 1)
            return *(void **)&b->kerns;
        else
            return b->kerns;
    }
    static inline void setKernI(WeightBlock_t b, int i, void *n)
    {
        detach(b->noOfKerns > 1 ? b->kerns[i] : b->kerns);
        if (b->noOfKerns == 1)
            *(void **)&b->kerns = n;
        else
            b->kerns[i] = n;
        attach(n);
    }
    static inline void *positionalKernel(va_list * arg, int rank, int *shape, void *(*defaultInit)(int, int *))
    {
        void *kernel = va_arg(*arg, void *);
        return kernel = kernel ? Initializer.get(kernel, rank, shape) : defaultInit(rank, shape);
    }
    static inline void *optionalKernel(va_list * arg, int rank, int *shape)
    {
        void *kernel = va_arg(*arg, void *);
        if (kernel)
            kernel = Initializer.get(kernel, rank, shape);
        return kernel;
    }
    static inline int noOfKerns(WeightBlock_t w)
    {
        return w->noOfKerns;
    }

#ifdef __cplusplus
}
#endif
#endif