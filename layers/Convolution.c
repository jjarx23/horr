#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "Convolution.h"
#include "Convolution.r.h"

static void cstr(void *obj, va_list *arg)
{
    // set up all weights and biases only
    // inputdim
    int inDim = va_arg(*arg, int);
    // dim
    int outDim = va_arg(*arg, int);
    // set rank of layer
    int rank = va_arg(*arg, int);
    //[filter shape]
    int *filter = va_arg(*arg, int *);
    if (!filter)
    {
        printf("filter shape is required\n");
        exit(-1);
    }
    initKerns(obj, 1);
    // kern shape
    int fshape[1 + rank];
    memcpy(fshape, filter, rank);
    fshape[rank] = outDim;
    // X-correlation map
    void *map = va_arg(*arg, void *);
    if (map)
    {
        setKernI(obj, 0, Initializer.get(map, 1 + rank, fshape));
    }
    else
        setKernI(obj, 0, Initializers.zeros(1 + rank, fshape));
    // activating fn
    void *act = va_arg(*arg, void *);
    setBlockMeta(obj, act ? act : Activators.identity);
}
static void dstr(void *obj)
{
    superdstr(Convolution, obj);
}
/*
//implement if necessary

//other implentation go here
static int rpr(const void *b, char *str, int length){
    return printf("Convolution %p \n", b);
}
*/
static ConvolutionClass_st Class;
const void *Convolution = 0;

// assigning inheritance and overrides
static void __attribute__((constructor)) convolutionClassf()
{
    if (Convolution)
        return;
    jao$$horrCnstr$$();
    weightblockLC();
    mut(Convolution, void *, &Class);
    memcpy((void *)Convolution, WeightBlock, sizeof(WeightBlockClass_st));
    static const char name[] = "Convolution";
    (*(ObjClass_t)&Class).name = name;
    (*(ObjClass_t)&Class).size = sizeof(Convolution_st);
    (*(ObjClass_t)&Class).super = WeightBlock;
    (*(ObjClass_t)&Class).cstr = cstr;
}
const fn_t convolutionLC = convolutionClassf;
// other implentation go here
