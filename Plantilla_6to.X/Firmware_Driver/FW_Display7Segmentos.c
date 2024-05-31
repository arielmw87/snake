/**********************************************************************************************************
*                                               Display 7 Segmentos
*                                       Manejo del display 7 segmentos 
*
*						<Copyright>
*
*						<Copyright or distribution terms>
*
*
*********************************************************************************************************/

/*********************************************************************************************************
*                                               FW_Display7Segmentos.c
*
* Filename	: FW_Display7Segmentos.c
* Version	: 1.0.0					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s): Para poder usar este módulo debe llamar a la función DP_BarridoDisplay (); dentro de 
*  Aplicacion() y llamar a la función DP_Tic() dentro de la interrupcion
*
*
*
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		FW_Display7Segmentos.c
 * \brief		Módulo para el manejo de los display 7 segmentos
 * \date		30 de septiembre de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/
#include "xc.h"
#include "Display7Segmentos.h"

#if SHIELD_ACTIVO == __SHIELD1
/*********************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
*********************************************************************************************************/
#define DIGITO0    0
#define DIGITO1    1
#define DIGITO2    2
#define DIGITO3    3
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
*********************************************************************************************************/
volatile uint8_t DP_Delay = DP_TIC;
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
	\fn  		void DP_BarridoDisplay (void);
	\brief 		Realiza el barrido de los displays
 	\author 	Nicolás Exequiel Ferragamo
 	\date 		30 de septiembre de 2019
 	\param [in] 	void
 	\param [out] 	void
*/
void DP_BarridoDisplay (void)
{
    static uint8_t digito = 0;

    DP_DISP1 = OFF; 
    DP_DISP2 = OFF; 
    DP_DISP3 = OFF;
    DP_DISP4 = OFF; 

    DP_SEGMENTOA =  (DP_msgDisplay[digito]      & (uint8_t) 0x01);
    DP_SEGMENTOB =  (DP_msgDisplay[digito] >> 1 & (uint8_t) 0x01);
    DP_SEGMENTOC =  (DP_msgDisplay[digito] >> 2 & (uint8_t) 0x01);
    DP_SEGMENTOD =  (DP_msgDisplay[digito] >> 3 & (uint8_t) 0x01);  
    
    switch(digito)
    {
        case DIGITO0:
         	DP_DISP1 = ON; 
            break;
        case DIGITO1:
            DP_DISP2 = ON;  
            break;
        case DIGITO2:
            DP_DISP3 = ON; 
            break;
        case DIGITO3:
            DP_DISP4 = ON; 
            break;
    }

	// Incremento el indice del display
	digito++;
	digito %= DP_DIGITOS;
}


/**
	\fn  		void DP_Tic(void);
	\brief 		Se encarga de la demora del barrido
 	\author 	Nicolás Exequiel Ferragamo
 	\date 		30 de septiembre de 2019
 	\param [in]     void
 	\param [out] 	void
*/
void DP_Tic(void)
{
    if(DP_Delay)
    {
        DP_Delay--;
    }
    else
    {
        DP_BarridoDisplay();
        DP_Delay = DP_TIC;
    }
}


#endif
