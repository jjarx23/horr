#ifndef MODEL_R_H
#define MODEL_R_H

#include "Block.r.h"

#ifdef __cplusplus
extern 'C'
{
#endif

    extern const fn_t modelLC;

    typedef struct ModelClass *ModelClass_t;
    typedef struct ModelClass ModelClass_st;
    typedef struct Model Model_st;
    struct ModelClass
    {
        BlockClass_st _;
    };
    struct Model
    {
        const Block_st _;
        const void *graphNode;
    };
    static inline void setModelGraphNode(Model_t layer, void *node)
    {
        *(void **)&layer->graphNode = node;
    }
    static inline void* modelGraphNode(Model_t layer)
    {
        return layer->graphNode;
    }

#ifdef __cplusplus
}
#endif
#endif