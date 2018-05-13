#include "Bouton.h"
void erreur(const char *txt)
{
    ALLEGRO_DISPLAY*d;
    d=al_is_system_installed()?al_get_current_display():NULL;
    al_show_native_message_box(d,"ERREUR",txt,NULL,NULL,0);
    exit(EXIT_FAILURE);
}
void jouer(ALLEGRO_DISPLAY *display,int mode)
{
    compteurJeu=0;
    int joueur[2]= {-1,1};
    int i,j,Mange,pym=0,selec=0;
if(mode==PR)
    initialiseBoard();

    char loading[]="Load...";

    int oldx=0,oldy=0,move=0;
    ALLEGRO_EVENT_QUEUE *e;
    al_init_font_addon();

    if(!al_init_ttf_addon())
        erreur("init font");
    ALLEGRO_FONT *police;
    ALLEGRO_FONT *police1;

    police=al_load_font("pythia.ttf",40,0);
        police1=al_load_font("DIOGENES.ttf",30,0);

    if(!police)
        erreur("font");
    const int w=al_get_display_width(display);
    const int h=al_get_display_height(display);
    const int ws=(w-320)/2;
    const int hs=(h-640)/2;
    al_set_window_title(display,"Arithmomachie");

    if(!al_init_image_addon())
        erreur("dd");
    al_init_primitives_addon();
    ALLEGRO_BITMAP *test;
    ALLEGRO_BITMAP *image,*back;
    back=al_load_bitmap("back.bmp");
    test=al_load_bitmap("plume.bmp");
    image=al_load_bitmap("bg.bmp");

    ALLEGRO_MOUSE_CURSOR *curseur;
    ALLEGRO_BITMAP *cur;
    cur=al_load_bitmap("plumer.bmp");

    curseur=al_create_mouse_cursor(cur,0,0);
    al_set_mouse_cursor(display,curseur);
     al_install_audio();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_reserve_samples(2);
    son1=al_load_sample("son1.wav");
    son2=al_load_sample("son2.wav");

    char nom[44];
    if(mode!=2)
    {
    for(i=0; i<=280; i++)
     {
         al_draw_bitmap(back,0,0,0);
         if(i%40==0)
         {
             sprintf(nom,"%c",loading[i/40]);
             al_set_target_bitmap(back);
             al_draw_text(police,ROUGE,w/2+i-150,hs+600,0,nom);
             al_set_target_backbuffer(display);
         }
         if(i/40<4)
             al_draw_bitmap(test,i-10+w/2-150,16*sin(6*i)+h/2+200,0);
         else
             al_draw_bitmap(test,i-10+w/2-150,h/2+200,0);
         al_flip_display();
         al_rest(0.01);
     }
    }
    al_draw_bitmap(back,0,0,0);
    if(mode==0)
    init_pion();
    if(mode==1)
        loadGame();
    afficherBoard(ws,hs,image);
    al_flip_display();
    al_install_mouse();

    al_install_keyboard();
    e=al_create_event_queue();
    al_register_event_source(e,al_get_mouse_event_source());
    al_register_event_source(e,al_get_display_event_source(display));
    al_register_event_source(e,al_get_keyboard_event_source());

    ALLEGRO_BITMAP * enregistrer;
    ALLEGRO_BITMAP * enregistrerp;
    enregistrer=al_create_bitmap(150,50);
    enregistrerp=al_create_bitmap(150,50);
    al_set_target_bitmap(enregistrer);
    al_draw_text(police1,al_map_rgb(255,135,0),75,0,ALLEGRO_ALIGN_CENTER,"Enregistrer");
    al_set_target_bitmap(enregistrerp);
    al_draw_text(police1,al_map_rgb(180,167,143),75,0,ALLEGRO_ALIGN_CENTER,"Enregistrer");
    al_set_target_backbuffer(al_get_current_display());
    Creer_Bouton(enregistrer,enregistrerp,ws+420,hs+640,SAVE);
    Afficher_Bouton(boutonJeu[1]);
           int dernierx=0,derniery=0;
    while(move!=4)
    {

        int t=0;
        ALLEGRO_EVENT ev= {0};
        al_wait_for_event(e,&ev);
        if(pym==2&&(p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme==CERCLE||p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme==CARRE||p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme==TRIANGLE||p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme==PYRAMIDE_NON_COMPAC))

        {
            {

                while(selec!=2)
                {
                    ALLEGRO_EVENT ev= {0};
                    al_wait_for_event(e,&ev);
                    switch(ev.type)
                    {
                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                        if(ev.mouse.button==1)
                        {
                            if((oldx-ws)/40+1<=4)
                            {
                                printf("%d",p[(oldx-ws)/40+1][(oldy-hs)/40+1].py.piece[(ev.mouse.x-(oldx/40*40))/40+1].valeur);
                                p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme=p[(oldx-ws)/40+1][(oldy-hs)/40+1].py.piece[(ev.mouse.x-(oldx/40*40))/40+1].forme;
                                pym=0;
                                selec=2;
                                al_draw_rectangle((ev.mouse.x-ws)/40*40+ws,(ev.mouse.y-hs)/40*40+hs,(ev.mouse.x-ws)/40*40+ws+40,(ev.mouse.y-hs)/40*40+hs+40,al_map_rgb(243,248,63),2);
                                al_flip_display();
                                al_rest(0.5);
                            }
                            if((oldx-ws)/40+1>4)
                            {
                                printf("%d",p[(oldx-ws)/40+1][(oldy-hs)/40+1].py.piece[(-ev.mouse.x+((oldx/40*40)+40))/40+1].valeur);
                                p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme=p[(oldx-ws)/40+1][(oldy-hs)/40+1].py.piece[(-ev.mouse.x+((oldx/40*40)+40))/40+1].forme;
                                pym=0;
                                selec=2;
                                al_draw_rectangle((ev.mouse.x-ws)/40*40+ws,(ev.mouse.y-hs)/40*40+hs,(ev.mouse.x-ws)/40*40+ws+40,(ev.mouse.y-hs)/40*40+hs+40,al_map_rgb(243,248,63),2);
                                al_flip_display();
                                al_rest(0.5);
                            }
                        }
                        break;

                    case ALLEGRO_EVENT_DISPLAY_CLOSE:
                        move=4;
                        break;
                    }
                }
            }
            selec=0;
            al_flush_event_queue(e);
        }

        else if(Mange==1)
        {
            coordonne tab[10][3];
            for(i=0; i<10; i++)
            {
                for(j=0; j<3; j++)
                {

                    tab[i][j].x=attacked_piece_list((ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].side,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].forme,ws,hs)[i*3+j].x;
                    tab[i][j].y=attacked_piece_list((ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].side,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].forme,ws,hs)[i*3+j].y;
                }
            }
            int k=tab[9][2].x;
            while(!mange_is_over(*tab))
            {
                for(i=0; i<k; i++)
                {
if(tab[i][0].x!=0&&tab[i][0].y!=0)
                    al_draw_rectangle((tab[i][0].x-1)*40+ws,(tab[i][0].y-1)*40+hs,(tab[i][0].x-1)*40+ws+40,(tab[i][0].y-1)*40+40+hs,al_map_rgb(255,0,0),2);
                    if(tab[i][1].x!=0&&tab[i][1].y!=0)
                    al_draw_rectangle((tab[i][1].x-1)*40+ws,(tab[i][1].y-1)*40+hs,(tab[i][1].x-1)*40+ws+40,(tab[i][1].y-1)*40+40+hs,al_map_rgb(243,248,63),2);
                  if(tab[i][2].x!=0&&tab[i][2].y!=0)
                    al_draw_rectangle((tab[i][2].x-1)*40+ws,(tab[i][2].y-1)*40+hs,(tab[i][2].x-1)*40+ws+40,(tab[i][2].y-1)*40+40+hs,al_map_rgb(243,248,63),2);
                    al_flip_display();
                }
                ALLEGRO_EVENT ev= {0};
                al_wait_for_event(e,&ev);
                switch(ev.type)
                {
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                    if(p[(ev.mouse.x-ws)/40 +1][(ev.mouse.y-hs)/40+1].existe!=-1&&p[(ev.mouse.x-ws)/40 +1][(ev.mouse.y-hs)/40+1].existe!=0)
                    {
                        move=1;
                        oldx=ev.mouse.x;
                        oldy=ev.mouse.y;

                    }
                    break;

                case ALLEGRO_EVENT_MOUSE_AXES:
                    if(move==1)
                    {
                        if(ev.mouse.x>ws+280)
                            ev.mouse.x=ws+280;
                        if(ev.mouse.x<ws)
                            ev.mouse.x=ws;
                        if(ev.mouse.y<hs)
                            ev.mouse.y=hs;
                        if(ev.mouse.y>600+hs)
                            ev.mouse.y=600+hs;


                        afficherBoard( ws, hs,image);
                        al_draw_filled_rectangle((oldx-ws)/40 *40+ws,(oldy-hs)/40 * 40+hs,(oldx-ws)/40 *40 +ws+40,(oldy-hs)/40 *40+hs+40,al_map_rgb(226,195,142));
                        al_draw_bitmap(p[(oldx-ws)/40+1][(oldy-hs)/40+1].image,ev.mouse.x,ev.mouse.y,0);
                        al_flip_display();
                    }
                    break;
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                    if((ev.mouse.y-hs)/40+1<17&&(ev.mouse.y-hs)/40+1>0)
                    {
                        if(p[(oldx-ws)/40+1][(oldy-hs)/40+1].existe==1)
                        {

                            move=0;
                            afficherBoard( ws, hs,image);

                            if((ev.mouse.x-ws)/40!=(oldx-ws)/40||(ev.mouse.y-hs)/40!=(oldy-hs)/40)
                            {
                                if(contain((oldx-ws)/40+1,(oldy-hs)/40+1,tab,(ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1)==1)
                                {
                                    ChangerPosition(ev.mouse.x,ev.mouse.y,oldx,oldy,ws,hs);
                            al_play_sample(son2,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

                                    tab[9][2].x--;
                                    for(i=0; i<11; i++)
                                    {
                                        if(tab[i][0].x==(ev.mouse.x-ws)/40+1&&tab[i][0].y==(ev.mouse.y-hs)/40+1)
                                        {
                                            tab[i][0].x=0;
                                            tab[i][0].y=0;
                                        }

                                    }
                                    for(i=0; i<11; i++)
                                    {
                                        for(j=1; j<3; j++)
                                            if(tab[i][j].x==(oldx-ws)/40+1&&tab[i][j].y==(oldy-hs)/40+1)
                                            {
                                                tab[i][j].x=0;
                                                tab[i][j].y=0;
                                            }
                                    }


                                }
                            }
                            //al_draw_bitmap(p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].image,(ev.mouse.x-ws)/40 * 40+ws,(ev.mouse.y-hs)/40 * 40+hs,0);
                            afficherBoard( ws, hs,image);
                            al_flip_display();

                            if(verifierDeplacement(oldx,oldy,ev.mouse.x,ev.mouse.y,p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme,ws,hs)==0)
                            {
                                move=0;
                                afficherBoard(ws, hs,image);
                                al_flip_display();
                            }
                        }

                        else
                        {
                            move=0;
                            afficherBoard( ws,hs,image);
                            al_flip_display();
                        }
                    }
                    break;
                }


            }
            Mange=0;
        }
        else
        {
            switch(ev.type)
            {
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(ev.mouse.x<ws||ev.mouse.x>ws+320||ev.mouse.y<hs||ev.mouse.y>hs+640)
                    Gerer_Bouton(ev.mouse.x,ev.mouse.y,PRESSED);
                if(ev.mouse.x>ws-50&&ev.mouse.x<ws+320+50&&ev.mouse.y<hs+640+50&&ev.mouse.y>hs)
                {
                    if(ev.mouse.x<ws&&ev.mouse.x>ws-40)
                        ev.mouse.x-=40;
                    if(p[(ev.mouse.x-ws)/40 +1][(ev.mouse.y-hs)/40+1].existe!=-1&&p[(ev.mouse.x-ws)/40 +1][(ev.mouse.y-hs)/40+1].existe!=0)
                    {
                        if(ev.mouse.button==2)
                            if(p[(ev.mouse.x-ws)/40 +1][(ev.mouse.y-hs)/40+1].py.ETAT==PYRAMIDE)
                            {
                                if(pym==1)
                                {
                                    pym=2;
                                    oldx=ev.mouse.x;
                                    oldy=ev.mouse.y;
                                    move=0;
                                }
                                if(pym==0)
                                    pym=1;
                                afficherPiecePyramide((ev.mouse.x-ws)/40 +1,(ev.mouse.y-hs)/40+1);
                                al_flip_display();

                            }
                        if(ev.mouse.button==1&&p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].side==joueur[compteurJeu%2])
                        {
                            move=1;
                            oldx=ev.mouse.x;
                            oldy=ev.mouse.y;
                            pym=0;
                            afficherPosvalide((ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].forme);
                        }
                    }
                }
                break;


            case ALLEGRO_EVENT_MOUSE_AXES:
                if(ev.mouse.x<ws||ev.mouse.x>ws+320||ev.mouse.y<hs||ev.mouse.y>hs+640)
                    Gerer_Bouton(ev.mouse.x,ev.mouse.y,PASSED);
                if(move==0&&ev.mouse.x>ws&&ev.mouse.x<ws+320&&ev.mouse.y>hs&&ev.mouse.y<hs+640)
                {
                    afficherBoard(ws,hs,image);
                    al_draw_rectangle((ev.mouse.x-ws)/40*40+ws,(ev.mouse.y-hs)/40*40+hs,(ev.mouse.x-ws)/40*40+ws+40,(ev.mouse.y-hs)/40*40+hs+40,al_map_rgb(243,248,63),2);
                    al_flip_display();
                }

                if(move==1)
                {
                    if(ev.mouse.x>ws+280)
                        ev.mouse.x=ws+280;
                    if(ev.mouse.x<ws)
                        ev.mouse.x=ws;
                    if(ev.mouse.y<hs)
                        ev.mouse.y=hs;
                    if(ev.mouse.y>600+hs)
                        ev.mouse.y=600+hs;
                    afficherBoard( ws, hs,image);
                    al_draw_filled_rectangle((oldx-ws)/40 *40+ws,(oldy-hs)/40 * 40+hs,(oldx-ws)/40 *40 +ws+40,(oldy-hs)/40 *40+hs+40,al_map_rgb(226,195,142));
                    al_draw_rectangle((ev.mouse.x-ws)/40*40+ws,(ev.mouse.y-hs)/40*40+hs,(ev.mouse.x-ws)/40*40+ws+40,(ev.mouse.y-hs)/40*40+hs+40,al_map_rgb(243,248,63),2);
                    al_draw_bitmap(p[(oldx-ws)/40+1][(oldy-hs)/40+1].image,ev.mouse.x,ev.mouse.y,0);
                    al_flip_display();
                }
                break;
                if(move==1)
                {
                    afficherPosvalide((oldx-ws)/40+1,(oldy-hs)/40+1,p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme);
                    al_flip_display();

                }
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if((ev.mouse.y-hs)/40+1<17&&(ev.mouse.y-hs)/40+1>0&&(ev.mouse.x-ws)/40+1<9&&(ev.mouse.x-ws)/40+1>0)
                {


                    if(p[(oldx-ws)/40+1][(oldy-hs)/40+1].existe==1&&p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].existe==-1||(verifierGlissement(oldx,oldy,ev.mouse.x,ev.mouse.y,p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme)==1&&is_blocked((ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].forme,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].side)==1&&is_in_blocked_piece_list((oldx-ws)/40+1,(oldy-hs)/40+1,(ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1)))
                    {

                        if(verifierDeplacement(oldx,oldy,ev.mouse.x,ev.mouse.y,p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme,ws,hs)==1||(click_is_out(oldx,oldy)&&p[(oldx-ws)/40+1][(oldy-hs)/40+1].existe==1)||(verifierGlissement(oldx,oldy,ev.mouse.x,ev.mouse.y,p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme)==1&&is_blocked((ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].forme,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].side)==1))
                        {
                            afficherBoard( ws, hs,image);

                            if((ev.mouse.x-ws)/40!=(oldx-ws)/40||(ev.mouse.y-hs)/40!=(oldy-hs)/40)
                            {
                                // animation_deplacement(oldx/40*40,oldy/40*40,ev.mouse.x/40*40,ev.mouse.y/40*40,image);
                                ChangerPosition(ev.mouse.x,ev.mouse.y,oldx,oldy,ws,hs);
                                dernierx=ev.mouse.x;
                                derniery=ev.mouse.y;
                                compteurJeu++;
                            }
                            // al_draw_bitmap(p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].image,(ev.mouse.x-ws)/40 * 40+ws,(ev.mouse.y-hs)/40 * 40+hs,0);
                            afficherBoard( ws, hs,image);
                            al_flip_display();
                            if(attacked_piece_list((ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].side,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].forme,ws,hs)[29].x!=0)
                            {
                                Mange=1;
                            }
                            if(is_blocked((ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].forme,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].side)==1)
                            {
                                ChangerPosition(ev.mouse.x,ev.mouse.y,ev.mouse.x,ev.mouse.y,ws,hs);
                                move=0;

                            }
                            al_set_target_backbuffer(display);
                        }
                        //  afficherPosvalide((ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1,p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].forme);

                        if(verifierDeplacement(oldx,oldy,ev.mouse.x,ev.mouse.y,p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme,ws,hs)==0)
                        {
                            move=0;
                            afficherBoard(ws, hs,image);
                            al_flip_display();
                        }
                    }

                   else
                    {
                        move=0;
                        afficherBoard(ws, hs,image);
                        al_flip_display();
                    }
                }

                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
                {

                  for(i=1;i<=3;i++)
                detuire_bouton(boutonJeu[i]);
                    MenuPrincipal(al_get_current_display(),AP);
                }
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                move=4;
                break;

            }

        }

if(is_pym_not_found()==1||is_pym_not_found()==-1)
    fin_de_partie();
    }

}

int is_ar_match(int x,int y,int z)
{
    if(y>x)
    {
        int a;
        a=y;
        y=x;
        x=a;
    }
    float m=x,d=y,p=z;
    if(m*d==p||(d+m)/2==p||m+d==z||m-d==p||m/d==p)
        return 1;
    else
        return 0;
}
void afficherBoard(int ws,int hs,ALLEGRO_BITMAP *image)
{
    al_draw_bitmap(image,(2*ws+320-500)/2-18,(2*hs+640-950)/2,0);
    int i,j;
    for(i=0; i<=320; i+=40)
    {
        for(j=0; j<=640; j+=40)
        {
            al_draw_line(i+ws,hs,i+ws,640+hs,al_map_rgb(20,20,20),1);
            al_draw_line(ws,hs+j,ws+320,hs+j,al_map_rgb(20,20,20),1);
            if(p[i/40+1][j/40+1].image!=NULL&&i<320&&j<640)
            {
                al_draw_bitmap(p[i/40+1][j/40+1].image,i+ws,j+hs,0);
            }
        }
    }

    for(i=8; i<12; i++)
    {
        for(j=0; j<16; j++)
        {
            if(p[i+1][j+1].existe==1)
            {

                if(p[i+1][j+1].image!=NULL&&p[i+1][j+1].side==-1)
                    al_draw_bitmap(p[i+1][j+1].image,i*40+ws,j*40+hs,0);
                if(p[i+1][j+1].image!=NULL&&p[i+1][j+1].side==1)
                    al_draw_bitmap(p[i+1][j+1].image,ws+(i)*40,j*40+hs,0);
            }

        }
        for(j=0; j<16; j++)
        {
            if(p[0][j+1].image!=NULL&&p[0][j+1].side==1)
                al_draw_bitmap(p[0][j+1].image,ws-40,j*40+hs,0);
        }


    }

}

int verifierDeplacement(int oldx,int oldy,int x,int y, int forme,int ws,int hs)
{
    int i=-3;
    int a=0;
    switch(forme)
    {
    case CERCLE:
        if(((oldx-ws)/40 -1 == (x-ws)/40 &&(oldy-hs)/40 -1 ==(y-hs)/40 )||((oldx-ws)/40 - 1 == (x-ws)/40 && (oldy-hs)/40 +1 ==(y-hs)/40 )||((oldx-ws)/40 +1 == (x-ws)/40 &&(oldy-hs)/40 -1 ==(y-hs)/40 )||((oldx-ws)/40 +1 == (x-ws)/40 &&(oldy-hs)/40 +1 ==(y-hs)/40 ))
            return 1;
        else
            return 0;
        break;
    case TRIANGLE:
        if(!is_blocked((oldx-ws)/40+1,(oldy-hs)/40+1,p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme,p[(oldx-ws)/40+1][(oldy-hs)/40+1].side))
            if((oldx-ws)/40==(x-ws)/40+1&&(oldy-hs)/40-1==(y-hs)/40+1||((oldx-ws)/40+2==(x-ws)/40+1&&((oldy-hs)/40-1==(y-hs)/40+1))||((oldx-ws)/40-1==(x-ws)/40+1&&(oldy-hs)/40==(y-hs)/40+1)||((oldx-ws)/40+3==(x-ws)/40+1&&(oldy-hs)/40==(y-hs)/40+1)
                    ||((oldx-ws)/40-1==(x-ws)/40+1&&(oldy-hs)/40==(y-hs)/40+1)||((oldx-ws)/40+3==(x-ws)/40+1&&(oldy-hs)/40==(y-hs)/40+1)||((oldx-ws)/40-1==(x-ws)/40+1&&(oldy-hs)/40+2==(y-hs)/40+1)||((oldx-ws)/40+3==(x-ws)/40+1&&(oldy-hs)/40+2==(y-hs)/40+1)||
                    ((oldx-ws)/40==(x-ws)/40+1&&(oldy-hs)/40+3==(y-hs)/40+1)||((oldx-ws)/40+2==(x-ws)/40+1&&(oldy-hs)/40+3==(y-hs)/40+1))
                a=1;

        if(((oldx-ws)/40+1==(x-ws)/40+1&&(oldy-hs)/40-1==(y-hs)/40+1)&&p[(oldx-ws)/40+1][(oldy-hs)/40].existe==-1)
            a=1;
        if(((oldx-ws)/40+1==(x-ws)/40+1&&((oldy-hs)/40+3==(y-hs)/40+1))&&p[(oldx-ws)/40+1][(oldy-hs)/40+2].existe==-1)
            a=1;
        if(((oldx-ws)/40+3==(x-ws)/40+1&&(oldy-hs)/40+1==(y-hs)/40+1)&&p[(oldx-ws)/40+2][(oldy-hs)/40+1].existe==-1)
            a=1;
        if(((oldx-ws)/40-1==(x-ws)/40+1&&(oldy-hs)/40+1==(y-hs)/40+1)&&p[(oldx-ws)/40][(oldy-hs)/40+1].existe==-1)
            a=1;

        return a;
        break;




    case CARRE:
        if(!is_blocked((oldx-ws)/40+1,(oldy-hs)/40+1,p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme,p[(oldx-ws)/40+1][(oldy-hs)/40+1].side))
            if((oldx-ws)/40==(x-ws)/40+1&&(oldy-hs)/40-2==(y-hs)/40+1||((oldx-ws)/40+2==(x-ws)/40+1&&((oldy-hs)/40-2==(y-hs)/40+1))||((oldx-ws)/40-3==(x-ws)/40+1&&(oldy-hs)/40==(y-hs)/40+1)||((oldx-ws)/40+4==(x-ws)/40+1&&(oldy-hs)/40==(y-hs)/40+1)
                    ||((oldx-ws)/40-2==(x-ws)/40+1&&(oldy-hs)/40==(y-hs)/40+1)||((oldx-ws)/40+4==(x-ws)/40+1&&(oldy-hs)/40==(y-hs)/40+1)||((oldx-ws)/40-2==(x-ws)/40+1&&(oldy-hs)/40+2==(y-hs)/40+1)||((oldx-ws)/40+4==(x-ws)/40+1&&(oldy-hs)/40+2==(y-hs)/40+1)||
                    ((oldx-ws)/40==(x-ws)/40+1&&(oldy-hs)/40+4==(y-hs)/40+1)||((oldx-ws)/40+2==(x-ws)/40+1&&(oldy-hs)/40+4==(y-hs)/40+1))
                a=1;

        if(((oldx-ws)/40+1==(x-ws)/40+1&&(oldy-hs)/40-2==(y-hs)/40+1)&&p[(oldx-ws)/40+1][(oldy-hs)/40].existe==-1&&p[(oldx-ws)/40+1][(oldy-hs)/40-1].existe==-1)
            a=1;
        if((((oldx-ws)/40+1==(x-ws)/40+1)&&(oldy-hs)/40+4==(y-hs)/40+1)&&p[(oldx-ws)/40+1][(oldy-hs)/40+2].existe==-1&&p[(oldx-ws)/40+1][(oldy-hs)/40+3].existe==-1)
            a=1;
        if(((oldx-ws)/40-2==(x-ws)/40+1&&(oldy-hs)/40+1==(y-hs)/40+1)&&p[(oldx-ws)/40][(oldy-hs)/40+1].existe==-1&&p[(oldx-ws)/40-1][(oldy-hs)/40+1].existe==-1)
            a=1;
        if((((oldx-ws)/40+4)==(x-ws)/40+1&&(oldy-hs)/40+1==(y-hs)/40+1)&&p[(oldx-ws)/40+2][(oldy-hs)/40+1].existe==-1&&p[(oldx-ws)/40+3][(oldy-hs)/40+1].existe==-1)
            a=1;
        return a;
        break;
    case PYRAMIDE:
        if(((oldx-ws)/40+1==(x-ws)/40+1&&(oldy-hs)/40-2==(y-hs)/40+1)&&p[(oldx-ws)/40+1][(oldy-hs)/40].existe==-1&&p[(oldx-ws)/40+1][(oldy-hs)/40-1].existe==-1)
            a=1;
        if((((oldx-ws)/40+1==(x-ws)/40+1)&&(oldy-hs)/40+4==(y-hs)/40+1)&&p[(oldx-ws)/40+1][(oldy-hs)/40+2].existe==-1&&p[(oldx-ws)/40+1][(oldy-hs)/40+3].existe==-1)
            a=1;
        if(((oldx-ws)/40-2==(x-ws)/40+1&&(oldy-hs)/40+1==(y-hs)/40+1)&&p[(oldx-ws)/40][(oldy-hs)/40+1].existe==-1&&p[(oldx-ws)/40-1][(oldy-hs)/40+1].existe==-1)
            a=1;
        if((((oldx-ws)/40+4)==(x-ws)/40+1&&(oldy-hs)/40+1==(y-hs)/40+1)&&p[(oldx-ws)/40+2][(oldy-hs)/40+1].existe==-1&&p[(oldx-ws)/40+3][(oldy-hs)/40+1].existe==-1)
            a=1;
        if(((oldx-ws)/40+1==(x-ws)/40+1&&(oldy-hs)/40-1==(y-hs)/40+1)&&p[(oldx-ws)/40+1][(oldy-hs)/40].existe==-1)
            a=1;
        if(((oldx-ws)/40+1==(x-ws)/40+1&&((oldy-hs)/40+3==(y-hs)/40+1))&&p[(oldx-ws)/40+1][(oldy-hs)/40+2].existe==-1)
            a=1;
        if(((oldx-ws)/40+3==(x-ws)/40+1&&(oldy-hs)/40+1==(y-hs)/40+1)&&p[(oldx-ws)/40+2][(oldy-hs)/40+1].existe==-1)
            a=1;
        if(((oldx-ws)/40-1==(x-ws)/40+1&&(oldy-hs)/40+1==(y-hs)/40+1)&&p[(oldx-ws)/40][(oldy-hs)/40+1].existe==-1)
            a=1;
        oldx=(oldx-ws)/40 +1;
        oldy=(oldy-hs)/40 +1;
        x=(x-ws)/40+1;
        y=(y-hs)/40+1;
        if((oldx==x&&oldy-1==y)||(oldx==x&&oldy+1==y)||(oldx-1==x&&oldy==y)||(oldx+1==x&&oldy==y))
            a=1;
        if((oldx-1==x&&oldy-1==y)||(oldx-1==x&&oldy+1==y)||(oldx+1==x&&oldy-1==y)||(oldx+1==x&&oldy+1==y))
            a=1;
        if(((oldx-2==x&&oldy-2==y)&&p[oldx-1][oldy-1].existe==-1)||((oldx-2==x&&oldy+2==y)&&p[oldx-1][oldy+1].existe==-1)||(oldx+2==x&&oldy-2==y&&p[oldx+1][oldy-1].existe==-1)||((oldx+2==x&&oldy+2==y)&&p[oldx+1][oldy+1].existe==-1))
            a=1;
        if(((oldx-3==x&&oldy-3==y)&&p[oldx-1][oldy-1].existe==-1&&p[oldx-2][oldy-2].existe==-1)||((oldx-3==x&&oldy+3==y)&&p[oldx-1][oldy+1].existe==-1&&p[oldx-2][oldy+2].existe==-1)||(oldx+3==x&&oldy-3==y&&p[oldx+1][oldy-1].existe==-1&&p[oldx+2][oldy-2].existe==-1)||((oldx+3==x&&oldy+3==y)&&p[oldx+1][oldy+1].existe==-1&&p[oldx+2][oldy+2].existe==-1))
            a=1;
        return a;
        break;
    }
}

void afficherPosvalide(int x,int y,int forme)
{
    switch(forme)
    {
    case CERCLE:
        if(caseBon(x+1,y+1))
            dessinerPoint(x+1,y+1,p[x][y].image);
        if(caseBon(x-1,y+1))
            dessinerPoint(x-1,y+1,p[x][y].image);
        if(caseBon(x+1,y-1))
            dessinerPoint(x+1,y-1,p[x][y].image);
        if(caseBon(x-1,y-1))
            dessinerPoint(x-1,y-1,p[x][y].image);

        break;

    case TRIANGLE:
        if(is_blocked(x,y,p[x][y].forme,p[x][y].side)!=1)
        {
            if(caseBon(x-1,y-2))
                dessinerPoint(x-1,y-2,p[x][y].image);
            if(caseBon(x+1,y-2))
                dessinerPoint(x+1,y-2,p[x][y].image);
            if(caseBon(x-1,y+2))
                dessinerPoint(x-1,y+2,p[x][y].image);
            if(caseBon(x+1,y+2))
                dessinerPoint(x+1,y+2,p[x][y].image);
            if(caseBon(x+2,y+1))
                dessinerPoint(x+2,y+1,p[x][y].image);
            if(caseBon(x+2,y-1))
                dessinerPoint(x+2,y-1,p[x][y].image);
            if(caseBon(x-2,y+1))
                dessinerPoint(x-2,y+1,p[x][y].image);
            if(caseBon(x-2,y-1))
                dessinerPoint(x-2,y-1,p[x][y].image);
        }
        if(caseBon(x,y+1)&&caseBon(x,y+2))
            dessinerPoint(x,y+2,p[x][y].image);
        if(caseBon(x,y-1)&&caseBon(x,y-2))
            dessinerPoint(x,y-2,p[x][y].image);
        if(caseBon(x+1,y)&&caseBon(x+2,y))
            dessinerPoint(x+2,y,p[x][y].image);
        if(caseBon(x-1,y)&&caseBon(x-2,y))
            dessinerPoint(x-2,y,p[x][y].image);
        break;

    case CARRE:
        if(is_blocked(x,y,p[x][y].forme,p[x][y].side)!=1)
        {
            if(caseBon(x-1,y-3))
                dessinerPoint(x-1,y-3,p[x][y].image);
            if(caseBon(x+1,y-3))
                dessinerPoint(x+1,y-3,p[x][y].image);
            if(caseBon(x-1,y+3))
                dessinerPoint(x-1,y+3,p[x][y].image);
            if(caseBon(x+1,y+3))
                dessinerPoint(x+1,y+3,p[x][y].image);
            if(caseBon(x+3,y+1))
                dessinerPoint(x+3,y+1,p[x][y].image);
            if(caseBon(x+3,y-1))
                dessinerPoint(x+3,y-1,p[x][y].image);
            if(caseBon(x-3,y+1))
                dessinerPoint(x-3,y+1,p[x][y].image);
            if(caseBon(x-3,y-1))
                dessinerPoint(x-3,y-1,p[x][y].image);
        }
        if(caseBon(x,y+1)&&caseBon(x,y+2)&&caseBon(x,y+3))
            dessinerPoint(x,y+3,p[x][y].image);
        if(caseBon(x,y-1)&&caseBon(x,y-2)&&caseBon(x,y-3))
            dessinerPoint(x,y-3,p[x][y].image);
        if(caseBon(x+1,y)&&caseBon(x+2,y)&&caseBon(x+3,y))
            dessinerPoint(x+3,y,p[x][y].image);
        if(caseBon(x-1,y)&&caseBon(x-2,y)&&caseBon(x-3,y))
            dessinerPoint(x-3,y,p[x][y].image);
        break;
    case PYRAMIDE:
        if(caseBon(x+1,y+1))
            dessinerPoint(x+1,y+1,p[x][y].image);
        if(caseBon(x-1,y+1))
            dessinerPoint(x-1,y+1,p[x][y].image);
        if(caseBon(x+1,y-1))
            dessinerPoint(x+1,y-1,p[x][y].image);
        if(caseBon(x-1,y-1))
            dessinerPoint(x-1,y-1,p[x][y].image);
        if(caseBon(x+1,y+1)&&caseBon(x+2,y+2))
            dessinerPoint(x+2,y+2,p[x][y].image);
        if(caseBon(x-1,y+1)&&caseBon(x-2,y+2))
            dessinerPoint(x-2,y+2,p[x][y].image);
        if(caseBon(x+1,y-1)&&caseBon(x+2,y-2))
            dessinerPoint(x+2,y-2,p[x][y].image);
        if(caseBon(x-1,y-1)&&caseBon(x-2,y-2))
            dessinerPoint(x-2,y-2,p[x][y].image);
        if(caseBon(x+1,y+1)&&caseBon(x+2,y+2)&&caseBon(x+3,y+3))
            dessinerPoint(x+3,y+3,p[x][y].image);
        if(caseBon(x-1,y+1)&&caseBon(x-2,y+2)&&caseBon(x-3,y+3))
            dessinerPoint(x-3,y+3,p[x][y].image);
        if(caseBon(x+1,y-1)&&caseBon(x+2,y-2)&&caseBon(x+3,y-3))
            dessinerPoint(x+3,y-3,p[x][y].image);
        if(caseBon(x-1,y-1)&&caseBon(x-2,y-2)&&caseBon(x-3,y-3))
            dessinerPoint(x-3,y-3,p[x][y].image);
        if(caseBon(x,y+1)&&caseBon(x,y+2))
            dessinerPoint(x,y+2,p[x][y].image);
        if(caseBon(x,y-1))
            dessinerPoint(x,y-1,p[x][y].image);
        if(caseBon(x,y+1))
            dessinerPoint(x,y+1,p[x][y].image);
        if(caseBon(x+1,y))
            dessinerPoint(x+1,y,p[x][y].image);
        if(caseBon(x-1,y))
            dessinerPoint(x-1,y,p[x][y].image);

        if(caseBon(x,y-1)&&caseBon(x,y-2))
            dessinerPoint(x,y-2,p[x][y].image);
        if(caseBon(x+1,y)&&caseBon(x+2,y))
            dessinerPoint(x+2,y,p[x][y].image);
        if(caseBon(x-1,y)&&caseBon(x-2,y))
            dessinerPoint(x-2,y,p[x][y].image);
        if(caseBon(x,y+1)&&caseBon(x,y+2)&&caseBon(x,y+3))
            dessinerPoint(x,y+3,p[x][y].image);
        if(caseBon(x,y-1)&&caseBon(x,y-2)&&caseBon(x,y-3))
            dessinerPoint(x,y-3,p[x][y].image);
        if(caseBon(x+1,y)&&caseBon(x+2,y)&&caseBon(x+3,y))
            dessinerPoint(x+3,y,p[x][y].image);
        if(caseBon(x-1,y)&&caseBon(x-2,y)&&caseBon(x-3,y))
            dessinerPoint(x-3,y,p[x][y].image);
        break;
    }
}

void ChangerPosition(int x,int y,int oldx,int oldy,int ws,int hs)
{
    Case a;
    a.existe=p[(x-ws)/40+1][(y-hs)/40+1].existe;
    a.forme=p[(x-ws)/40+1][(y-hs)/40+1].forme;
    a.image= p[(x-ws)/40+1][(y-hs)/40+1].image;
    a.valeur=p[(x-ws)/40+1][(y-hs)/40+1].valeur;
    a.side= p[(x-ws)/40+1][(y-hs)/40+1].side;
    a.py=p[(x-ws)/40+1][(y-hs)/40+1].py;
    p[(x-ws)/40+1][(y-hs)/40+1].existe=p[(oldx-ws)/40+1][(oldy-hs)/40+1].existe;
    p[(x-ws)/40+1][(y-hs)/40+1].forme=p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme;
    p[(x-ws)/40+1][(y-hs)/40+1].image=p[(oldx-ws)/40+1][(oldy-hs)/40+1].image;
    p[(x-ws)/40+1][(y-hs)/40+1].valeur=p[(oldx-ws)/40+1][(oldy-hs)/40+1].valeur;
    p[(x-ws)/40+1][(y-hs)/40+1].side=p[(oldx-ws)/40+1][(oldy-hs)/40+1].side;
    p[(x-ws)/40+1][(y-hs)/40+1].py=p[(oldx-ws)/40+1][(oldy-hs)/40+1].py;

    p[(oldx-ws)/40+1][(oldy-hs)/40+1].existe=-1;
    p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme=0;
    p[(oldx-ws)/40+1][(oldy-hs)/40+1].image=NULL;
    p[(oldx-ws)/40+1][(oldy-hs)/40+1].valeur=0;
    p[(oldx-ws)/40+1][(oldy-hs)/40+1].side=0;
    if(a.side==-1)
    {
        int compteurBlanc=recherchek(-1);
        p[0][compteurBlanc-compteurBlanc/17 * 16 ].existe=a.existe;
        p[0][compteurBlanc-compteurBlanc/17 * 16 ].forme=a.forme;
        p[0][compteurBlanc-compteurBlanc/17 * 16 ].valeur=a.valeur;
        p[0][compteurBlanc-compteurBlanc/17 * 16 ].side=1;
        p[0][compteurBlanc-compteurBlanc/17 * 16 ].py=a.py;

        switch(a.forme)
        {
        case CERCLE:
            p[0][compteurBlanc-compteurBlanc/17 * 16 ].image=dessinerCercle(al_map_rgb(20,20,20),Plein,a.valeur,al_map_rgb(255,168,0));
            break;
        case TRIANGLE:
            p[0][compteurBlanc-compteurBlanc/17 * 16 ].image=dessinerTriangle(al_map_rgb(20,20,20),Plein,a.valeur,al_map_rgb(255,168,0));
            break;
        case CARRE:
            p[0][compteurBlanc-compteurBlanc/17 * 16 ].image=dessinerCarre(al_map_rgb(20,20,20),Plein,a.valeur,al_map_rgb(255,168,0));
            break;
        }
    }
    if(a.side==1)
    {
        int compteurNoir=recherchek(1);
        p[9+compteurNoir/17][compteurNoir-compteurNoir/17 * 16].existe=a.existe;
        p[9+compteurNoir/17][compteurNoir-compteurNoir/17 * 16].forme=a.forme;
        p[9+compteurNoir/17][compteurNoir-compteurNoir/17 * 16].valeur=a.valeur;
        p[9+compteurNoir/17][compteurNoir-compteurNoir/17 * 16].side=-1;
        p[9+compteurNoir/17][compteurNoir-compteurNoir/17 * 16].py=a.py;

        switch(a.forme)
        {
        case CERCLE:
            p[9+compteurNoir/17][compteurNoir-compteurNoir/17*16].image=dessinerCercle(al_map_rgb(255,168,0),Plein,a.valeur,al_map_rgb(20,20,20));
            break;
        case TRIANGLE:
            p[9+compteurNoir/17][compteurNoir-compteurNoir/17*16].image=dessinerTriangle(al_map_rgb(255,168,0),Plein,a.valeur,al_map_rgb(20,20,20));
            break;
        case CARRE:
            p[9+compteurNoir/17][compteurNoir-compteurNoir/17 * 16 ].image=dessinerCarre(al_map_rgb(255,168,0),Plein,a.valeur,al_map_rgb(20,20,20));
            break;
        }
    }

}

void initialiseBoard(void)
{
    int i,j,k=0;
    for(i=0; i<10; i++)
    {
        for(j=1; j<17; j++)
        {
            p[i][j].image=NULL;
            p[i][j].forme=0;
            p[i][j].side=0;
            p[i][j].valeur=0;
            p[i][j].existe=-1;
            p[i][j].py.ETAT=0;
            p[i][j].py.NbPiece=0;
        }
    }
}
coordonne *attacked_piece_list(int mx,int my,int side,int forme,int ws,int hs)
{
    int i,j,r,cosd,sind;
    double jj;

    coordonne attackedPiece[10][3];
    for(i=0; i<10; i++)
    {
        for(j=0; j<3; j++)
        {
            attackedPiece[i][j].x=0;
            attackedPiece[i][j].y=0;
        }
    }
    int k=0,x,t,l,y,pys;
    switch(forme)
    {
    case CERCLE:
        for(t=-1; t<2; t++)
        {
            if(t==0)
                continue;
            for(l=-1; l<2; l++)
            {
                if(l==0)
                    continue;
                x=mx+t;
                y=my+l;

                if(x<9&&x>0&&y<17&&y>0)
                {

                    for(i=x-3; i<x+4; i++)
                    {

                        for(j=y-3; j<y+4; j++)
                        {
                            if(i<9&&i>0&&j<17&&j>0&&((i!=mx||j!=my)&&(i!=x||j!=y))||(i==mx&&j==my&&p[i][j].side==side&&(p[i][j].valeur==p[x][y].valeur&&p[i][j].forme!=p[x][y].forme)))
                            {
                                if(p[x][y].py.ETAT==PYRAMIDE)
                                {
                                    for(pys=1; pys<=p[x][y].py.NbPiece; pys++)
                                    {
                                        if((p[i][j].existe==1&&p[x][y].side!=side&&p[i][j].side==side&&is_ar_match(p[mx][my].valeur,p[i][j].valeur,p[x][y].py.piece[pys].valeur)==1&&verifierGlissement((i-1)*40+ws,(j-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[i][j].forme)==1)||(p[mx][my].side==side&&p[mx][my].valeur==p[x][y].py.piece[pys].valeur&&p[mx][my].forme!=p[x][y].py.piece[pys].forme))
                                        {
                                            p[x][y].valeur-=p[x][y].py.piece[pys].valeur=0;
                                            p[x][y].py.piece[pys].forme=0;
                                            p[x][y].py.piece[pys].image=NULL;
                                            p[x][y].py.piece[pys].valeur=0;
                                            arrangerPym(x,y);
                                            p[x][y].py.NbPiece--;
                                            p[x][y].forme=PYRAMIDE_NON_COMPAC;
                                            p[x][y].valeur=sommeValPy(x,y);
                                                    al_play_sample(son1,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

                                        }
                                    }
                                }
                                else if(p[x][y].existe==1&&p[i][j].existe==1&&p[x][y].side!=side&&p[i][j].side==side&&is_ar_match(p[mx][my].valeur,p[i][j].valeur,p[x][y].valeur)==1)
                                {

                                    if(verifierGlissement((i-1)*40+ws,(j-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[i][j].forme)==1)
                                    {
                                        attackedPiece[k][0].x=x;
                                        attackedPiece[k][0].y=y;
                                        attackedPiece[k][1].x=i;
                                        attackedPiece[k][1].y=j;
                                        attackedPiece[k][2].x=mx;
                                        attackedPiece[k][2].y=my;
                                        k++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    case TRIANGLE:
    {
        for(jj=0; jj<2*M_PI; jj+=M_PI_2)
        {
            cosd=cos(jj)*2;
            sind=sin(jj)*2;
            x=mx+cosd;
            y=my+sind;
            for(t=x-3; t<x+4; t++)
            {
                for(l=y-3; l<y+4; l++)
                {
                    if(verifierGlissement((mx-1)*40+ws,(my-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[mx][my].forme)==1)
                        if(t<9&&t>0&&l<17&&l>0&&((t!=mx||l!=my)&&(t!=x||l!=y)||(t==mx&&l==my&&p[t][l].side==side&&(p[t][l].valeur==p[x][y].valeur&&p[t][l].forme!=p[x][y].forme))))
                        {
                            if(p[x][y].py.ETAT==PYRAMIDE)
                            {
                                for(pys=1; pys<=p[x][y].py.NbPiece; pys++)
                                {
                                    if((p[t][l].existe==1&&p[x][y].side!=side&&p[t][l].side==side&&is_ar_match(p[mx][my].valeur,p[t][l].valeur,p[x][y].py.piece[pys].valeur)&&verifierGlissement((t-1)*40+ws,(l-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[t][l].forme)==1)||(p[mx][my].side==side&&p[mx][my].valeur==p[x][y].py.piece[pys].valeur&&p[mx][my].forme!=p[x][y].py.piece[pys].forme))
                                    {
                                        p[x][y].py.piece[pys].valeur=0;
                                        p[x][y].py.piece[pys].forme=0;
                                        p[x][y].py.piece[pys].image=NULL;
                                        p[x][y].py.piece[pys].valeur=0;
                                        arrangerPym(x,y);
                                        p[x][y].py.NbPiece--;
                                        p[x][y].forme=PYRAMIDE_NON_COMPAC;
                                        p[x][y].valeur=sommeValPy(x,y);
                                                    al_play_sample(son1,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);


                                    }
                                }
                            }

                            else if(p[x][y].existe==1&&p[t][l].existe==1&&p[x][y].side!=side&&p[t][l].side==side&&is_ar_match(p[mx][my].valeur,p[t][l].valeur,p[x][y].valeur)==1)
                            {

                                if(verifierGlissement((t-1)*40+ws,(l-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[t][l].forme)==1)
                                {
                                    if(x>0&&x<9&&y>0&&y<17)
                                    {
                                        attackedPiece[k][0].x=x;
                                        attackedPiece[k][0].y=y;
                                        attackedPiece[k][1].x=t;
                                        attackedPiece[k][1].y=l;
                                        attackedPiece[k][2].x=mx;
                                        attackedPiece[k][2].y=my;
                                        k++;
                                    }
                                }
                            }
                        }
                }
            }
        }
    }
    break;
    case CARRE:
        for(jj=0; jj<2*M_PI; jj+=M_PI_2)
        {
            cosd=cos(jj)*3;
            sind=sin(jj)*3;
            x=mx+cosd;
            y=my+sind;
            for(t=x-3; t<x+4; t++)
            {
                for(l=y-3; l<y+4; l++)
                {
                    if(verifierGlissement((mx-1)*40+ws,(my-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[mx][my].forme)==1)
                        if(t<9&&t>0&&l<17&&l>0&&((t!=mx||l!=my)&&(t!=x||l!=y))||(t==mx&&l==my&&p[t][l].side==side&&p[t][l].valeur==p[x][y].valeur))
                        {
                            if(p[x][y].py.ETAT==PYRAMIDE)
                            {
                                for(pys=1; pys<=p[x][y].py.NbPiece; pys++)
                                {
                                    if((p[t][l].existe==1&&p[x][y].side!=side&&p[t][l].side==side&&is_ar_match(p[mx][my].valeur,p[t][l].valeur,p[x][y].py.piece[pys].valeur)&&verifierGlissement((t-1)*40+ws,(l-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[t][l].forme)==1)||(p[mx][my].side==side&&p[mx][my].valeur==p[x][y].py.piece[pys].valeur&&p[mx][my].forme!=p[x][y].py.piece[pys].forme))
                                    {
                                        p[x][y].py.piece[pys].valeur=0;
                                        p[x][y].py.piece[pys].forme=0;
                                        p[x][y].py.piece[pys].image=NULL;
                                        p[x][y].py.piece[pys].valeur=0;
                                        arrangerPym(x,y);
                                        p[x][y].py.NbPiece--;
                                        p[x][y].forme=PYRAMIDE_NON_COMPAC;
                                        p[x][y].valeur=sommeValPy(x,y);
                                                    al_play_sample(son1,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

                                    }
                                }
                            }
                            else if(p[x][y].existe==1&&p[t][l].existe==1&&p[x][y].side!=side&&p[t][l].side==side&&is_ar_match(p[mx][my].valeur,p[t][l].valeur,p[x][y].valeur)==1)
                            {


                                if(verifierGlissement((t-1)*40+ws,(l-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[t][l].forme)==1)
                                {
                                    if(x>0&&x<9&&y>0&&y<17)
                                    {


                                        attackedPiece[k][0].x=x;
                                        attackedPiece[k][0].y=y;
                                        attackedPiece[k][1].x=t;
                                        attackedPiece[k][1].y=l;
                                        attackedPiece[k][2].x=mx;
                                        attackedPiece[k][2].y=my;
                                        k++;
                                    }
                                }
                            }
                        }
                }
            }
        }

        break;
    case PYRAMIDE:
        for(j=1; j<4; j++)
            for(jj=0; jj<2*M_PI; jj+=M_PI_4)
            {
                if((jj==M_PI_4||jj==3*M_PI_4||jj==5*M_PI_4||jj==7*M_PI_4)&&j<3)
                {
                    cosd=cos(jj)*(j+1);
                    sind=sin(jj)*(j+1);
                }
                else if((jj==M_PI_4||jj==3*M_PI_4||jj==5*M_PI_4||jj==7*M_PI_4)&&j==3)
                {
                    cosd=cos(jj)*(j+2);
                    sind=sin(jj)*(j+2);
                }
                else
                {
                    cosd=cos(jj)*j;
                    sind=sin(jj)*j;
                }
                x=mx+cosd;
                y=my+sind;
                for(t=x-3; t<x+4; t++)
                {
                    for(l=y-3; l<y+4; l++)
                    {
                        if(verifierGlissement((mx-1)*40+ws,(my-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[mx][my].forme)==1)
                            if(t<9&&t>0&&l<17&&l>0&&((t!=mx||l!=my)&&(t!=x||l!=y))||(t==mx&&l==my&&p[t][l].side==side&&p[t][l].valeur==p[x][y].valeur))
                            {
                                if(p[x][y].py.ETAT==PYRAMIDE)
                                {
                                    for(pys=1; pys<=p[x][y].py.NbPiece; pys++)
                                    {
                                        if((p[t][l].existe==1&&p[x][y].side!=side&&p[t][l].side==side&&is_ar_match(p[mx][my].valeur,p[t][l].valeur,p[x][y].py.piece[pys].valeur)&&verifierGlissement((t-1)*40+ws,(l-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[t][l].forme)==1)||(p[mx][my].side==side&&p[mx][my].valeur==p[x][y].py.piece[pys].valeur&&p[mx][my].forme!=p[x][y].py.piece[pys].forme))
                                        {
                                            p[x][y].py.piece[pys].valeur=0;
                                            p[x][y].py.piece[pys].forme=0;
                                            p[x][y].py.piece[pys].image=NULL;
                                            p[x][y].py.piece[pys].valeur=0;
                                            arrangerPym(x,y);
                                            p[x][y].py.NbPiece--;
                                            p[x][y].forme=PYRAMIDE_NON_COMPAC;
                                            p[x][y].valeur=sommeValPy(x,y);
                                    al_play_sample(son1,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

                                        }
                                    }
                                }
                                else if(p[x][y].existe==1&&p[t][l].existe==1&&p[x][y].side!=side&&p[t][l].side==side&&is_ar_match(p[mx][my].valeur,p[t][l].valeur,p[x][y].valeur)==1)
                                {


                                    if(verifierGlissement((t-1)*40+ws,(l-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[t][l].forme)==1)
                                    {
                                        if(x>0&&x<9&&y>0&&y<17)
                                        {
                                            attackedPiece[k][0].x=x;
                                            attackedPiece[k][0].y=y;
                                            attackedPiece[k][1].x=t;
                                            attackedPiece[k][1].y=l;
                                            attackedPiece[k][2].x=mx;
                                            attackedPiece[k][2].y=my;
                                            k++;
                                        }
                                    }
                                }
                            }
                    }
                }

            }
        break;
    }
    attackedPiece[9][2].x=k;
    return attackedPiece;
}

int is_blocked(int x,int y,int forme,int side)
{
    int a=1,i;
    switch(forme)
    {
    case TRIANGLE:
        if((ccb(x,y-1,side)||ccb(x,y-2,side))&&(ccb(x,y+1,side)||ccb(x,y+2,side))&&(ccb(x-1,y,side)||ccb(x-2,y,side))&&(ccb(x+1,y,side)||ccb(x+2,y,side)))
            return 1;
        else
            return 0;
        break;
    case CERCLE:
        if(ccb(x-1,y+1,side)&&ccb(x-1,y-1,side)&&ccb(x+1,y-1,side)&&ccb(x+1,y+1,side))
            return 1;
        else
            return 0;
        break;
    case CARRE:
        if((ccb(x,y-1,side)||ccb(x,y-2,side)||ccb(x,y-3,side))&&(ccb(x,y+1,side)||ccb(x,y+2,side)||ccb(x,y+3,side))&&(ccb(x-1,y,side)||ccb(x-2,y,side)||ccb(x-3,y,side))&&(ccb(x+1,y,side)||ccb(x+2,y,side)||ccb(x+3,y,side)))
            return 1;
        else
            return 0;
        break;
    case PYRAMIDE:
        if(ccb(x,y+1,side)&&ccb(x,y-1,side)&&ccb(x-1,y,side)&&ccb(x+1,y,side)&&ccb(x-1,y+1,side)&&ccb(x-1,y-1,side)&&ccb(x+1,y-1,side)&&ccb(x+1,y+1,side))
            return 1;
        else
            return 0;
        break;
    case PYRAMIDE_NON_COMPAC:
        for(i=1;i<=p[x][y].py.NbPiece;i++){
            if(!is_blocked_2(x,y,p[x][y].py.piece[i].forme,p[x][y].side)){
                a=0;
                break;
            }
        }
        if(a==1)
            return 1;
        else
            return 0;
            break;
    }
}

int contain(int x,int y,coordonne *tab,int a,int b)
{
    int f=0,i,j=0;
    for(i=0; i<10; i++)
    {
        if(a==tab[i*3+j].x&&b==tab[i*3+j].y)
        {
            for(j=0; j<3; j++)
            {
                if(x==tab[i*3+j].x&&y==tab[i*3+j].y)
                    f=1;
            }
        }
    }
    return f;
}
void init_pion(void)
{
    int i;
    //mettre pion///////////////////////////////////////////////////////////////////////////////////
///////////////////////al_map_rgb(255,168,0)//////////////////////////////////
    for(i=3; i<7; i++)
    {
        if(i==3)
            p[i][11].valeur=8;
        else
            p[i][11].valeur=p[i-1][11].valeur-2;
        p[i][11].image=dessinerCercle(al_map_rgb(255,168,0),Plein,p[i][11].valeur,al_map_rgb(20,20,20));
        p[i][11].existe=1;
        p[i][11].forme=CERCLE;
        p[i][11].side=-1;
    }
    for(i=3; i<7; i++)
    {
        p[i][12].valeur=p[i][11].valeur*p[i][11].valeur;
        p[i][12].image=dessinerCercle(al_map_rgb(255,168,0),Plein,p[i][12].valeur,al_map_rgb(20,20,20));
        p[i][12].existe=1;
        p[i][12].forme=CERCLE;
        p[i][12].side=-1;
    }
    int baseT[8]= {9,9,7,7,5,5,3,3};
    //////////////triangle////////////
    int r;
    for(i=1; i<9; i++)
    {
        if(i<5)
            r=1;
        else
            r=0;
        if(i<3||i>6)
        {

            if (i%2==r)
                p[i][12].valeur=baseT[i-1]*baseT[i-1];
            else
                p[i][12].valeur=baseT[i-1]*(baseT[i-1]-1);
            p[i][12].image=dessinerTriangle(al_map_rgb(255,168,0),Plein,p[i][12].valeur,al_map_rgb(20,20,20));
            p[i][12].existe=1;
            p[i][12].forme=TRIANGLE;
            p[i][12].side=-1;
        }
        else
        {
            if (i%2==r)
                p[i][13].valeur=baseT[i-1]*baseT[i-1];
            else
                p[i][13].valeur=baseT[i-1]*(baseT[i-1]-1);
            p[i][13].image=dessinerTriangle(al_map_rgb(255,168,0),Plein,p[i][13].valeur,al_map_rgb(20,20,20));
            p[i][13].existe=1;
            p[i][13].forme=TRIANGLE;
            p[i][13].side=-1;
        }
    }
    ////////////////////////////////////
    int tabc[8]= {17,13,0,0,0,0,9,5};
    for(i=1; i<9; i++)
    {
        if(i<3||i>6)
        {
            p[i][14].valeur=tabc[i-1]*tabc[i-1];
            p[i][14].existe=1;
            p[i][14].forme=CARRE;
            p[i][14].side=-1;
            p[i][14].image=dessinerCarre(al_map_rgb(255,168,0),Plein,p[i][14].valeur,al_map_rgb(20,20,20));
        }
    }
    for(i=1; i<9; i++)
    {
        if((i<3||i>6)&&i!=2)
        {
            if(i==1)
                p[i][13].valeur=153;
            if(i==7)
                p[i][13].valeur=45;
            if(i==8)
                p[i][13].valeur=15;
            p[i][13].existe=1;
            p[i][13].forme=CARRE;
            p[i][13].side=-1;
            p[i][13].image=dessinerCarre(al_map_rgb(255,168,0),Plein,p[i][13].valeur,al_map_rgb(20,20,20));
        }
    }
    /////////////////////////NOIR/////////////////////////////////////
    for(i=3; i<7; i++)
    {
        if(i==3)
            p[i][6].valeur=3;
        else
            p[i][6].valeur=p[i-1][6].valeur+2;
        p[i][6].image=dessinerCercle(al_map_rgb(20,20,20),Plein,p[i][6].valeur,al_map_rgb(255,168,0));
        p[i][6].existe=1;
        p[i][6].forme=CERCLE;
        p[i][6].side=1;
    }
    for(i=3; i<7; i++)
    {
        p[i][5].valeur=p[i][6].valeur*p[i][6].valeur;
        p[i][5].image=dessinerCercle(al_map_rgb(20,20,20),Plein,p[i][5].valeur,al_map_rgb(255,168,0));
        p[i][5].existe=1;
        p[i][5].forme=CERCLE;
        p[i][5].side=1;
    }
    ///////TRIANGLE////////////
    int baseT1[8]= {4,4,6,6,8,8,10,10};
    for(i=1; i<9; i++)
    {
        if(i<5)
            r=1;
        else
            r=0;
        if(i<3||i>6)
        {

            if (i%2==r)
                p[i][5].valeur=baseT1[i-1]*baseT1[i-1];
            else
                p[i][5].valeur=baseT1[i-1]*(baseT1[i-1]-1);
            p[i][5].image=dessinerTriangle(al_map_rgb(20,20,20),Plein,p[i][5].valeur,al_map_rgb(255,168,0));
            p[i][5].existe=1;
            p[i][5].forme=TRIANGLE;
            p[i][5].side=1;
        }
        else
        {
            if (i%2==r)
                p[i][4].valeur=baseT1[i-1]*baseT1[i-1];
            else
                p[i][4].valeur=baseT1[i-1]*(baseT1[i-1]-1);
            p[i][4].image=dessinerTriangle(al_map_rgb(20,20,20),Plein,p[i][4].valeur,al_map_rgb(255,168,0));
            p[i][4].existe=1;
            p[i][4].forme=TRIANGLE;
            p[i][4].side=1;
        }
    }
    ///////CARRE////////////
    int tabcb[8]= {7,11,0,0,0,0,15,19};
    for(i=1; i<9; i++)
    {
        if(i<3||i>6)
        {
            p[i][3].valeur=tabcb[i-1]*tabcb[i-1];
            p[i][3].existe=1;
            p[i][3].forme=CARRE;
            p[i][3].side=1;
            p[i][3].image=dessinerCarre(al_map_rgb(20,20,20),Plein,p[i][3].valeur,al_map_rgb(255,168,0));
        }
    }
    for(i=1; i<9; i++)
    {
        if((i<3||i>6)&&i!=8)
        {
            if(i==1)
                p[i][4].valeur=28;
            if(i==7)
                p[i][4].valeur=120;
            if(i==2)
                p[i][4].valeur=66;
            p[i][4].existe=1;
            p[i][4].forme=CARRE;
            p[i][4].side=1;
            p[i][4].image=dessinerCarre(al_map_rgb(20,20,20),Plein,p[i][4].valeur,al_map_rgb(255,168,0));
        }
    }
    p[8][4].image=dessinerPyramide(al_map_rgb(20,20,20));
    p[8][4].forme=PYRAMIDE;
    p[8][4].side=1;
    p[8][4].existe=1;
    p[8][4].py.NbPiece=5;
    p[8][4].py.ETAT=PYRAMIDE;
    p[8][4].py.piece[1].forme=CERCLE;
    p[8][4].py.piece[1].valeur=16;
    p[8][4].py.piece[1].image=dessinerCercle(al_map_rgb(20,20,20),Plein,16,al_map_rgb(255,168,0));
    p[8][4].py.piece[2].forme=TRIANGLE;
    p[8][4].py.piece[2].valeur=25;
    p[8][4].py.piece[2].image=dessinerTriangle(al_map_rgb(20,20,20),Plein,25,al_map_rgb(255,168,0));
    p[8][4].py.piece[3].forme=TRIANGLE;
    p[8][4].py.piece[3].valeur=36;
    p[8][4].py.piece[3].image=dessinerTriangle(al_map_rgb(20,20,20),Plein,36,al_map_rgb(255,168,0));
    p[8][4].py.piece[4].forme=CARRE;
    p[8][4].py.piece[4].valeur=49;
    p[8][4].py.piece[4].image=dessinerCarre(al_map_rgb(20,20,20),Plein,49,al_map_rgb(255,168,0));
    p[8][4].py.piece[5].forme=CARRE;
    p[8][4].py.piece[5].valeur=64;
    p[8][4].py.piece[5].image=dessinerCarre(al_map_rgb(20,20,20),Plein,64,al_map_rgb(255,168,0));
    p[8][4].valeur=sommeValPy(8,4);

    ///////////////////////////////////////////////////////////////
    p[2][13].image=dessinerPyramide(al_map_rgb(255,168,0));
    p[2][13].forme=PYRAMIDE;
    p[2][13].side=-1;
    p[2][13].existe=1;
    p[2][13].py.ETAT=PYRAMIDE;
    p[2][13].py.NbPiece=6;
    p[2][13].py.piece[1].forme=CERCLE;
    p[2][13].py.piece[1].valeur=1;
    p[2][13].py.piece[1].image=dessinerCercle(al_map_rgb(255,168,0),Plein,1,al_map_rgb(20,20,20));
    p[2][13].py.piece[2].forme=CERCLE;
    p[2][13].py.piece[2].valeur=4;
    p[2][13].py.piece[2].image=dessinerCercle(al_map_rgb(255,168,0),Plein,4,al_map_rgb(20,20,20));
    p[2][13].py.piece[3].forme=TRIANGLE;
    p[2][13].py.piece[3].valeur=9;
    p[2][13].py.piece[3].image=dessinerTriangle(al_map_rgb(255,168,0),Plein,9,al_map_rgb(20,20,20));
    p[2][13].py.piece[4].forme=TRIANGLE;
    p[2][13].py.piece[4].valeur=16;
    p[2][13].py.piece[4].image=dessinerTriangle(al_map_rgb(255,168,0),Plein,16,al_map_rgb(20,20,20));
    p[2][13].py.piece[5].forme=CARRE;
    p[2][13].py.piece[5].valeur=25;
    p[2][13].py.piece[5].image=dessinerCarre(al_map_rgb(255,168,0),Plein,25,al_map_rgb(20,20,20));
    p[2][13].py.piece[6].forme=CARRE;
    p[2][13].py.piece[6].valeur=36;
    p[2][13].py.piece[6].image=dessinerCarre(al_map_rgb(255,168,0),Plein,36,al_map_rgb(20,20,20));
    p[2][13].valeur=sommeValPy(2,13);


    /////////////////////////////////////////////////////////////////////////////////////////////////

}
bool click_is_out(int x,int y)
{
    ALLEGRO_DISPLAY *d=al_get_current_display();
    const int ws=(al_get_display_width(d)-320)/2;
    if((x>ws+320&&x<ws+520)||x<ws-40)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int verifierGlissement(int oldx,int oldy,int x,int y,int forme)
{
    ALLEGRO_DISPLAY *d=al_get_current_display();
    const int ws=(al_get_display_width(d)-320)/2;
    const int hs=(al_get_display_height(d)-640)/2;
    int a=0;
    switch(forme)
    {
    case CARRE:
        if(((oldx-ws)/40+1==(x-ws)/40+1&&(oldy-hs)/40-2==(y-hs)/40+1)&&p[(oldx-ws)/40+1][(oldy-hs)/40].existe==-1&&p[(oldx-ws)/40+1][(oldy-hs)/40-1].existe==-1)
            a=1;
        if((((oldx-ws)/40+1==(x-ws)/40+1)&&(oldy-hs)/40+4==(y-hs)/40+1)&&p[(oldx-ws)/40+1][(oldy-hs)/40+2].existe==-1&&p[(oldx-ws)/40+1][(oldy-hs)/40+3].existe==-1)
            a=1;
        if(((oldx-ws)/40-2==(x-ws)/40+1&&(oldy-hs)/40+1==(y-hs)/40+1)&&p[(oldx-ws)/40][(oldy-hs)/40+1].existe==-1&&p[(oldx-ws)/40-1][(oldy-hs)/40+1].existe==-1)
            a=1;
        if((((oldx-ws)/40+4)==(x-ws)/40+1&&(oldy-hs)/40+1==(y-hs)/40+1)&&p[(oldx-ws)/40+2][(oldy-hs)/40+1].existe==-1&&p[(oldx-ws)/40+3][(oldy-hs)/40+1].existe==-1)
            a=1;
        break;

    case TRIANGLE:
        if(((oldx-ws)/40+1==(x-ws)/40+1&&(oldy-hs)/40-1==(y-hs)/40+1)&&p[(oldx-ws)/40+1][(oldy-hs)/40].existe==-1)
            a=1;
        if(((oldx-ws)/40+1==(x-ws)/40+1&&((oldy-hs)/40+3==(y-hs)/40+1))&&p[(oldx-ws)/40+1][(oldy-hs)/40+2].existe==-1)
            a=1;
        if(((oldx-ws)/40+3==(x-ws)/40+1&&(oldy-hs)/40+1==(y-hs)/40+1)&&p[(oldx-ws)/40+2][(oldy-hs)/40+1].existe==-1)
            a=1;
        if(((oldx-ws)/40-1==(x-ws)/40+1&&(oldy-hs)/40+1==(y-hs)/40+1)&&p[(oldx-ws)/40][(oldy-hs)/40+1].existe==-1)
            a=1;
        break;
    case CERCLE:
        if(verifierDeplacement(oldx,oldy,x,y,CERCLE,ws,hs)==1)
            a=1;
        break;
    case PYRAMIDE:
        if(verifierDeplacement(oldx,oldy,x,y,PYRAMIDE,ws,hs)==1)
            a=1;
        break;
    }
    return a;
}
bool ccb(int x,int y,int side)
{
    if((x<1||x>8||y<1||y>16)||(p[x][y].side!=side&&p[x][y].existe==1))
        return true;
    else
        return false;
}
bool is_in_blocked_piece_list(int x,int y,int bx,int by)
{
    switch(p[bx][by].forme)
    {
    case CERCLE:
        if((x==bx+1&&y==by+1)||(x==bx-1&&y==by+1)||(x==bx-1&&y==by-1)||(x==bx+1&&y==by-1))
            return true;
        else
            return false;
        break;
    case TRIANGLE:
        if((x==bx-1&&y==by)||(x==bx-2&&y==by)||(x==bx+1&&y==by)||(x==bx+2&&by==y)||(x==bx&&by-2==y)||(x==bx&&by-1==y)||(x==bx&&by+1==y)||(x==bx&&by+2==y))
            return true;
        else
            return false;
        break;
    case CARRE:
        if((x==bx-1&&y==by)||(x==bx-2&&y==by)||(x==bx-3&&y==by)||(x==bx+1&&y==by)||(x==bx+2&&by==y)||(x==bx+3&&by==y)||(x==bx&&by-2==y)||(x==bx&&y==by-3)||(x==bx&&by-1==y)||(x==bx&&by+1==y)||(x==bx&&by+2==y)||(x==bx&&by+3==y))
            return true;
        else
            return false;
        break;
    case PYRAMIDE:
        if((x==bx+1&&y==by+1)||(x==bx-1&&y==by+1)||(x==bx-1&&y==by-1)||(x==bx+1&&y==by-1)||(x==bx&&y==by+1)||(x==bx&&y==by-1)||(x==bx+1&&by==y)||(x==bx-1&&by==y))
            return true;
        else
            return false;
        break;
    }
}
int recherchek(int side)
{
    int k=1;
    if(side==1)
    {
        while(p[k/17+9][k-k/17 * 16 ].existe!=-1)
        {
            k++;
        }
    }
    if(side==-1)
    {
        while(p[k/17][k-k/17 * 16 ].existe!=-1)
        {
            k++;
        }

    }
    return k;
}
int sommeValPy(int x,int y)
{
    int i,s=0;
    for(i=1; i<=p[x][y].py.NbPiece; i++)
    {
        if(p[x][y].py.piece[i].valeur!=0)
            s+=p[x][y].py.piece[i].valeur;
    }
    return s;
}
void afficherPiecePyramide(int x,int y)
{
    int i;
    ALLEGRO_DISPLAY *d=al_get_current_display();
    const int ws=(al_get_display_width(d)-320)/2;
    int t=1;
    const int hs=(al_get_display_height(d)-640)/2;
    for(i=1; i<=p[x][y].py.NbPiece; i++)
    {
        if(x<=4)
        {
            if(p[x][y].py.piece[i].image!=NULL)
            {
                al_draw_filled_rectangle((x-1)*40+40*(t-1)+ws,(y-1)*40+hs,(x-1)*40+40*(t-1)+40+ws,(y-1)*40+hs+40,al_map_rgb(255,34,34));
                al_draw_bitmap(p[x][y].py.piece[i].image,ws+(x-1)*40+40*(t-1),(y-1)*40+hs,0);
                al_flip_display();
                t++;
                al_rest(0.03);
            }
        }
    }

    if(x>4)
    {
        for(i=1; i<=p[x][y].py.NbPiece; i++)
        {
            if(p[x][y].py.piece[i].image!=NULL)
            {
                al_draw_filled_rectangle((x)*40-40*(t-1)+ws,(y-1)*40+hs,(x)*40-40*(t-1)-40+ws,(y-1)*40+hs+40,ROUGE);
                al_draw_bitmap(p[x][y].py.piece[i].image,ws+(x-1)*40-40*(t-1),(y-1)*40+hs,0);
                t++;
                al_flip_display();
                al_rest(0.03);
            }
        }
    }
}
void arrangerPym(int x,int y)
{
    int ps=1,i=1;
    while(p[x][y].py.piece[i].image!=NULL)
    {
        ps++;
        i++;
    }
    for(i=ps; i<p[x][y].py.NbPiece; i++)
    {
        p[x][y].py.piece[i]=p[x][y].py.piece[i+1];
    }
    p[x][y].py.piece[i+1].image=0;
    p[x][y].py.piece[i+1].valeur=0;
}

bool caseBon(int x,int y)
{
    if(x<1||x>8||y<1||y>16||p[x][y].existe!=-1)
        return false;
    else
        return true;
}
void dessinerPoint(int x,int y,ALLEGRO_BITMAP *image)
{
    const int ws=(al_get_display_width(al_get_current_display())-320)/2;
    const int hs=(al_get_display_height(al_get_current_display())-640)/2;
    al_draw_filled_rectangle((x-1)*40+ws+2,(y-1)*40+hs+2,(x-1)*40+ws+38,(y-1)*40+hs+38,al_map_rgb(226,195,142));
    ALLEGRO_COLOR tint=al_map_rgba_f(0.5, 0.5, 0.5, 0.5);
al_draw_tinted_bitmap(image, tint, (x-1)*40+ws, (y-1)*40+hs, 0);
        al_rest(0.02);
    al_flip_display();
}
int is_pym_not_found()
{
    int i,j,a=-1;
    for(i=1; i<9; i++)
    {
        for(j=1; j<17; j++)
        {
            if(p[i][j].py.ETAT==PYRAMIDE&&p[i][j].side==-1&&p[i][j].py.NbPiece!=0)
                a=0;
        }

    }
    if(a==-1)
        return a;
    a=1;
    for(i=1; i<9; i++)
    {
        for(j=1; j<17; j++)
        {
            if(p[i][j].py.ETAT==PYRAMIDE&&p[i][j].side==1&&p[i][j].py.NbPiece!=0)
                a=0;
        }

    }
    if(a==1)
        return a;

     return 0;
}

void saveGame()
{
    int i,j,t;
    ALLEGRO_FILECHOOSER *repertoire;
    repertoire=al_create_native_file_dialog(NULL,"Enregistrer une partie",0,0);
    al_show_native_file_dialog(al_get_current_display(),repertoire);
    FILE *fichier=NULL;
    fichier=fopen(al_get_native_file_dialog_path(repertoire,0),"w");
    if(fichier!=NULL)
    {
        for(i=0; i<11; i++)
        {
            for(j=0; j<17; j++)
            {
                fprintf(fichier,"%d %d %d %d %d %d ",p[i][j].valeur,p[i][j].existe,p[i][j].forme,p[i][j].side,
                        p[i][j].py.NbPiece,p[i][j].py.ETAT);
                if(p[i][j].py.ETAT==PYRAMIDE)
                {
                    for(t=1; t<=p[i][j].py.NbPiece; t++)
                    {
                        fprintf(fichier,"%d %d ",p[i][j].py.piece[t].forme,p[i][j].py.piece[t].valeur);
                    }

                }
                fprintf(fichier,"\n");

            }

        }
        fclose(fichier);
        al_destroy_native_file_dialog(repertoire);
    }
    else
    {
        printf("erreur lors de la sauvegarde veuillez reesayer");
    }
}
void loadGame()
{
    int i,j,t;
    ALLEGRO_FILECHOOSER *repertoire;
    repertoire=al_create_native_file_dialog(NULL,"Charger une partie",0,0);
    al_show_native_file_dialog(al_get_current_display(),repertoire);
    if(al_get_native_file_dialog_path(repertoire,0)!=NULL)
    {
        FILE *fichier=NULL;
        fichier=fopen(al_get_native_file_dialog_path(repertoire,0),"r");
        if(fichier!=NULL)
        {
            for(i=0; i<11; i++)
            {
                for(j=0; j<17; j++)
                {
                    fscanf(fichier,"%d %d %d %d %d %d",&p[i][j].valeur,&p[i][j].existe,&p[i][j].forme,&p[i][j].side,&p[i][j].py.NbPiece,&p[i][j].py.ETAT);

                    if(p[i][j].py.ETAT!=PYRAMIDE)
                    {
                        switch(p[i][j].forme)
                        {
                        case TRIANGLE:
                            if(p[i][j].side==-1)
                                p[i][j].image=dessinerTriangle(BLANC,Plein,p[i][j].valeur,al_map_rgb(20,20,20));
                            else if(p[i][j].side==1)
                                p[i][j].image=dessinerTriangle(al_map_rgb(20,20,20),Plein,p[i][j].valeur,BLANC);
                            break;
                        case CERCLE:
                            if(p[i][j].side==-1)
                                p[i][j].image=dessinerCercle(BLANC,Plein,p[i][j].valeur,al_map_rgb(20,20,20));
                            else if(p[i][j].side==1)
                                p[i][j].image=dessinerCercle(al_map_rgb(20,20,20),Plein,p[i][j].valeur,BLANC);
                            break;
                        case CARRE:
                            if(p[i][j].side==-1)
                                p[i][j].image=dessinerCarre(BLANC,Plein,p[i][j].valeur,al_map_rgb(20,20,20));
                            else if(p[i][j].side==1)
                                p[i][j].image=dessinerCarre(al_map_rgb(20,20,20),Plein,p[i][j].valeur,BLANC);
                            break;
                        }
                    }
                    if(p[i][j].py.ETAT==PYRAMIDE)
                    {
                        if(p[i][j].side==-1)
                            p[i][j].image=dessinerPyramide(BLANC);
                        else if(p[i][j].side==1)
                            p[i][j].image=dessinerPyramide(al_map_rgb(20,20,20));
                        for(t=1; t<=p[i][j].py.NbPiece; t++)
                        {
                            fscanf(fichier,"%d %d ",&p[i][j].py.piece[t].forme, &p[i][j].py.piece[t].valeur);
                            switch(p[i][j].py.piece[t].forme)
                            {
                            case TRIANGLE:
                                if(p[i][j].side==-1)
                                    p[i][j].py.piece[t].image=dessinerTriangle(BLANC,Plein,p[i][j].py.piece[t].valeur,al_map_rgb(20,20,20));
                                else if(p[i][j].side==1)
                                    p[i][j].py.piece[t].image=dessinerTriangle(al_map_rgb(20,20,20),Plein,p[i][j].py.piece[t].valeur,BLANC);
                                break;
                            case CERCLE:
                                if(p[i][j].side==-1)
                                    p[i][j].py.piece[t].image=dessinerCercle(BLANC,Plein,p[i][j].py.piece[t].valeur,al_map_rgb(20,20,20));
                                else if(p[i][j].side==1)
                                    p[i][j].py.piece[t].image=dessinerCercle(al_map_rgb(20,20,20),Plein,p[i][j].py.piece[t].valeur,BLANC);
                                break;
                            case CARRE:
                                if(p[i][j].side==-1)
                                    p[i][j].py.piece[t].image=dessinerCarre(BLANC,Plein,p[i][j].py.piece[t].valeur,al_map_rgb(20,20,20));
                                else if(p[i][j].side==1)
                                    p[i][j].py.piece[t].image=dessinerCarre(al_map_rgb(20,20,20),Plein,p[i][j].py.piece[t].valeur,BLANC);
                                break;
                            }
                        }

                    }
                }
            }
            fclose(fichier);
            al_destroy_native_file_dialog(repertoire);
        }
        else
        {
            printf("Erreur lors du chargement de partie ");
        }
    }
}
bool mange_is_over(coordonne A[][3])
{
    int i,a,b=0;
    for(i=0; i<8; i++){
        a=0;
        if(A[i][0].x!=0&&A[i][0].y!=0)
            a++;
        if(A[i][1].x!=0&&A[i][1].y!=0)
            a++;
        if(A[i][2].x!=0&&A[i][2].y!=0)
            a++;
        if(a>=2)
        {
              b=1;
            break;
        }
    }
    if(b==1)
        return false;
    else
        return true;
}
void animation_deplacement(float x1,float y1,float x2,float y2,ALLEGRO_BITMAP *images)
{
    int t;
    int bx1=x1;
    int by1=y1;
    const int w=al_get_display_width(al_get_current_display());
    const int h=al_get_display_height(al_get_current_display());
    const int ws=(w-320)/2;
    const int hs=(h-640)/2;
    for(t=x1; t<=x2; t+=3)
    {
        al_draw_bitmap(p[(bx1-ws)/40+1][(by1-hs)/40+1].image,t,((y1-y2)/(x1-x2)) * t + y1-((y1-y2)/(x1-x2)) *x1,0);
        al_flip_display();
        afficherBoard(ws,hs,images);
    }
}
bool is_blocked_2(int x,int y, int forme,int side)
{
    switch(forme)
    {
    case TRIANGLE:
        if((ccb(x,y-1,side)||ccb(x,y-2,side))&&(ccb(x,y+1,side)||ccb(x,y+2,side))&&(ccb(x-1,y,side)||ccb(x-2,y,side))&&(ccb(x+1,y,side)||ccb(x+2,y,side)))
            return true;
        else
            return false;
        break;
    case CERCLE:
        if(ccb(x-1,y+1,side)&&ccb(x-1,y-1,side)&&ccb(x+1,y-1,side)&&ccb(x+1,y+1,side))
            return true;
        else
            return false;
        break;
    case CARRE:
        if((ccb(x,y-1,side)||ccb(x,y-2,side)||ccb(x,y-3,side))&&(ccb(x,y+1,side)||ccb(x,y+2,side)||ccb(x,y+3,side))&&(ccb(x-1,y,side)||ccb(x-2,y,side)||ccb(x-3,y,side))&&(ccb(x+1,y,side)||ccb(x+2,y,side)||ccb(x+3,y,side)))
            return true;
        else
            return false;
        break;
    }
}
void jouer_intermediaire()
{
    int w=al_get_display_width(al_get_current_display()),i;
    int h=al_get_display_height(al_get_current_display());
    ALLEGRO_BITMAP *bg=al_load_bitmap("back.jpg");
    al_draw_bitmap(bg,w/2 -280,h/2-100,0);
    al_flip_display();
    ALLEGRO_BITMAP *iap,*ia,*charger,*chargerp,*reseau,*reseaup,*dp,*dpp,*conti,*contip;
    ia=al_create_bitmap(90,50);
    iap=al_create_bitmap(90,50);
    charger=al_create_bitmap(180,50);
    chargerp=al_create_bitmap(180,50);
    reseau=al_create_bitmap(180,50);
    reseaup=al_create_bitmap(180,50);
    dp=al_create_bitmap(200,50);
    dpp=al_create_bitmap(200,50);
    conti=al_create_bitmap(150,50);
    contip=al_create_bitmap(150,50);
    al_set_target_bitmap(ia);
    ALLEGRO_FONT *font;
    font=al_load_font("DIOGENES.ttf",40,0);
       al_draw_text(font,al_map_rgb(20,20,20),45,0,ALLEGRO_ALIGN_CENTER,"IA");
   al_set_target_bitmap(iap);
      al_draw_text(font,al_map_rgb(255,135,0),45,0,ALLEGRO_ALIGN_CENTER,"IA");
      al_set_target_bitmap(charger);
             al_draw_text(font,al_map_rgb(20,20,20),90,0,ALLEGRO_ALIGN_CENTER,"Charger");
             al_set_target_bitmap(chargerp);
    al_draw_text(font,al_map_rgb(255,135,0),90,0,ALLEGRO_ALIGN_CENTER,"Charger");
    al_set_target_bitmap(reseau);
        al_draw_text(font,al_map_rgb(20,20,20),90,0,ALLEGRO_ALIGN_CENTER,"Reseau");
        al_set_target_bitmap(reseaup);
                al_draw_text(font,al_map_rgb(255,135,0),90,0,ALLEGRO_ALIGN_CENTER,"Reseau");
          al_set_target_bitmap(dp);
       al_draw_text(font,al_map_rgb(20,20,20),100,0,ALLEGRO_ALIGN_CENTER,"Nouveau");
   al_set_target_bitmap(dpp);
      al_draw_text(font,al_map_rgb(255,135,0),100,0,ALLEGRO_ALIGN_CENTER,"Nouveau");
      if(is_pym_not_found()==0)
      {
           al_set_target_bitmap(conti);
       al_draw_text(font,al_map_rgb(20,20,20),75,0,ALLEGRO_ALIGN_CENTER,"Continuer");
   al_set_target_bitmap(contip);
      al_draw_text(font,al_map_rgb(255,135,0),75,0,ALLEGRO_ALIGN_CENTER,"Continuer");
      }
      al_set_target_backbuffer(al_get_current_display());
Creer_Bouton(ia,iap,w/2-250,h/2,JOUERIA);
Afficher_Bouton(boutonJeu[1]);
Creer_Bouton(dp,dpp,w/2-100,h/2-100,JOUER);
Afficher_Bouton(boutonJeu[2]);
Creer_Bouton(reseau,reseaup,w/2-100,h/2+90,JOUERRESEAU);
Afficher_Bouton(boutonJeu[3]);
Creer_Bouton(charger,chargerp,w/2+100,h/2,LOAD);
Afficher_Bouton(boutonJeu[4]);
if(is_pym_not_found()==0)
{
    Creer_Bouton(conti,contip,w/2-80,h/2,CONTINUERPARTIE);
    Afficher_Bouton(boutonJeu[5]);
}
ALLEGRO_EVENT_QUEUE *e;
    e=al_create_event_queue();
    al_register_event_source(e,al_get_mouse_event_source());
    int quit=1;
    while (quit!=0)
    {
if(quit!=0)
{
        ALLEGRO_EVENT ev= {0};
        al_wait_for_event(e,&ev);
        switch(ev.type)
        {


        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
             Gerer_Bouton(ev.mouse.x,ev.mouse.y,PRESSED);
            if(ev.mouse.x<w/2 -280||ev.mouse.x>w/2-280+al_get_bitmap_width(bg)||ev.mouse.y<h/2-100||ev.mouse.y>h/2-100+al_get_bitmap_height(bg))
            {
                for(i=0;i<6;i++)
                    detuire_bouton(boutonJeu[i]);
                MenuPrincipal(al_get_current_display(),1);
            }
            else
        Gerer_Bouton(ev.mouse.x,ev.mouse.y,PRESSED);

            break;
              case ALLEGRO_EVENT_MOUSE_AXES:
                                               Gerer_Bouton(ev.mouse.x,ev.mouse.y,PASSED);

                   break;
        }
}
    }





}
void fin_de_partie()
{
    int w=al_get_display_width(al_get_current_display()),i;
    int h=al_get_display_height(al_get_current_display());
ALLEGRO_COLOR tint;
//tint=al_map_rgb_f(0.1,0.1,0.1,0.9);
    ALLEGRO_FONT *font;
    font=al_load_font("DIOGENES.ttf",30,0);
 ALLEGRO_FONT *font1;
    font1=al_load_font("Flame.ttf",40,0);
    ALLEGRO_BITMAP *fd=al_load_bitmap("back.jpg");
    al_draw_bitmap(fd,w/2 -280,h/2-100,0);
    al_flip_display();
    ALLEGRO_BITMAP *recommencer;
    ALLEGRO_BITMAP *recommencerp=al_create_bitmap(200,50);
    recommencer=al_create_bitmap(200,50);
    al_set_target_bitmap(recommencer);
    al_draw_text(font,al_map_rgb(20,20,20),100,0,ALLEGRO_ALIGN_CENTER,"Recommencer");
    al_set_target_bitmap(recommencerp);
    al_draw_text(font,al_map_rgb(255,135,0),100,0,ALLEGRO_ALIGN_CENTER,"Recommencer");
    ALLEGRO_BITMAP *menu=al_create_bitmap(100,50);
    ALLEGRO_BITMAP *menup=al_create_bitmap(100,50);
    al_set_target_bitmap(menu);
    al_draw_text(font,al_map_rgb(20,20,20),50,0,ALLEGRO_ALIGN_CENTER,"Menu");
    al_set_target_bitmap(menup);
    al_draw_text(font,al_map_rgb(255,135,0),50,0,ALLEGRO_ALIGN_CENTER,"Menu");
    al_set_target_backbuffer(al_get_current_display());
    Creer_Bouton(recommencer,recommencerp,w/2,h/2+100,JOUER);

    if(is_pym_not_found()==-1)
        al_draw_text(font1,al_map_rgb(25,13,20),w/2,h/2,ALLEGRO_ALIGN_CENTER,"Les Noirs Gagnent :)");
        if(is_pym_not_found()==1)
               al_draw_text(font1,al_map_rgb(25,13,20),w/2,h/2,ALLEGRO_ALIGN_CENTER,"Les Blancs Gagnent :)");
        Creer_Bouton(menu,menup,w/2-200,h/2+100,RETOURMENU);
Afficher_Bouton(boutonJeu[1]);
Afficher_Bouton(boutonJeu[2]);
    ALLEGRO_EVENT_QUEUE *e;
    e=al_create_event_queue();
    al_register_event_source(e,al_get_mouse_event_source());
    int quit=1;
       while (quit!=0)
    {
if(quit!=0)
{
        ALLEGRO_EVENT ev= {0};
        al_wait_for_event(e,&ev);
        switch(ev.type)
        {
        case ALLEGRO_EVENT_MOUSE_AXES:
Gerer_Bouton(ev.mouse.x,ev.mouse.y,PASSED);
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        Gerer_Bouton(ev.mouse.x,ev.mouse.y,PRESSED);
                   break;
        }
}
    }

}
void aide()
{
       int w=al_get_display_width(al_get_current_display());
    int h=al_get_display_height(al_get_current_display());
    ALLEGRO_BITMAP *fond,*parchemin;
    fond=al_load_bitmap("back.bmp");
    parchemin=al_load_bitmap("aide.png");
    al_draw_bitmap(fond,0,0,0);
    al_draw_bitmap(parchemin,w/2-300,0,0);
    al_flip_display();
        ALLEGRO_EVENT_QUEUE *e;
    e=al_create_event_queue();
    al_install_keyboard();
    al_register_event_source(e,al_get_keyboard_event_source());
    int quit=1,i;
       while (quit!=0)
    {
        ALLEGRO_EVENT ev= {0};
        al_wait_for_event(e,&ev);
        switch(ev.type)
        {
      case ALLEGRO_EVENT_KEY_DOWN:
                if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
                {
                  for(i=1;i<=6;i++)
                detuire_bouton(boutonJeu[i]);
                    MenuPrincipal(al_get_current_display(),AP);
                    quit=0;
                }
                break;
        }

    }


}
