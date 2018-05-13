#include "Ar_Mode_Reseau.h"

char *convertisseurChar(int positionx,int positiony)
{
    char coor[2];
    switch(positionx)
    {
    case 1:
        sprintf(coor,"a%d",positiony);
        break;
    case 2:
        sprintf(coor,"b%d",positiony);
        break;
    case 3:
        sprintf(coor,"c%d",positiony);
        break;
    case 4:
        sprintf(coor,"d%d",positiony);
        break;
    case 5:
        sprintf(coor,"e%d",positiony);
        break;
    case 6:
        sprintf(coor,"f%d",positiony);
        break;
    case 7:
        sprintf(coor,"g%d",positiony);
        break;
    case 8:
        sprintf(coor,"h%d",positiony);
        break;
    }
    return coor;

}

coordonne convertisseurPosition(char *texte)
{
    coordonne position;
    switch(texte[0])
    {
    case 'a':
        position.x=1;
        break;
    case 'b':
        position.x=2;
        break;
    case 'c':
        position.x=3;
        break;
    case 'd':
        position.x=4;
        break;
    case 'e':
        position.x=5;
        break;
    case 'f':
        position.x=6;
        break;
    case 'g':
        position.x=7;
        break;
    case 'h':
        position.x=8;
        break;
    }
    char y[3];
    y[0]=texte[1];
    y[1]=texte[2];
    position.y=strtol(&y,NULL,10);

    return position;
}


void purger()
{
    int c;
    while ((c = getchar()) != '\0' && c != '\n');
}

int askport()
{
    int port;
    printf("Port : ");
    scanf("%i",&port);
    purger();
    return port;
}

void askIP(char ip[15])
{
    printf("Ip : ");
    scanf("%s",ip);
    purger();
}
void MainReseau(ALLEGRO_DISPLAY *display)
{
    int choix;
    int ret;
#ifdef WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,0),&wsa);
#endif
    printf("Serveur = 0 ; Client = 1 : ");
    scanf("%d",&choix);
    if (choix==0)
    {
        SOCKET sock_attente;
        SOCKET sock_dialogue;
        SOCKADDR_IN csin;
        int len;
        char buffer[50];
        int err=0;
        int port = askport();
        csin.sin_family=AF_INET;
        csin.sin_addr.s_addr=htonl(INADDR_ANY);
        csin.sin_port=htons(port);
        sock_attente = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        if (sock_attente == INVALID_SOCKET)
            return -1;
        if (bind(sock_attente,(SOCKADDR*)&csin,sizeof(csin)) == SOCKET_ERROR)
            return -2;
        printf("Listen...\n");
        if (listen(sock_attente, 1) == SOCKET_ERROR)
            return -3;
        len = sizeof(csin);
        printf("Attente client...\n");
        sock_dialogue = accept(sock_attente, (SOCKADDR *)&csin, &len);
        if (sock_dialogue==INVALID_SOCKET)
            return -4;
        printf("Connection ok\n");
        jouer_reseau(display,sock_dialogue,0);
    }
    else
    {
        char ip[15];
        int port;
        SOCKET sock;
        SOCKADDR_IN sin;
        askIP(ip);
        port = askport();
        sin.sin_family=AF_INET;
        sin.sin_addr.s_addr=inet_addr(ip);
        sin.sin_port=htons(port);
        sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        if (sock == INVALID_SOCKET)
            return -1;
        printf("Connection...\n");
        if(connect(sock,(SOCKADDR*)&sin,sizeof(sin)) == SOCKET_ERROR)
            return -2;
        printf("Connection ok\n");
        jouer_reseau(display,sock,1);
    }
    printf("Retour : %d\n",ret);
#ifdef WIN32
    WSACleanup();
#endif

}

int jouer_reseau(ALLEGRO_DISPLAY *display,SOCKET sock,int tour)
{



    char commande[10];
    int compteurJeu=0;
    int joueur[2]= {-1,1};
    int i,j,Mange,pym=0,selec=0;
    initialiseBoard();
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
        memset(commande,0,sizeof(commande));

        if(tour==1)
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
                                    p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme=p[(oldx-ws)/40+1][(oldy-hs)/40+1].py.piece[(ev.mouse.x-(oldx/40*40))/40+1].forme;
                                    pym=0;
                                    selec=2;
                                    al_draw_rectangle((ev.mouse.x-ws)/40*40+ws,(ev.mouse.y-hs)/40*40+hs,(ev.mouse.x-ws)/40*40+ws+40,(ev.mouse.y-hs)/40*40+hs+40,al_map_rgb(243,248,63),2);
                                    al_flip_display();
                                    al_rest(0.5);
                                }
                                if((oldx-ws)/40+1>4)
                                {
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
                            if(ev.mouse.button==1)
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
case ALLEGRO_EVENT_KEY_DOWN:
                if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
                {

                  for(i=1;i<=3;i++)
                detuire_bouton(boutonJeu[i]);
                    MenuPrincipal(al_get_current_display(),AP);
                }
break;
                case ALLEGRO_EVENT_MOUSE_AXES:
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


                        if(p[(oldx-ws)/40+1][(oldy-hs)/40+1].existe==1&&p[(ev.mouse.x-ws)/40+1][(ev.mouse.y-hs)/40+1].existe==-1)
                        {

                            if(verifierDeplacement(oldx,oldy,ev.mouse.x,ev.mouse.y,p[(oldx-ws)/40+1][(oldy-hs)/40+1].forme,ws,hs)==1||(click_is_out(oldx,oldy)&&p[(oldx-ws)/40+1][(oldy-hs)/40+1].existe==1))
                            {
                                afficherBoard( ws, hs,image);

                                if((ev.mouse.x-ws)/40!=(oldx-ws)/40||(ev.mouse.y-hs)/40!=(oldy-hs)/40)
                                {
                                    ChangerPosition(ev.mouse.x,ev.mouse.y,oldx,oldy,ws,hs);
                                    compteurJeu++;
                                    char pos1[3],pos2[3];
                                    pos1[0]=convertisseurChar((oldx-ws)/40+1,(oldy-hs)/40+1)[0];
                                    pos1[1]=convertisseurChar((oldx-ws)/40+1,(oldy-hs)/40+1)[1];
                                    pos1[2]=convertisseurChar((oldx-ws)/40+1,(oldy-hs)/40+1)[2];
                                    pos2[0]=convertisseurChar((ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1)[0];
                                    pos2[1]=convertisseurChar((ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1)[1];
                                    pos2[2]=convertisseurChar((ev.mouse.x-ws)/40+1,(ev.mouse.y-hs)/40+1)[2];
                                    commande[0]=pos1[0];
                                    commande[1]=pos1[1];
                                    commande[2]=pos1[2];
                                    commande[3]=pos2[0];
                                    commande[4]=pos2[1];
                                    commande[5]=pos2[2];
                                    send(sock,commande,sizeof(commande),0);
                                    for(i=0; i<6; i++)
                                        printf("%c",commande[i]);
                                    tour = 0;
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

                    break;
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    move=4;
                    break;

                }

            }

        }
        else if(tour==0)
        {
            printf("Attente : ");
            recv(sock,commande,sizeof(commande),0);
            char avant[3],apres[3];
            avant[0]=commande[0];
            avant[1]=commande[1];
            avant[2]=commande[2];
            apres[0]=commande[3];
            apres[1]=commande[4];
            apres[2]=commande[5];
            for(i=0; i<6; i++)
            ChangerPosition((convertisseurPosition(apres).x-1)*40+ws,(convertisseurPosition(apres).y-1)*40+hs,(convertisseurPosition(avant).x-1)*40+ws,(convertisseurPosition(avant).y-1)*40+hs,ws,hs);
            afficherBoard(ws,hs,image);
            al_flip_display();
            tour = 1;
        }
    }
}



