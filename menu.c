#include"headers/global.h"
int main_menu()
{
    al_set_target_bitmap(al_get_backbuffer(display));       //Setting up display buffer

    int m[4]= {0,0,0,0};
    int _i=0,j=0;

    while (1)
    {
        event__queue = al_create_event_queue();
        al_register_event_source(event__queue, al_get_keyboard_event_source());

        al_clear_to_color (al_map_rgb(0,0,0));

        for (j=0; j<4; j++)
        {
            m[j]=0;
            if (_i==j) m[j]=1;
        }

        al_draw_bitmap(_snake,0,0,0);
        al_draw_text(font, al_map_rgb(255,255*!m[0],255*!m[0]), 375-m[0]*25, 100,ALLEGRO_ALIGN_CENTRE,"New Game");
        al_draw_text(font, al_map_rgb(255,255*!m[1],255*!m[1]), 375-m[1]*25, 200,ALLEGRO_ALIGN_CENTRE,"High Scores");
        al_draw_text(font, al_map_rgb(255,255*!m[2],255*!m[2]), 375-m[2]*25, 300,ALLEGRO_ALIGN_CENTRE,"About");
        al_draw_text(font, al_map_rgb(255,255*!m[3],255*!m[3]), 375-m[3]*25, 400,ALLEGRO_ALIGN_CENTRE,"Exit");

        al_flip_display();

        ALLEGRO_EVENT _ev;
        al_wait_for_event(event__queue, &_ev);

        if (_ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (_ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
                al_play_sample(navi, 1.0, -1.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                if (_i==3) _i=0;
                else _i++;
            }
            else if (_ev.keyboard.keycode == ALLEGRO_KEY_UP)
            {
                al_play_sample(navi, 1.0, -1.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                if (_i==0) _i=3;
                else _i--;
            }
            else if (_ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                al_play_sample(enter, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                al_destroy_event_queue(event__queue);
                switch (_i)
                {
                case 0:
                    game_running = true;
                    food_counter = 0;
                    current_level = 0;
                    length = 5;
                    score = 0;
                    draw_elements();
                    break;
                case 1:
                    print_highscore();
                    break;
                case 2:
                    al_draw_bitmap(about,0,0,0);
                    al_flip_display();
                    al_rest(5);
                    break;
                case 3:
                    return 0;
                }
            }
        }
    }
}
