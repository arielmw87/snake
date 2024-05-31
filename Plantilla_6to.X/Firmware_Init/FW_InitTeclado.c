/*********************************************************************************************************
*                                                Teclado
*               			Módulo encargado del manejo del teclado
*
*						<Copyright>
*
*						<Copyright or distribution terms>
*
*
*********************************************************************************************************/

/*********************************************************************************************************
*                                               <File description>
*
* Filename	: FW_InitTeclado.c
* Version	: 1.0.0					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s):  Para poder usarla debe llamar llamar a la función void tic_teclado(void); en la interrupción 
*  del timer configutrado a 1mS.
*
*
*
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		FW_InitTeclado.c
 * \brief		Módulo encargado del manejo del teclado, contiene los drivers necesarios
 *              para inicializar el Teclado
 * \date		13 de junio de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/

#include "FW_Teclado.h"

/*********************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
*********************************************************************************************************/
volatile uint8_t TDO_fila = TDO_NO_FILA; 
volatile uint8_t TDO_col  = TDO_NO_COL;// Aquí guardará indice de matriz
volatile uint8_t TDO_flag_kb = 0;
volatile uint8_t TDO_delay_kb     = 0;// Modificadas por hardware (interrupciones)
/*********************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
*********************************************************************************************************/


#if SHIELD_ACTIVO == __SHIELD2

/** \fn         void TDO_Init(void)
 *	\brief      Inicializa el puerto y las interrupciones
 *  \details    La siguiente funcion inicializa el puerto y las interrupciones.           *
 *              Para incorporar el teclado al puerto B debe de llamarse luego de:                                               *
 *              Kit_Init() y Tmr0_Init() IMPORTANTE!! esta función solamente 
 *              funciona con el Shield 1.3 y no debe de ser tenida en cuenta 
 *              para otros micros o placas
 *	\author     Esteban Lemos
 *	\date 
*/
void TDO_Init(void)
{
    LATB    = 0;                               //Borrado de latches
    PORTB   = 0;                              //borrado del puerto
    TRISB   = 0xF0;                           //RB7_4 entradas , RB3_0 salidas
    RBPU    = 0;                               //PULLUPs habilitados
    RBIP    = 1;                               //Prioridad alta  
    RBIF    = 0;                               //Flag de interrupción borrado
    RBIE    = 1;                               //interrupción de Puerto B ON
}

#endif
