#include "type.h"
#include "DELAY.h"

extern UINT32 Compteur_Horloge;
//------------------------------------------------------------------------------
void Attendre_ms(UINT32 P_Duree){
 UINT32 L_Fin =  Compteur_Horloge+P_Duree;

 //   if (L_Fin>Compteur_Horloge) {
        while (Compteur_Horloge<L_Fin) { asm("nop");}
//    } else {
//        while (Compteur_Horloge>L_Fin) { asm("nop");}
//        while (Compteur_Horloge<L_Fin){ asm("nop");}
//    }

}
//------------------------------------------------------------------------------
UINT32 Donne_Nombres_Tics()
{
    return Compteur_Horloge;
}
