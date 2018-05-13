#ifndef MENUPRINCIPAL_H_INCLUDED
#define MENUPRINCIPAL_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "bouton.h"
void MenuPrincipal(ALLEGRO_DISPLAY *display,int MODE_OUVERTURE);
void Sci();
void dessiner_oeil(float x,float y,ALLEGRO_BITMAP *oeil,ALLEGRO_BITMAP * paupiere,ALLEGRO_BITMAP *pupille);
#endif // MENUPRINCIPAL_H_INCLUDED
