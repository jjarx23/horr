#ifndef ACTIVATORS_H
#define ACTIVATORS_H

#include "../horr.h"

#ifdef __cplusplus
extern 'C'
{
#endif
#define Activators horr.activators

    extern struct
    {
        void *(*get)(void *ptr, void *x, ...);
    } Activator;
#ifdef __cplusplus
}
#endif
#endif