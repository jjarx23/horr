#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "Initializers.h"
#include "Initializers.r.h"

static inline mut_(void **f, void *n)
{
    *f = n;
}

static void *get(Initializer_t fn, int rank, int *shape, ...)
{
    return fn(rank, shape);
}
const struct initer_t Initializer = {get};

static void *zeros(int rank, int *shape);
static void *ones(int rank, int *shape);
static void __attribute__((constructor)) initsClassf()
{
    jao$$horrCnstr$$();
    //*(void **)&horr_->initializers.zeros = zeros;
    mut_(&horr_->initializers.zeros, zeros);
    *(void **)&horr.initializers.ones = ones;
}

static void *zeros(int rank, int *shape)
{
    return Flow.constants.zero;
}
static void *ones(int rank, int *shape)
{
    return Flow.constants.one;
}