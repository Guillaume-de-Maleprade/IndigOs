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

//#include "CALLBACK_USER.h"


//extern volatile UINT32 Compteur_Horloge=0;

void OS_Main();

//----------------------------------------------------------------------------
void Affiche_Informations_Boot(T_BOOT_INFO* P_Info)
{
 if ( (P_Info->Flags & BOOT_INFO_MEMOIRE) == BOOT_INFO_MEMOIRE) {
    Regle_Couleur(BLANC); Affiche_Chaine(">>>Memoire detectee : " );
    UINT32 L_Taille_Memoire =P_Info->Adresse_Basse +P_Info->Adresse_Haute + 1024;
    Regle_Couleur(BLEU| LUMINEUX); Affiche_Chaine(Entier_Vers_Chaine(L_Taille_Memoire/1024) );
    Affiche_Chaine(" Mo \n" );
  }
}
//----------------------------------------------------------------------------
void Affiche_Message(UCHAR* P_Message, UCHAR* P_Etat)
{
  Regle_Couleur(BLANC); Affiche_Chaine(P_Message);
  Positionne_Curseur(78-Taille_Chaine(P_Etat),Donne_Curseur_Y());
  Regle_Couleur(VERT | LUMINEUX); Affiche_Chaine(P_Etat);
  Affiche_Caractere('\n');
}
 //----------------------------------------------------------------------------



 //----------------------------------------------------------------------------
void OS_Start(T_BOOT_INFO* P_Info)
{
  Efface_Ecran();

  Affiche_Message(">>>BOOT GDM OS V1 - 2019 Via GRUB : ", "OK");
  Affiche_Informations_Boot(P_Info);

  Initialisation_GDT();
  Affiche_Message(">>>Initialisation de la GDT : ","OK");

  //Initialiser le pointeur pile.
  // NE PAS ETRE DANS UNE FONCTION CAR à la sortie d'une fonction, le regsitre ESP est réinitialisé à la valeur précédant l'appel.
 //  INITIALISE_SS_ESP(SELECTEUR_STACK_NOYAU,DEBUT_STACK_NOYAU);


  INITIALISE_SS_ESP(SELECTEUR_STACK_NOYAU,DEBUT_STACK_NOYAU);
   OS_Main();
   asm ("NOP");
}
//------------------------------------------------------------------------------
typedef void(*PT_THREAD)();

/*
volatile PT_THREAD Thread_Actif=0;


void Thread_1(){
    while(Thread_Actif==Thread_1){
        Regle_Couleur(ROUGE); Affiche_Chaine("Tache 1\n");
    }
}

void Thread_2(){
    while(Thread_Actif==Thread_2){
    Regle_Couleur(BLEU); Affiche_Chaine("\tTache 2\n");
    }
}

void Thread_3(){
    while(Thread_Actif==Thread_3){
    Regle_Couleur(VERT); Affiche_Chaine("\t\tTache 3\n");
    }
}

void Thread_4(){
    while(Thread_Actif==Thread_4){
    Regle_Couleur(BLANC); Affiche_Chaine("\t\t\tTache 4\n");
    }
}
*/


typedef struct Thread{
    PT_THREAD Thread_Actif;
    UINT32 P_Duree;
};
UINT32 MAX = 4;
UINT32 i = 0;

Thread thread[MAX];

void Ajouter_Thread(PT_THREAD pt, UINT32 duree){
    thread[i].Thread_Actif = pt;
    thread[i].P_Duree = duree;
    if(i<3) i++;
    else i = 0;
}

BYTE Top_Ordonnanceur=0;
void Ordonnanceur()
{
/*
    if(Top_Ordonnanceur<64){
        Thread_Actif=Thread_1;
    }
    else if(Top_Ordonnanceur<128){
        Thread_Actif=Thread_2;
    }
    else if(Top_Ordonnanceur<192){
        Thread_Actif=Thread_3;
    }else{
        Thread_Actif=Thread_4;
    }
*/
    
    Top_Ordonnanceur++;
}


//------------------------------------------------------------------------------
void OS_Main()
{
 
  Affiche_Message(">>>Initialisation de la Pile (ESP) : ","OK");

  Initialisation_IDT();
  Affiche_Message(">>>Initialisation de la IDT : ","OK");

  Initialisation_8259A();
  Affiche_Message(">>>Initialisation du PIC 8259A : ","OK");

  Initialisation_8253(1193);
  Affiche_Message(">>>Initialisation du controleur 8253 : ","OK");
  //

    AUTORISE_INTERRUPTION;
//---------------------------------------------------------------------------- 


//   while(1) {
//        Affiche_Chaine(Entier_Vers_Chaine(Donne_Nombres_Tics()));
//        Affiche_Caractere('\n');
//        Attendre_ms(5000);  
//   }
  
    Thread_Actif=Thread_1;
  
    while(1){
        Thread_Actif();
    }
}





