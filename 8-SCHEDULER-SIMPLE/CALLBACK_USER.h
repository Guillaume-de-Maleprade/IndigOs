/* 
 * File:   CALLBACK_USER.h
 * Author: Administrateur
 *
 * Created on 5 mai 2014, 16:03
 */

#ifndef CALLBACK_USER_H
#define	CALLBACK_USER_H
#include "type.h"


#define NOMBRE_MAX_CALLBACK_USER 25

typedef void (*T_FUNCTION_USER_CALLBACK)(void);

 
 typedef struct  {
   T_FUNCTION_USER_CALLBACK  La_Fonction;
   UINT32 Periode;
   UINT32 Temps_Enclenchement;
}T_USER_CALLBACK;

extern T_USER_CALLBACK User_Callback[NOMBRE_MAX_CALLBACK_USER];
 
#endif	/* CALLBACK_USER_H */

