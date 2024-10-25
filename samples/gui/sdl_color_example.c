#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int RECT_SIZE = 50;
const int SPEED = 5;

// 사각형 애니메이션 함수
void rectangle() {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // 창과 렌더러 생성
    SDL_Window* window = SDL_CreateWindow("SDL Renderer Animation Example",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // 사각형의 초기 위치 설정
    SDL_Rect rect = {SCREEN_WIDTH / 2 - RECT_SIZE / 2, SCREEN_HEIGHT / 2 - RECT_SIZE / 2, RECT_SIZE, RECT_SIZE};

    int dx = SPEED, dy = SPEED;  // 사각형의 이동 방향 및 속도
    int r = 0, g = 0, b = 255;   // 사각형의 초기 색상 (파란색)
    int color_change_speed = 5;   // 색상 변화 속도

    bool running = true;
    SDL_Event event;

    // 메인 루프
    while (running) {
        // 이벤트 처리
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // 사각형의 위치를 계속 변경
        rect.x += dx;
        rect.y += dy;

        // 화면 경계에서 반전 (벽에 부딪히면 반대 방향으로 이동)
        if (rect.x <= 0 || rect.x >= SCREEN_WIDTH - RECT_SIZE) {
            dx = -dx;
        }
        if (rect.y <= 0 || rect.y >= SCREEN_HEIGHT - RECT_SIZE) {
            dy = -dy;
        }

        // 색상 변화
        r += color_change_speed;
        g += color_change_speed / 2;
        b -= color_change_speed;

        if (r > 255) r = 0;
        if (g > 255) g = 0;
        if (b < 0) b = 255;

        // 화면을 검은색으로 지우기
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 사각형을 현재 색상으로 그리기
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &rect);

        // 렌더러 업데이트 (화면에 표시)
        SDL_RenderPresent(renderer);

        // 약간의 딜레이 추가 (60FPS)
        SDL_Delay(16);
    }

    // 창과 렌더러 제거
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    // rectangle 함수 호출
    rectangle();
    return 0;
}
