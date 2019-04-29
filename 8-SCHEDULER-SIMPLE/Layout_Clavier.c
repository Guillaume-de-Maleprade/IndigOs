
#include "Ecran.h"


#define NOMBRE_TOUCHES_CLAVIER 128
int Layout[NOMBRE_TOUCHES_CLAVIER];

void Init_Layout_Clavier() {
    int L_Index = 0;
    for (L_Index = 16; L_Index < 28; L_Index++) {
        Layout[L_Index] = "azertyuiop^$"[L_Index - 16];
        Affiche_Caractere(Layout[L_Index]);
    }



}

int Translate(int P_Scan_Code) {
    if ((P_Scan_Code > 15) && (P_Scan_Code < 28)) return Layout[P_Scan_Code];
    else return 0;
}


//==============================================================================

int Lecture_ASCII() {
    int L_Touche = Attendre_Touche_Relache();
    if ((L_Touche > 15) && (L_Touche < 28)) return Layout[L_Touche];
    else return 0;

}
