/*********************************************************************************************************
*                                               LCD
*                                   		Driver del LCD
*
*                                   <Copyright>
*
*						<Copyright or distribution terms>
*
*
*********************************************************************************************************/

/*********************************************************************************************************
*                                               <File description>
*
* Filename	: FW_LCD
* Version	: 1.0.1					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s):
*
*
*
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		FW_LCD.c
 * \brief		Contiene los drivers necesarios para la libreria del dispplay LCD
 * \date		13 de junio de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/

#include "FW_LCD.h"

#if SHIELD_ACTIVO == __SHIELD2
/*********************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
*********************************************************************************************************/

#define     LCD_ENTRADA     0xF0            //!< Esto es para invertir el bus de datos y poder
#define     LCD_SALIDA      0x0F            //!<leer cuando necesito ver si está busy..
#define     LCD_BUSY        PORTDbits.RD7	//!< Con estos defines me abstraigo del hardware
#define     LCD_BUS_DIR     TRISD

#define     LCD_TRUE        0x1
#define     LCD_FALSE       0x0

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
volatile uint8_t LCD_Tout = 0;

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
 *	\fn         void LCD_Read_Busy(void)
 *	\brief      Se encarga de leer el bit busy
 *  \details    La función se asegura que el LCD haya terminado la operación ctual
 *	\author     Esteban Lemos
 *	\date 
*/
void LCD_ReadBusy (void)
{
    uint8_t aux;

	LCD_BUS_DIR | = LCD_ENTRADA;	// Pone el bus como entrada (hay que leer) D7 a D4
	LCD_RS        = LCD_FALSE;      // Pone las señales para indicar que va a leer
	LCD_RW        = LCD_TRUE;
	do{                     // Hace
		LCD_E     = LCD_TRUE;       // E=1
		aux       = LCD_BUSY;       // Lee bit de busy
		LCD_E     = LCD_FALSE;      // E=0
		LCD_E     = LCD_TRUE;       // E=1
		(void) BUSY;         // Lectura dummy para completar el byte
		LCD_E     = LCD_FALSE;      // E=0, completo byte
	}while (aux);           // Mientras busy = 1, cuando busy = 0 (LCD terminó), sale de este do-while
	LCD_RW        = LCD_FALSE;		// Normaliza las señales
	LCD_BUS_DIR & = LCD_SALIDA;     // Hace el bus salida para seguir escribiendo al LCD
}


/**
 *	\fn         void LCD_Write_CMD(uint8_t comando)
 *	\brief      Se encarga de escribir un comando en el LCD
 *	\author     Esteban Lemos
 *	\date 
 *  \param      [in]  Recive el comando a enviar al LCD
*/
void LCD_WriteCMD (uint8_t comando)
{
    LCD_RS = LCD_FALSE;
	LCD_RW = LCD_FALSE;
	LCD_Write (comando);	// Envía efectivamente el comando
}

/**
 *	\fn         void LCD_Write(unsigned char dato)
 *	\brief      Se encarga de escribir un dato en bus de a un nibble por vez
 *  \details    Se encarga de escribir un dato en bus de a un nibble por vez
 *              para poder trabajar en 4 bits.
 *	\author     Esteban Lemos
 *	\date 
 *  \param      [in]  Recive el dato a enviar al LCD
*/
void LCD_Write (uint8_t dato)
{
    LCD_DISPLAY & = 0x0F;
    LCD_E         = LCD_TRUE;
    LCD_DISPLAY | = (uint8_t)(dato & 0xF0);		// Pone el nibble alto en el bus
    LCD_E         = LCD_FALSE;
    LCD_DISPLAY & = 0x0F;
    LCD_E         = LCD_TRUE;
    LCD_DISPLAY | = (uint8_t)(dato << 4);		// Pone el nibble alto en el bus
    LCD_E         = LCD_FALSE;
}

/**
 *	\fn         void LCD_Write_Data (uint8_t dato)
 *	\brief      Configura las señales necesarias para escribir el dato
 *	\author     Esteban Lemos
 *	\date 
 *  \param      [in]  Recive el dato a enviar al LCD
*/
void LCD_WriteData (uint8_t dato)
{
    LCD_RS = LCD_TRUE;
	LCD_RW = LCD_FALSE;
	LCD_Write (dato);	// Envía efectivamente el dato
}


/**
 *	\fn         void LCD_TicLCD(void)
 *	\brief      Rutina necesaria para el fncionamiento del módulo
 *  \details    Esta rutina se debe llama desde la interrupción de timer cada 1mS
 *	\author     Esteban Lemos
 *	\date 
*/
void LCD_TicLCD (void)
{
     if (LCD_Tout) LCD_Tout--;
}

#endif