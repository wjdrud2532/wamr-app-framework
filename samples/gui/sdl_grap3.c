#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define RECT_SIZE 50
#define BULLET_WIDTH 10
#define BULLET_HEIGHT 5
#define BLOCK_WIDTH 50
#define BLOCK_HEIGHT 20
#define SPEED 5
#define BULLET_SPEED 10
#define NUM_BLOCKS 10

typedef struct {
    int x, y;
    bool active;
} Bullet;

typedef struct {
    int x, y;
    bool active;
} Block;

// 충돌 감지 함수 (AABB 방식)
bool check_collision(SDL_Rect a, SDL_Rect b) {
    return a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y;
}

int create_window3() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Moving Rectangle with Blocks and Bullet Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    // 사각형 초기 위치
    SDL_Rect rect = {WINDOW_WIDTH / 2 - RECT_SIZE / 2, WINDOW_HEIGHT / 2 - RECT_SIZE / 2, RECT_SIZE, RECT_SIZE};

    Bullet bullet = {0, 0, false}; // 총알 초기화 (비활성 상태)

    // 블록 초기화
    Block blocks[NUM_BLOCKS];
    for (int i = 0; i < NUM_BLOCKS; i++) {
        blocks[i].x = i * (BLOCK_WIDTH + 10) + 20; // 블록 간 간격을 10으로 설정
        blocks[i].y = 50; // 상단에 위치
        blocks[i].active = true; // 블록 활성화
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        // 이벤트 처리
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // 키보드 입력 상태 확인
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_UP]) {
            rect.y -= SPEED;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            rect.y += SPEED;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            rect.x -= SPEED;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            rect.x += SPEED;
        }

        // 사각형 경계 체크
        if (rect.x < 0) rect.x = 0;
        if (rect.x > WINDOW_WIDTH - RECT_SIZE) rect.x = WINDOW_WIDTH - RECT_SIZE;
        if (rect.y < 0) rect.y = 0;
        if (rect.y > WINDOW_HEIGHT - RECT_SIZE) rect.y = WINDOW_HEIGHT - RECT_SIZE;

        // 스페이스바 눌렀을 때 총알 발사
        if (state[SDL_SCANCODE_SPACE] && !bullet.active) {
            bullet.x = rect.x + RECT_SIZE / 2 - BULLET_WIDTH / 2;
            bullet.y = rect.y;
            bullet.active = true;
        }

        // 총알이 발사 중이면 위로 움직임
        if (bullet.active) {
            bullet.y -= BULLET_SPEED;
            if (bullet.y < 0) {
                bullet.active = false; // 화면을 벗어나면 비활성화
            }
        }

        // 블록과 총알 충돌 체크
        SDL_Rect bulletRect = {bullet.x, bullet.y, BULLET_WIDTH, BULLET_HEIGHT};
        for (int i = 0; i < NUM_BLOCKS; i++) {
            if (blocks[i].active) {
                SDL_Rect blockRect = {blocks[i].x, blocks[i].y, BLOCK_WIDTH, BLOCK_HEIGHT};
                if (check_collision(bulletRect, blockRect)) {
                    blocks[i].active = false; // 블록 비활성화 (총알에 맞음)
                    bullet.active = false; // 총알도 비활성화
                    break; // 한번에 하나의 블록만 제거
                }
            }
        }

        // 화면을 흰색으로 채우기
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

        // 사각형을 빨간색으로 채우기
        SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));

        // 블록 그리기
        for (int i = 0; i < NUM_BLOCKS; i++) {
            if (blocks[i].active) {
                SDL_Rect blockRect = {blocks[i].x, blocks[i].y, BLOCK_WIDTH, BLOCK_HEIGHT};
                SDL_FillRect(screenSurface, &blockRect, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0xFF)); // 파란색 블록
            }
        }

        // 총알이 활성 상태일 때 총알을 그리기
        if (bullet.active) {
            SDL_Rect bulletRect = {bullet.x, bullet.y, BULLET_WIDTH, BULLET_HEIGHT};
            SDL_FillRect(screenSurface, &bulletRect, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00)); // 검은색 총알
        }

        // 윈도우 업데이트
        SDL_UpdateWindowSurface(window);

        SDL_Delay(16); // 약 60FPS로 업데이트
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int main(int argc, char* argv[]) {
    return create_window3();
}
