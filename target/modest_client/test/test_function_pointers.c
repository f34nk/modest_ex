
// #ifndef NEW_FUN_H_
// #define NEW_FUN_H_

#include <stdio.h>

typedef int speed;
speed fun(int x);

enum fp {
    f1, f2, f3, f4, f5
};

void F1();
void F2();
void F3();
void F4();
void F5();
// #endif

//////////////////////////////////////////////////////////////////////

// #include "New_Fun.h"
// New_Fun.c

speed fun(int x)
{
    int Vel;
    Vel = x;
    return Vel;
}

void F1()
{
    printf("From F1\n");
}

void F2()
{
    printf("From F2\n");
}

void F3()
{
    printf("From F3\n");
}

void F4()
{
    printf("From F4\n");
}

void F5()
{
    printf("From F5\n");
}

//////////////////////////////////////////////////////////////////////


#include <stdio.h>
// #include "New_Fun.h"

int main()
{
    int (*F_P)(int y);
    void (*F_A[5])() = { F1, F2, F3, F4, F5 };    // if it is int the pointer incompatible is bound to happen
    int xyz, i;

    printf("Hello Function Pointer!\n");
    F_P = fun;
    xyz = F_P(5);
    printf("The Value is %d\n", xyz);
    
    printf("\n\n");
    for (i = 0; i < 5; i++)
    {
        F_A[i]();
    }
    
    printf("\n\n");
    F_A[f1]();
    F_A[f2]();
    F_A[f3]();
    F_A[f4]();
    return 0;
}