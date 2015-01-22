#include "headers/global.h"
bool collison_detect_body(float ,float);
bool collison_detect_map(float,float);
bool collison_detect_food(float,float);

void draw_map(int);
char * make_string(char);
void save_highscore(char []);

void draw_elements(void)
{
    int i,j;
    bool pause = false;

    while (game_running)      //Creating Game Loop
    {
        level_running=true;
        redraw = true;
        pos = 0;
        food._number=0;
        food_counter = 0;
        length=5;
        FPS=10;
        strcpy(display_hud[0],make_string('S'));
        strcpy(display_hud[1],make_string('L'));
        strcpy(display_hud[2],make_string('D'));

        for (i=0; i<4; i++)
            if (i==2)
                direction[i] = true;
            else
                direction[i] = false;


        for (i=0; i<20; i++)        //Initializing food coordinates and properties
        {
            int _x,_y;
            do
            {
                _x = (rand()%800);
                _y = (rand()%600);
            }
            while (_level[current_level].column[_x/20].row[_y/20].c != '0');
            food.eatables[i]._x =_x/10*10-5;
            food.eatables[i]._y = _y/10*10-5;
            food.eatables[i].bonus = (rand()%1000 <= 100) ? 1:0;
            food.eatables[i].status = 0;
            for (j=0; j<i; j++)
                if ((food.eatables[i]._x == food.eatables[j]._x) && (food.eatables[i]._y == food.eatables[j]._y)) i--;
        }

        bod[0].x=400;       //Initializing Snake Coordinates
        bod[0].y=300;

        for(i=1; i<MAX_SIZE; i++)
        {
            bod[i].x = 400+i*10;
            bod[i].y = 300;
            bod[i].rotate=0;
        }

        al_set_target_bitmap(map);      //Creating Map
        al_clear_to_color(al_map_rgb(0, 0, 0));

        draw_map(current_level);

        background=al_clone_bitmap(map);

        al_set_target_bitmap(al_get_backbuffer(display));       //Setting up display buffer
        event_queue = al_create_event_queue();

        al_stop_timer(timer);
        timer=al_create_timer(1.0/FPS);
        al_start_timer(timer);

        al_register_event_source(event_queue, al_get_timer_event_source(timer));        //Registering Events
        al_register_event_source(event_queue, al_get_keyboard_event_source());

        while(level_running)      //Starting Level
        {
            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);

            if (food._number < 6)       //Creating food coordinates and properties
            {
                if ((((rand() % 10000) < 500) || food._number == 0)&&food_counter<20)
                {
                    food._number++;
                    food.eatables[food_counter++].status = 1;
                }
            }

            if(ev.type == ALLEGRO_EVENT_TIMER)      //Updating coordinates if no key was pressed
            {
                if(direction[UP])
                {
                    for(i=MAX_SIZE-2; i>=0; i--)
                        bod[i+1]=bod[i];
                    bod[0].y-= BITMAP_H;
                    bod[0].rotate=rad90;
                }
                if(direction[DOWN])
                {
                    for(i=MAX_SIZE-2; i>=0; i--)
                        bod[i+1]=bod[i];
                    bod[0].y+= BITMAP_H;
                    bod[0].rotate=rad90*3;
                }
                if(direction[LEFT])
                {
                    for(i=MAX_SIZE-2; i>=0; i--)
                        bod[i+1]=bod[i];
                    bod[0].x -= BITMAP_W;
                    bod[0].rotate=0;
                }
                if(direction[RIGHT])
                {
                    for(i=MAX_SIZE-2; i>=0; i--)
                        bod[i+1]=bod[i];
                    bod[0].x += BITMAP_W;
                    bod[0].rotate=rad90*2;
                }
                redraw = true;
            } // End of timer

            if(collison_detect_body(bod[0].x,bod[0].y) || collison_detect_map(bod[0].x,bod[0].y)) // Detecting Collision
            {
                al_play_sample(die, 1.0, -1.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                save_highscore(display_hud[0]);
            }

            if (collison_detect_food(bod[0].x,bod[0].y))     //Detecting Collision with foods
            {
                length +=2;
                food._number--;
                FPS=FPS+0.125*_difficulty;
                al_stop_timer(timer);
                timer=al_create_timer(1.0 / FPS);
                al_start_timer(timer);
                al_register_event_source(event_queue, al_get_timer_event_source(timer));
            }


            if (food_counter==20 && food._number==0)
            {
                level_running=false;
                if (current_level == max_level-1)
                {
                    current_level=0;
                    _difficulty++;
                }
                else
                    current_level++;
            }

            if (ev.type == ALLEGRO_EVENT_KEY_DOWN)      //Detecting Keystrokes
            {
                if(ev.keyboard.keycode==ALLEGRO_KEY_UP && (direction[UP]==false && direction[DOWN]==false))
                {
                    direction[UP] = true;
                    direction[DOWN] = false;
                    direction[RIGHT] = false;
                    direction[LEFT] = false;
                }
                if(ev.keyboard.keycode==ALLEGRO_KEY_DOWN && (direction[UP]==false && direction[DOWN]==false))
                {
                    direction[UP] = false;
                    direction[DOWN] = true;
                    direction[RIGHT] = false;
                    direction[LEFT] = false;
                }
                if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT && (direction[LEFT]==false && direction[RIGHT]==false))
                {
                    direction[UP] = false;
                    direction[DOWN] = false;
                    direction[RIGHT] = false;
                    direction[LEFT] = true;
                }
                if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT && (direction[LEFT]==false && direction[RIGHT]==false))
                {
                    direction[UP] = false;
                    direction[DOWN] = false;
                    direction[RIGHT] = true;
                    direction[LEFT] = false;
                }
                if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
                {
                    save_highscore(display_hud[0]);
                }
                if (ev.keyboard.keycode==ALLEGRO_KEY_P)
                {
                    pause = true;
                    while (pause)
                    {
                        ALLEGRO_EVENT ev_;
                        al_wait_for_event(event_queue, &ev_);
                        if (ev_.type = ALLEGRO_KEY_DOWN)
                            if (ev_.keyboard.keycode != ALLEGRO_KEY_ENTER) pause = true;
                            else pause = false;
                    }
                }
            } // End Of Keystroke Detection

            if(redraw)      //Redrawing snake and food in new positions
            {
                redraw = false;
                al_clear_to_color(al_map_rgb(0,0,0));
                al_set_target_bitmap(background);
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(map,0,0,0);
                strcpy(display_hud[0],make_string('S'));
                strcpy(display_hud[1],make_string('L'));
                strcpy(display_hud[2],make_string('D'));
                al_draw_text(font, al_map_rgb(255,255,255), 640, 10,ALLEGRO_ALIGN_CENTRE, display_hud[0]);
                al_draw_text(font, al_map_rgb(255,255,255), 440, 10,ALLEGRO_ALIGN_CENTRE, display_hud[1]);
                al_draw_text(font, al_map_rgb(255,255,255), 240, 10,ALLEGRO_ALIGN_CENTRE, display_hud[2]);
                al_set_target_bitmap(al_get_backbuffer(display));
                al_draw_bitmap(background,0,0,0);

                for (i=0; i<20; i++)
                    if (food.eatables[i].status == 1)
                    {
                        if (food.eatables[i].bonus)
                            al_draw_bitmap(b_food,food.eatables[i]._x,food.eatables[i]._y,0);
                        else
                            al_draw_bitmap(_food,food.eatables[i]._x,food.eatables[i]._y,ALLEGRO_FLIP_HORIZONTAL*(int)(rand()%2));
                    }

                for(i=0; i<length; i++)
                    if (i==0)
                        al_draw_rotated_bitmap(head,BITMAP_W/2.0,BITMAP_H/2.0,(bod[i].x),(bod[i].y),bod[i].rotate,0);
                    else if (i==(length-1))
                        al_draw_rotated_bitmap(tail,BITMAP_W/2.0,BITMAP_H/2.0,(bod[i].x),(bod[i].y),bod[i-1].rotate,0);
                    else
                        al_draw_rotated_bitmap(body,BITMAP_W/2.0,BITMAP_H/2.0,(bod[i].x),(bod[i].y),bod[i].rotate,0);

                al_flip_display();
            } // End Of Redrawing
        } // Loop Of Current Level
    } // Loop Of Game
} // End of function

bool collison_detect_body(float x,float y)
{
    int i=0;
    float tmpx,tmpy;
    for(i=2; i<(length-1); i++)
    {
        tmpx=bod[i].x;
        tmpy=bod[i].y;
        if ( ( x > tmpx +BITMAP_W-2) || ( y > tmpy + BITMAP_H-2) || ( tmpx > x + BITMAP_W-2) || ( tmpy > y + BITMAP_H-2) )
            continue;
        else
            return(1);
    }
    return 0;
}

bool collison_detect_map(float x,float y)
{
    int tmpx=x/20,tmpy=y/20;
    if (_level[current_level].column[tmpx].row[tmpy].c == '1')
        return(1);
    return 0;
}

bool collison_detect_food(float x,float y)
{
    int _x,_y,i;

    for (i=0; i<20; i++)
    {
        if (food.eatables[i].status == 1)
        {
            _x = food.eatables[i]._x+5;
            _y = food.eatables[i]._y+5;

            if (x == _x && y == _y)
            {
                food.eatables[i].status = 2;
                score += 10*_difficulty + food.eatables[i].bonus * 50 * _difficulty;

                if (food.eatables[i].bonus==1) al_play_sample(eat, 1.0, -1.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                else al_play_sample(eat_b, 1.0, -1.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

                return 1;
            }
        }
    }
    return 0;
}
