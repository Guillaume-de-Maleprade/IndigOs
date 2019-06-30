#include "stdio.h"
#include "math.h"
#include <windows.h>

#define NOMBRE_TACHES_MAXI 10

//############################################################
//                      STRUCTURE TACHE
//############################################################

typedef void (*PT_TACHES)();
typedef struct
{
    PT_TACHES Fonction; // Le code de la fonction
    int Ci;         // Durée
    int Pi;         // Période
    float Priorite; // Prioritée (calculée en  fonction de Pi et Ci)
    int aFaire;     // Si la foction est
} T_Tache;


//############################################################
//                      VARIABLE GLOBALE
//############################################################

volatile int Nombre_Taches = 0;         //
T_Tache Les_Taches[NOMBRE_TACHES_MAXI]; //
int tache_encours = 0;                  //
int saveTache_encours = 0;              //
int saveCi_encours = 0;                 //


//############################################################
//                           FONCTIONS
//############################################################

// Change la couleur du texte affiché dans la console
void color(int t, int f)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, f * 16 + t);
}

//-----------------------------------------------------

// Ajoute une tache à Scheduler par l'ordonnanceur
void Ajoute_Tache(PT_TACHES P_Tache, int P_Ci, int P_Pi)
{
    if (Nombre_Taches < NOMBRE_TACHES_MAXI)
    {
        Les_Taches[Nombre_Taches].Fonction = P_Tache;
        Les_Taches[Nombre_Taches].Ci = P_Ci;
        Les_Taches[Nombre_Taches].Pi = P_Pi;
        Les_Taches[Nombre_Taches].Priorite = 1.0 / (float)P_Pi;
        Les_Taches[Nombre_Taches].aFaire = 1; // Pour savoir si la tache à déja été faite ou est à faire

        Nombre_Taches++;
    }
}

//-----------------------------------------------------

// Recupere une tache
T_Tache Get_Tache(int P_Numero)
{
    if (P_Numero < Nombre_Taches)
        return Les_Taches[P_Numero];
    return Les_Taches[0];
}

//-----------------------------------------------------

// Passe à la tache suivante
T_Tache Get_Next_Tache()
{
    // Tant que la tache suivante n'est pas à faire, on avance dans le tableau
    do{
        tache_encours++;
    }while(Les_Taches[tache_encours].aFaire != 1);

    color(7, 0);
    // Quand on atteint le bout du tableau, on reprend au début
    if (tache_encours > Nombre_Taches - 1)
    {
        tache_encours = 1;
    }

    // Si une tache avait été coupée, on reprend à partir de cette tache
    if (saveTache_encours != 0)
    {
        tache_encours = saveTache_encours;
        saveTache_encours = 0;
    }

    return Les_Taches[tache_encours];
}

volatile T_Tache Tache_Actif = {0, 0};


//############################################################
//                      L'ORDONNANCEUR
//############################################################

void Ordonnanceur(int horloge)
{
    // Si la périodicité d'une tache est atteinte, alors elle doit etre refaite, on regarde pour toutes les taches du tableau
    int j;
    for (j = 0; j < Nombre_Taches - 1; j++)
    {
        if (horloge % Les_Taches[j].Pi == 0 && horloge != 0)
        {
            //printf("Remise à 1");
            Les_Taches[j].aFaire = 1;
        }
    }


    if ((horloge % Les_Taches[0].Pi == 0) && horloge != 0)
    {
        // Si la période de la tache est un modulo de l'horloge alors on recommence le tableau
        Tache_Actif = Les_Taches[0];

        // On regarde si on coupe la tache dans sa durée
        if (Tache_Actif.Ci != 0 && tache_encours != Nombre_Taches - 1)
        {
            // On enregistre la tache et le Ci manquant
            saveTache_encours = tache_encours;
            saveCi_encours = Tache_Actif.Ci - 1;
        }

        // On remet le tableau au début
        tache_encours = 0;
        printf("\n");
        Tache_Actif.Ci--; // La tache aura déja été faite donc il faut décrémenter
    }
    else
    {
        // Si il y avait une tache en cours, on repend cette tache et la durée qu'elle lui rste à faire
        if (saveCi_encours != 0 && tache_encours != 0)
        {
            Tache_Actif.Ci = saveCi_encours;
            saveCi_encours = 0;
        }
        if (Tache_Actif.Ci == 0) // On décrémente la tache
        {
            Les_Taches[tache_encours].aFaire = 0; // La tache est fini, elle n'est plus à faire
            Tache_Actif = Get_Next_Tache(); // On va chercher la tache suivante
        }
        Tache_Actif.Ci--;
    }
}

//############################################################
//       VERIFICATION SI L'ORDONNANCEMENT EST POSSIBLE
//############################################################

// Test si un ordonacement est possible avec les taches déclarées
int OrdonnancementPossible()
{
    int j;
    double U_Pratique = 0, U_Theorique;

    // Valeur Theorique
    U_Theorique = Nombre_Taches * ((pow(2, 1 / (double)Nombre_Taches)) - 1);
    printf("\nU_Theorique = %lf\n", U_Theorique);

    // Valeur Pratique
    for (j = 0; j < Nombre_Taches; j++)
    {
        double Rapport_Tache = (double)Les_Taches[j].Ci / (double)Les_Taches[j].Pi;
        U_Pratique = U_Pratique + Rapport_Tache;
    }
    printf("U_Pratique = %lf\n", U_Pratique);

    if (U_Theorique >= U_Pratique)
    {
        printf("Ordonnanceur possible\n\n");
        return 1;
    }
    else
    {
        printf("Ordonnanceur impossible\n");
        return 0;
    }
}


//############################################################
//            TRI DES TACHES SELON LEUR PRIORITE
//############################################################

int PrioriteMinimale(T_Tache tab[], int taille) // Fonction pour trier en fonction de la priorité
{
    // On considère que le plus grand élément est le premier
    int i = 0, PrioriteMinimale = 0;

    while (i < taille)
    {
        if (tab[i].Priorite < tab[PrioriteMinimale].Priorite)
            PrioriteMinimale = i;
        i++;
    }
    return PrioriteMinimale;
}

//-----------------------------------------------------
void echanger(T_Tache tab[], int x, int y) // Fonction pour echanger les places dans le tableau
{
    T_Tache tmp;
    tmp = tab[x];
    tab[x] = tab[y];
    tab[y] = tmp;
}

//-----------------------------------------------------
void tri_selection() // Fonction pour trier le tableau
{
    int PrioriteMinimaleValeur;

    // à chaque tour de boucle, on va déplacer le plus grand élément
    // vers la fin du tableau, on diminue donc à chaque fois sa taille
    // car le dernier élément est obligatoirement correctement
    // placé (et n'a donc plus besoin d'être parcouru/déplacé)

    for (; Nombre_Taches > 1; Nombre_Taches--) // Tant qu'il reste des éléments non triés
    {
        PrioriteMinimaleValeur = PrioriteMinimale(Les_Taches, Nombre_Taches);

        echanger(Les_Taches, Nombre_Taches - 1, PrioriteMinimaleValeur); // On échange le dernier élément avec le plus grand
    }
}

//-----------------------------------------------------

//############################################################
//                     LE CODE DES TACHES
//############################################################

void Tache1()
{
    color(1, 0);
    printf("##Tache 1##\t\t");
}


void Tache2()
{
    color(12, 0);
    printf("##Tache 2##\t\t");
}


void Tache3()
{
    color(15, 0);
    printf("##Tache 3##\t\t");
}


void sousTache()
{
    color(5, 0);
    printf("##SOUS TACHE##\t\t");
};


//############################################################
//                             MAIN
//############################################################

int main(void)
{
    // (Nom, Ci, Pi)
    Ajoute_Tache(Tache1, 3, 20);
    Ajoute_Tache(Tache2, 2, 5);
    Ajoute_Tache(Tache3, 2, 10);

    if (OrdonnancementPossible()) // On verifie si un ordonnancement est possible
    {
        // On ajoute une tache vide (ou sous tache) Elle ne doit pas etre prise en compte dans le calcul du Scheduling
        Ajoute_Tache(sousTache, 50, 100);
        int i = 0;
        // On tri les fonctions dans l'ordre de priorité (la premiere dans la case )
        int tmp = Nombre_Taches; // sauvegarde du nombre de tache - la valeur change a cause de la fonction tri_selection()
        tri_selection();
        Nombre_Taches = tmp;
        // On défini la 1ere tache sur la case 0 du tableau
        Tache_Actif = Get_Tache(0);

        while (i <= 40) // la boucle while simule l'horloge
        {
            Ordonnanceur(i); // Fonction pour l'ordonnanceur (ici i représente l'horloge / en vrai c'est une variable globale)
            color(10, 0);    // defini la couleur (on utilisera la fonction du prof)
            printf("-%d-\t", i);
            if (Tache_Actif.Fonction)
            {
                Tache_Actif.Fonction();
            }
            i++;
        }
        color(15, 0);
    }
    else // Si ordonnancement non possible
    {
        printf("\n##\tERREUR - Verifiez les taches (duree et periodicitee)\t##\n");
        printf("##\tFIN DE L'OS\t##\n\n");
        return 0;
    }
}
