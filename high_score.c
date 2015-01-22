#include "headers/global.h"
void print_highscore(void)
{
    int i=0;

    bool doexit = false;

    char _score_st[20]="";

    FILE *_score=NULL;

    _score = fopen("data/score.dat","r");

    for(i=0; i<10; i++)
        fscanf(_score,"%s\n%d\n",player[i].name,&player[i].score);

    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(0,0,0));

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    for (i=0; i<10; i++)
    {
        itoa(player[i].score,_score_st,10);
        al_draw_text(font, al_map_rgb(255,255,255), 100, 60+i*40,ALLEGRO_ALIGN_CENTRE,player[i].name);
        al_draw_text(font, al_map_rgb(255,255,255), 500, 60+i*40,ALLEGRO_ALIGN_CENTRE,_score_st);
    }

    al_draw_text(font,al_map_rgb(255,255,255),10,10,ALLEGRO_ALIGN_LEFT,"Highscore");
    al_draw_text(font,al_map_rgb(255,255,255),10,550,ALLEGRO_ALIGN_LEFT,"Press SPACE to go to mainmenu");
    al_flip_display();

    while (!doexit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type = ALLEGRO_KEY_DOWN)
            if (ev.keyboard.keycode != ALLEGRO_KEY_SPACE) doexit = false;
            else doexit = true;
    }
}
