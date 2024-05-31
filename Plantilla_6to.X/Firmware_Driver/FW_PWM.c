/**********************************************************************************************************
*                                               PWM
*                                           Manejo de PWM
*
*						<Copyright>
*
*						<Copyright or distribution terms>
*
*
*********************************************************************************************************/

/*********************************************************************************************************
*                                               FW_PWM.c
*
* Filename	: FW_PWM.c
* Version	: 1.0.0					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s):
*
*
*
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		FW_PWM.c
 * \brief		Manejo de PWM
 * \date		1 de octubre de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/

#include <xc.h>
#include "PWM.h"

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

/*********************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
*********************************************************************************************************/
uint16_t PWM_MedioPeriodoSet  = 0;
uint8_t  PWM_UpperByte        = 0xFF;
uint8_t  PWM_LowerByte        = 0x00;
uint8_t  PWM_OffsetPeriodo    = 32;
uint8_t  PWM_Multiplicador    = 0;
uint8_t  PWM_MultiplicadorSet = 0;
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
	\fn  		void PWM_CalcFrec(void)
	\brief 		
                 
 	\author 	Nombre
 	\date 		${date}
 	\param [in] 	periodo
 *  \param [in] 	duty
 	\param [out] 	void
*/
void PWM_CalcFrec(void)
{
    if(PWM_Frecuencia > 100)
    {
        PWM_MultiplicadorSet = 0;
        PWM_MedioPeriodoSet  = (2000000 / PWM_Frecuencia);
        PWM_MedioPeriodoSet  = (PWM_MedioPeriodoSet - PWM_OffsetPeriodo) * 3;
     }
    /*preescaler *************************************************************/
    else if(PWM_Frecuencia <= 100 && PWM_Frecuencia > 60 )
    {
        PWM_MultiplicadorSet = 0;
        T1CONbits.T1CKPS = 1;   //Preescaler en 2
        PWM_MedioPeriodoSet  =( 1000000 / PWM_Frecuencia);
        PWM_MedioPeriodoSet  = (PWM_MedioPeriodoSet - PWM_OffsetPeriodo) * 3;
      
    }
    else if(PWM_Frecuencia <= 60 && PWM_Frecuencia > 30)
    {
        PWM_MultiplicadorSet  = 0;
        T1CONbits.T1CKPS0 = 0;   //Preescaler en 4
        T1CONbits.T1CKPS1 = 1;   //Preescaler en 4
        PWM_MedioPeriodoSet   = (500000 / PWM_Frecuencia - PWM_OffsetPeriodo) * 3;
              
    }
    else if(PWM_Frecuencia <= 30 && PWM_Frecuencia > 20){
        PWM_MultiplicadorSet  = 0;
        T1CONbits.T1CKPS0 = 1;   //Preescaler en 8
        T1CONbits.T1CKPS1 = 1;   //Preescaler en 8
        PWM_MedioPeriodoSet   = (250000 / PWM_Frecuencia - PWM_OffsetPeriodo) *3;
               
    }
    else if(PWM_Frecuencia <= 20)
    {
        PWM_MultiplicadorSet  = 12;
        T1CONbits.T1CKPS0 = 1;   //Preescaler en 8
        T1CONbits.T1CKPS1 = 1;   //Preescaler en 8
        PWM_MedioPeriodoSet   = (62500 / PWM_Frecuencia - PWM_OffsetPeriodo);
   
    }
    
    PWM_MedioPeriodoSet       = 65535 - PWM_MedioPeriodoSet;
    PWM_UpperByte             = (uint8_t)(PWM_MedioPeriodoSet >> 8);
    PWM_LowerByte             = (uint8_t) PWM_MedioPeriodoSet;
}
