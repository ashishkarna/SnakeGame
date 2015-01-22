#include "headers/initialize.h"
void init_allegro_elements(void)
{
    /* Initializing Elements*/
    if(!al_init())
    {
        al_show_native_message_box(al_get_current_display(),"Error","Allegro","Could not initialize allegro ",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    if(!al_init_image_addon())
    {
        al_show_native_message_box(al_get_current_display(),"Error","Image","Could not initialize image addon ",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    if(!al_install_keyboard())
    {
        al_show_native_message_box(al_get_current_display(),"Error","Keyboard","Could not initialize keyboard ",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    al_init_font_addon();
    if(!al_init_ttf_addon())
    {
        al_show_native_message_box(al_get_current_display(),"Error","Font","Failed to initialize ttf addon",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }

    /*Creating display, timer and events */
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        al_show_native_message_box(al_get_current_display(),"Error","Keyboard","Could not initialize keyboard ",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        al_show_native_message_box(al_get_current_display(),"Error","Timer","Failed to create timer ",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        al_show_native_message_box(al_get_current_display(),"Error","Event","Failed to create event queue",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    if(!al_install_audio())
    {
        al_show_native_message_box(al_get_current_display(),"Error","Audio","Failed to install audio",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }

    if(!al_init_acodec_addon())
    {
        al_show_native_message_box(al_get_current_display(),"Error","Audio","Failed to install audio codec",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }

    if (!al_reserve_samples(6))
    {
        al_show_native_message_box(al_get_current_display(),"Error","Audio","Failed to reserve audio samples",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }

    enter = al_load_sample( "audio/enter.wav" );
    _type = al_load_sample( "audio/_type.wav" );
    navi = al_load_sample( "audio/navi.wav" );
    die = al_load_sample( "audio/die.wav" );
    eat = al_load_sample( "audio/eat.wav" );
    eat_b = al_load_sample ("audio/eat_b.wav");

    if (!enter || !_type || !navi || !die || !eat || !eat_b)
    {
        al_show_native_message_box(al_get_current_display(),"Error","Audio","Failed to load audio files",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }

    /*Loading the font */
    font=al_load_font("fonts/Snake.ttf",30,0);
    big_font=al_load_font("fonts/Snake.ttf",72,0);

    if(!font || !big_font)
    {
        al_show_native_message_box(al_get_current_display(),"Error","Font","Failed to load font(Arial.ttf)",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }


    /*Creating bitmap for background and map */
    background=al_create_bitmap(SCREEN_W,SCREEN_H);
    map=al_create_bitmap(SCREEN_W,SCREEN_H);
    about  = al_load_bitmap("images/about.png");

    /*Loading image files for snake */
    head = al_load_bitmap("images/snakeh.png");
    body = al_load_bitmap("images/snakeb.png");
    tail = al_load_bitmap("images/snaket.png");
    _snake = al_load_bitmap("images/snake.jpg");

    _food = al_load_bitmap("images/image_f.png");
    b_food=al_load_bitmap("images/image_fb.png");

    /*Loading image files for map */
    block_blue = al_load_bitmap("images/block_blue.png");
    block_green = al_load_bitmap("images/block_green.png");
    block_red = al_load_bitmap("images/block_red.png");
    block_yellow = al_load_bitmap("images/block_yellow.png");
    block_gray=al_load_bitmap("images/block_gray.png");

    if(!head || !body || !tail)
    {
        al_show_native_message_box(al_get_current_display(),"Error","Bitmap","Failed to create snake ",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }

    if(!block_blue || !block_green || !block_red|| !block_yellow  || !block_gray || !_food || !b_food)
    {
        al_show_native_message_box(display, "Error", "Level", "Failed to load Level image!",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }

    /*Loading level data file*/
    file = fopen("data/level.dat","r");
    for (k=0; k<max_level; k++)
        for (j=0; j<30; j++)
            for (i=0; i<40; i++)
                fscanf (file,"%c",&(_level[k].column[i].row[j].c));
    fclose (file);

    _score = fopen("data/score.dat","r");
    for(i=0; i<10; i++)
        fscanf(_score,"%s\n%d\n",player[i].name,&player[i].score);
}
