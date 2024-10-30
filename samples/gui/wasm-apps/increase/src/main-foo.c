/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

// #include "/usr/local/include/SDL2/SDL.h"
// #include "/usr/include/SDL2/SDL.h" // SDL 관련 함수

#include "wa-inc/lvgl/lvgl.h"
#include "wa-inc/timer_wasm_app.h"
#include "wasm_app.h"
#include <stdlib.h>


#include "mystr.h"
// #include "./zlib.h"
// #include "./zlog.h"


// #define MONITOR_SDL_INCLUDE_PATH <SDL2/SDL.h>
// #include <SDL2/SDL.h>
// #include "./SDL2/SDL.h"
// #include </usr/include/SDL2/SDL_ttf.h>  // SDL_ttf를 사용하는 경우
#include <stdio.h>         // 입출력 함수 사용을 위해
#include <stdint.h>

extern char g_widget_text[];



typedef struct SDL_Rect SDL_Rect;

typedef struct mystr mystr;

// typedef struct mystr
// {
//     int a;
//     int b;
// } mystr;

int foo4(const int * num);

int foo7(mystr * stru);
mystr* foo8(int a, int b);
mystr* foo9(mystr * stru, int a, int b);

uint32_t foo10(int a, int b);

// typedef struct SDL_Rect
// {
//     int x, y;
//     int w, h;
// } SDL_Rect;


static void btn_event_cb(lv_obj_t *btn, lv_event_t event);


typedef uint8_t Uint8;
typedef uint16_t Uint16;
typedef uint32_t Uint32;
typedef int SDL_bool;

typedef struct SDL_BlitMap SDL_BlitMap;
typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Surface SDL_Surface;





uint32_t count = 0;
char count_str[11] = {0};
lv_obj_t *hello_world_label;
lv_obj_t *count_label;
lv_obj_t *btn1;
lv_obj_t *label_count1;
int label_count1_value = 1;
char label_count1_str[11] = {0};

void timer1_update(user_timer_t timer1)
{
  if ((count % 100) == 0)
  {
    snprintf(count_str, sizeof(count_str), "%d", count / 100);
    lv_label_set_text(count_label, count_str);
  }
  ++count;
}

void on_init()
{
  char *text;

  hello_world_label = lv_label_create(NULL, NULL);
  lv_label_set_text(hello_world_label, " ");
  text = lv_label_get_text(hello_world_label);
  printf("Label text %lu %s \n\n", strlen(text), text);
  lv_obj_align(hello_world_label, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

  count_label = lv_label_create(NULL, NULL);
  lv_obj_align(count_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

  /* Create a button on the current loaded screen */
  btn1 = lv_btn_create(NULL, NULL);
  /* Set function to be called when the button is released */
  lv_obj_set_event_cb(btn1, (lv_event_cb_t)btn_event_cb);
  /* Align below the label */
  lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, 0);

  /* Create a label on the button */
  lv_obj_t *btn_label = lv_label_create(btn1, NULL);
  lv_label_set_text(btn_label, "import test");

  label_count1 = lv_label_create(NULL, NULL);
  lv_label_set_text(label_count1, "1");
  lv_obj_align(label_count1, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

  /* Set up a timer */
  user_timer_t timer;
  timer = api_timer_create(10, true, false, timer1_update);
  if (timer)
    api_timer_restart(timer, 10);
  else
    printf("Fail to create timer.\n");





// printf("foo3 : %d\n", foo3(5, 6));
// int num = 5;
// foo4(&num);
// printf("num : %d\n", num);

// float fff = 5.5;
// float * fffp = &fff;

// printf("fff pointer %p\n", &fff);
// printf("fffp 포인터 주소값 %p\n", &fffp);
// printf("fffp 포인터가 가리키는 주소값 %p\n", fffp);
// printf("fffp 포인터가 가리키는 주소값의 값 %f\n", *fffp);

int num1 = 5;
int * num1p = &num1;

printf("num1 pointer %p\n", &num1);
printf("num1p 포인터 주소값 %p\n", &num1p);
printf("num1p 포인터가 가리키는 주소값 %p\n", num1p);
printf("num1p 포인터가 가리키는 주소값의 값 %d\n", *num1p);

// mystr *stru = malloc(sizeof(int) * 2);

if (sizeof(void*) == 8) {
        printf("이 프로그램은 64비트로 컴파일되었습니다.\n");
    }
    else if (sizeof(void*) == 4) {
        printf("이 프로그램은 32비트로 컴파일되었습니다.\n");
    }
    else {
        printf("알 수 없는 비트 수입니다.\n");
    }

mystr *stru = malloc(sizeof(mystr));

printf("%d\n", sizeof(mystr));

stru->a = 11;
stru->b = 22;
printf("함수 호출 전\n");
printf("stru a : %d\n", stru->a);
printf("stru b : %d\n", stru->b);

// foo7(stru);
mystr *strufoo9 = malloc(sizeof(mystr));
printf("strufoo9's original pointer %p\n", strufoo9);
strufoo9 = foo9(stru, 33, 44);

printf("비트 마스킹 전 :");
printf("strufoo9's pointer %p\n", strufoo9);

strufoo9 = (uint32)strufoo9 & 0x0000FFFF;

printf("비트 마스킹 후 :");
printf("strufoo9's pointer %p\n", strufoo9);

printf("함수 호출 후\n");
printf("stru a : %d\n", stru->a);
printf("stru b : %d\n", stru->b);

printf("strufoo9 마스킹 된 함수 호출 \n");
if(strufoo9 == NULL)
{
  printf("strufoo9 is NULL\n");
}
else
{
  printf("strufoo9 a : %d\n", strufoo9->a);
  printf("strufoo9 b : %d\n", strufoo9->b);
}


// stru = foo8(33, 44);
// printf("stru a : %d\n", stru->a);
// printf("stru b : %d\n", stru->b);

// SDL_Rect *window = NULL;

// set_rect(window, 1, 2, 3, 4);

//   print_rect(window);

}

static void btn_event_cb(lv_obj_t *btn, lv_event_t event)
{
  if (event == LV_EVENT_RELEASED)
  {
    label_count1_value++;
    snprintf(label_count1_str, sizeof(label_count1_str), "%d",
             label_count1_value);
    lv_label_set_text(label_count1, label_count1_str);
    if (label_count1_value == 100)
      label_count1_value = 0;
  }
}

