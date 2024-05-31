/*********************************************************************************************************
*                                                ADC
*						Contiene las funciones para el manejo del ADC
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
* Filename	: PR_ADC
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
 * \file		ADC
 * \brief		Incluye las definiciones necesarias para el manejo
 *               del ADC
 * \date		12 de septiembre de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/

#include "PR_ADC.h"

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
 *	\fn  		ADC_Obtener8bits
 *	\brief 		Devuelve el valor de la convercion del ADC en 8 bits
 *  \details    Funcion que lee la entrada AN0 y devuelve el valor de la convercion
 *              en 8 bits
 *	\author 	Nombre
 *	\date 		
 *	\param [in] 	
 *	\param [out] 	 resultado de la conversión 
 *	\return uint8_t  resultado de la conversión
*/
uint8_t  ADC_Obtener8bits (void)
{
    uint8_t   guardo_porta, guardo_trisa; 
    
    
    guardo_porta = PORTA;
    guardo_trisa = TRISA;
    
    TRISAbits.RA0=1;        //RA0 se transforma en AN0
    ADCON1 = 0x0E;          //selección de entradas analógicas canal 0 por defecto
    ADCON2 = 0x2D;
    ADCON0bits.ADON=1;
    ADCON0bits.GO=1;        //inicia la conversión
    
    while(ADCON0bits.GO);
    
    ADCON0bits.ADON=0;      //se apaga el conversor
    ADCON1 = 0x0F;
    LATA = guardo_porta;
    TRISA = guardo_trisa;
                    
    return ADRESH;
}


/**
 *  \fn  		ADC_Obtener10bits
 *	\brief 		Devuelve el valor de la convercion del ADC en 10 bits
 *              Funcion que lee la entrada AN0 y devuelve el valor de la convercion
 *              en 10 bits
 *	\author 	Nombre
 *	\date 		
 *	\param [in] 	
 *	\param [out] 	 resultado de la conversión 
 *	\return uint16_t  resultado de la conversión
*/
uint16_t ADC_Obtener10bits (void)
{
    uint8_t   guardo_porta, guardo_trisa; 
    
    
    guardo_porta = PORTA;
    guardo_trisa = TRISA;
    
    TRISAbits.RA0=1;        //RA0 se transforma en AN0
    ADCON1 = 0x0E;          //selección de entradas analógicas canal 0 por defecto
    ADCON2 = 0xAD;
    ADCON0bits.ADON=1;
    ADCON0bits.GO=1;        //inicia la conversión
    
    while(ADCON0bits.GO);
    
    ADCON0bits.ADON=0;      //se apaga el conversor
    ADCON1 = 0x0F;
    LATA = guardo_porta;
    TRISA = guardo_trisa;
                    
    return (ADRESH << 8) + ADRESL;
//  return (ADRESH & 0x03) * 256 + ADRESL   
}
