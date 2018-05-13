#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include "dessinerPion.h"
#include "EatPawn.h"
#include <math.h>
#define ROUGE al_map_rgb(140,92,36)
#define BLANC al_map_rgb(240,240,240)
#define CERCLE 1
#define CARRE 2
#define TRIANGLE 3
#define PYRAMIDE 4

bool caseBon(int x,int y);
void dessinerPoint(int x,int y,ALLEGRO_BITMAP *image);
void jouer(ALLEGRO_DISPLAY *display);
void erreur(const char*txt);

typedef struct pieces pieces;
struct pieces
{
    int forme;
    int valeur;
    ALLEGRO_BITMAP *image;
};
typedef struct pyramide pyramide;
struct pyramide
{
    pieces piece[8];
    int NbPiece;
    int ETAT;
};


typedef struct Case Case;
struct Case
{
    ALLEGRO_BITMAP *image;
    int valeur;
    int existe;
    int forme;
    int side;
    pyramide py;
};
typedef struct coordonne coordonne;
struct coordonne
{
    int x;
    int y;
};
void afficherBoard(int ws,int hs,ALLEGRO_BITMAP *image);
void afficherPosvalide(int x,int y, int forme);
int verifierDeplacement(int oldx,int oldy,int x,int y, int forme,int ws,int hs);
void initialiseBoard(void);
int is_blocked(int x,int y,int forme,int side);
void ChangerPosition(int x1,int y1,int x2,int y2,int ws,int hs);
bool click_is_out(int x,int y);
void init_pion(void);
int contain(int x,int y,coordonne *tab,int a,int b);
bool ccb(int x,int y,int side);
bool verifierGlissement(int oldx,int oldy,int x,int y,int forme);
coordonne *attacked_piece_list(int mx,int my,int side,int forme,int ws,int hs);
void blocked_piece_list(int x,int y,int ws,int hs);
int recherchek(int side);
int is_Pym_not_found();
int sommeValPy(int x,int y);
void afficherPiecePyramide(int x,int y);
void arrangerPym(int x,int y);
void saveGame();
void loadGame();
 Case p[11][16];

#endif // JEU_H_INCLUDED
