/**********************************************************************************************************
*                                               BaseBoard
*						Contiene los define de la BaseBoard
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
* Filename	: BaseBoard.h
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
 * \file		BaseBoard.h
 * \brief		Contiene las definciones necesarias de la BaseBoard
 * \date		13 de junio de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** MODULO
*********************************************************************************************************/

#ifndef BASE_BOARD_H
#define BASE_BOARD_H

/*********************************************************************************************************
 *** INCLUDES GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** DEFINES GLOBALES
*********************************************************************************************************/

#define __SHIELD1  1    //!< Selecciono el shield 1
#define __SHIELD2  2    //!< Selecciono el shield 2 
#define SHIELD_ACTIVO __SHIELD1 //!< seleciona el shield activo

#if SHIELD_ACTIVO == __SHIELD1

/************************* Definiciones de los Leds **************************/
#define LED5    LATDbits.LD0    //!< Indica ingreso a modo BootLoader, puede ser usado por el usuario
#define LED6    LATDbits.LD1    //!< Inica modo conectado, puede ser usado por el usuario
#define LED1    LATDbits.LD2    
#define LED2    LATDbits.LD3
#define LED3    LATCbits.LC6
#define LED4    LATCbits.LC7

/********************** Definiciones de los Pulsadores ***********************/
#define BOT1    PORTDbits.RD4
#define BOT2    PORTDbits.RD5
#define BOT3    PORTDbits.RD6
#define BOT4    PORTDbits.RD7

/*********************** Definiciones de los Displays ************************/
#define DISP1   LATAbits.LA4
#define DISP2   LATAbits.LA5
#define DISP3   LATEbits.LE0
#define DISP4   LATEbits.LE1
#define DOT     LATEbits.LE2

#define Init_Kit_PULSADORES  (PORTD^0xF0)&0xF0    //!<Nibble superior del puerto D

#elif SHIELD_ACTIVO == __SHIELD2


/********************** Definiciones de los Pulsadores ***********************/

#define BOT1    PORTBbits.RB4 
#define BOT2    PORTBbits.RB5
#define BOT3    PORTBbits.RB6
#define BOT4    PORTBbits.RB7
#define BOOT    PORTBbits.RB4
#define Init_Kit_PULSADORES  (PORTB^0xF0)&0xF0

/********************* Definiciones de los Displays LCD **********************/
#define DISPLAY LATD

/******************* Definiciones de entradas analógicas *********************/
#define ANALOGICA_1 PORTAbits.RA0
#define ANALOGICA_2 PORTAbits.RA1


/************************* Definiciones de la USART **************************/
#define USART_TX PORTCbits.TX
#define USART_RX PORTCbits.RX


/******************** Definiciones de salidas disponibles ********************/
#define SAL0    PORTAbits.RA2
#define SAL1    PORTAbits.RA3
#define SAL2    PORTAbits.RA4
#define SAL3    PORTAbits.RA5


/************Configuración del triestado de las salidas puesrto A ************/
#define SAL0_ON     TRISAbits.TRISA2 = 0;
#define SAL0_OFF    TRISAbits.TRISA2 = 1;

#define SAL1_ON     TRISAbits.TRISA3 = 0;
#define SAL1_OFF    TRISAbits.TRISA3 = 1;

#define SAL2_ON     TRISAbits.TRISA4 = 0;
#define SAL2_OFF    TRISAbits.TRISA4 = 1;

#define SAL3_ON     TRISAbits.TRISA5 = 0;
#define SAL3_OFF    TRISAbits.TRISA5 = 1;

#else

    #error "No seleccionó ningun shield"

#endif

#define		ENTRADA		1
#define		SALIDA		0

#define		ON			1
#define		OFF			0

#define     ACTIVO_ALTO 1
#define     ACTIVO_BAJO 0

/*********************************************************************************************************
 *** MACROS GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** TIPO DE DATOS GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** VARIABLES GLOBALES
*********************************************************************************************************/

/*********************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
**********************************************************************************************************/

#endif /* BASE_BOARD_H */
