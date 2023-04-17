#ifndef BLOCK_R_H
#define BLOCK_R_H

#include <Obj.r.h>
#include "../util/Activators.r.h"
#include "../util/Initializers.r.h"

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
        void (*run)();
    };
    struct Block
    {
        const Obj_st _;
        // other members go here
        const void *meta;
    };
    /*--------------------------------*/
    static inline blockMeta(Block_t b)
    {
        return b->meta;
    }
    static inline setBlockMeta(Block_t b, void *v)
    {
        return *(void **)b->meta = v;
    }
#ifdef __cplusplus
}
#endif
#endif