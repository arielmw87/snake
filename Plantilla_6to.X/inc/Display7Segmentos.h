/**********************************************************************************************************
*                                               Display 7 Segmentos
*                                       Manejo del display 7 segmentos 
*
*                                        <Copyright>
*
*                           <Copyright or distribution terms>
*
*
*********************************************************************************************************/

/*********************************************************************************************************
*                                               Display7Segmentos.h
*
* Filename	: Display7Segmentos.h
* Version	: 1.0.0					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s): Para poder usar este módulo debe llamar a la función DP_BarridoDisplay (); dentro de 
*  Aplicacion() y llamar a la función DP_Tic() dentro de la interrupcion
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		Display7Segmentos.h
 * \brief		Módulo para el manejo de los display 7 segmentos
 * \date		30 de septiembre de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** MODULO
*********************************************************************************************************/

#ifndef __DISPLAY_7_SEGMENTOS_H
#define __DISPLAY_7_SEGMENTOS_H

/*********************************************************************************************************
 *** INCLUDES GLOBALES
*********************************************************************************************************/
#include "Tdatos.h"
#include "BaseBoard.h"

#if SHIELD_ACTIVO == __SHIELD1
/*********************************************************************************************************
 *** DEFINES GLOBALES
*********************************************************************************************************/
#define 	DP_DIGITOS		4  //!< Números de diplays
#define     DP_TIC          5  //!< Demora del barrido

#define DP_DISP4   LATAbits.LA4
#define DP_DISP3   LATAbits.LA5
#define DP_DISP2   LATEbits.LE0
#define DP_DISP1   LATEbits.LE1


#define DP_SEGMENTOA LATAbits.LA0
#define DP_SEGMENTOB LATAbits.LA1
#define DP_SEGMENTOC LATAbits.LA2
#define DP_SEGMENTOD LATAbits.LA3
#define DP_DOT       LATEbits.LE2

/*********************************************************************************************************
 *** MACROS GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** TIPO DE DATOS GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** VARIABLES GLOBALES

*********************************************************************************************************/
extern volatile uint8_t DP_msgDisplay[DP_DIGITOS];			
extern volatile uint8_t DP_Delay;
/*********************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
**********************************************************************************************************/


/**
	\fn  		void DP_BarridoDisplay (void);
	\brief 		Realiza el barrido de los displays
 	\author 	Nicolás Exequiel Ferragamo
 	\date 		30 de septiembre de 2019
 	\param [in] 	void
 	\param [out] 	void
*/
void DP_BarridoDisplay (void);

/**
	\fn  		void DP_Display_bcd (uint16_t, uint8_t);
	\brief 		Se encarga de descomponer el número y enviarlo a cada display
 	\author 	Nicolás Exequiel Ferragamo
 	\date 		30 de septiembre de 2019
 	\param [in]     valor a mostrar en los displays
    \param [in]     Número de display
 	\param [out] 	void
*/
void DP_DisplayBCD(uint16_t valor, uint8_t dsp);


/**
	\fn  		void DP_Tic(void);
	\brief 		Se encarga de la demora del barrido
 	\author 	Nicolás Exequiel Ferragamo
 	\date 		30 de septiembre de 2019
 	\param [in]     void
 	\param [out] 	void
*/
void DP_Tic(void);

#endif

#endif /* __DISPLAY_7_SEGMENTOS_H */ 
