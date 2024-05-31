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
*                                              MacTimer.h
*
* Filename	: MacTimer.h
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
 *** MODULO
*********************************************************************************************************/

#ifndef __MACT_TIMER_H
#define __MACT_TIMER_H

/*********************************************************************************************************
 *** INCLUDES GLOBALES
*********************************************************************************************************/
#include "Tdatos.h"

/*********************************************************************************************************
 *** DEFINES GLOBALES
*********************************************************************************************************/

#define             MCTMR_TIMERS	8 // cantidad de temporizadores que necesito
	// --- Eventos
#define			MCTMR_EVENTO0		0	//Evento cada 1 seg
#define			MCTMR_EVENTO1		1	//Evento cada 2 segundo
#define			MCTMR_EVENTO2		2	//Evento cada 3 segundos
#define			MCTMR_EVENTO3		3	//Evento cada 4 segundos
#define			MCTMR_EVENTO4		4	//Evento cada 5 segundos
#define			MCTMR_EVENTO5		5	//Evento cada 6 segundos
#define			MCTMR_EVENTO6		6	//Evento cada 7 segundos
#define			MCTMR_EVENTO7		7	//Evento cada 8 segundos

	// --- Tiempos
#define			MCTMR_T0			1000
#define			MCTMR_T1			2000
#define			MCTMR_T2			3000
#define			MCTMR_T3			4000
#define			MCTMR_T4			5000
#define			MCTMR_T5			6000
#define			MCTMR_T6			7000
#define			MCTMR_T7			8000

/*********************************************************************************************************
 *** MACROS GLOBALES
*********************************************************************************************************/
#define   MCTMR_LIMPIO_BANDERA	MCTMR_Eventos &= ~i
/*********************************************************************************************************
 *** TIPO DE DATOS GLOBALES
*********************************************************************************************************/
extern volatile uint16_t MCTMR_Run[MCTMR_TIMERS];  //!< el tipo de dato lo defino dependiendo el timepo que 
extern volatile uint8_t  MCTMR_Eventos ;                                                  //!< necesite y la base de tiempo propuesta cada posicón 
/*********************************************************************************************************
 *** VARIABLES GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
**********************************************************************************************************/

void MCTMR_Analizar (void); // analiza si vencio algun timer en el MCTMR_Run[] y
// activa un flag en la variable MCTMR_Eventos ( se ve en el main). Esta funsión va en la interrupcion

void MCTMR_Start (uint8_t evento, uint8_t temp); // es para inicializar el timer

void MCTMR_Stop (uint8_t evento); // apaga el timer indicado

void MCTMR_Close (void); // apaga todo los timers

void MCTMR_Event (void); // lo mira el main analiza que timer vencio y hace lo que tenga que hacer
// ante ese evento
#endif /* __MACT_TIMER_H */