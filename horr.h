#ifndef HORR_H
#define HORR_H

#include "Flow.h"

#ifdef __cplusplus
extern 'C'
{
#endif
    typedef void *(*Initializer_t)(int rank, int *shape, ...);
    typedef struct horr
    {
        struct
        {
            int *(*INT)(int length, ...);
            int *(*DBL)(int length, ...);
        } array;
        struct
        {
            void *sigmoid;
            void *tanh;
            void *identity;
        } activators;
        struct
        {
            void *(*prepped)(void *kern);
            Initializer_t zeros;
            Initializer_t ones;
        } initializers;
        struct
        {
            void *(*convolution)(int out, int in, int convRank, int *filterShape, void *kernInitializer, void *activator);
        } nn;
    } horr_t;
    extern const horr_t horr;
// other declarations go here
#ifdef __cplusplus
}
#endif
#endif