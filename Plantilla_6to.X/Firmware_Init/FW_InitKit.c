/****************************************************************************************************
 * \file:       FW_InitKit
 * \brief:      Archivo con las funciones de inicializacion del PIC18F4550
 * \author:     Nicolás Ferragamo ferragamo.nico@est.frbautn.edu.ar
 * \date:       22 de abril de 2019
 * \version:    1.1.0
 ****************************************************************************************************/
 
/****************************************************************************************************
 *** INCLUDES
****************************************************************************************************/

#include "FW_InitKit.h"

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

#if SHIELD_ACTIVO == __SHIELD1

/**
 *	\fn         void Kit_Init(void)
 *	\brief      Inicializa el entrenador para el shield 1
 *  \details    Inicializa todos los puertos del entrenador preparandolo para usar
 *              el display y deshabilitando los comparadores de entrada y los
 *              canales analógicos. También limpia todas las salidas.
 *	\author     Esteban Lemos
 *	\date 
 *  \param      [in]  void 
 *  \param      [out] void 
 *	\return           void
*/
void Kit_Init(void){
    
    //Borrado de todos los puertos
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;

    //LEDS y pulsadores

    TRISD         = 0xF0;   // RD0 a RD3 salidas RD4 a RD7 entradas
    TRISCbits.RC6 = 0;      // RC6 y RC7 salidas
    TRISCbits.RC7 = 0;

    //Display

    CMCON  = 0x07;          // comparadores de entrada deshabilitados
    ADCON1 = 0x0F;          // Conversores AD deshabilitados
    TRISA  = 0xC0;          // RA1 a RA5 salidas
    TRISE  = 0x00;          // RE0 a RE2 salidas el resto no está implementado

    //Puerto B

    TRISB  = 0xFF;          // todas entradas, de ser necesario será configuradas por
                            // el alumno según el mismo necesite
}

#elif SHIELD_ACTIVO == __SHIELD2

/**
 *	\fn         void Kit_Init(void)
 *	\brief      Inicializa el entrenador para el shield 2
 *  \details    Inicializa todos los puertos del entrenador preparandolo para usar
 *              el display y deshabilitando los comparadores de entrada y los
 *              canales analógicos. También limpia todas las salidas.
 *	\author     Esteban Lemos
 *	\date 
 *  \param      [in]  void 
 *  \param      [out] void 
 *	\return           void
*/
void Kit_Init(void){
    
 //Se borran todos los puertos
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    
    //Por defecto se toman todos los pines como entradas para protegerlos.
    
    TRISA = 0xFF;           //!< RA0 y RA1 están conectadas a trimers de 10K.
                            //!< Los mismos puedes ser deconectados por jumpers
    TRISB = 0xFF;           //!< El puerto B usa 4 pulsadores.
    TRISC = 0xFF;           //!< RC0 , RC1, RC2 son entradas directas.
                            //!< RC4 y RC5 se conectan al puerto USB.
                            //!< RC6 y RC7 se conectan el puerto RS232.
                            //!< RC3 no está implementada.
    TRISD = 0x0C;           //!< El nibble superior se conecta al LCD.
                            //!< El nible inferior tiene dos LEDS RD0,1     
    TRISE = 0x00;           //!< RE0,1,2 se conectan al LCD RW, RS, E son salidas
    
     
    CMCON  = 0x07;          //!< Comparadores de entrada deshabilitados
    ADCON1 = 0x0F;          //!< Conversores AD deshabilitados la habilitación 
                            //!< de los periféricos se realiza por el usuario
}
#endif

