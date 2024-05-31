/*********************************************************************************************************
*                                               LCD
*                               Manejo del display LCD
*
*                                   <Copyright>
*
*                               <Copyright or distribution terms>
*
*
*********************************************************************************************************/

/*********************************************************************************************************
*                                               <File description>
*
* Filename	: PR_LCD
* Version	: 1.0.1					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s): Esta librería solo puede utilizar las cuatro líneas menos significativas de 
*   un puerto en caso de querer utilizar otras líneas se debe de reprogramar.
*   Es necesarío este habilitada la interrupción de timer0 en la cual se debe de 
*   llamar a la función LCD_tic() la misma establece las demoras que de otra
*   manera habría que implementarlas como una función aparte. No olvide declarar 
*   la variable extern uint8_t LCD_Tout en el archivo FW__Interrupt.c
*
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		PR_LCD
 * \brief		Archivo con la función para el manejo del Display LCD
 * \date		11 de junio del 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/

#include "FW_LCD.h"
#include "PR_LCD.h"

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
#if SHIELD_ACTIVO == __SHIELD2
/**
 *	\fn         void LCD_Char2LCD(uint8_t caracter)
 *	\brief      Envia un carater al LCD
 *	\author     Esteban Lemos
 *	\date 
 *  \param      [in]  caracter 
*/
void LCD_Char2LCD (uint8_t caracter)
{
    LCD_WriteData (caracter);
	LCD_ReadBusy();
}


/**
 *	\fn         void LCD_Msg2LCD(const uint8_t* msg)
 *	\brief      Envia un string al LCD
 *	\author     Esteban Lemos
 *	\date 
 *  \param      [in]  msg
*/
void LCD_Msg2LCD (const uint8_t* msg)
{
    while (*msg != 0)
    {
		LCD_WriteData(*msg);
		LCD_ReadBusy();
		msg++;
	}
}
   
/**
 *	\fn         void LCD_Clear(void)
 *	\brief      Borra el LCD
 *	\author     Esteban Lemos
 *	\date 
 *  \param      [in]  mensaje a enviar al LCD
*/
void LCD_Clear (void)
{
    LCD_WriteCMD (0x01);
	LCD_ReadBusy();
}
   
/**
 *	\fn         void LCD_RetHome(void)
 *	\brief      Regresa el curor al inicio
 *	\author     Esteban Lemos
 *	\date 
*/
void LCD_RetHome (void)
{
    LCD_WriteCMD (0x02);
	LCD_ReadBusy();
}
   
/**
 *	\fn         void LCD_SetCursor(uint8_t)
 *	\brief      Ubica el cursor en una posición determinada
 *	\author     Esteban Lemos
 *	\date 
 *  \param      [in]  posición del cursor
*/
void LCD_SetCursor (uint8_t pos)
{
    pos |= 0x80;
    LCD_WriteCMD (pos);
	LCD_ReadBusy();
}


/**
 *	\fn         void LCD_Desp2Izq(void)
 *	\brief      Desplaza al LCD a la izq
 *	\author     Esteban Lemos
 *	\date 
*/
void LCD_Desp2Izq (void)
{
    LCD_WriteCMD (24);
	LCD_ReadBusy();
}

#endif