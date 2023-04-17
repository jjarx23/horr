#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "horr.h"
#include "horr.r.h"

static int *intArray(int count, ...)
{
    int *a = malloc(count * sizeof(int));
    if (!a)
        return NULL;
    va_list v;
    va_start(v, count);
    for (int i = 0; i < count; i++)
    {
        a[i] = va_arg(v, int);
    }
    va_end(v);
    return a;
}
static int *dblArray(int count, ...)
{
    int *a = malloc(count * sizeof(double));
    if (!a)
        return NULL;
    va_list v;
    va_start(v, count);
    for (int i = 0; i < count; i++)
    {
        a[i] = va_arg(v, double);
    }
    va_end(v);
    return a;
}

const horr_t horr = {0};
void __attribute__((constructor)) jao$$horrCnstr$$()
{
    if (horr.array.INT)
        return;
    *(void **)&horr.array.INT = intArray;
    *(void **)&horr.array.DBL = dblArray;
}