#include <stdio.h>

// 두 정수를 더하는 함수
int add(int a, int b) {
    return a + b;
}

// main 함수 (선택 사항)
void on_init()
{
    int result = add(5, 3);
    printf("add(5, 3) = %d\n", result);
    // return 0;
}

int main() {
    on_init();
}

