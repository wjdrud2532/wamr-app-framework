// sdl_graphics.c
#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // 창 생성
    SDL_Window* window = SDL_CreateWindow("Moving Rectangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // 렌더러 생성
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 사각형의 초기 위치와 크기
    SDL_Rect rect = {50, 200, 100, 100}; 
    int speed = 5; // 사각형 이동 속도
    int direction = 1; // 사각형 이동 방향

    int running = 1;
    SDL_Event event;

    // 메인 애니메이션 루프
    while (running) {
        // 이벤트 처리 (창 닫기 등)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // 사각형 위치 업데이트
        rect.x += speed * direction;

        // 사각형이 화면 끝에 도달하면 반대 방향으로 이동
        if (rect.x + rect.w >= 640 || rect.x <= 0) {
            direction = -direction;
        }

        // 화면을 검은색으로 지우기
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // 빨간색 사각형 그리기
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &rect);

        // 화면 업데이트
        SDL_RenderPresent(renderer);

        // 프레임 속도를 조절하기 위한 지연
        SDL_Delay(30);
    }

    // 자원 해제
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
