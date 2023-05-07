#ifndef BLOCK_R_H
#define BLOCK_R_H

#include <Obj.r.h>
#include "../util/Activators.r.h"
#include "../util/Initializers.r.h"
#include "../horr.r.h"

#ifdef __cplusplus
extern 'C'
{
#endif
    typedef void *(*voidf)();

    extern const fn_t blockLC;

    typedef struct BlockClass *BlockClass_t;
    typedef struct BlockClass BlockClass_st;
    typedef struct Block Block_st;
    struct BlockClass
    {
        ObjClass_st _;
        // other members go here
        void *(*build)(void *layer, void *inputnode);
        void *(*eval)(void *layer, void *input);
    };
    struct Block
    {
        const Obj_st _;
        // other members go here
        const void *meta;
        const void *graphNode;
    };
    /*--------------------------------*/
    static inline void *blockMeta(Block_t b)
    {
        return b->meta;
    }
    static inline void setBlockMeta(Block_t b, void *v)
    {
        *(void **)&b->meta = v;
    }
    /// @brief build a layer
    /// @param layer layer to build
    /// @param inputnode input computation node to use
    /// @return layer's computation output node
    static inline void *buildLayer(Block_t layer, void *inputnode)
    {
        return ((BlockClass_t)classOf(layer))->build(layer, inputnode);
    }
    static inline void setGraphNode(Block_t layer, void *node)
    {
        *(void **)&layer->graphNode = node;
    }
    static inline void *graphNode(Block_t layer)
    {
        return layer->graphNode;
    }

#ifdef __cplusplus
}
#endif
#endif