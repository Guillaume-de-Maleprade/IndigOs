
#include "CALLBACK_USER.h"

UINT32 Nombre_Fonction_Callback;

extern UINT32 Compteur_Horloge;



//..............................................................................
T_USER_CALLBACK User_Callback[NOMBRE_MAX_CALLBACK_USER];


//..............................................................................

void Init_User_Callback() {
    UINT16 L_Index;
    for (L_Index = 0; L_Index < NOMBRE_MAX_CALLBACK_USER; L_Index++) {
        User_Callback[L_Index].La_Fonction = 0;
        User_Callback[L_Index].Temps_Enclenchement = 0;
    }
    Nombre_Fonction_Callback = 0;
}

//------------------------------------------------------------------------------

UINT32 Ajoute_User_Callback(T_FUNCTION_USER_CALLBACK P_Fonction, UINT32 P_Temps) {
    User_Callback[Nombre_Fonction_Callback].La_Fonction = P_Fonction;
    User_Callback[Nombre_Fonction_Callback].Temps_Enclenchement = P_Temps + Compteur_Horloge;
    User_Callback[Nombre_Fonction_Callback].Periode = P_Temps;

    Nombre_Fonction_Callback++;
    return Nombre_Fonction_Callback;
}

