void init_allegro_elements(void);
void draw_elements(void);
void exit_game(void);

int main_menu();

int main(int argc, char **argv)
{
    init_allegro_elements();

    if (main_menu()==0)
    {
        exit_game();
        return 0;
    }
}
