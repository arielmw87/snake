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
* Filename	: FW_EntradasDigitales.c
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
 * \file		FW_EntradasDigitales
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
 volatile uint8_t  ED_Delay = ED_TIC;
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
	\fn         void ED_Debounce(void)
	\brief      Funcion para el debounce de las entradas digitales 
 	\author     Nicolas Ferragamo
 	\date       30 de septiembre de 2019
 	\param      [in] void
 	\param      [out] void
	\return     void
*/

void ED_Debounce (void)
{
    uint8_t cambios = 0, j = 0;
    // cambios me avisa si hay algun cambio, esto indica que hay alguna tecla presionada
    // en J se guarda el estado de cada tecla, 1 bit por cada tecla
    static uint8_t contador_estados[ED_ENTRADAS];
    // aca se guarda el estado de la cuenta para validar la tecla

    j = !BOT1; 
    j |= (uint8_t) (!BOT2 << (0x01));
    j |= (uint8_t) (!BOT3 << (0x02));
    j |= (uint8_t) (!BOT4 << (0x03));
     
    cambios = ED_BufferEntradas ^ j ; // en cambios queda bit por bit los cambios registrados
    // correspondentes a cada tecla precionada;

    if(cambios)
        {
        for(j=0; j < ED_ENTRADAS; j++)
        {
            if(cambios & (0x01) << j)
            {
                contador_estados[j]++; 
                if(contador_estados[j]== ED_ACEPTAR_ESTADO)
                {
                    ED_BufferEntradas ^= (0x01 << j);
                   	contador_estados[j] = 0;
                }
            }
            else
                contador_estados[j] = 0;
        }   
     }
     else
     {

        for(j=0; j < ED_ENTRADAS; j++)
        {
          	contador_estados[j] = 0;
        }
    }
}


/**
	\fn         void ED_Tic(void)
	\brief      Funcion para el debounce de las entradas digitales 
 	\author     Nicolas Ferragamo
 	\date       30 de septiembre de 2019
 	\param      [in] void
 	\param      [out] void
	\return     void
*/
void ED_Tic (void)
{
    if(ED_Delay)
    {
        ED_Delay--;
    }
    else
    {   
        ED_Delay = ED_TIC;
        ED_Debounce ();
    }
}

