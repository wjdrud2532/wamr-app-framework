// example.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hello()
{
    printf("Hello from the shared library!\n");
}

int add(int a, int b)
{
    return a + b;
}

int func222(int x, int y)
{
    return x + 1;
}

void user_func1(int a)
{
    const char *original_str = "Hello, World!";
    const char *korean_str = " qqqqqqqqq  ";

    // 원본 문자열과 한글 문자열의 길이 계산
    size_t original_len = strlen(original_str);
    size_t korean_len = strlen(korean_str);
    size_t total_len = original_len + korean_len + 1; // 널 종료 문자 포함

    // 새로운 문자열을 위한 메모리 할당
    char *result_str = (char *)malloc(total_len);
    if (result_str == NULL)
    {
        printf("메모리 할당 실패\n");
        return;
    }

    // 문자열 연결
    strcpy(result_str, original_str);
    strcat(result_str, korean_str);

    // 결과 출력
    printf("%s\n", result_str);

    // 동적 할당된 메모리 해제
    free(result_str);
}

void user_func2(const char *original_str)
{
    printf("%s\n", original_str);
}

char *user_func3(char *str)
{
    return str;
}

float halfff(float x)
{
    printf("inside 1 halfff is %f\n", x);
    return x;
}

float halfff2(float x)
{
    printf("inside 2 halfff is %f\n", x);
    // float y = 12.345;
    // printf("%f\n", y);
    // printf("%d\n", x);
    return x;
}

int halfff3(float x)
{
    printf("%f\n", x);
    return x;
}