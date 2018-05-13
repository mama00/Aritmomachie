#include "Bouton.h"
int NbBouton=0;
void Creer_Bouton(ALLEGRO_BITMAP *image,ALLEGRO_BITMAP *imageP,int posx,int posy,ACTIVITE activite)
{
    NbBouton++;
    boutonJeu[NbBouton].activite=activite;
    boutonJeu[NbBouton].image=image;
    boutonJeu[NbBouton].image_P=imageP;
    boutonJeu[NbBouton].B_H=al_get_bitmap_height(image);
    boutonJeu[NbBouton].B_W=al_get_bitmap_width(image);
    boutonJeu[NbBouton].etat=NORMAL;
    boutonJeu[NbBouton].posx=posx;
    boutonJeu[NbBouton].posy=posy;
}
void Afficher_Bouton(Bouton bouton)
{
    al_draw_bitmap(bouton.image,bouton.posx,bouton.posy,0);
    al_flip_display();
}
void effectuer_activite_button(Bouton bouton)
{
    int i;
    switch(bouton.etat)
    {
    case NORMAL:
        break;
    case PRESSED:
        switch(bouton.activite)
        {
        case JOUERINTERMEDIAIRE:
            for(i=1;i<=NbBouton;i++)
                detuire_bouton(boutonJeu[i]);
jouer_intermediaire();
            break;
        case JOUER:
               for(i=1;i<=NbBouton;i++)
                detuire_bouton(boutonJeu[i]);
                al_stop_samples();
                jouer(al_get_current_display(),0);
                break;
        case LOAD:
                           for(i=1;i<=NbBouton;i++)
                detuire_bouton(boutonJeu[i]);
                                al_stop_samples();
                                initialiseBoard();
            jouer(al_get_current_display(),1);
            break;
        case FINPA:
              for(i=1;i<=NbBouton;i++)
                detuire_bouton(boutonJeu[i]);
            fin_de_partie();
            break;
        case SAVE:
            saveGame();
            break;
        case QUIT:
            exit(EXIT_SUCCESS);
            break;
        case RECOMMENCER:
            break;
        case PAUSE:
            break;
        case MENUPRINCIPAL:
            for(i=1;i<=NbBouton;i++)
                detuire_bouton(boutonJeu[i]);
                                al_stop_samples();
            MenuPrincipal(al_get_current_display());
            break;
        case JOUERIA:
            for(i=1;i<=NbBouton;i++)
                detuire_bouton(boutonJeu[i]);
                                al_stop_samples();
            jouer_IA(al_get_current_display());
            break;
        case JOUERRESEAU:
            for(i=1;i<=NbBouton;i++)
                detuire_bouton(boutonJeu[i]);
                                al_stop_samples();
            MainReseau(al_get_current_display());
            break;
        case RETOURMENU:
            for(i=1;i<=NbBouton;i++)
                detuire_bouton(boutonJeu[i]);
                MenuPrincipal(al_get_current_display(),1);
            break;
            case CONTINUERPARTIE:
            for(i=1;i<=NbBouton;i++)
                detuire_bouton(boutonJeu[i]);
                                al_stop_samples();
            jouer(al_get_current_display(),CR);
        break;
            case AIDE:
                aide();
                break;
            case AUCUN:
                break;
        }

    case PASSED:
        al_draw_bitmap(bouton.image_P,bouton.posx,bouton.posy,0);
        al_flip_display();
        break;
    }
}
bool is_souris_match_bouton(Bouton bouton,int xs,int ys)
{
    if(bouton.posx<xs&&xs<bouton.B_W+bouton.posx&&bouton.posy<ys&&ys<bouton.posy+bouton.B_H)
        return true;
    else
        return false;
}
void Gerer_Bouton(int xs,int ys,ETAT etat)
{
    int i;
    for(i=1; i<=NbBouton; i++)
    {
        if(boutonJeu[NbBouton].posx!=0)
        if(is_souris_match_bouton(boutonJeu[i],xs,ys))
        {
            boutonJeu[i].etat=etat;
            effectuer_activite_button(boutonJeu[i]);
            break;
        }
        else
        {
            if(boutonJeu[i].etat!=NORMAL)
            {
                boutonJeu[i].etat=NORMAL;
                al_draw_bitmap(boutonJeu[i].image,boutonJeu[i].posx,boutonJeu[i].posy,0);
                al_flip_display();
            }
        }
    }
}
void detuire_bouton(Bouton b)
{
      b.activite=0;
    b.image=NULL;
    b.image_P=NULL;
    b.B_H=0;
    b.B_W=0;
    b.etat=0;
    b.posx=0;
    b.posy=0;
    NbBouton=0;
}




