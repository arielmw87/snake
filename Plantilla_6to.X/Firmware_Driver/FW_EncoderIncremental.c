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
*                                               FW_EncderIncremental.c
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
#include "Display7Segmentos.h"

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
volatile uint8_t EDER_Delay = EDER_DELAY;
volatile uint8_t EDER_FlagCanal = 0;

/*********************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
*********************************************************************************************************/
static void EDER_Incrementar(void){
    
    if (EDER_Posicion < EDER_Maximo) 
    {
        EDER_Posicion++;
    }
    else
    {
        EDER_Posicion = EDER_Minimo;     
    }
}
  
static void EDER_Decrementar(void){
    
        if (EDER_Posicion > EDER_Minimo)
        {
            EDER_Posicion--;
        }
        else
        {
            EDER_Posicion = EDER_Maximo;   
        }
}
/*********************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
*********************************************************************************************************/

   /**
	\fn  		void EDER_Interrup(void);
	\brief 		Esta función lee el valor del encoder 
 	\author 	
 	\date 		
 	\param [in]    void   
 	\param [out]   void
    */

    void EDER_Interrupt (void)
    {
        if(INT0IE) {       
        if(INT0IF){
            asm("NOP");
            EDER_FlagCanal = 0;
            INT0IF         = 0; 
            INT1IF         = 0;  
            INT0IE         = 0;
            INT1IE         = 0;
            LED1           =~ LED1;
        }
        else if(INT1IF){
            asm("NOP");
            EDER_FlagCanal = 1;
            INT0IF         = 0; 
            INT1IF         = 0;  
            INT0IE         = 0;
            INT1IE         = 0;
            LED1           =~ LED1;
        }
    }          
    }

     /**
	\fn  		void EDER_Tic(void);
	\brief 		Se encarga de la demora 
 	\author 	
 	\date 		
 	\param [in]    void
 	\param [out]   void
    */
    void EDER_Tic (void)
    {
        static unsigned char estado=4;
    
        if(EDER_Delay)EDER_Delay--;
    
        switch(estado)
        {
            case 0:
                if(EDER_CANALA == 1 && EDER_CANALB == 1)
                { 
                    estado = 1;
                    EDER_Delay = EDER_DELAY;
                }
                break;
            case 1:
                if(!EDER_Delay)
                {
                    if(!EDER_FlagCanal)
                    {
                        EDER_Decrementar();                
                    }
                    if(EDER_FlagCanal)
                    {
                        EDER_Incrementar();
                    }
                    estado = 2;
                }
                break;
        case 2:
            
                DP_DisplayBCD(EDER_Posicion, 0);
                estado = 3;
                break;
        case 3:
            INT0IF=0;
            INT1IF=0;
            INT0IE=1;
            INT1IE=1;
            estado =4;
            break;
        case 4:
            if(!INT0IE)
            {
                estado = 0;
            }
            break;
        default:
            estado = 4;
            break;
        }
    }

#endif /* SHIELD_ACTIVO */