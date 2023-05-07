#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "Block.h"
#include "Block.r.h"

static void build()
{
    err("%s: default build(), override this function\n", "Block");
}

static void eval()
{
    err("%s: default eval(), override this function\n", "Block");
}

static void *evalLayer(Block_t layer, void *input)
{
    return ((BlockClass_t)classOf(layer))->eval(layer, input);
}

static BlockClass_st Class;
const void *Block = 0;

// assigning inheritance and overrides
static void __attribute__((constructor)) blockClassf()
{
    if (Block)
        return;
    jao$$horrCnstr$$();
    mut(Block, void *, &Class);
    memcpy((void *)Block, Obj, sizeof(ObjClass_st));
    static const char name[] = "Block";
    (*(ObjClass_t)&Class).name = name;
    (*(ObjClass_t)&Class).size = sizeof(Block_st);
    (*(ObjClass_t)&Class).super = Obj;
    Class.build = (void *(*)(void *, void *))build;
    Class.eval = (void *(*)(void *, void *))eval;
    *(void **)&horr.eval = evalLayer;
}
const fn_t blockLC = blockClassf;
