#include "helper.h"

// caller-pop, variadic function
int CDECL variadicSum(int count, ...);

// callee-pop function
int STDCALL listSum(int count, const int * list);

// callee-pop FASTCALL function. caller tries to pass 
// argument(s) using registers first.
int FASTCALL fastSum(int count, const int * list);

// callee-pop THISCALL functions. "this" pointer is passed 
// to callee via ecx. other arguments are pushed onto stack
class CMath
{
private:
    int * list;
    int count;
public:
    int THISCALL calculateSum();
    int THISCALL calculateAverage();
    void THISCALL setList(const int list_count, const int * int_list);
};

int main()
{
    // call a CDECL function
    int variadicSum_ans = 0;

    variadicSum_ans = variadicSum(5, 1, 2, 3, 4, 5);
    printf("variadicSum: sum is %d\n", variadicSum_ans);

    // call a STDCALL function
    int listSum_ans = 0;
    int int_list1[5] = { 1, 3, 5, 7, 9 };

    listSum_ans = listSum(sizeof(int_list1) / sizeof(int), int_list1);
    printf("listSum: sum is %d\n", listSum_ans);

    // call a FASTCALL function
    int fastSum_ans = 0;
    int int_list2[4] = { 5, 3, 5, 1 };

    fastSum_ans = fastSum(sizeof(int_list2) / sizeof(int), int_list2);
    printf("fastSum: sum is %d\n", fastSum_ans);

    // call THISCALL functions
    CMath * myCMath = new CMath;
    int int_list3[6] = { 2, 1, 6, 3, 8, 9 };

    myCMath->setList(sizeof(int_list3) / sizeof(int), int_list3);
    int sum = myCMath->calculateSum();
    int avg = myCMath->calculateAverage();
    printf("calculateSum: sum is %d\n", sum);
    printf("calculateAverage: sum is %d\n", avg);

    return 0;
}

int THISCALL CMath::calculateAverage()
{
    int sum = 0;
    int avg = 0;

    sum = this->calculateSum();
    avg = sum / this->count;
    return avg;
}

int THISCALL CMath::calculateSum()
{
    int sum = 0;
    for (int i = 0; i < this->count; i++)
        sum += (this->list)[i];

    return sum;
}

void THISCALL CMath::setList(const int list_count, const int * int_list)
{
    this->list = new int[list_count];
    this->count = list_count;

    for (int i = 0; i < list_count; i++)
        (this->list)[i] = int_list[i];
}

int FASTCALL fastSum(int count, const int * list)
{
    int sum = 0;
    int i = 0;

    for (int i = 0; i < count; i++)
        sum += list[i];

    return sum;
}

int STDCALL listSum(int count, const int * list)
{
    int sum = 0;
    int i = 0;

    for (int i = 0; i < count; i++)
        sum += list[i];

    return sum;
}

int CDECL variadicSum(int count, ...)
{
    va_list ap;
    int sum = 0;

    va_start(ap, count);
    for (int i = 0; i < count; i++)
        sum += va_arg(ap, int);
    va_end(ap);

    return sum;
}
