#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define rad90 1.5707963267948966192313216916398
#define max_level 7
#define MAX_SIZE 100

extern int SCREEN_W,SCREEN_H;
extern int BITMAP_W,BITMAP_H;
extern int img_w,img_h;
extern int food_w,food_h;
extern int score,length,current_level;
extern int food_counter,_difficulty;

extern float FPS;

extern bool direction[4],redraw, level_running,game_running;

extern char display_hud[3][30];

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *big_font,*font;
extern ALLEGRO_EVENT_QUEUE *event_queue, *event__queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_BITMAP *_food,*b_food;
extern ALLEGRO_BITMAP *head,*body,*tail,*map,*background, *about,*_snake;
extern ALLEGRO_BITMAP *block_blue,*block_red,*block_green,*block_yellow,*block_gray;
extern ALLEGRO_SAMPLE *navi,*enter,*eat,*die,*_type, *eat_b;

typedef struct for_level
{
    struct for_column
    {
        struct for_row
        {
            char c;
        } row [30];
    } column [40];
} level;
extern level _level[max_level];

enum direction {UP, DOWN, LEFT, RIGHT};

typedef struct
{
    float x;
    float y;
    float rotate;
} snake;
extern snake bod[MAX_SIZE];

typedef struct for_foods
{
    struct for_eatables
    {
        int _x,_y;
        int bonus;
        int status;
    } eatables [20];
    int _number;
} food_str;
extern food_str food;

typedef struct for_score
{
    char name[15];
    int score;
} player_list;

extern player_list player[10];

player_list _tmp;

extern int pos;

#endif // GLOBAL_H_INCLUDED
