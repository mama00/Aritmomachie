#ifndef DESSINERPION_H_INCLUDED
#define DESSINERPION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define Plein 1
#define vide 0

ALLEGRO_BITMAP *dessinerCercle(ALLEGRO_COLOR color,int forme,int valeur);
ALLEGRO_BITMAP *dessinerCarre(ALLEGRO_COLOR color,int forme,int valeur);
ALLEGRO_BITMAP *dessinerTriangle(ALLEGRO_COLOR color,int forme,int valeur);
ALLEGRO_BITMAP *dessinerPyramide(ALLEGRO_COLOR color);


#endif // DESSINERPION_H_INCLUDED
