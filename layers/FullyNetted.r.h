#ifndef FULLYNETTED_R_H
#define FULLYNETTED_R_H

#include "../block/WeightBlock.r.h"

#ifdef __cplusplus
extern 'C'
{
#endif

    extern const fn_t fullynettedLC;

    typedef struct FullyNettedClass *FullyNettedClass_t;
    typedef struct FullyNettedClass FullyNettedClass_st;
    typedef struct FullyNetted FullyNetted_st;
    struct FullyNettedClass
    {
        WeightBlockClass_st _;
        // other members go here
    };
    struct FullyNetted
    {
        const WeightBlock_st _;
        // other members go here
    };

#ifdef __cplusplus
}
#endif
#endif