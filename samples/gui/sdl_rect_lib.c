#include <stdio.h>

// SDL_Rect 구조체 정의
typedef struct SDL_Rect {
    int x, y;
    int w, h;
} SDL_Rect;

// SDL_Rect 구조체의 내용을 설정하는 함수
void set_rect(SDL_Rect *rect, int x, int y, int w, int h) {
    
        rect->x = x;
        rect->y = y;
        rect->w = w;
        rect->h = h;

        printf("set_rect\n");
    
}

// SDL_Rect 구조체 내용을 출력하는 함수
void print_rect(const SDL_Rect *rect) {
    if (rect) {
        printf("SDL_Rect values:\n");
        printf("x: %d, y: %d\n", rect->x, rect->y);
        printf("w: %d, h: %d\n", rect->w, rect->h);
    } else {
        printf("Invalid SDL_Rect pointer 22\n");
    }
}
