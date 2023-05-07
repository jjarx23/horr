#ifndef HORR_H
#define HORR_H

#define HORR_V_MAJ 0
#define HORR_V_MIN 2
#include <Flow.h>

#ifdef __cplusplus
extern 'C'
{
#endif
    typedef void *(*Initializer_t)(int rank, int *shape, ...);
    typedef struct horr
    {
        void *(*eval)(void *model, void *input);
        void (*version)(int *major, int *minor);
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
            void *(*model)(void *layer1, ...) __attribute__((sentinel));
            void *(*convolution)(int out, int in, int convRank, int *filterShape, void *kernInitializer, void *biasInitializer, void *activator);
            void *(*fullynetted)(int out, int in, void *kernelInit, void *biasInit, void *activator);
        } nn;
    } horr_t;
    extern const horr_t *horr_;
#define horr (*horr_)
// other declarations go here
#ifdef __cplusplus
}
#endif
#endif