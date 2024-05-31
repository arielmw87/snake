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
* Filename	: PR_EntradasDigitales.c
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
 * \file		PR_EntradasDigitales
 * \brief		Contiene las funciones para manejar entradas digitales
 * \date		30 de septiembre de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/

#include <xc.h>
#include "Tdatos.h"
#include "BaseBoard.h"
#include "EntradasDigitales.h"

/*********************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODUL
*********************************************************************************************************/

/*********************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 *   se escriben en CamelCase y estan precedidas por la identificación del 
 *   módulo segida de un _ 
 *   ej: MEM_POOL  Mem_PoolHeap; 
*********************************************************************************************************/
volatile uint8_t ED_BufferEntradas = 0 ;  //!< aca por cada bit me indica el estado de una tecla
        
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


/**
	\fn         void ED_CuentaPulsos(void);
	\brief      Funcion primitiva de entradas digitales 
 	\author     Nicolas Ferragamo
 	\date       30 de septiembre de 2019
 	\param      [in] void
 	\param      [out] void
	\return     void
*/
void ED_CuentaPulsos(void)
{
    static uint8_t antkey0 = 0; 
    static uint8_t antkey1 = 0;
    static uint8_t antkey2 = 0;
    static uint8_t antkey3 = 0;
    
	if(ED_TECLA0 && !antkey0)
	{
		antkey0 =! antkey0;
		// hago lo que tenga que hacer
	}
	else if(!ED_TECLA0 && antkey0)
	{
		antkey0 =! antkey0;
	}

	if(ED_TECLA1 && !antkey1)
	{
		antkey1 =! antkey1;
		// hago lo que tenga que hacer
	}
	else if(!ED_TECLA1 && antkey1)
	{
		antkey1 =! antkey1;
	}

	if(ED_TECLA2 && !antkey2)
	{
		antkey2 =! antkey2;
		// hago lo que tenga que hacer
	}
	else if(!ED_TECLA2 && antkey2)
	{
		antkey2 =! antkey2;
	}
    
    if(ED_TECLA3 && !antkey3)
	{
		antkey3 =! antkey3;
		// hago lo que tenga que hacer
	}
	else if(!ED_TECLA3 && antkey3)
	{
		antkey3 =! antkey3;
	}

}

