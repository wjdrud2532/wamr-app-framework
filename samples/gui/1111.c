#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// typedef struct mystr mystr;
typedef struct mystr
{
    int a;
    int b;
} mystr;

uint32_t* foo10(int a, int b)
{
    uint32_t *ptr = (uint32_t *)malloc(sizeof(uint32_t));  // 4바이트 메모리 할당
    if (ptr) {
        *ptr = a + b;
    }
    printf("inside foo10's pointer %p\n", ptr);
    return ptr;  // 4바이트 포인터 반환
}

mystr* foo9(mystr * stru, int a, int b)
{
    stru->a = a;
    stru->b = b;

    printf("inside foo99 stru pointer %p\n", stru);

    printf("inside foo99 stru a : %d\n", stru->a);
    printf("inside foo99 stru b : %d\n", stru->b);

    return stru;
}

mystr* foo8(int a, int b)
{
    mystr *stru = malloc(sizeof(mystr));

    stru->a = a;
    stru->b = b;

    // printf("inside foo8\n");
    printf("inside foo8 stru a : %d\n", stru->a);
    printf("inside foo8 stru b : %d\n", stru->b);

    return stru;
}

int *foo7(mystr * stru)
{
    printf("foo7 inside1 a : %d\n", stru->a);

    stru->a = 99;
    stru->b = 77;

    printf("foo7 inside2 a : %d\n", stru->a);

    int * num = 99;
    // return 0;
    return num;
}

// mystr foo6()
// {
//     mystr stru;
//     mystr *struPtr = &stru;

//     struPtr->a = 1;
//     struPtr->b = 2;

//     return stru;
// }

void foo5(int a1, int a2)
{
    a1 = 1;
    a2 = 2;
}

int foo4(int * num)
{
    *num = 7777;
    printf("num pointer %p\n", num);
    return num;
}

int foo3(int a, int b)
{
    int foo3A = 3333;

    return a + b;
}

int foo2()
{
    int foo2A = 2222;
    return foo2A;
}

void foo1()
{
    int foo1A = 1111;
}

int main()
{
    volatile int b = 3;
    volatile int c;
    volatile int *d = malloc(4);
    volatile int *e = NULL;

    foo1();
    
    c = foo2();

    c = foo3(4444, 5555);

    c = foo4(d);

    foo5(b, c);   

    mystr *stru = malloc(sizeof(mystr));

    // mystr *stru = (void *)malloc(sizeof(int) * 2);
    // mystr *stru = NULL;
    // printf("Size of mystr: %zu bytes\n", sizeof(mystr));    // 8byte

    // foo6();
    
    stru->a = 5;
    stru->b = 6;
    printf("stru a : %d\n", stru->a);
    printf("stru b : %d\n", stru->b);
    // foo7(stru);

    // printf("stru a : %d\n", stru->a);
    // printf("stru b : %d\n", stru->b);

    int * tempnum = foo7(stru);
    printf("tempnum pointer is : %p\n", &tempnum);
    printf("foo7 = %d\n", tempnum);

    stru = foo8(33, 44);
    printf("stru a : %d\n", stru->a);
    printf("stru b : %d\n", stru->b);

    uint32_t *myPtr = foo10(1,2);
    if (myPtr) {
        printf("Value: %u\n", *myPtr);  // 값 출력
        free(myPtr);                    // 메모리 해제
    }
}