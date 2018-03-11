#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define SIZE 20
#define nbJoueurs 4

// Projet d'arène
// Projet de programmation 11/03/2018

// Pearl league
// &J

struct Coordonnees
{
    int x, y;
};

typedef enum Etat Etat;
enum Etat
{
    MORT = 0, VIE
};

typedef struct Player Player;
struct Player
{
    struct Coordonnees coord;
    Etat etat;
    int Couleur;
    int nbTour;
    int Classement;

    //string
};


void RandomCase_IA(Player joueurs[nbJoueurs], int i, int carte[SIZE][SIZE]);
void AssignRandomNewStartPosition(Player joueurs[4]);
void ClearConsole();

int PlayerAlive;

void Fill_Map(int map[SIZE][SIZE], Player joueurs[nbJoueurs])
{
    // On detecte la pos de tous les joueurs et on les placent sur la map en fonction des coordonnées x et y

    int ActualPlayer, i, j ;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (map[i][j] == 6)
            {

            }
            else
            {
                map[i][j] = 9;

            }
        }
    }

    for (ActualPlayer = 0; ActualPlayer < nbJoueurs ; ActualPlayer ++)
    {
        for ( i = 0; i < SIZE; i ++)
        {
            for (j = 0; j < SIZE; j++)
            {
                if (map[i][j] == 6)
                {

                }
                else if (joueurs[ActualPlayer].coord.x == i && joueurs[ActualPlayer].coord.y == j)
                {
                    // Pour les quatres joueurs, on check leurs positions sur la carte.
                    // Quand on trouvent leurs positions, on leurs assigne 1,2,3 ou 4
                    map[i][j] = ActualPlayer;
                }
            }
        }
    }
}

void Afficher_Map(int map[SIZE][SIZE], Player joueurs[nbJoueurs])
{
    ClearConsole();
    SetColor(255);
    // 0 joueur 0
    // 1 joueur 1
    // 2 joueur 2
    // 3 joueur 3
    // 6 Fire  666
    // 9 terrain
    int i, j;
    for (i = 0; i < SIZE * 3 + 4; i ++)
        printf("|");
    printf("\n");
    for (i = 0; i < SIZE; i ++)
    {
        printf("||");
        for (j = 0; j < SIZE; j ++)
        {
            switch(map[i][j])
            {
            case 0:
                // terrain
                SetColor(joueurs[0].Couleur);
                printf(" 0 ");
                break;
            case 1:
				SetColor(joueurs[1].Couleur);
                printf(" 1 ");
                break;
            case 2:
				SetColor(joueurs[2].Couleur);
                printf(" 2 ");
                break;
            case 3:
				SetColor(joueurs[3].Couleur);
                printf(" 3 ");
                break;
            case 6:
                SetColor(44);
                printf(" # ");
                break;
            // terrain
            case 9:
                SetColor(35);
                printf(" . ");
                break;
            }
        }
        SetColor(255);
        printf("||\n");
    }
    for (i = 0; i < SIZE * 3 + 4; i ++)
        printf("|");
}

void newRound(int map[SIZE][SIZE], Player joueurs[nbJoueurs])
{
    int CurrPlayer;

    for (CurrPlayer = 0; CurrPlayer < nbJoueurs; CurrPlayer ++ )
    {
        if (PlayerAlive <= 1)
        {
            return;
        }
        // On check si ils sont en vies avant
        while (joueurs[CurrPlayer].etat == MORT)
        {
            CurrPlayer ++;
            if (CurrPlayer >= nbJoueurs)
                CurrPlayer = 0;

        }

        switch (CurrPlayer)
        {
            // Exemple
        case 0:
            RandomCase_IA(joueurs, CurrPlayer, map);
            break;
        case 1:
            RandomCase_IA(joueurs, CurrPlayer, map);
            break;
        case 2:
            RandomCase_IA(joueurs, CurrPlayer, map);
            break;
        case 3:
            RandomCase_IA(joueurs, CurrPlayer, map);
            break;
        }
        CheckFire(map, joueurs);
        Fill_Map(map, joueurs);
        Afficher_Map(map, joueurs);

        SetColor(joueurs[CurrPlayer].Couleur);
        printf("\nC'est le tour du joueur %d !", CurrPlayer);
        printf("\n--------------------------\n\n\n");

        printScore(joueurs);
        Wait(1000);
    }

    // Output


}
void CheckFire(int carte[SIZE][SIZE], Player joueurs[nbJoueurs])
{
    int j;

    for (j = 0; j < nbJoueurs; j++)
    {
        if (carte [joueurs[j].coord.x] [joueurs[j].coord.y] == 6)
        {
            if (joueurs[j].etat == VIE)
            {
                joueurs[j].etat = MORT;
                joueurs[j].Classement = PlayerAlive;
                PlayerAlive --;
            }
        }
    }
}

void Jeu()
{
    int Map[SIZE][SIZE];
    Player Joueurs[nbJoueurs];

    PlayerAlive = nbJoueurs;
    AssignRandomNewStartPosition(Joueurs);

    int i;
    for (i = 0; i < nbJoueurs; i ++)
    {
        Joueurs[i].Classement = 0;
        Joueurs[i].etat = VIE;
        Joueurs[i].nbTour = 0;
    }
    Joueurs[0].Couleur = 21;
    Joueurs[1].Couleur = 30;
    Joueurs[2].Couleur = 23;
    Joueurs[3].Couleur = 42;

    while (PlayerAlive > 1)
    {
        newRound(Map, Joueurs);
    }
    Wait(6000);
}


int main()
{
    srand(time(NULL));
    int a;
    do
    {
        ClearConsole();
        printf("Bienvenue !\nFireArena est un jeu d'arène ou s'affrontent 4 joueurs, chaque joueur jouent chacun leurs tours\n");
        printf("a chaque tour, lorsque qu'un joueur se déplace, une trainée de flamme sort des pieds du joueur\n");
        printf("\nLorqu'un joueur se déplace sur une flamme, le joueur meurt\n\n\n");
        printf("1 : Jouer a Fire Arena");
        printf("\n\n\n2 : Quitter\n");

        scanf("%d", &a);
        switch (a){
        case 1:
            Jeu();
            break;
        }
    } while ( a != 2);

    return 0;
}

void printScore(Player joueurs[nbJoueurs])
{
    SetColor(255);
    int k;
    printf("--------------------------");
    for (k = 0; k < nbJoueurs; k ++)
    {
        if (joueurs[k].etat == MORT)
        {
            SetColor(joueurs[k].Couleur);
            printf("\n%d eme) Joueur %d         ||", joueurs[k].Classement, k);
        }
    }
    SetColor(255);
    printf("\n--------------------------");
}
// FOR IA
// Les IA peuvent pour l'instant déplacer les autres joueurs
void Move_Up(int joueurs[nbJoueurs][2], int i)
{
    if (joueurs[nbJoueurs][0] < SIZE)
    {
        joueurs[nbJoueurs][0] += 1;
    }
}

void Move_Down(int joueurs[nbJoueurs][2], int i)
{
    if (joueurs[nbJoueurs][0] > 0)
    {
        joueurs[nbJoueurs][0] -= 1;
    }
}

void Move_Left(int joueurs[nbJoueurs][2], int i)
{
    if (joueurs[nbJoueurs][1] > 0)
    {
        joueurs[nbJoueurs][0] -= 1;
    }
}

void Move_Right(int joueurs[nbJoueurs][2], int i)
{
    if (joueurs[nbJoueurs][1] < SIZE)
    {
        joueurs[nbJoueurs][0] += 1;
    }
}


void RandomCase_IA(Player joueurs[nbJoueurs], int i, int carte[SIZE][SIZE])
{
    // Pas trop besoin de s'en occuper, ça fait une case aléatoire a cote
    // On fera des fonctions pour chaque comportement des IA
    // C'est juste un exemple pour tester


    // Si le joueur est mort
    if (joueurs[i].etat == MORT)
       return;
    // SI LE JOUEUR EST SUR UNE CASE DE FEU :::::::     IL PEUT PLUS BOUGER

    // ON MET LA CASE OU IL ETAIT AVANT EN FEU
    carte [joueurs[i].coord.x]   [joueurs[i].coord.y] = 6;

    int xy, n;
    for (xy = 0; xy < 2; xy ++)
    {
        n = rand() % 2;

        if (n == 0  && joueurs[i].coord.x - 1 >= 0 )
        {
            joueurs[i].coord.x = joueurs[i].coord.x - 1;
        }
        else if (n == 1 && joueurs[i].coord.y + 1 < SIZE)
        {
            joueurs[i].coord.y = joueurs[i].coord.y + 1;
        }
    }
}

void AssignRandomNewStartPosition(Player joueurs[nbJoueurs])
{
    int ActualPlayer, xy;

    // BUG POSSIBLE : 2 JOUEURS ONT LA MEME POSITIONS
    for (ActualPlayer = 0; ActualPlayer < nbJoueurs; ActualPlayer ++ )
    {
        joueurs[ActualPlayer].coord.x = rand() % SIZE;
        joueurs[ActualPlayer].coord.y = rand() % SIZE;
    }
}

void ClearConsole()
{
    system("cls");
}

void Wait(int time)
{
    Sleep(time);
}


//cest pour la gestion des joueurs
//
void SetColor(int ForgC)
{
  WORD wColor;
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
  {
    wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
    SetConsoleTextAttribute(hStdOut, wColor);
  }
  return;
}
