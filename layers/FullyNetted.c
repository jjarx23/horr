#include <stdlib.h>
#include <stdarg.h>
#include "FullyNetted.h"
#include "FullyNetted.r.h"

#define UNIT_NAME "FullyNetted"

static void *fullnet(int out, int in, void *kernelInit, void *biasInit, void *activator)
{
    return neu(FullyNetted, out, in, kernelInit, biasInit, activator);
}

static void *build(void *layer, void *input)
{
    if (!graphNode(layer))
    {
        void *corr = jCG.Xcorrelation(input, jCG.var(kernI(layer, 0)));
        if (noOfKerns(layer) == 2)
            jCG.add(corr, jCG.var(kernI(layer, 1)));
        setGraphNode(layer, corr);
        return corr;
    }
    warn("%s: rebuilding layer\n", UNIT_NAME);
    return 0;
}

static void cstr(void *layer, va_list *arg)
{ // set up all weights and biases only
    // dim
    int outDim = va_arg(*arg, int);
    // inputdim
    int inDim = va_arg(*arg, int);
    // kernel shape
    int shape[2] = {inDim, outDim};
    // weight
    void *weight = positionalKernel(arg, 2, shape, Initializers.zeros);
    // bias
    void *bias = optionalKernel(arg, 1, outDim);
    // initialize kernels holder
    initKerns(layer, bias ? 2 : 1);
    // insert kernels
    setKernI(layer, 0, weight);
    if (bias)
        setKernI(layer, 1, bias);
    // activating fn
    void *act = va_arg(*arg, void *);
    setBlockMeta(layer, act ? act : Activators.identity);
}

static void dstr(void *layer)
{
    superdstr(FullyNetted, layer);
}

static FullyNettedClass_st Class;
const void *FullyNetted = 0;

// assigning inheritance and overrides
static void __attribute__((constructor)) fullynettedClassf()
{
    if (FullyNetted)
        return;
    jao$$horrCnstr$$();
    *(void **)&horr.nn.fullynetted = fullnet;
    weightblockLC();
    mut(FullyNetted, void *, &Class);
    memcpy(FullyNetted, WeightBlock, sizeof(WeightBlockClass_st));
    (*(ObjClass_t)&Class).size = sizeof(FullyNetted_st);
    (*(ObjClass_t)&Class).super = WeightBlock;
    static const char name[] = "FullyNetted";
    (*(ObjClass_t)&Class).name = name;
    (*(ObjClass_t)&Class).cstr = cstr;
    (*(BlockClass_t)&Class).build = build;
}
const fn_t fullynettedLC = fullynettedClassf;
// other implentation go here
