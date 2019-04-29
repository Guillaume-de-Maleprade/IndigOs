/*
 * File:   OUTILS.h
 * Author: JLV
 * TP EMA OS 2011
 *
 */
#ifndef OUTILS_H
#define	OUTILS_H
#include "Type.h"

 UINT32 Taille_Chaine(UCHAR P_Chaine[]);
 UCHAR* Entier_Vers_Chaine(UINT32 P_Valeur);
 UCHAR* Entier_Vers_Chaine_Hexa(UINT32 P_Valeur, BYTE P_Nombre_Octets);

#endif	/* OUTILS_H */

