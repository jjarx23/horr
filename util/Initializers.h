#ifndef INITIALIZERS_H
#define INITIALIZERS_H

#include <horr.h>

#ifdef __cplusplus
extern 'C'
{
#endif

#define Initializers horr.initializers

    struct initer_t
    {
        ///@brief initializes a kernel based on ptr info
        ///@param ptr kernel type
        void *(*get)(void *ptr, int rnk, int *shape, ...);
    };
    const extern struct initer_t Initializer;
#ifdef __cplusplus
}
#endif
#endif