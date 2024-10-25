// sdl_graphics.c
#include <SDL2/SDL.h>
#include <stdio.h>

int create_window() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Color Change Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    // 색상 배열 (빨강, 주황, 노랑, 초록, 파랑)
    Uint32 colors[] = {
        SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00), // 빨강
        SDL_MapRGB(screenSurface->format, 0xFF, 0xA5, 0x00), // 주황
        SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0x00), // 노랑
        SDL_MapRGB(screenSurface->format, 0x00, 0xFF, 0x00), // 초록
        SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0xFF)  // 파랑
    };

    // 색상을 순차적으로 변경
    for (int i = 0; i < 5; i++) {
        SDL_FillRect(screenSurface, NULL, colors[i]); // 현재 색상으로 화면 채우기
        SDL_UpdateWindowSurface(window); // 화면 업데이트
        SDL_Delay(1000); // 1초 대기
    }

    SDL_DestroyWindow(window);
    // SDL_Quit();

    return 0;
}
