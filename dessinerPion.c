#include "dessinerPion.h"


ALLEGRO_BITMAP *dessinerCercle(ALLEGRO_COLOR color,int forme,int valeur,ALLEGRO_COLOR couleurP)
{
    ALLEGRO_FONT *font;
    font=al_load_font("DIOGENES.ttf",17,0);
    ALLEGRO_BITMAP *image;
    image=al_create_bitmap(40,40);
    al_set_target_bitmap(image);
    if(forme==Plein)
    {
        al_draw_filled_circle(20,20,15,color);
        al_draw_circle(20,20,15,couleurP,1.5);
    }
    if(forme==vide)
        al_draw_circle(20,20,15,color,2);
    al_draw_textf(font,couleurP,20,10,ALLEGRO_ALIGN_CENTER,"%i",valeur);
    ALLEGRO_DISPLAY *d=al_get_current_display();
    al_set_target_backbuffer(d);
    return image;
}
ALLEGRO_BITMAP *dessinerCarre(ALLEGRO_COLOR color,int forme,int valeur,ALLEGRO_COLOR couleurP)
{
    ALLEGRO_FONT  *font;
    font=al_load_font("DIOGENES.ttf",17,0);

    ALLEGRO_BITMAP *image1;
    image1=al_create_bitmap(40,40);

    al_set_target_bitmap(image1);
    if(forme==Plein)
    {
        al_draw_filled_rectangle(4,4,35,35,color);
        al_draw_rectangle(5,5,34,34,couleurP,1.5);
    }
    if(forme==vide)
        al_draw_rectangle(3,3,36,36,color,2);
    al_draw_textf(font,couleurP,20,10,ALLEGRO_ALIGN_CENTER,"%i",valeur);
    ALLEGRO_DISPLAY *d=al_get_current_display();
    al_set_target_backbuffer(d);
    return image1;
}
ALLEGRO_BITMAP *dessinerTriangle(ALLEGRO_COLOR color,int forme,int valeur,ALLEGRO_COLOR couleurP)
{
    ALLEGRO_FONT *font;
    font=al_load_font("DIOGENES.ttf",17,0);
    ALLEGRO_BITMAP *image2;
    image2=al_create_bitmap(40,40);
    al_set_target_bitmap(image2);
    if(forme==Plein)
    {
        al_draw_filled_triangle(20,4,4,36,36,36,color);
        al_draw_triangle(20,4,4,36,36,36,couleurP,1.5);
    }
    if(forme==vide)
        al_draw_triangle(20,4,4,36,36,36,color,2);
   /* al_draw_line(20,2,38,38,color,1);
    al_draw_line(2,38,38,38,color,1);*/
    al_draw_textf(font,couleurP,20,17,ALLEGRO_ALIGN_CENTER,"%i",valeur);
    ALLEGRO_DISPLAY *d=al_get_current_display();
    al_set_target_backbuffer(d);

    return image2;
}
ALLEGRO_BITMAP *dessinerPyramide(ALLEGRO_COLOR color)
{

    ALLEGRO_BITMAP *image3;
    image3=al_create_bitmap(40,40);
    al_set_target_bitmap(image3);
    al_draw_line(39,31,20,38,color,2);
    al_draw_line(20,38,2,31,color,2);
    al_draw_line(2,31,7,25,color,2);
    al_draw_line(7,25,20,31,color,2);
    al_draw_line(20,31,36,24,color,2);
    al_draw_line(36,24,31,18,color,2);
    al_draw_line(31,18,20,24,color,2);
    al_draw_line(20,24,9,19,color,2);
    al_draw_line(9,19,13,13,color,2);
    al_draw_line(13,13,20,18,color,2);
    al_draw_line(20,18,28,13,color,2);
    al_draw_line(28,13,24,8,color,2);
    al_draw_line(24,8,20,12,color,2);
    al_draw_line(20,12,15,8,color,2);
    al_draw_line(15,8,20,2,color,2);
    ALLEGRO_DISPLAY *d=al_get_current_display();
    al_set_target_backbuffer(d);
    return image3;
}
