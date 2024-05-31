/**********************************************************************************************************
*                                               Teclado
*               			Módulo encargado del manejo del teclado
*
*                                             <Copyright>
*
*                                       <Copyright or distribution terms>
*
*
*********************************************************************************************************/

/*********************************************************************************************************
*                                               <File description>
*
* Filename	: FW_Teclado.h
* Version	: 1.0.0					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s): Para poder usarla debe llamar llamar a la función void TDO_Tic(void); en la interrupción 
*  del timer configutrado a 1mS.
*
*
*
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		FW_Teclado.h
 * \brief		Módulo encargado del manejo del teclado, contiene los drivers necesarios
 * \date		13 de junio de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** MODULO
*********************************************************************************************************/

#ifndef FW_TECLADO_H
#define FW_TECLADO_H

/*********************************************************************************************************
 *** INCLUDES GLOBALES
*********************************************************************************************************/

#include <xc.h>
#include "Tdatos.h"
#include "PR_Teclado.h"
#include "BaseBoard.h"

/*********************************************************************************************************
 *** DEFINES GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** MACROS GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** TIPO DE DATOS GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** VARIABLES GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
**********************************************************************************************************/


#if SHIELD_ACTIVO == __SHIELD1

/** 
 *	\brief      Inicializa el puerto y las interrupciones
 *  \details    La siguiente funcion inicializa el puerto y las interrupciones.           *
 *              Para incorporar el teclado al puerto B debe de llamarse luego de:                                               *
 *              Kit_Init() y Tmr0_Init() IMPORTANTE!! esta función solamente 
 *              funciona con el Shield 1.3 y no debe de ser tenida en cuenta 
 *              para otros micros o placas
 *	\author     Esteban Lemos
 *	\date 
*/
void TDO_Init (void);  
    
/** 
 *  \details    Funcion para uso de teclado la misma se incluye en la interrupción      
 *              de teclado. La misma pone un estado alto el flag que indica el 
 *              evento de teclado para otros micros o placas
 *	\author     Esteban Lemos
 *	\date 
*/
void TDO_MarcaTecla (void);			// Usada para indicar que se presionó tecla


/** 
 *  \details    Función para el tratamiento del rebote se incluye en la interrupción     
 *              del timer , que deberá estar configurado en 1ms un milisegundo.
 *              La misma decrementa una variable que se encarga de definir los 
 *              tiempos de estabilidad y así evitar el rebote.
 *	\author     Esteban Lemos
 *	\date 
*/

 void TDO_Tic (void);		// Para producir demora, debe llamarse 
                           // x int de timer cada 1mS
 
 void TDO_LittleDelay (void);
 
 #endif

#endif /* FW_TECLADO_H */