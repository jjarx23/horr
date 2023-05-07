#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "Model.h"
#include "Model.r.h"
static void *model(void *layr1, ...)
{
    va_list arg;
    va_start(arg, layr1);
    void *layer = neu(Model, layr1, &arg);
    va_end(arg);
    return layer;
}
static void **layers(void *inputNode, void **outputNode, int *count, va_list *arg)
{
    // layer
    void *layer = va_arg(*arg, void *);
    if (layer)
    {
        int index = count[0]++;
        void **layers_ = layers(buildLayer(layer, inputNode), outputNode, count, arg);
        layers_[index] = layer;
        return layers_;
    }
    else
    {
        outputNode[0] = inputNode;
        return *count > 1 ? malloc(*count * sizeof(void *)) : NULL;
    }
}
static void cstr(void *layer, va_list *arg)
{
    // layer 1
    void *layer1 = va_arg(*arg, void *);
    if (layer1)
    {
        int count = 1;
        void *initialNode = jCG.var(NULL), *finalNode;
        void **layers_ = layers(buildLayer(layer1, initialNode), &finalNode, &count, va_arg(*arg, va_list *));
        if (count > 1)
            layers_[0] = layer1;
        else
            layers_ = layer1;
        setGraphNode(layer, finalNode);
        setModelGraphNode(layer, initialNode);
    }
    else
    {
        warn("%s: No layers provided\n", "Model");
    }
}
static void *evalLayer(void *layer, void *input)
{
    void *node = graphNode(layer);
    jCG.setVarData(modelGraphNode(layer), input);
    jCG.eval(node);
    return jCG.varData(node);
}
static ModelClass_st Class;
const void *Model = 0;

// assigning inheritance and overrides
static void __attribute__((constructor)) modelClassf()
{
    if (Model)
        return;
    blockLC();
    jao$$horrCnstr$$();
    *(void **)&horr.nn.model = model;
    mut(Model, void *, &Class);
    memcpy((void *)Model, Block, sizeof(BlockClass_st));
    static const char name[] = "Model";
    (*(ObjClass_t)&Class).name = name;
    (*(ObjClass_t)&Class).size = sizeof(Model_st);
    (*(ObjClass_t)&Class).super = Block;
    (*(ObjClass_t)&Class).cstr = cstr;
    (*(BlockClass_t)&Class).eval = evalLayer;
}
const fn_t modelLC = modelClassf;
