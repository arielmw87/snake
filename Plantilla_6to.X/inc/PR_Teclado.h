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
* Filename	: PR_Teclado.h
* Version	: 1.0.0					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s):  Definiciones del hardware según conexión del teclado, las FILAS 
*  (deben estar inicializadas como entradas en el MCU. Deben de ser lineas con 
*  interrupción externa disponible
*
*
*
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		PR_Teclado.h
 * \brief		Módulo encargado del manejo del teclado, contiene las primitivas necesarios
 * \date		13 de junio de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** MODULO
*********************************************************************************************************/

#ifndef PR_TECLADO_H
#define PR_TECLADO_H

/*********************************************************************************************************
 *** INCLUDES GLOBALES
*********************************************************************************************************/

#include <xc.h>
#include "Tdatos.h"
#include "BaseBoard.h"

/*********************************************************************************************************
 *** DEFINES GLOBALES
*********************************************************************************************************/

//#define ResASCII		// Si el resultado será binario, comentar esta línea

#define TDO_FILA4	PORTBbits.RB4     //conectar al PIN2 del teclado
#define TDO_FILA3	PORTBbits.RB5     //conectar al PIN7 del teclado
#define TDO_FILA2	PORTBbits.RB6     //conectar al PIN6 del teclado
#define TDO_FILA1	PORTBbits.RB7     //conectar al PIN4 del teclado
// COLUMNAS (deben estar inicializadas como salidas en el MCU)

#define TDO_COL1	TRISBbits.RB3     //conectar al PIN3 del teclado
#define TDO_COL2	TRISBbits.RB2     //conectar al PIN1 del teclado
#define TDO_COL3	TRISBbits.RB1     //conectar al PIN5 del teclado
#define TDO_COL4    TRISBbits.RB0

// Define un valor que devuelve la función si no hay tecla
#define TDO_NO_TECLA		0xFF

// Define el tiempo en mS de antirrebote y espera por liberación del teclado
#define TDO_DLY_DEBOUNCE			30
#define TDO_DLY_RELEASE				50

#define TDO_NO_FILA			0xFF
#define TDO_NO_COL			0xFF

//define valores booleanos para las funciones incorporadas
#define TDO_FALSE 0
#define TDO_TRUE 1

// define el tipo de tabla a utilizar, si quiere la tabla binaria comente esta linea
#define ResASCII 1
/*********************************************************************************************************
 *** MACROS GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** TIPO DE DATOS GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** VARIABLES GLOBALES
*********************************************************************************************************/
extern volatile uint8_t TDO_fila; 
extern volatile uint8_t TDO_col;// Aquí guardará indice de matriz
extern volatile uint8_t TDO_flag_kb;
extern volatile uint8_t TDO_delay_kb;// Modificadas por hardware (interrupciones)

/*********************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
**********************************************************************************************************/

#if SHIELD_ACTIVO == __SHIELD1
/**  
 *  \brief      Debuelve la tecla seleccionada
 *  \details    Función que devuelve una tecla presionada o TDO_NO_TECLA = 0xFF      
 *              si no hay novedad. El dato puede configurarse como binario o 
 *              como ASCII  definiendo o no ResASCII   
 *	\author     Esteban Lemos
 *	\date 
*/
uint8_t TDO_Tecla(void);  

#endif

#endif /* PR_TECLADO_H */