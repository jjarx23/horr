#ifndef CONVOLUTION_R_H
#define CONVOLUTION_R_H

#include "../block/WeightBlock.r.h"

#ifdef __cplusplus
extern 'C'
{
#endif

    extern const fn_t convolutionLC;

    typedef struct ConvolutionClass *ConvolutionClass_t;
    typedef struct ConvolutionClass ConvolutionClass_st;
    typedef struct Convolution Convolution_st;
    struct ConvolutionClass
    {
        WeightBlockClass_st _;
        // other members go here
    };
    struct Convolution
    {
        const WeightBlock_st _;
        // other members go here
    };

#ifdef __cplusplus
}
#endif
#endif