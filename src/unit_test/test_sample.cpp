#include "test_sample.hpp"

void rawFreeFuncNoParamA(void)
{
    int i = 1 + 1;
    int a = i + 1;
    int b = a * i;
    b = b * 2;
}

void rawFreeFuncNoParamB(void)
{
    return;
}

void SingleInheritBaseClass::rawStaticMemFuncNoParamA(void)
{

}

void SingleInheritBaseClass::rawStaticMemFuncNoParamB(void)
{

}

void SingleInheritBaseClass::rawMemFuncNoParamA(void)
{

}

void SingleInheritBaseClass::rawMemFuncNoParamB(void)
{

}

void SingleInheritBaseClass::rawMemFuncWithParamA(EventSPtr)
{

}

void SingleInheritBaseClass::rawMemFuncWithParamB(EventSPtr)
{

}

void SingleInheritClass::rawMemFuncNoParamA(void)
{

}

void SingleInheritClass::rawMemFuncNoParamB(void)
{

}

void SingleInheritClass::rawMemFuncWithParamA(EventSPtr)
{

}

void SingleInheritClass::rawMemFuncWithParamB(EventSPtr)
{

}