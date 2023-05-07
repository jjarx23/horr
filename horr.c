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
int v = 0;
static horr_t h = {0};
const horr_t *horr_ = &h;

void __attribute__((constructor)) jao$$horrCnstr$$()
{
    if (h.array.INT)
        return;
    *(void **)&h.array.INT = intArray;
    *(void **)&h.array.DBL = dblArray;
}