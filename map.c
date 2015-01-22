#include "headers/global.h"
void draw_map(int level)
{
    srand (time(0));
    int color,i,j;
    float block_rotation;

    /*Drawing the map on the temporary bitmap */
    for (j=0; j<30; j++)
        for (i=0; i<40; i++)
        {
            if (_level[level].column[i].row[j].c == '1')
            {
                color = 1+ rand()%5;
                block_rotation=0+rand()%3;
                switch (color)
                {
                case 1:
                    al_draw_rotated_bitmap(block_yellow,img_w/2.0,img_h/2.0,5+i*20,5+j*20,block_rotation*rad90,0);
                    break;
                case 2:
                    al_draw_rotated_bitmap(block_blue,img_w/2.0,img_h/2.0,5+i*20,5+j*20,block_rotation*rad90,0);
                    break;
                case 3:
                    al_draw_rotated_bitmap(block_red,img_w/2.0,img_h/2.0,5+i*20,5+j*20,block_rotation*rad90,0);
                    break;
                case 4:
                    al_draw_rotated_bitmap(block_green,img_w/2.0,img_h/2.0,5+i*20,5+j*20,block_rotation*rad90,0);
                    break;
                case 5:
                    al_draw_rotated_bitmap(block_gray,img_w/2.0,img_h/2.0,5+i*20,5+j*20,block_rotation*rad90,0);
                    break;
                }
            }
        }
}

