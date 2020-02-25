
#include <stdlib.h> /*strtod*/
#include <string.h> /*strlen*/

#include "calculator.h"
#include "stack.h"

#define UNUSED(x)   (void)(x)

typedef void (*func_t)(stack_t *stack_nums, stack_t *stack_operators, char **str);

void InitCalculator();
double RunCalculator(stack_t *stack_nums, stack_t *stack_operators, char **str);

void EmptyFunc(stack_t *stack_numbers, stack_t *stack_operators, char **str);

void PushOpenningBracket(stack_t *stack_numbers, stack_t *stack_operators, char **str);
void PushClosingBracket(stack_t *stack_numbers, stack_t *stack_operators, char **str);
void PushMultiply(stack_t *stack_numbers, stack_t *stack_operators, char **str);
void PushPlus(stack_t *stack_numbers, stack_t *stack_operators, char **str);
void PushMinus(stack_t *stack_numbers, stack_t *stack_operators, char **str);
void PushDevision(stack_t *stack_numbers, stack_t *stack_operators, char **str);
void PushNumber(stack_t *stack_numbers, stack_t *stack_operators, char **str);

/*Act funcs*/
void ActMultiply(stack_t *stack_numbers, stack_t *stack_operators, char **str);
void ActPlus(stack_t *stack_numbers, stack_t *stack_operators, char **str);
void ActMinus(stack_t *stack_numbers, stack_t *stack_operators, char **str);
void ActDevision(stack_t *stack_numbers, stack_t *stack_operators, char **str);

func_t lut_funcs[256] = {NULL};
const int ACT = 100;


double Calculate(char *str)
{
    double result = 0;
    size_t len = strlen(str);
    stack_t *stack_operators = StackCreate(len, sizeof(char));
    stack_t *stack_nums = StackCreate(len, sizeof(double));

    InitCalculator();

    while ('\0' != *str)
    {
        lut_funcs[(int)(*str)](stack_nums, stack_operators, &str);
    }

    while (!IsStackEmpty(stack_operators))
    {
        lut_funcs[*(char*)(StackPeek(stack_operators)) + ACT](stack_nums, stack_operators, &str);
    }
    
    result = *((double*)(StackPeek(stack_nums)));
    StackDestroy(stack_nums);
    StackDestroy(stack_operators);

    return result;
}


void InitCalculator()
{
    size_t i = 0;    

    for (i = 0; i < 256; i++)
    {
        lut_funcs[i] = EmptyFunc;
    }

    /*reading funcs for operators*/
    lut_funcs['('] = &PushOpenningBracket;
    lut_funcs[')'] = &PushClosingBracket;
    lut_funcs['*'] = &PushMultiply;
    lut_funcs['+'] = &PushPlus;
    lut_funcs['-'] = &PushMinus;
    lut_funcs['/'] = &PushDevision;
    
    /*reading funcs for nums*/
    for (i = 48; i < 58; ++i)
    {
        lut_funcs[i] = &PushNumber;
    }

    /*acting funcs*/
    lut_funcs['*' + ACT] = &ActMultiply;
    lut_funcs['+' + ACT] = &ActPlus;
    lut_funcs['-' + ACT] = &ActMinus;
    lut_funcs['/' + ACT] = &ActDevision;
}


void EmptyFunc(stack_t *stack_nums, stack_t *stack_operators, char **str)
{
    UNUSED(stack_nums);
    UNUSED(stack_operators);
    UNUSED(str);

    ++(*str);
}

void PushOpenningBracket(stack_t *stack_nums, stack_t *stack_operators, char **str)
{
    StackPush(stack_operators, *str);

    ++(*str);
}

void PushClosingBracket(stack_t *stack_nums, stack_t *stack_operators, char **str)
{
    while (*(char*)StackPeek(stack_operators) != '(')
    {
        lut_funcs[*(char*)(StackPeek(stack_operators)) + ACT](stack_nums, stack_operators, str);
    }

    StackPop(stack_operators);

    ++(*str);
}

void PushMultiply(stack_t *stack_nums, stack_t *stack_operators, char **str)
{
    while (!IsStackEmpty(stack_operators) && ('*' == *(char*)(StackPeek(stack_operators)) || ('/' == *(char*)(StackPeek(stack_operators)))))
    {
        lut_funcs[*(char*)(StackPeek(stack_operators)) + ACT](stack_nums, stack_operators, str);
    }

    StackPush(stack_operators, *str);
    ++(*str);

}

void PushDevision(stack_t *stack_nums, stack_t *stack_operators, char **str)
{
     while (!IsStackEmpty(stack_operators) && ('*' == *(char*)(StackPeek(stack_operators)) || ('/' == *(char*)(StackPeek(stack_operators)))))
    {
        lut_funcs[*(char*)(StackPeek(stack_operators)) + ACT](stack_nums, stack_operators, str);
    }

    StackPush(stack_operators, *str);
    ++(*str);

}

void PushPlus(stack_t *stack_nums, stack_t *stack_operators, char **str)
{
    while (!IsStackEmpty(stack_operators) && ('(' != *(char*)(StackPeek(stack_operators))))
    {
        lut_funcs[*(char*)(StackPeek(stack_operators)) + ACT](stack_nums, stack_operators, str);
    }

    StackPush(stack_operators, *str);
    ++(*str);

}

void PushMinus(stack_t *stack_nums, stack_t *stack_operators, char **str)
{
    while (!IsStackEmpty(stack_operators) && ('(' != *(char*)(StackPeek(stack_operators))))
    {
        lut_funcs[*(char*)(StackPeek(stack_operators)) + ACT](stack_nums, stack_operators, str);
    }

    StackPush(stack_operators, *str);
    ++(*str);

}

void PushNumber(stack_t *stack_nums, stack_t *stack_operators, char **str)
{
    double current_num = strtod(*str, str);
    StackPush(stack_nums, &current_num);
}

void ActMultiply(stack_t *stack_nums, stack_t *stack_operators, char **str)
{
     double result = *(double*)(StackPeek(stack_nums));
    StackPop(stack_nums);

    result = *(double*)(StackPeek(stack_nums)) * result;
    StackPop(stack_nums);

    StackPush(stack_nums, &result);
    StackPop(stack_operators);
    
}

void ActPlus(stack_t *stack_nums, stack_t *stack_operators, char **str)
{
    double result = *(double*)(StackPeek(stack_nums));
    StackPop(stack_nums);

    result = *(double*)(StackPeek(stack_nums)) + result;
    StackPop(stack_nums);

    StackPush(stack_nums, &result);
    StackPop(stack_operators);
}

void ActMinus(stack_t *stack_nums, stack_t *stack_operators, char **str)
{
     double result = *(double*)(StackPeek(stack_nums));
    StackPop(stack_nums);

    result = *(double*)(StackPeek(stack_nums)) - result;
    StackPop(stack_nums);

    StackPush(stack_nums, &result);
    StackPop(stack_operators);
}

void ActDevision(stack_t *stack_nums, stack_t *stack_operators, char **str)
{
    double result = *(double*)(StackPeek(stack_nums));
    StackPop(stack_nums);

    result = *(double*)(StackPeek(stack_nums)) / result;
    StackPop(stack_nums);

    StackPush(stack_nums, &result);
    StackPop(stack_operators);
}