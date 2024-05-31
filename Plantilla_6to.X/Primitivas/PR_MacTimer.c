/**********************************************************************************************************
*                                               Maquina de Timer
*                                   Genera retardos por software
*
*						<Copyright>
*
*						<Copyright or distribution terms>
*
*
*********************************************************************************************************/
/*********************************************************************************************************
*                                              PR_MacTimer.c
*
* Filename	: PR_MacTimer.c
* Version	: 1.0.0					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s): /*TODAS LAS FUNNCIONES ESTAN PENSADAS PARA UN TIMER DE 8 EVENTOS SI SE NECESITAN MAS
MODIFICAR LAS VARIABLES DE CADA FUNCION PARA QUE PUEDAN SER DE 16 O 32; ESTAS VARIABLES
SON Evento, LOS INDICES PARA RECORRER LOS ARRAYS 
*
 * Deve llamar a la función MCTMR_Analizar en la interrupcion
 * 
* definir un array llamado "MCTMR_Run[TIMERS]", el tipo de dato lo defino
* dependiendo el timepo que necesite y la base de tiempo propuesta cada posicón
* contiene el valor a decrementar que se multiplica por la base de tiempo utilizada
*===========================================
*="inicializar todo el buffer MCTMR_Run en 0"=
*===========================================
*"MCTMR_Eventos" es una variable que se ve en el main y contiene los flags de los timers vencidos
 * 
 * Use la funcion MCTMR_Event() en si aplicación
*
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		MacTimer.h
 * \brief		Genera retardos por software
 * \date		1 de octubre de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/

#include <xc.h>
#include "MacTimer.h"
#include "BaseBoard.h"

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
volatile uint16_t MCTMR_Run[MCTMR_TIMERS];  //!< el tipo de dato lo defino dependiendo el timepo que 
volatile uint8_t  MCTMR_Eventos = 0 ;                                               //!< necesite y la base de tiempo propuesta cada posicón 
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
	\fn  		void MCTMR_Analizar (void);
	\brief 		Descuento de Timers. No es una primitiva. Es una función de la capa inferior.
				La ubico en este .c para tener todas las funciones de timers juntas.
 	\author 	Nicolás Ferragamo
 	\date 		1 de octubre de 2019
 	\param [in] 	void
 	\param [out] 	void
*/
void MCTMR_Analizar (void)
{
    uint8_t i;
	for(i=0; i < MCTMR_TIMERS ; i++)
    {
		if(MCTMR_Run[i])
		{
			MCTMR_Run[i] --;
			if(!MCTMR_Run[i])
			{
				MCTMR_Eventos |= (0x0001 << i);
			}
		}
    }
}


/**
	\fn  		void MCTMR_Start (uint8_t evento, uint8_t temp);
	\brief 		Lanzamientos de Timers.
 	\author 	Nicolás Ferragamo
 	\date 		1 de octubre de 2019
 	\param [in] 	numero de evento
    \param [in] 	valor del timer
 	\param [out] 	void
*/
void MCTMR_Start (uint8_t evento, uint8_t tiempo)
{
    INTCONbits.TMR0IE     = OFF;
	if(tiempo)
	{
		MCTMR_Run[evento] = tiempo; // cargo el timer
		MCTMR_Eventos    &= ~(0x01 << evento); // reseteo el flag
	}
	else // si mande 0 quiere decir que quise vencer el timer antes
	{
		MCTMR_Run[evento] = tiempo; // cargo el timrer
		MCTMR_Eventos    |= (0x01 << evento);// activo el flag
	}

	INTCONbits.TMR0IE     = ON;
}

/**
	\fn  		void MCTMR_Close (void);
	\brief 		Apaga todo los timers
 	\author 	Nicolás Ferragamo
 	\date 		1 de octubre de 2019
 	\param [in] 	void
 	\param [out] 	void
*/
void MCTMR_Close (void)
{
    uint8_t i;
	INTCONbits.TMR0IE = OFF;
	for (i=0 ; i < MCTMR_TIMERS ;  i++)
    {
        MCTMR_Run[i] = 0;
    }	
  	MCTMR_Eventos = 0;
  	INTCONbits.TMR0IE = ON;
} 
/**
	\fnMCTMR_  		void MCTMR_Stop (uint8_t evento)
	\brief 		Aapaga el timer indicado
 	\author 	Nicolás Ferragamo
 	\date 		1 de octubre de 2019
 	\param [in] 	numero de evento
 	\param [out] 	void
*/
void MCTMR_Stop (uint8_t evento)
{
    INTCONbits.TMR0IE = OFF;
    MCTMR_Run[evento]     = 0;
  	MCTMR_Eventos    &= ~((uint8_t) 0x01 << evento);
    INTCONbits.TMR0IE = ON;
}

/**
	\fn  		void MCTMR_Event (void)
	\brief 		Analiza Eventos de timers. No es una primitiva. Es parte o toda la aplicación
				La ubico en este .c para tener todas las funciones de timers juntas.
 	\author 	Nicolás Ferragamo
 	\date 		1 de octubre de 2019
 	\param [in] 	void
 	\param [out] 	void
*/
void MCTMR_Event (void)
{
    uint8_t i;
	for(i=0x01; i ; i <<=1)// recorro la variable i mintras sea distinta de 0
	{
		switch(MCTMR_Eventos & i)
		{
		case 0x01:
			MCTMR_LIMPIO_BANDERA ;
			// hago lo aplaicacion cuando vensa el timer
			break;

		case 0x02:
			MCTMR_LIMPIO_BANDERA ;
			// hago lo aplaicacion cuando vensa el timer
			break;

		case 0x04:
			MCTMR_LIMPIO_BANDERA ;
			// hago lo aplaicacion cuando vensa el timer
			break;

		case 0x08:
			MCTMR_LIMPIO_BANDERA ;
			// hago lo aplaicacion cuando vensa el timer
			break;

		case 0x010:
			MCTMR_LIMPIO_BANDERA ;
			// hago lo aplaicacion cuando vensa el timer
			break;

		case 0x020:
			MCTMR_LIMPIO_BANDERA ;
			// hago lo aplaicacion cuando vensa el timer
			break;
		case 0x040:
			MCTMR_LIMPIO_BANDERA ;
			// hago lo aplaicacion cuando vensa el timer
			break;
		case 0x080:
			MCTMR_LIMPIO_BANDERA ;
			// hago lo aplaicacion cuando vensa el timer
			break;
		}
	}
}