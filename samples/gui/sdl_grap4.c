#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const float DECAY_RATE = 0.1f;  // 기본 감소 속도
const float FAST_DECAY_RATE = 0.5f;  // 'a' 키를 눌렀을 때의 빠른 감소 속도
const float INCREASE_RATE = 0.5f;  // 스페이스바를 눌렀을 때의 증가 속도
const float MAX_GAUGE = 100.0f;  // 게이지 최대 값

// 원형 호를 그리는 함수
void draw_arc(SDL_Surface* surface, int centerX, int centerY, int radius, float startAngle, float endAngle, Uint32 color) {
    for (float angle = startAngle; angle >= endAngle; angle -= 0.01f) {  // 각도를 거꾸로
        int x = centerX + (int)(radius * cos(angle));
        int y = centerY - (int)(radius * sin(angle));  // SDL 좌표계에서 y는 아래로 갈수록 증가하므로 - 사용
        if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
            Uint32* pixels = (Uint32*)surface->pixels;
            pixels[(y * SCREEN_WIDTH) + x] = color;
        }
    }
}

// 텍스트 그리기 함수
void draw_text(SDL_Surface* surface, const char* text, int x, int y, TTF_Font* font, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface != NULL) {
        SDL_Rect dest = {x, y, textSurface->w, textSurface->h};
        SDL_BlitSurface(textSurface, NULL, surface, &dest);
        SDL_FreeSurface(textSurface);
    }
}

void create_dashboard() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Car Dashboard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    TTF_Font* font = TTF_OpenFont("fox.ttf", 48);  // 폰트 크기를 48로 변경

    if (font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return;
    }

    float gauge_value = 0.0f;
    int quit = 0;
    SDL_Event event;

    int gauge_radius = 150; // 계기판 반지름
    int centerX = SCREEN_WIDTH / 2; // 계기판 중심 X
    int centerY = SCREEN_HEIGHT / 2 + 100; // 계기판 중심 Y, 아래로 조금 내림

    while (!quit) {
        // 이벤트 처리
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // 키보드 상태 가져오기
        const Uint8* state = SDL_GetKeyboardState(NULL);

        // 스페이스바가 눌렸을 때 게이지 증가
        if (state[SDL_SCANCODE_SPACE]) {
            gauge_value += INCREASE_RATE;
            if (gauge_value > MAX_GAUGE) {
                gauge_value = MAX_GAUGE;
            }
        } else {
            // 'a' 키가 눌렸을 때 더 빠르게 감소, 그렇지 않으면 천천히 감소
            if (state[SDL_SCANCODE_A]) {
                gauge_value -= FAST_DECAY_RATE;
            } else {
                gauge_value -= DECAY_RATE;
            }

            if (gauge_value < 0) {
                gauge_value = 0;
            }
        }

        // 화면 그리기
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 135, 206, 235));  // 배경 하늘색

        // 게이지 각도 계산
        float startAngle = M_PI;  // 위에서 시작 (180도)
        float endAngle = M_PI - (gauge_value / MAX_GAUGE) * M_PI;  // 게이지에 따라 끝나는 각도

        // 원형 게이지 그리기
        Uint32 gauge_color = SDL_MapRGB(screenSurface->format, 255, 0, 0);  // 게이지 빨간색
        draw_arc(screenSurface, centerX, centerY, gauge_radius, startAngle, endAngle, gauge_color);

        // 텍스트 그리기 (게이지 값)
        char gauge_text[10];
        snprintf(gauge_text, sizeof(gauge_text), "%.0f", gauge_value);
        SDL_Color textColor = {255, 0, 0};  // 텍스트 빨간색으로 변경
        draw_text(screenSurface, gauge_text, centerX - 40, centerY - gauge_radius - 50, font, textColor);

        // 화면 업데이트
        SDL_UpdateWindowSurface(window);

        SDL_Delay(16); // 약 60fps로 제한
    }

    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    create_dashboard();
    return 0;
}
