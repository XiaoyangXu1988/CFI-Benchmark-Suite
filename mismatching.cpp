#include "helper.h"
#include <setjmp.h>

void exception_test();
void exception_callee1();
void exception_callee2();

jmp_buf buf;
void longjmp_test();
void longjmp_callee1();
void longjmp_callee2();

int main()
{
    exception_test();
    printf("exception_test passed\n\n");

    longjmp_test();
    printf("longjmp_test passed\n");

    return 0;
}

void exception_test()
{
    try
    {
        printf("1. a message in exception_test try block\n");
        exception_callee1();
    }
    catch (int e)
    {
        printf("4. a message in exception_test catch block\n");
    }
}

void exception_callee1()
{
    printf("2. a message in exception_callee1\n");
    exception_callee2();
}

void exception_callee2()
{
    printf("3. a message in exception_callee2\n");
    throw 7;
}

void longjmp_test()
{
    printf("5. a message in longjmp_test\n");
    if (setjmp(buf))
        printf("8. a message after longjmp\n");
    else
        longjmp_callee1();
}

void longjmp_callee1()
{
    printf("6. a message in longjmp_callee1\n");
    longjmp_callee2();
}

void longjmp_callee2()
{
    printf("7. a message in longjmp_callee2\n");
    longjmp(buf, 1);
    printf("-1, oops, should never reach this!\n");
}
