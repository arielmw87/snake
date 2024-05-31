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
* Filename	: FW_Teclado.c
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
 * \file		FW_Teclado.c
 * \brief		Módulo encargado del manejo del teclado, contiene los drivers necesarios
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
extern volatile uint8_t TDO_fila; 
extern volatile uint8_t TDO_col;// Aquí guardará indice de matriz
extern volatile uint8_t TDO_flag_kb;
extern volatile uint8_t TDO_delay_kb;// Modificadas por hardware (interrupciones)
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

/** \fn         void TCDO_MarcaTecla (void)
 *  \details    Funcion para uso de teclado la misma se incluye en la interrupción      
 *              de teclado. La misma pone un estado alto el flag que indica el 
 *              evento de teclado para otros micros o placas
 *	\author     Esteban Lemos
 *	\date 
*/
void TDO_MarcaTecla (void)			// Usada para indicar que se presionó tecla
{
    (void) PORTB;            //Lee el puerto pero no efectua ninguna acción
    asm( "NOP");
    asm ("NOP");//Espera un ciclo sin hacer nada
	TDO_flag_kb = TDO_TRUE;         //Guarda el evento en el flag
    asm ("NOP");
    asm ("NOP");//Espera un ciclo sin hacer nada    
}

/** \fn         void TDO_Tic (void);
 *  \details    Función para el tratamiento del rebote se incluye en la interrupción     
 *              del timer , que deberá estar configurado en 1ms un milisegundo.
 *              La misma decrementa una variable que se encarga de definir los 
 *              tiempos de estabilidad y así evitar el rebote.
 *	\author     Esteban Lemos
 *	\date 
*/

 void TDO_Tic (void)		// Para producir demora, debe llamarse  x int de timer cada 1mS
 {
     if (TDO_delay_kb) TDO_delay_kb--;
 }
 
 /** \fn        void TDO_LittleDelay (void)
 *  \brief      demora breve
 *	\author     Esteban Lemos
 *	\date 
*/

 void TDO_LittleDelay (void)
 {
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
 }
 
 
#endif
