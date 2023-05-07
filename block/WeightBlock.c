#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "WeightBlock.h"
#include "WeightBlock.r.h"

static void dstr(void *obj)
{
    brkKerns(obj);
}
static WeightBlockClass_st Class;
const void *WeightBlock = 0;

// assigning inheritance and overrides
static void __attribute__((constructor)) weightblockClassf()
{
    if (WeightBlock)
        return;
    blockLC();
    mut(WeightBlock, void *, &Class);
    memcpy((void *)WeightBlock, Block, sizeof(BlockClass_st));
    static const char name[] = "WeightBlock";
    (*(ObjClass_t)&Class).name = name;
    (*(ObjClass_t)&Class).size = sizeof(WeightBlock_st);
    (*(ObjClass_t)&Class).super = Block;
}
const fn_t weightblockLC = weightblockClassf;
