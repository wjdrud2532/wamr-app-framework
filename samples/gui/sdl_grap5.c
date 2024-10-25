#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1920;  // 화면 크기를 3배로 설정
const int SCREEN_HEIGHT = 1080;
const int GAUGE_RADIUS = 250;   // 게이지 반지름
const float MAX_SPEED = 240.0f;  // 속도계 최대값
const float MAX_RPM = 7000.0f;  // RPM 최대값
const float SPEED_INCREMENT = 2.0f;  // 속도 증가량
const float RPM_INCREMENT = 100.0f;  // RPM 증가량
const float DECAY_RATE = 0.2f;       // 속도 감소 비율 (자동으로 감소)
const float FAST_DECAY_RATE = 1.0f;  // 'a'를 눌렀을 때 더 빠른 감소

// 원형 호를 그리는 함수 (Surface 사용)
void draw_arc(SDL_Surface* surface, int centerX, int centerY, int radius, float startAngle, float endAngle, Uint32 color) {
    for (float angle = startAngle; angle >= endAngle; angle -= 0.01f) {
        int x = centerX + (int)(radius * cos(angle));
        int y = centerY - (int)(radius * sin(angle));  // SDL 좌표계에서 y는 아래로 갈수록 증가하므로 - 사용
        if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
            Uint32* pixels = (Uint32*)surface->pixels;
            pixels[(y * SCREEN_WIDTH) + x] = color;
        }
    }
}

// 원형 게이지 그리기 함수
void draw_gauge(SDL_Surface* surface, int centerX, int centerY, int radius, float value, float max_value, Uint32 color) {
    float startAngle = M_PI;  // 게이지는 180도에서 시작 (위쪽)
    float endAngle = M_PI - (value / max_value) * M_PI;  // 값에 비례해 각도를 계산하여 줄어듦
    draw_arc(surface, centerX, centerY, radius, startAngle, endAngle, color);
}

// 텍스트 그리기 함수 (Surface 사용)
void draw_text(SDL_Surface* surface, const char* text, int x, int y, TTF_Font* font, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface != NULL) {
        SDL_Rect dest = {x, y, textSurface->w, textSurface->h};
        SDL_BlitSurface(textSurface, NULL, surface, &dest);
        SDL_FreeSurface(textSurface);
    }
}

int create_dashboard2() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Car Dashboard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    TTF_Font* font = TTF_OpenFont("fox.ttf", 48);  // 사용할 폰트를 지정해줘야 함

    if (font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 0;
    }

    Uint32 gauge_color = SDL_MapRGB(screenSurface->format, 255, 0, 0);  // 게이지 색상 (빨간색)
    Uint32 road_color = SDL_MapRGB(screenSurface->format, 50, 50, 50);  // 도로 색상 (회색)

    float speed_value = 0.0f;
    float rpm_value = 0.0f;
    int quit = 0;
    SDL_Event event;

    int speed_radius = GAUGE_RADIUS;  // 속도계 반지름
    int rpm_radius = GAUGE_RADIUS;    // RPM 반지름
    int centerX_left = SCREEN_WIDTH / 3;    // 왼쪽 속도계 중심 X
    int centerY = SCREEN_HEIGHT / 2;        // 계기판 중심 Y
    int centerX_right = 2 * SCREEN_WIDTH / 3;  // 오른쪽 RPM 계기판 중심 X

    while (!quit) {
        // 이벤트 처리
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // 키보드 상태 확인
        const Uint8* state = SDL_GetKeyboardState(NULL);

        // 스페이스바를 누르면 속도와 RPM이 증가
        if (state[SDL_SCANCODE_SPACE]) {
            speed_value += SPEED_INCREMENT;
            rpm_value += RPM_INCREMENT;

            if (speed_value > MAX_SPEED) {
                speed_value = MAX_SPEED;
            }

            if (rpm_value > MAX_RPM) {
                rpm_value = MAX_RPM;
            }
        } else {
            // 스페이스바를 떼면 속도와 RPM이 감소
            if (state[SDL_SCANCODE_A]) {
                // 'a'를 누르면 더 빠르게 감소
                if (speed_value > 0) {
                    speed_value -= FAST_DECAY_RATE;
                } else {
                    speed_value = 0;
                }

                if (rpm_value > 0) {
                    rpm_value -= FAST_DECAY_RATE * RPM_INCREMENT;
                } else {
                    rpm_value = 0;
                }
            } else {
                // 천천히 감소
                if (speed_value > 0) {
                    speed_value -= DECAY_RATE;
                } else {
                    speed_value = 0;
                }

                if (rpm_value > 0) {
                    rpm_value -= DECAY_RATE * RPM_INCREMENT;
                } else {
                    rpm_value = 0;
                }
            }
        }

        // 화면 그리기
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 135, 206, 235));  // 배경 하늘색

        // 중앙 도로 그리기
        SDL_Rect road = {SCREEN_WIDTH / 2 - 100, 0, 200, SCREEN_HEIGHT};
        SDL_FillRect(screenSurface, &road, road_color);

        // 왼쪽 속도계 호 그리기 (속도에 따른 게이지)
        draw_gauge(screenSurface, centerX_left, centerY, speed_radius, speed_value, MAX_SPEED, gauge_color);

        // 오른쪽 RPM 계기판 호 그리기 (RPM에 따른 게이지)
        draw_gauge(screenSurface, centerX_right, centerY, rpm_radius, rpm_value, MAX_RPM, gauge_color);

        // 텍스트 그리기
        SDL_Color textColor = {255, 0, 0};  // 빨간색 텍스트
        char speed_text[20];
        char rpm_text[20];
        snprintf(speed_text, sizeof(speed_text), "%.0f km/h", speed_value);
        snprintf(rpm_text, sizeof(rpm_text), "%.0f RPM", rpm_value);
        draw_text(screenSurface, speed_text, centerX_left - 50, centerY + 100, font, textColor);
        draw_text(screenSurface, rpm_text, centerX_right - 70, centerY + 100, font, textColor);

        // 화면 업데이트
        SDL_UpdateWindowSurface(window);

        SDL_Delay(16);  // 약 60fps로 제한
    }

    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

int main(int argc, char* args[]) {
    create_dashboard2();
    return 0;
}
