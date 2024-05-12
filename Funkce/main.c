#include "drawing.h"
#include <stdio.h>

void draw_prerusovana_cara(int);
void draw_schody(int);
void draw_kvetina(int, int);
void draw_louka(int, int);
void draw_smile();

int main() {
    // Keep this line here
    clear_screen();

    // Load the input - what should be drawn.
    int drawing = 0;
    scanf("%d", &drawing);

    // Put your drawing code here
    clear_screen();
    if (drawing == 0)
    {
        set_blue_color();
        draw_prerusovana_cara(10);
        move_down();
        set_red_color();
        draw_prerusovana_cara(5);
        move_down();
        set_yellow_color();
        draw_prerusovana_cara(30);
        move_down();
    }
    else if (drawing == 1) {
        set_white_color();
        draw_schody(6);
        move_down();
        set_green_color();
        draw_schody(4);
        move_down();
        set_blue_color();
        draw_schody(7);
    }
    else if (drawing == 2)
    {
        draw_kvetina(9,11);
        move_to(8,13);
        draw_kvetina(6,9);
        move_to(3,25);
        draw_kvetina(3,5);
        move_to(10,27);
        draw_kvetina(3,4);
    }
    else if (drawing == 3)
    {
        draw_louka(67,20);
    }
    else if (drawing == 4)
    {
        draw_smile();
    }
  

    // Keep this line here
    end_drawing();

    return 0;
}

void draw_prerusovana_cara(int length)
{
    for (int i = 0; i < length; i++)
    {
        if (i%2==0)
        {
            draw_pixel();
        }
        move_right();        
    }
    for (int i = 0; i < length; i++)
    {
        move_left();        
    }
    move_down();
}

void draw_schody(int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int k = 0; k <= i; k++)
        {
            draw_pixel();
            move_right();
        }
        for (int k = 0; k <= i; k++)
        {
            move_left();        
        }
        move_down();
    }
}

void draw_kvetina(int size_x, int size_y)
{
    int kv_size = size_x / 3;
    set_white_color();
    for (int k = 0; k < kv_size; k++)
    {
        for (int i = 0; i < kv_size-1; i++)
        {
            move_right();
        }
        for (int i = 0; i < kv_size; i++)
        {
            move_right();
            draw_pixel();
        }
        for (int i = 0; i < kv_size*2-1; i++)
        {
            move_left();
        }
        move_down();
    }
    for (int k = 0; k < kv_size; k++)
    {
        set_white_color();
        for (int i = 0; i < kv_size; i++)
        {
            draw_pixel();
            move_right();
        }
        set_yellow_color();
        for (int i = 0; i < kv_size; i++)
        {
            draw_pixel();
            move_right();
        }
        set_white_color();
        for (int i = 0; i < kv_size; i++)
        {
            draw_pixel();
            move_right();
        }
        for (int i = 0; i < kv_size*3; i++)
        {
            move_left();
        }
        move_down();
    }
    set_white_color();
    for (int k = 0; k < kv_size; k++)
    {
        for (int i = 0; i < kv_size-1; i++)
        {
            move_right();
        }
        for (int i = 0; i < kv_size; i++)
        {
            move_right();
            draw_pixel();
        }
        for (int i = 0; i < kv_size*2-1; i++)
        {
            move_left();
        }
        move_down();
    }
    set_green_color();
    for (int k = 0; k < size_y-kv_size*3; k++)
    {
        for (int i = 0; i < kv_size-1; i++)
        {
            move_right();
        }
        for (int i = 0; i < kv_size; i++)
        {
            move_right();
            draw_pixel();
        }
        for (int i = 0; i < kv_size*2-1; i++)
        {
            move_left();
        }
        move_down();
    }
}

void draw_louka(int size_x, int size_y)
{
    set_green_color();
    for (int i = 0; i < size_y; i++)
    {
        for (int k = 0; k < size_x; k++)
        {
            move_to(i,k);
            draw_pixel();
        }
    }
    for (int i = 0; i * 10 <= size_y-9; i++)
    {
        for (int k = 0; k * 10 <= size_x+11; k++)
        {
            move_to(2+i*8,2+k*8);
            draw_kvetina(6,6);
        }
    }
}




//////////////////////////////////////////////
///////////////SMILE ANIMATION////////////////
//////////////////////////////////////////////
void draw_smile_mouth1();
void draw_smile_mouth2();
void draw_smile_mouth3();
void draw_smile_mouth4();
void draw_smile_mouth5();
void draw_smile_mouth6();
void draw_smile_eye_left1();
void draw_smile_eye_left2();
void draw_smile_eye_left3();
void draw_smile_eye_right1();

void draw_smile()
{
    int state = 1;
    
    for (int j = 0; j < 10; j++)
    {

        if (state == 1)
        {
            draw_smile_eye_left1();
            draw_smile_eye_right1();
            draw_smile_mouth1();     
        }

        else if (state == 2)
        {
            draw_smile_eye_left1();
            draw_smile_eye_right1();
            draw_smile_mouth2();
        }

        else if (state == 3)
        {
            draw_smile_eye_left1();
            draw_smile_eye_right1();
            draw_smile_mouth3();
        }

        else if (state == 4)
        {
            draw_smile_eye_left1();
            draw_smile_eye_right1();
            draw_smile_mouth4();   
        }

        else if (state == 5)
        {
            draw_smile_eye_left1();
            draw_smile_eye_right1();
            draw_smile_mouth5();    
        }

        else if (state == 6)
        {
            draw_smile_eye_left1();
            draw_smile_eye_right1();
            draw_smile_mouth6();     
        }

        else if (state == 7)
        {
            draw_smile_eye_left2();
            draw_smile_eye_right1();
            draw_smile_mouth6(); 
        }

        else if (state == 8)
        {
            draw_smile_eye_left3();
            draw_smile_eye_right1();
            draw_smile_mouth6();
        }

        else if (state == 9)
        {
            draw_smile_eye_left2();
            draw_smile_eye_right1();
            draw_smile_mouth6();
        }

        else if (state == 10)
        {
            draw_smile_eye_left1();
            draw_smile_eye_right1();
            draw_smile_mouth6();
        }

        animate_ms(100);
        if (state == 6) {animate_ms(500);}
        if (state == 10) {animate_ms(1000);}
        // if (state == 10) {animate_ms(5000);}  // for debugging
        clear_screen();
        state++;
    }
}

void draw_smile_mouth1()
{
    set_black_color();
    move_to(13,11);
    for (int k = 0; k < 12; k++)
    {
        draw_pixel();
        move_right();
    }  
}

void draw_smile_mouth2()
{
    set_black_color();
    move_to(13,9);
    for (int k = 0; k < 16; k++)
    {
        if (k == 4) {move_down();}
        if (k == 12) {move_up();}
        draw_pixel();
        move_right();
    }       
}

void draw_smile_mouth3()
{
    set_black_color();
    move_to(13,9);
    for (int k = 0; k < 16; k++)
    {
        if (k == 2 || k == 4) {move_down();}
        if (k == 14 || k == 12) {move_up();}
        draw_pixel();
        move_right();
    }       
}

void draw_smile_mouth4()
{
    set_black_color();
    move_to(13,9);
    for (int k = 0; k < 16; k++)
    {
        draw_pixel();
        move_right();
    }
    move_to(14,11);
    for (int k = 0; k < 12; k++)
    {
        if (k == 2) {set_white_color();}
        if (k == 10) {set_black_color();}
        draw_pixel();
        move_right();
    }
    move_to(15,13);
    for (int k = 0; k < 8; k++)
    {
        draw_pixel();
        move_right();
    }
}

void draw_smile_mouth5()
{
    set_black_color();
    move_to(13,9);
    for (int k = 0; k < 16; k++)
    {
        draw_pixel();
        move_right();
    }
    move_to(14,9);
    for (int k = 0; k < 16; k++)
    {
        if (k == 2) {set_white_color();}
        if (k == 14) {set_black_color();}
        draw_pixel();
        move_right();
    }
    move_to(15,11);
    for (int k = 0; k < 12; k++)
    {
        if (k == 2) {set_white_color();}
        if (k == 10) {set_black_color();}
        draw_pixel();
        move_right();
    }
    move_to(16,13);
    for (int k = 0; k < 8; k++)
    {
        draw_pixel();
        move_right();
    }
}

void draw_smile_mouth6()
{
    set_black_color();
    move_to(13,9);
    for (int k = 0; k < 6; k++)
    {
        draw_pixel();
        move_right();
    }
    move_to(14,9);
    for (int k = 0; k < 16; k++)
    {
        if (k == 2) {set_white_color();}
        if (k == 6) {set_black_color();}
        draw_pixel();
        move_right();
    }
    move_to(15,9);
    for (int k = 0; k < 16; k++)
    {
        if (k == 2) {set_white_color();}
        if (k == 14) {set_black_color();}
        draw_pixel();
        move_right();
    }
    move_to(16,11);
    for (int k = 0; k < 12; k++)
    {
        if (k == 2) {set_white_color();}
        if (k == 10) {set_black_color();}
        draw_pixel();
        move_right();
    }
    move_to(17,13);
    for (int k = 0; k < 8; k++)
    {
        draw_pixel();
        move_right();
    }
}

void draw_smile_eye_left1()
{
    set_black_color();
    move_to(3,3);
    for (int k = 0; k < 10; k++)
    {
        for (int j = 0; j < k/2; j++)
        {
            draw_pixel();
            move_right();
            draw_pixel();
            move_right();
        }
        move_to(3+k,3);
    }
}

void draw_smile_eye_left2()
{
    set_black_color();
    move_to(8,3);
    for (int k = 0; k < 5; k++)
    {
        for (int j = 0; j < k; j++)
        {
            draw_pixel();
            move_right();
            draw_pixel();
            move_right();
        }
        move_to(8+k,3);
    }
}

void draw_smile_eye_left3()
{
    set_black_color();
    move_to(10,3);
    for (int k = 0; k < 10; k++)
    {
        if (k == 6) {move_down();}
        draw_pixel();
        move_right();
    }
}

void draw_smile_eye_right1()
{
    set_black_color();
    move_to(20,3);
    for (int k = 0; k < 10; k++)
    {
        for (int j = 0; j < k/2; j++)
        {
            draw_pixel();
            move_left();
            draw_pixel();
            move_left();
        }
        move_to(3+k,30);
    }
}