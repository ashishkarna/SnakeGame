#include "headers/global.h"
// Creating current score to display on the screen
void draw_elements(void);
void exit_game(void);
char * input (void);
char * make_string(char select)
{
    int n=0,r=0,i=0,j=0;
    char hud[20]="";
    char ch[30]="",tmp[30]="";
    switch (select)
    {
    case 'D':
    {
        if(_difficulty==1)
            return("Easy");
        if (_difficulty==2)
            return("Medium");
        if(_difficulty==3)
            return("Hard");
    }
    case 'S':
    {
        n=score;
        strcpy(hud,"  erocS"); //Score is stored in reverse form so later whole string ch is reversed and stored in tmp
        break;

    }
    case 'L':
    {
        n=current_level+1;
        strcpy(hud,"  leveL");
        break;

    }
    case 'H':
    {
        n=player[pos++].score;
        strcpy(hud," ");
        break;
    }
    }
    if (n==0)
        ch[i++]='0';
    while(n!=0)
    {
        r = n%10;
        ch[i] = r +'0';
        n=n/10;
        i++;
    }

    ch[i]='\0';
    strcat(ch,hud);
    for(i=strlen(ch)-1; i>=0; i--)
        tmp[j++]=ch[i];
    return(tmp);

}

void save_highscore(char str_score[])
{
    int i,j,pos=-1;
    bool play_again=false;
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_text(big_font,al_map_rgb(255,0,0), 400, 300,ALLEGRO_ALIGN_CENTRE, "Game Over!!!!!");
    al_draw_text(big_font, al_map_rgb(0,0,255), 400, 400,ALLEGRO_ALIGN_CENTRE, str_score);
    al_flip_display();
    al_rest(1);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    if (score > player[9].score)
    {
        strcpy(player[9].name,input());
        player[9].score = score;

        for(i=0; i<10; i++)
        {
            for(j=0; j<9; j++)
            {
                if(player[j].score<player[j+1].score)
                {
                    _tmp=player[j];
                    player[j]=player[j+1];
                    player[j+1]=_tmp;
                }
            }
        }

        FILE *fptr=NULL;
        fptr=fopen("data/score.dat","w");
        for(i=0; i<10; i++)
            fprintf(fptr,"%s\n%d\n",player[i].name,player[i].score);
        fclose(fptr);
    }

    else
    {
        level_running=false;
        game_running=false;
    }
    print_highscore();

// Codes below are to be repalced by launching main menu
    /*


        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_text(font,al_map_rgb(0,255,0), 400, 500,ALLEGRO_ALIGN_CENTRE, "Tap enter key to play again ");
        al_flip_display();
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        while(1)
        {
            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);
            if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if(ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
                    play_again=true;
                break;
            }
        }
        if(play_again==true)
        {
            score=0;
            current_level=0;
            level_running=false;
            game_running=true;
            return;
        }
        else
        {
            al_clear_to_color(al_map_rgb(0,0,0));
            level_running=false;
            game_running=false;
            return;
        }*/
}

void exit_game(void)
{
    al_destroy_font(font);
    al_destroy_font(big_font);
    al_destroy_bitmap(head);
    al_destroy_bitmap(body);
    al_destroy_bitmap(tail);
    al_destroy_bitmap(block_red);
    al_destroy_bitmap(block_green);
    al_destroy_bitmap(block_blue);
    al_destroy_bitmap(block_yellow);
    al_destroy_bitmap(block_gray);
    al_destroy_bitmap(_food);
    al_destroy_bitmap(b_food);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_sample(_type);
    al_destroy_sample(navi);
    al_destroy_sample(eat);
    al_destroy_sample(die);
    al_destroy_sample(enter);
    al_destroy_display(display);
}


char * input(void)
{
    int i=0;
    char name[15]="";
    al_set_target_bitmap(background);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font,al_map_rgb(100,100,100), 640/2+2, 480/4+2,ALLEGRO_ALIGN_CENTRE, "You Got Highscore Enter your name:");
    al_draw_text(font,al_map_rgb(255,255,255), 640/2, 480/4,ALLEGRO_ALIGN_CENTRE, "You Got Highscore Enter your name:");

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_set_target_bitmap(al_get_backbuffer(display));
    while(1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue,&ev);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(background,0,0,0);
        al_draw_text(font,al_map_rgb(255,255,255), 640/2, 480,ALLEGRO_ALIGN_CENTRE, name);;
        al_flip_display();

        if(ev.type==ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode>=ALLEGRO_KEY_A && ev.keyboard.keycode<=ALLEGRO_KEY_Z)
                al_play_sample(_type, 1.0, -1.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            if(ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
            {
                al_play_sample(enter, 1.0, -1.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                break;
            }

            if(ev.keyboard.keycode==ALLEGRO_KEY_BACKSPACE)
            {
                al_play_sample(_type, 1.0, -1.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                i--;
                name[i]=' ';
                name[i+1]='\0';
            }

            if(ev.keyboard.keycode==ALLEGRO_KEY_A)
            {
                name[i]='A';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_B)
            {
                name[i]='B';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_C)
            {
                name[i]='C';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_D)
            {
                name[i]='D';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_E)
            {
                name[i]='E';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_F)
            {
                name[i]='F';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_G)
            {
                name[i]='G';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_H)
            {
                name[i]='H';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_I)
            {
                name[i]='I';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_J)
            {
                name[i]='J';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_K)
            {
                name[i]='K';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_L)
            {
                name[i]='L';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_M)
            {
                name[i]='M';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_N)
            {
                name[i]='N';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_O)
            {
                name[i]='O';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_P)
            {
                name[i]='P';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_Q)
            {
                name[i]='Q';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_R)
            {
                name[i]='R';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_S)
            {
                name[i]='S';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_T)
            {
                name[i]='T';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_U)
            {
                name[i]='U';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_V)
            {
                name[i]='V';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_W)
            {
                name[i]='W';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_X)
            {
                name[i]='X';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_Y)
            {
                name[i]='Y';
                name[i+1]='\0';
                i++;
            }
            if(ev.keyboard.keycode==ALLEGRO_KEY_Z)
            {
                name[i]='Z';
                name[i+1]='\0';
                i++;
            }
        }// End of key detection
    } // End of while loop
    level_running=false;
    game_running=false;

    return(name);
}
