#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "Activators.h"
#include "Activators.r.h"

static void *sig(void *x);
static void *tanh(void *x);

static void __attribute__((constructor)) actClassf()
{
    jao$$horrCnstr$$();
    *(void **)horr.activators.sigmoid = sig;
    *(void **)horr.activators.tanh = tanh;
}

static void *tanh(void *x)
{
    return NULL;
}
static void *sig(void *x)
{
    return NULL;
}
