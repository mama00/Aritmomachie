#ifndef AR_MODE_RESEAU_H_INCLUDED
#define AR_MODE_RESEAU_H_INCLUDED
#define Mode_Text 1
#define Mode_Position 2
#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")

char *convertisseurChar(int positionx,int positiony);
coordonne convertisseurPosition(char *texte);
void purger();
void askIP(char ip[15]);
int askport();
jouer_reseau(ALLEGRO_DISPLAY *display,SOCKET sock,int tour);
void MainReseau(ALLEGRO_DISPLAY *fenetre);


#endif // AR_MODE_RESEAU_H_INCLUDED
