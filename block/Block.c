#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "Block.h"
#include "Block.r.h"

/*
//implement if necessary
static void cstr(void *obj, va_list *arg){
    printf("Block constructor \n");
}
static void dstr(void *obj){
    printf("Block destructor \n");
}
//other implentation go here
static int rpr(const void *b, char *str, int length){
    return printf("Block %p \n", b);
}
*/
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
}
const fn_t blockLC = blockClassf;
// other implentation go here
