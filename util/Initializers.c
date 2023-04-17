#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "Initializers.h"
#include "Initializers.r.h"

static void *get(Initializer_t fn, int rank, int *shape, ...)
{

    return NULL;
}
const struct initer_t Initializer = {get};

static void *zeros(int rank, int *shape);
static void *ones(int rank, int *shape);
static void __attribute__((constructor)) initsClassf()
{
    jao$$horrCnstr$$();
    *(void **)horr.initializers.zeros = zeros;
    *(void **)horr.initializers.ones = ones;
}

static void *zeros(int rank, int *shape)
{
    return NULL;
}
static void *ones(int rank, int *shape)
{
    return NULL;
}