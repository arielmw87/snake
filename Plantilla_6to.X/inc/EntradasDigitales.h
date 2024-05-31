/**********************************************************************************************************
*                                               Entradas Digitales
*						Contiene las funciones para manejar entradas digitales
*
*						<Copyright>
*
*						<Copyright or distribution terms>
*
*
*********************************************************************************************************/

/*********************************************************************************************************
*                                                Entradas Digitales
*
* Filename	: EntradasDigitales.h
* Version	: 1.0.0					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s): Para poder usar llamar a la fucnión ED_Tic(); en la interrupción y a ED_Debounce();
*   dentro de aplicacion();
*   Incluír el archivo EntradasDigitaes.h en el archivo FW_Interrupt.c y en cualquier archivo que use 
*   ED_TECLA*
* 
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		EntradasDigitales.h
 * \brief		Contiene las funciones para manejar entradas digitales
 * \date		30 de septiembre de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** MODULO
*********************************************************************************************************/

#ifndef ENTRADAS_DIGITALES_H
#define ENTRADAS_DIGITALES_H


/*********************************************************************************************************
 *** INCLUDES GLOBALES
*********************************************************************************************************/
#include"Tdatos.h"
#include "BaseBoard.h"


/*********************************************************************************************************
 *** DEFINES GLOBALES
*********************************************************************************************************/

#define		ED_ACEPTAR_ESTADO	10  //!< cantidad de veces que deve contar para validar el estado 
#define		ED_ENTRADAS         4   //!< cantidad de entradas 
#define     ED_TIC              1

/*********************************************************************************************************
 *** MACROS GLOBALES
*********************************************************************************************************/
#define		ED_TECLA0  (uint8_t)((ED_BufferEntradas) & 0x01)        //!< macros para las teclas de entrada 
#define		ED_TECLA1  (uint8_t)((ED_BufferEntradas >> 1) & 0x01)   //!< macros para las teclas de entrada 
#define		ED_TECLA2  (uint8_t)((ED_BufferEntradas >> 2) & 0x01)   //!< macros para las teclas de entrada 
#define		ED_TECLA3  (uint8_t)((ED_BufferEntradas >> 3) & 0x01)   //!< macros para las teclas de entrada 

/*********************************************************************************************************
 *** TIPO DE DATOS GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** VARIABLES GLOBALES 
*********************************************************************************************************/
extern volatile uint8_t ED_BufferEntradas;
extern volatile uint8_t ED_Delay;
/*********************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
*********************************************************************************************************/

/**
	\fn         void ED_CuentaPulsos(void);
	\brief      Funcion primitiva de entradas digitales 
 	\author     Nicolas Ferragamo
 	\date       30 de septiembre de 2019
 	\param      [in] void
 	\param      [out] void
	\return     void
*/

void ED_CuentaPulsos(void);


/**
	\fn         void ED_Debounce(void)
	\brief      Funcion para el debounce de las entradas digitales 
 	\author     Nicolas Ferragamo
 	\date       30 de septiembre de 2019
 	\param      [in] void
 	\param      [out] void
	\return     void
*/
void ED_Debounce(void);

/**
	\fn         void ED_Tic(void)
	\brief      Funcion para el debounce de las entradas digitales 
 	\author     Nicolas Ferragamo
 	\date       30 de septiembre de 2019
 	\param      [in] void
 	\param      [out] void
	\return     void
*/
void ED_Tic(void);



#endif /* ENTRADAS_DIGITALES_H */





