/**********************************************************************************************************
*                                               Encoder Incremental
*						Contiene las librerias necesarias para manejar el encoder
*
*						<Copyright>
*
*						<Copyright or distribution terms>
*
*
*********************************************************************************************************/

/*********************************************************************************************************
*                                               FW_InitEncderIncremental.c
*
* Filename	: FW_InitEncderIncremental.c
* Version	: 1.0.0					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s): Para poder usar esta libreria debe agregar las funciones EDER_Tic() y EDER_Interrupt
* dentro de la interrupció del timer.
 * También debe llamar a la funcion de inicialiación en el main()
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		FW_InitEncderIncremental.c
 * \brief		Breve descripción del objetivo del Módulo
 * \date		1 de octubre de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version
*********************************************************************************************************/


/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/

#include <xc.h>
#include "Tdatos.h"
#include "BaseBoard.h"
#include "EncoderIncremental.h"

#if SHIELD_ACTIVO == __SHIELD1

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
volatile uint8_t EDER_Maximo = 0;
volatile uint8_t EDER_Minimo = 0;

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
	\fn  		void EDER_Init(uint8_t setMAX, uint8_t setMin);
	\brief 		Funcion necesaria para inicializar el encoder, en la misma se define el 
    * rango del encoder
 	\author 	
 	\date 		
 	\param [in]     setMAX    necesario para definir la posicion maxima
    \param [in]     setMin    necesario para definir la posicion minima
 	\param [out] 	void
*/
    void EDER_Init(uint8_t setMAX, uint8_t setMin)
    {
        EDER_Maximo = setMAX;     //define el valor maximo del rango
        EDER_Minimo = setMin;     //define el valor minimo del rango
    
        //Se configura la direccion del puerto, vea las definiciones de hardware
        EDER_SET_ENTRADA_A
        EDER_SET_ENTRADA_B
              
        INTCON2bits.RBPU    = 0;       //en caso de contar con pullUps utilizarlos 
        INTCON2bits.INTEDG0 = 0;    //selecciona el tipo de flanco de la INT0
        INTCON2bits.INTEDG1 = 0;    //selecciona el tipo de flanco de la INT0
        INTCONbits.INT0IF   = 0;      //borra el flag de la INT0
        INTCON3bits.INT1F   = 0;      //borra el flag de la INT1
        INTCONbits.INT0IE   = 1;
        INTCON3bits.INT1IE  = 1;
    }

#endif /* SHIELD_ACTIVO */