#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "Activators.h"
#include "Activators.r.h"

static void *identity(void *x);
static void *sig(void *x);
static void *tanh(void *x);

static void __attribute__((constructor)) actClassf()
{
    jao$$horrCnstr$$();
    *(void **)&horr.activators.sigmoid = sig;
    *(void **)&horr.activators.tanh = tanh;
    *(void **)&horr.activators.identity = identity;
}

static void *identity(void *x)
{
    return x;
}
static void *tanh(void *x)
{
    return jCG.tanh(x);
}
static void *sig(void *x)
{
    return NULL;
}
