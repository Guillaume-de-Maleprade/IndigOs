#include "type.h"
#include "Ecran.h"
#include "Outils.h"
#include "Info_Boot.h"
#include "Init_GDT.h"
#include "Init_IDT.h"
#include "MACRO.h"
#include "PLAN_MEMOIRE.h"
#include "HARD_8042_Clavier.h"
#include "DELAY.h"


/*
 * ATTENTION : 
 * Code : de 1Mo à 2Mo
 * Data : à partir de 2 Mo jusqu'à 32 Mo - Taille Pile
 * 
 -Ttext=0x100000 --entry=_start --oformat i586-pc-elf 
 -Tdata=0x200000 -Map=Noyau.map
 */


void OS_Main();

//----------------------------------------------------------------------------

void Affiche_Informations_Boot(T_BOOT_INFO* P_Info) {
    if ((P_Info->Flags & BOOT_INFO_MEMOIRE) == BOOT_INFO_MEMOIRE) {
        Regle_Couleur(BLANC);
        Affiche_Chaine(">>>Memoire detectee : ");
        UINT32 L_Taille_Memoire = P_Info->Adresse_Basse + P_Info->Adresse_Haute + 1024;
        Regle_Couleur(BLEU | LUMINEUX);
        Affiche_Chaine(Entier_Vers_Chaine(L_Taille_Memoire / 1024));
        Affiche_Chaine(" Mo \n");
    }
}
//----------------------------------------------------------------------------

void Affiche_Message(UCHAR* P_Message, UCHAR* P_Etat) {
    Regle_Couleur(BLANC);
    Affiche_Chaine(P_Message);
    Positionne_Curseur(78 - Taille_Chaine(P_Etat), Donne_Curseur_Y());
    Regle_Couleur(VERT | LUMINEUX);
    Affiche_Chaine(P_Etat);
    Affiche_Caractere('\n');
}
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------

void OS_Start(T_BOOT_INFO* P_Info) {
    Efface_Ecran();

    Affiche_Message(">>>BOOT JLV OS V1 - 2011 Via GRUB : ", "OK");
    Affiche_Informations_Boot(P_Info);

    Initialisation_GDT();
    Affiche_Message(">>>Initialisation de la GDT : ", "OK");

    //Initialiser le pointeur pile.
    // NE PAS ETRE DANS UNE FONCTION CAR à la sortie d'une fonction, le regsitre ESP est réinitialisé à la valeur précédant l'appel.
    //  INITIALISE_SS_ESP(SELECTEUR_STACK_NOYAU,DEBUT_STACK_NOYAU);


    INITIALISE_SS_ESP(SELECTEUR_STACK_NOYAU, DEBUT_STACK_NOYAU)
    OS_Main();
    asm ("NOP");
}
//------------------------------------------------------------------------------
//==============================================================================
/*
 EXEMPLE D'ORDONNANCEUR TRES SIMPLE NON PREHEMPTIF
 
 */

//==============================================================================

#define NOMBRE_THREADS_MAXI 10

typedef void(*PT_THREAD)();

typedef struct {
    PT_THREAD Fonction;
    int Duree;
    int Tic_Restant;
} T_THREAD;



volatile BYTE Nombre_Thread = 0;
T_THREAD Les_Threads[NOMBRE_THREADS_MAXI];

void Ajoute_Thread(PT_THREAD P_Thread, int P_Duree) {
    if (Nombre_Thread < NOMBRE_THREADS_MAXI) {
        Les_Threads[Nombre_Thread].Fonction = P_Thread;
        Les_Threads[Nombre_Thread].Duree = P_Duree;
        Les_Threads[Nombre_Thread].Tic_Restant = P_Duree;

        Nombre_Thread++;
    }
}
//-----------------------------------------------------

T_THREAD Get_Thread(int P_Numero) {
    if (P_Numero < Nombre_Thread)return Les_Threads[P_Numero];
    return Les_Threads[0];
}
//-----------------------------------------------------

T_THREAD Get_Next_Thread() {
    static BYTE LS_Index_Thread = 0;
    if (LS_Index_Thread >= Nombre_Thread)LS_Index_Thread = 0;
    Les_Threads[LS_Index_Thread].Tic_Restant = Les_Threads[LS_Index_Thread].Duree;
    return Les_Threads[LS_Index_Thread++];
}
//##############################################################################

volatile T_THREAD Thread_Actif = {0, 0};

volatile void Tache_1() {
    while (Thread_Actif.Fonction == Tache_1) {
        Regle_Couleur(VERT | LUMINEUX);
        Affiche_Chaine("TACHE 1\n");
    }
}

//-------------------------------------------------- 

volatile void Tache_2() {
    while (Thread_Actif.Fonction == Tache_2) {
        Regle_Couleur(BLEU | LUMINEUX);
        Affiche_Chaine("    TACHE 2\n");
    }
}

//-------------------------------------------------- 

volatile void Tache_3() {
    while (Thread_Actif.Fonction == Tache_3) {
        Regle_Couleur(ROUGE | LUMINEUX);
        Affiche_Chaine("        TACHE 3\n");
    }
}
//-------------------------------------------------- 

volatile void Tache_4() {
    while (Thread_Actif.Fonction == Tache_4) {
        Regle_Couleur(BLEU | VERT | LUMINEUX);
        Affiche_Chaine("            TACHE 4\n");
    }
}

//-------------------------------------------------- 

void Ordonnancer() {
    if (Thread_Actif.Tic_Restant == 0) {
        Thread_Actif = Get_Next_Thread();
    }
    Thread_Actif.Tic_Restant--;
}

//------------------------------------------------------------------------------

void OS_Main() {

    Affiche_Message(">>>Initialisation de la Pile (ESP) : ", "OK");

    Initialisation_IDT();
    Affiche_Message(">>>Initialisation de la IDT : ", "OK");

    Initialisation_8259A();
    Affiche_Message(">>>Initialisation du PIC 8259A : ", "OK");

    Initialisation_8253(119);
    Affiche_Message(">>>Initialisation du controleur 8253 : ", "OK");
    //

    AUTORISE_INTERRUPTION;
    //---------------------------------------------------------------------------- 

    Ajoute_Thread(Tache_1, 100);
    Ajoute_Thread(Tache_2, 200);
    Ajoute_Thread(Tache_3, 500);
    Ajoute_Thread(Tache_4, 1000);

    Thread_Actif = Get_Thread(0);

    while (1) {
        if (Thread_Actif.Fonction) Thread_Actif.Fonction();
    }
}





