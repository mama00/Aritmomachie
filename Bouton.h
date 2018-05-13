#ifndef BOUTON_H_INCLUDED
#define BOUTON_H_INCLUDED
#include "jeu.h"
typedef enum ACTIVITE ACTIVITE;
typedef enum ETAT ETAT;
typedef struct Bouton Bouton;
enum ETAT
{
    NORMAL,PRESSED,PASSED
};
enum ACTIVITE
{
    LOAD,SAVE,MENUPRINCIPAL,JOUER,QUIT,PAUSE,JOUERRESEAU,JOUERIA,JOUERINTERMEDIAIRE,CONTINUERPARTIE,RECOMMENCER,RETOURMENU,FINPA,AIDE,AUCUN
};
struct Bouton
{
    ALLEGRO_BITMAP *image;
    ALLEGRO_BITMAP *image_P;
    int B_H;
    int B_W;
    int posx;
    int posy;
    ACTIVITE activite;
    ETAT etat;
};
Bouton boutonJeu[20];
void Creer_Bouton(ALLEGRO_BITMAP *,ALLEGRO_BITMAP *,int,int,ACTIVITE);
void Afficher_Bouton(Bouton);
void Gerer_Bouton(int,int,ETAT);
bool is_souris_match_bouton(Bouton,int,int);
void effectuer_activite_button(Bouton);
void detuire_bouton(Bouton);
#endif // BOUTON_H_INCLUDED



