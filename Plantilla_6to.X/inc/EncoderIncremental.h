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
*                                               EncoderIncremental.h
*
* Filename	: EncoderIncremental.h
* Version	: 1.0.0					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s): Para poder usar esta libreria debe agregar las funciones EDER_Tic() y EDER_Interrupt
* dentro de la interrupció del timer.
 * También debe llamar a la funcion de inicialiación en el main()
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		EncoderIncremental.h
 * \brief		Breve descripción del objetivo del Módulo
 * \date		1 de octubre de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version
*********************************************************************************************************/

/*********************************************************************************************************
 *** MODULO
*********************************************************************************************************/

#ifndef __ENCODER_INCLREMENTAL_H
#define __ENCODER_INCLREMENTAL_H

/*********************************************************************************************************
 *** INCLUDES GLOBALES
*********************************************************************************************************/
#include "Tdatos.h"
#include "BaseBoard.h"

#if SHIELD_ACTIVO == __SHIELD1
/*********************************************************************************************************
 *** DEFINES GLOBALES
*********************************************************************************************************/
//Definiciones de Hardware cambiar si es necesario
    #define EDER_CANALA            PORTBbits.RB0
    #define EDER_CANALB            PORTBbits.RB1
    #define EDER_DELAY             30


/*********************************************************************************************************
 *** MACROS GLOBALES
*********************************************************************************************************/
    #define EDER_SET_ENTRADA_A     TRISBbits.RB0 = ENTRADA;
    #define EDER_SET_ENTRADA_B     TRISBbits.RB1 = ENTRADA;
/*********************************************************************************************************
 *** TIPO DE DATOS GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** VARIABLES GLOBALES
*********************************************************************************************************/
extern volatile uint8_t EDER_Maximo;
extern volatile uint8_t EDER_Minimo;
extern volatile uint8_t EDER_Delay;
extern volatile uint8_t EDER_Posicion;
extern volatile uint8_t EDER_FlagCanal;

/*********************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
**********************************************************************************************************/
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
    void EDER_Init(uint8_t setMAX, uint8_t setMin);
    
    
     /**
	\fn  		uint8_t EDER_GetPos(void);
	\brief 		Llamando a esta funcion se obtiene un numero entre el valor MAX y el min
 	\author 	
 	\date 		
 	\param [in]     void   
 	\param [out]   posicion_encoder
    \retunr        uint8_t
*/
    uint8_t EDER_GetPos(void);
    
    
    /**
	\fn  		void EDER_PutPos(unsigned char posicion);
	\brief 		Llamando a esta funcion se inicializa la posicion del encoder 
 	\author 	
 	\date 		
 	\param [in]    posicion  indica que posicion tiene el encoder fisicamente   
 	\param [out]   void
    */
    void EDER_PutPos(unsigned char posicion);
     
 
     
      /**
	\fn  		void EDER_Interrup(void);
	\brief 		Esta función lee el valor del encoder 
 	\author 	
 	\date 		
 	\param [in]    void   
 	\param [out]   void
    */

    void EDER_Interrupt(void);

     /**
	\fn  		void EDER_Tic(void);
	\brief 		Se encarga de la demora 
 	\author 	
 	\date 		
 	\param [in]    void
 	\param [out]   void
    */
    void EDER_Tic(void);
    
#endif /* SHIELD_ACTIVO */


#endif /* __ENCODER_INCLREMENTAL_H */
