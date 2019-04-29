/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ecran.h
 * Author: Guillaume
 *
 * Created on 22 mars 2019, 09:26
 */

#ifndef ECRAN_H
#define ECRAN_H

#include "type.h"
#define BLEU 0x01
#define FOND_BLEU 0x10
#define VERT 0x02
#define FOND_VERT 0x20
#define ROUGE 0x04
#define FOND_ROUGE 0x40
#define LUMINEUX 0x08
#define CLIGNOTANT 0x80

#pragma pack(1)
typedef struct { 
    UCHAR Caractere;
    BYTE Attribut;
}T_CARACTERE_ECRAN;
#pragma pack()
//------------------------------------------------------------
extern BYTE* Video;
extern T_CARACTERE_ECRAN* Map_Video; //------------------------------------------------------------
void Efface_Ecran();
void Affiche_Chaine_XY(BYTE P_X, BYTE P_Y, char* P_Chaine);
void Affiche_Chaine_XY_Couleur(BYTE P_X, BYTE P_Y, char* P_Chaine, BYTE P_Attribut);
void Remplir_Ecran(UCHAR P_Caractere, BYTE P_Attribut);
void Defilement_Haut();
void Positionne_Curseur(BYTE P_X, BYTE P_Y);
void Affiche_Caractere(UCHAR P_Caractere);
void Affiche_Chaine(UCHAR* P_Chaine);

#endif /* ECRAN_H */

