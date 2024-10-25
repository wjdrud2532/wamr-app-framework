// sdl_graphics.c
#include <SDL2/SDL.h>
#include <stdio.h>

int create_window() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Moving Rectangle Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect rect = {50, 50, 100, 100}; // 사각형의 위치와 크기 설정
    int speed = 5; // 사각형 이동 속도
    int direction = 1; // 이동 방향 (1은 오른쪽, -1은 왼쪽)

    int running = 1;
    SDL_Event event;

    while (running) {
        // 이벤트 처리 (창 닫기 등)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // 사각형의 위치 업데이트
        rect.x += speed * direction;

        // 사각형이 화면의 끝에 도달하면 방향을 바꿈
        if (rect.x + rect.w >= 640 || rect.x <= 0) {
            direction = -direction;
        }

        // 화면 지우기
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // 검은색 배경
        SDL_RenderClear(renderer);

        // 사각형 그리기 (빨간색)
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &rect);

        // 화면 업데이트
        SDL_RenderPresent(renderer);

        // 애니메이션 속도를 조절하기 위한 짧은 시간 대기
        SDL_Delay(30);
    }

    // 자원 해제
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

