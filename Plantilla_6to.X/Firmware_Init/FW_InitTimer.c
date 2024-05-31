/****************************************************************************************************
 *
 * \file		FW_Timer.c
 * \brief		Contiene el prototipo de inicializacion de los Timers
 * \date		22 de abri de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
****************************************************************************************************/

/****************************************************************************************************
 *** INCLUDES
****************************************************************************************************/

#include "FW_InitTimer.h"
#include <xc.h>
#include "Tdatos.h"
#include "BaseBoard.h"

/****************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
****************************************************************************************************/

/****************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
****************************************************************************************************/

/****************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODUL
****************************************************************************************************/

/****************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
****************************************************************************************************/

/****************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
****************************************************************************************************/

/****************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
****************************************************************************************************/

/****************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
****************************************************************************************************/

/****************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
****************************************************************************************************/

/****************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
****************************************************************************************************/

/**
 *	\fn         Tmr0_Init
 *	\brief      Inicializacion del Tmr0
 *  \details    Inicializa el timer 0 en 8 bits, con el prescaler en 256 y con 
 *              la interrupcion activada. Esta configurado para que interrumpa
 *              cada 1.0022ms
 *  \author I   Esteban Lemos
 *	\date  
 *	\param      [in]  void
 *  \param      [out] void
 *	\return           void
*/
void Tmr0_Init(void)
{
    T0CONbits.TMR0ON  = OFF;      /* apago el timer */
    T0CONbits.T08BIT  = 1;      /* selecciono el timer en 8 bits */
    T0CONbits.T0CS    = 0;      /* el timer cuenta fosc/4 */
    T0CONbits.PSA     = 0;      /* habilito el preescaler */
    T0CONbits.T0PS0   = 1;      /* cargo el preescaler con 256 */ 
    T0CONbits.T0PS1   = 1;
    T0CONbits.T0PS2   = 1;
    TMR0H             = 0xFF;   /* en total aprox 1.0022ms  casi 1ms */
    TMR0L             = 209;    /* el timer contará 47 fosc/4 * 256 = 12032 * 0,0833us */
    INTCONbits.TMR0IE = ON;      /* Habilita la interrupción de timer 0 */
    T0CONbits.TMR0ON  = ON;      /* Enciendo el timer */
}

/**
 *	\fn         Tmr1_Init
 *	\brief      Inicializacion del Tmr1
 *  \details    Inicializa el timer 0 en 8 bits, con el prescaler en 256 y con 
 *              la interrupcion activada. Esta configurado para que interrumpa
 *              cada 99,96 uS
 *  \author I   Esteban Lemos
 *	\date  
 *	\param      [in]  void
 *  \param      [out] void
 *	\return           void
*/
void Tmr1_Init(void)
{
    T1CONbits.TMR1ON  = OFF;     /*apago el timer */
    T1CONbits.TMR1CS  = 0;     /*el timer cuenta fosc/4 */
    T1CONbits.nT1SYNC = 1;     /*Timer no sincronizado en forma externa */
    T1CONbits.T1OSCEN = 0;     /*T1OS shut off */
    T1CONbits.T1CKPS  = 0;     /*Preescaler en 1 */
    T1CONbits.RD16    = 0;     /*LEctura en dos pasos de 8 bits */
    T1CONbits.T1RUN   = 0;     /*Reloj interno del micro desde otra fuente */
    TMR1L             = 0x4F;  /*el timer contará 1200 fosc/4 * 1 = 12032 * 0,0833us */
    TMR1H	          = 0xFB;  /*en total aprox 99.96us  casi 100us */
    PIR1bits.TMR1IF   = 0;     /*flag de interrupción borrado */
    PIE1bits.TMR1IE   = ON;     /*interrupción de timer 1 habilitada */
    INTCONbits.PEIE   = ON;     /*Interrupciones de perifericos habilitadas */
    T1CONbits.TMR1ON  = ON;     /*apago el timer */
    
}
