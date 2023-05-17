#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "Convolution.h"
#include "Convolution.r.h"

#define UNIT_NAME "Convolution"

static void *convolution(int out, int in, int rank, int *filtershape, void *weightInit, void *biasInit, void *activator)
{
    return neu(Convolution, out, in, rank, filtershape, weightInit, biasInit, activator);
}
static void *build(void *layer, void *input)
{
    if (!graphNode(layer))
    {
        void *corr = jCG.xcorrelation(input, jCG.var(kernI(layer, 0)));
        if (noOfKerns(layer) == 2)
            jCG.add(corr, jCG.var(kernI(layer, 1)));
        setGraphNode(layer, corr);
        return corr;
    }
    warn("%s: rebuilding layer\n", UNIT_NAME);
    return 0;
}
static void cstr(void *layer, va_list *arg)
{
    // set up all weights and biases only
    // dim
    int outDim = va_arg(*arg, int);
    // inputdim
    int inDim = va_arg(*arg, int);
    // set rank of layer
    int rank = va_arg(*arg, int);
    //[filter shape]
    int *filter = va_arg(*arg, int *);
    if (!filter)
    {
        fatalErr("%s: filter shape is required\n", UNIT_NAME);
    }
    // kern shape
    int fshape[1 + rank];
    memcpy(fshape, filter, rank * sizeof(int));
    fshape[rank] = outDim;
    // X-correlation weight
    void *weight = positionalKernel(arg, 1 + rank, fshape, Initializers.zeros);
    // X-correlation bias
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
    superdstr(Convolution, layer);
}
static ConvolutionClass_st Class;
const void *Convolution = 0;

// assigning inheritance and overrides
static void __attribute__((constructor)) convolutionClassf()
{
    if (Convolution)
        return;
    jao$$horrCnstr$$();
    *(void **)&horr.nn.convolution = convolution;
    weightblockLC();
    mut(Convolution, void *, &Class);
    memcpy((void *)Convolution, WeightBlock, sizeof(WeightBlockClass_st));
    static const char name[] = "Convolution";
    (*(ObjClass_t)&Class).name = name;
    (*(ObjClass_t)&Class).size = sizeof(Convolution_st);
    (*(ObjClass_t)&Class).super = WeightBlock;
    (*(ObjClass_t)&Class).cstr = cstr;
    (*(BlockClass_t)&Class).build = build;
}
const fn_t convolutionLC = convolutionClassf;
// other implentation go here
