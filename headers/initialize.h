#ifndef INITIALIZE_H_INCLUDED
#define INITIALIZE_H_INCLUDED

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define max_level 7
#define MAX_SIZE 100

const int SCREEN_W=800;
const int SCREEN_H=600;
const int BITMAP_W=10;
const int BITMAP_H=10;
const int img_w = 20;
const int img_h = 20;
const int food_w=10;
const int food_h=10;

int i,j,k;

int score=0,current_level=0;
int food_counter=0;
int _difficulty = 1;
int length=5;

float FPS = 10;

char display_hud[3][30];

bool direction[4]= {false, true, false,false},redraw, level_running=true,game_running =true;

FILE *file=NULL,*_score=NULL;

ALLEGRO_DISPLAY *display = NULL;

ALLEGRO_EVENT_QUEUE *event_queue = NULL, *event__queue = NULL;

ALLEGRO_TIMER *timer = NULL;

ALLEGRO_FONT *font=NULL,*big_font=NULL;

ALLEGRO_BITMAP *background=NULL,*map=NULL, *about=NULL;
ALLEGRO_BITMAP *_food = NULL,*b_food=NULL;
ALLEGRO_BITMAP *block_red = NULL,*block_green = NULL,*block_blue = NULL,*block_yellow = NULL,*block_gray=NULL;
ALLEGRO_BITMAP *head=NULL,*body = NULL,*tail = NULL,*_snake = NULL;

ALLEGRO_SAMPLE *navi=NULL,*enter=NULL,*eat=NULL,*die=NULL,*_type=NULL, *eat_b=NULL;

typedef struct for_level
{
    struct for_column
    {
        struct for_rod
        {
            char c;
        } row [30];
    } column [40];
} level;
level _level[max_level];

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
food_str food;

typedef struct
{
    float x;
    float y;
    float rotate;
} snake;
snake bod[MAX_SIZE];

typedef struct for_score
{
    char name[15];
    int score;
} player_list;
player_list player[10];
int pos=0;
#endif // INITIALIZE_H_INCLUDED
