#include "MODULE_IA.h"

bool in_board(int x,int y)
{
    if(x>0&&x<9&&y>0&&y<17)
        return true;
    else
        return false;
}
coordonne select_piece(int side)
{
    int oldx=0,oldy=0;
    coordonne cs= {0};
    while(p[oldx][oldy].existe!=1||p[oldx][oldy].side!=side||!in_board(oldx,oldy))
    {
        oldx=rand()%9;
        oldy=rand()%17;
    }
    printf("FOUND %d %d\n",oldx,oldy);
    cs.x=oldx;
    cs.y=oldy;
    return cs;
}
coordonne Coup_IA(const int oldx,const int oldy)
{
    int x,y,found_it=0,j=0,cosd,sind;
    double jj;
    const int ws=(al_get_display_width(al_get_current_display())-320)/2;
    const int hs=(al_get_display_height(al_get_current_display())-640)/2;
    coordonne cs;

    switch(p[oldx][oldy].forme)
    {
    case CERCLE:
        if(p[oldx-1][oldy+1].existe!=1&&in_board(oldx-1,oldy+1)&&in_board(oldx-1,oldy+1))
        {
            cs.x=oldx-1;
            cs.y=oldy+1;
            found_it=1;
        }
        if(p[oldx-1][oldy-1].existe!=1&&in_board(oldx-1,oldy-1)&&in_board(oldx-1,oldy-1))
        {
            cs.x=oldx-1;
            cs.y=oldy-1;
            found_it=1;
        }
        if(p[oldx+1][oldy-1].existe!=1&&in_board(oldx+1,oldy-1)&&in_board(oldx+1,oldy-1))
        {
            cs.x=oldx+1;
            cs.y=oldy-1;
            found_it=1;
        }
        if(p[oldx+1][oldy+1].existe!=1&&in_board(oldx+1,oldy+1)&&in_board(oldx+1,oldy+1))
        {
            cs.x=oldx+1;
            cs.y=oldy+1;
            found_it=1;
        }
        break;
    case TRIANGLE:
               for(jj=0; jj<2*M_PI; jj+=M_PI_2)
        {
            cosd=cos(jj)*2;
            sind=sin(jj)*2;
            x=oldx+cosd;
            y=oldy+sind;
            if(p[x][y].existe!=1&&in_board(x,y)&&verifierDeplacement((oldx-1)*40+ws,(oldy-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[oldx][oldy].forme,ws,hs)==1)
            {
                cs.x=x;
                cs.y=y;
                found_it=1;
            }

        }
        if(p[oldx-1][oldy-2].existe!=1&&in_board(oldx-1,oldy-2))
        {

            cs.x=oldx-1;
            cs.y=oldy-2;
            found_it=1;
        }
        if(p[oldx+1][oldy-2].existe!=1&&in_board(oldx+1,oldy-2))
        {
            cs.x=oldx+1;
            cs.y=oldy-2;
            found_it=1;
        }
           if(p[oldx-1][oldy+2].existe!=1&&in_board(oldx-1,oldy+2))
        {
            cs.x=oldx-1;
            cs.y=oldy+2;
            found_it=1;
        }
           if(p[oldx+1][oldy+2].existe!=1&&in_board(oldx+1,oldy+2))
        {
            cs.x=oldx+1;
            cs.y=oldy+2;
            found_it=1;
        }

        break;
    case CARRE:
        for(jj=0; jj<2*M_PI; jj+=M_PI_2)
        {
            cosd=cos(jj)*3;
            sind=sin(jj)*3;
            x=oldx+cosd;
            y=oldy+sind;
            if(p[x][y].existe!=1&&in_board(x,y)&&verifierDeplacement((oldx-1)*40+ws,(oldy-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,p[oldx][oldy].forme,ws,hs)==1)
            {
                cs.x=x;
                cs.y=y;
                found_it=1;

            }

        }
                if(p[oldx-1][oldy-3].existe!=1&&in_board(oldx-1,oldy-3))
        {

            cs.x=oldx-1;
            cs.y=oldy-3;
            found_it=1;
        }
        if(p[oldx+1][oldy-3].existe!=1&&in_board(oldx+1,oldy-3))
        {
            cs.x=oldx+1;
            cs.y=oldy-3;
            found_it=1;
        }
           if(p[oldx-1][oldy+3].existe!=1&&in_board(oldx-1,oldy+3))
        {
            cs.x=oldx-1;
            cs.y=oldy+3;
            found_it=1;
        }
           if(p[oldx+1][oldy+3].existe!=1&&in_board(oldx+1,oldy+3))
        {
            cs.x=oldx+1;
            cs.y=oldy+3;
            found_it=1;
        }
        break;
    case PYRAMIDE:
        for(j=1; j<4; j++)
        {
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
                x=oldx+cosd;
                y=oldy+sind;
                if(p[x][y].existe!=1&&in_board(x,y)&&verifierDeplacement((oldx-1)*40+ws,(oldy-1)*40+hs,(x-1)*40+ws,(y-1)*40+hs,PYRAMIDE,ws,hs)==1)
                {
                    cs.x=x;
                    cs.y=y;
                    found_it=1;

                }
                printf("%f",jj);
            }


        }
        break;
    }



    if(found_it==1)
    {
        moveok=1;
        printf(" IA %d %d\n",cs.x,cs.y);
        return cs;
    }
}
void jouer_IA(ALLEGRO_DISPLAY *display)
{
    int compteurJeu=0;
    moveok=0;
    int joueur[2]= {-1,1};
    int i,j,Mange=0,pym=0,selec=0;

    initialiseBoard();

    char loading[]="Load...";

    int oldx=0,oldy=0,move=0;
    ALLEGRO_EVENT_QUEUE *e;
    al_init_font_addon();

    if(!al_init_ttf_addon())
        erreur("init font");
    ALLEGRO_FONT *police;

    police=al_load_font("pythia.ttf",60,0);
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
    char nom[44];
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

    al_draw_bitmap(back,0,0,0);
    init_pion();
    afficherBoard(ws,hs,image);

    al_flip_display();
    al_install_mouse();
    al_install_keyboard();
    e=al_create_event_queue();
    al_register_event_source(e,al_get_mouse_event_source());
    al_register_event_source(e,al_get_display_event_source(display));
    al_register_event_source(e,al_get_keyboard_event_source());
    while(move!=4)
    {
        if(compteurJeu%2==1&&Mange==0)
        {
            coordonne mouvement_Avant,mouvement_Apres;
            while(moveok!=1)
            {
                mouvement_Avant=select_piece(1);
                al_draw_rectangle((mouvement_Avant.x-1)*40+ws,(mouvement_Avant.y-1)*40+hs,(mouvement_Avant.x-1)*40+ws+40,(mouvement_Avant.y-1)*40+hs+40,al_map_rgb(243,248,63),2);
                al_flip_display();
                al_rest(0.3);
                mouvement_Apres=Coup_IA(mouvement_Avant.x,mouvement_Avant.y);
            }
            animation_deplacement((mouvement_Avant.x-1)*40+ws,(mouvement_Avant.y-1)*40+hs,(mouvement_Apres.x-1)*40+ws,(mouvement_Apres.y-1)*40+hs,image);

            ChangerPosition((mouvement_Apres.x-1)*40+ws,(mouvement_Apres.y-1)*40+hs,(mouvement_Avant.x-1)*40+ws,(mouvement_Avant.y-1)*40+hs,ws,hs);
            moveok=0;

            compteurJeu++;
            al_rest(0.3);
            afficherBoard(ws,hs,image);
            al_draw_rectangle((mouvement_Avant.x-1)*40+ws,(mouvement_Avant.y-1)*40+hs,(mouvement_Avant.x-1)*40+ws+40,(mouvement_Avant.y-1)*40+hs+40,al_map_rgb(244,0,0),2);
            al_draw_rectangle((mouvement_Apres.x-1)*40+ws,(mouvement_Apres.y-1)*40+hs,(mouvement_Apres.x-1)*40+ws+40,(mouvement_Apres.y-1)*40+hs+40,al_map_rgb(244,0,0),2);
            al_flip_display();
//if(attacked_piece_list((mouvement_Apres.x,mouvement_Apres.y,p[mouvement_Apres.x][mouvement_Apres.y].side,p[mouvement_Apres.x][mouvement_Apres.y].forme,ws,hs)[29].x!=0)
            {

            }
        }
        else
        {
            int t=0;
            ALLEGRO_EVENT ev= {0};
            al_wait_for_event(e,&ev);
            if(pym==2&&(p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme==CERCLE||p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme==CARRE||p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme==TRIANGLE||p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme==0))

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
                while(t!=k)
                {
                    for(i=0; i<k; i++)
                    {
                        al_draw_rectangle((tab[i][0].x-1)*40+ws,(tab[i][0].y-1)*40+hs,(tab[i][0].x-1)*40+ws+40,(tab[i][0].y-1)*40+40+hs,al_map_rgb(243,248,63),2);
                        al_draw_rectangle((tab[i][1].x-1)*40+ws,(tab[i][1].y-1)*40+hs,(tab[i][1].x-1)*40+ws+40,(tab[i][1].y-1)*40+40+hs,al_map_rgb(255,0,0),2);
                        al_draw_rectangle((tab[i][2].x-1)*40+ws,(tab[i][2].y-1)*40+hs,(tab[i][2].x-1)*40+ws+40,(tab[i][2].y-1)*40+40+hs,al_map_rgb(255,0,0),2);
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
                                        ALLEGRO_DISPLAY *display =al_get_current_display();
                                        al_set_target_backbuffer(display);
                                        t++;
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
                            if(ev.mouse.button==1&&joueur[compteurJeu%2]==p[(ev.mouse.x-ws)/40 +1][(ev.mouse.y-hs)/40+1].side)
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
                                    ChangerPosition(ev.mouse.x,ev.mouse.y,oldx,oldy,ws,hs);
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
                            afficherBoard( ws,hs,image);
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
                    break;
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    move=4;
                    break;

                }

            }

        }
    }
}
