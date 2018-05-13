#include "jeu.h"

int main()
{
    if(!al_init())
        erreur("al_init()");
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_DISPLAY *fenetre;
    fenetre=al_create_display( 1280,800);
    jouer_reseau(fenetre);
    al_destroy_display(fenetre);
    return 0;
}
