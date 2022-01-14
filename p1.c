#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANDOM ((rand()%12+1) + rand()%12+1);

typedef struct
{
    int x;
    int y;
}  T_case ;

//typedef T_case T_Tab_Case[4];

int nimber(T_case tested_case, int nbrcol, int nbrlin)
{
    int nimber;
    if (((nbrcol)%3 == (tested_case.x)%3) && ((nbrlin)%3 == (tested_case.y)%3))
    {
        nimber=0;
    }
    else
    {
        nimber=1;
    }
    return nimber;
}



int creaGrille(int col, int lin, int x, int y)
{
    int i,j;
    for (i = 1; i <= lin; i++)
    {
        printf("|");
        for ( j = 1; j <= col; j++)
        {
            if (i == y && j == x)
            {
                printf("X|");
            }
            else
            {
                printf("-|");
            }
            
           
        }
        printf("\n");   
    }    
}


int compteVoisine(int col, int lin, int x, int y, int * pvoisx, int * pvoisy)
{
    *pvoisx=*pvoisy=0;
    
    if ((lin-y)>=2)
    {
        *pvoisy = 2;
    }
    else if ((lin-y)==1)
    {
        *pvoisy=1;
    }

    if ((col-x)>=2)
    {
        *pvoisx = 2;
    }
    else if ((col-x)==1)
    {
        *pvoisx=1;
    }

}


int ordiRandom(int totalVois)
{
    int dice;
    dice = RANDOM;
    printf("Coup aleatoire effectue\n");
    return((dice % totalVois));
}


int ordiWin(int totalVois, T_case pion, T_case nbvois[], int nbrlin, int nbrcol)
{
    int i;
    printf("Coup gagnant annonce\n");
    for (i = 0; i < totalVois; i++)
    {
        if (nimber(nbvois[i], nbrlin, nbrcol)==0)
        {
            return i;
        }  
    }
    return(ordiRandom(totalVois));   
}


int coupOrdi(int totalVois, T_case nbvois[], int lvl, T_case pion, int nbrlin, int nbrcol)
{
    int dice, typeMoveDice;
    dice = RANDOM;
    typeMoveDice = (dice % 3)+1;
    if (typeMoveDice <= lvl-1)
    {
        return(ordiWin(totalVois, pion, nbvois, nbrlin, nbrcol));
    }
    else
    {
        return(ordiRandom(totalVois));
    }
}


int moveJoueur(int nbr)
{
    int move;
    if (nbr>1)
    {
        do
        {
            printf("Entrez le numero correspondant\n");
            scanf("%d", &move);
            if (move<1 || move>nbr)
            {
                printf("Erreur!\n");
            }
            
        } while (move<1 || move>nbr);
    }
    else
    {
        printf("Un seul deplacement est possible : ");
        move=1;
    }
    

    return move-1;
}


int voisine(int * pvoisx, int * pvoisy, int x, int y, T_case nbvois[], T_case * ppion)
{
    int totalVois;
    totalVois = *pvoisx + *pvoisy;
    int compte_vois;
    compte_vois=0;
    int i;
    T_case remplissage_voisin;

    
    for (i = 1; i <= *pvoisx; i++)
    {
        remplissage_voisin.x= ppion->x+i;
        remplissage_voisin.y= ppion->y;
        nbvois[compte_vois] = remplissage_voisin;
        compte_vois=compte_vois+1;
    }

    for (i = 1; i <= *pvoisy; i++)
    {
        remplissage_voisin.x= ppion->x;
        remplissage_voisin.y= ppion->y+i;
        nbvois[compte_vois] = remplissage_voisin;
        compte_vois=compte_vois+1;
    }
    return compte_vois;
}


int coupJoueur(int totalVois, T_case nbvois[])
{
    int i;
     printf("Vers quelle case voulez-vous vous deplacer ?\n");
    for (i = 0; i < totalVois; i++)
    {
        printf("%i : ", i+1);
        printf("(%i",nbvois[i].x);
        printf(";%i) \n",nbvois[i].y);
    }

    return(moveJoueur(totalVois));
}


int nlin()
{
    int nbrlin;
    do
    {
        printf("Saisir le nombre de ligne entre 5 et 30\n");
        scanf("%d", &nbrlin);
    } while (nbrlin<5 || nbrlin>30);

    return nbrlin;
}

int ncol()
{
    int nbrcol;
    do
    {
       printf("Saisir le nombre de colonne entre 5 et 30\n");
        scanf("%d", &nbrcol);
    } while (nbrcol<5 || nbrcol>30);

    return nbrcol;
}

int niveau()
{
    int lvl;
    do
    {
       printf("Saisir le niveau entre 1 et 4\n");
        scanf("%d", &lvl);
    } while (lvl<1 || lvl>4);

    return lvl;
}


int next()
{
    int startplayer;
    do
    {
       printf("Qui commence ? 1 pour l'ordi, 2 pour le joueur\n");
        scanf("%d", &startplayer);
    } while (startplayer<1 || startplayer>2);

    return startplayer;
}

void winner(int startplayer, int nbrtour ){
    if (startplayer==1)
    {
        if ((nbrtour%2)==1)
        {
            printf("J1 (Ordinateur) a gagne!");
        }
        else
        {
            printf("J2 (Joueur) a gagne!");
        } 
    }
    else
    {
        if ((nbrtour%2)==1)
        {
            printf("J2 (Joueur) a gagne!");
        }
        else
        {
            printf("J1 (Ordinateur) a gagne!");
        } 
    }
}


int aToiDeJouer(int startplayer, int nbrtour){
    if ((startplayer == 1 && nbrtour%2 == 0) || (startplayer == 2 && nbrtour%2 == 1)){
        printf("A toi de jouer\n");
        return(1);
    }
    else{
        printf("C'est a l'ordinateur de jouer\n");
        return(0);
    }
}




int main()
{
    int nbrlin, nbrcol;
    int lvl;
    int startplayer;
    int gameover=0;
    int voisx, voisy;
    int move;
    int totalVois;
    int nbrtour=0;
    int playerTurn;

    T_case nbvois[4];

    nbrlin=nlin();
    nbrcol=ncol();
    lvl=niveau();
    startplayer=next();

    T_case pion;

    pion.x=1;
    pion.y=1;

    printf("%i;", pion.x);
    printf("%i\n", pion.y);

    while (pion.x!=nbrcol || pion.y!=nbrlin)
    {
        nbrtour++;
        printf("\n ==== TOUR %i ==== \n", nbrtour);
        playerTurn=aToiDeJouer(startplayer, nbrtour);
        creaGrille(nbrcol, nbrlin, pion.x, pion.y);
        compteVoisine(nbrcol, nbrlin, pion.x, pion.y, &voisx, &voisy); 
        totalVois = voisine(&voisx, &voisy, pion.x, pion.y, nbvois, &pion);

        if (playerTurn==1)
        {
            move=coupJoueur(totalVois, nbvois);
        }
        else
        {
            move=coupOrdi(totalVois, nbvois, lvl, pion, nbrlin, nbrcol);
        }
        
        
        
        pion=nbvois[move];
        printf("(%i;", pion.x);
        printf("%i)\n", pion.y);
    }

    printf("\n ==== FIN DE LA PARTIE ==== \n");
    creaGrille(nbrcol, nbrlin, pion.x, pion.y);
    winner(startplayer, nbrtour);
}