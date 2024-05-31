/*********************************************************************************************************
*                                               LCD
*                               Inicialización del LCD
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
* Filename	: FW_InitLCD
* Version	: 1.0.0					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s): Esta librería solo puede utilizar las cuatro líneas menos significativas de 
*   un puerto en caso de querer utilizar otras líneas se debe de reprogramar.
*   Es necesarío este habilitada la interrupción de timer en la cual se debe de 
*   llamar a la función LCD_tic() la misma establece las demoras que de otra
*   manera habría que implementarlas como una función aparte. No olvide declarar 
*   la variable extern uint8_t LCD_Tout en el archivo FW__Interrupt.c
*
*
*
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		FW_InitLCD
 * \brief		Archivo con la función de inicalizacion del Display LCD
 * \date		11 de junio del 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/

#include "FW_LCD.h"
#include "PR_LCD.h"

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

/***
* \var		LCD_CharactersCGRAM[ ]
* \brief    Tabla que contine los caracteres de los usuarios
* \details  Tabla que contine los caracteres de los usuarios, para usarla complete
*          los valores de cada elemento de la tabla con sus caraceres
*/

static const uint8_t LCD_CharactersCGRAM[ ] = {
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00,  //!< caracter 0x00 '|     ' una barra
    0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00,  //!< caracter 0x01 '||    ' dos barras
    0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x00,  //!< caracter 0x02 '|||   ' tes barras
    0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x00,  //!< caracter 0x03 '||||  ' cuatro barras
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00,  //!< caracter 0x04 '||||| ' cinco barras
    0x00, 0x04, 0x02, 0x1F, 0x02, 0x04, 0x00, 0x00,  //!< caracter 0x05 '-     ' flechita  
    0x00, 0x04, 0x08, 0x1F, 0x18, 0x14, 0x10, 0x00,  //!< caracter 0x06 '<-    ' flechita 
    0x0E, 0x0E, 0x0F, 0x1F, 0x04, 0x0A, 0x11, 0x00   //!< caracter 0x07 '      ' muñequito
    
};

/*********************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
*********************************************************************************************************/
extern volatile uint8_t LCD_Tout;

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
 *	\fn         void LCD_Init(void)
 *	\brief      Inicializa el LCD para el shield 2
 *  \details    Inicializa los puertos del entrenador necesarios para usar
 *              el display LCD e inicializa el LCD propiamente dicho.
 *	\author     Esteban Lemos
 *	\date 
*/
void LCD_Init(void)
{
    uint16_t aux = 0;
    
    LCD_BUS_DIR     & = LCD_SALIDA;	// Hace el bus salida para escribir en el LCD
    LCD_RS_BUS_DIR    = 0;
    LCD_RW_BUS_DIR    = 0;
    LCD_E_BUS_DIR     = 0;
        

	LCD_Tout = 30;          // Espera 30 interrup de timer
	//while (LCD_Tout);
    for(aux=0; aux<65000; aux++);
    for(aux=0; aux<65000; aux++);
    for(aux=0; aux<65000; aux++);
    
	LCD_WriteCMD (0x02);        // trabajar en 4bits 0010****
	LCD_Tout = 1;		// Al menos 50uS 
	//while (LCD_Tout);	// Espera acá hasta que LCD_tout se hace 0
    for(aux=0; aux<65000; aux++);

	LCD_WriteCMD (0x28);	// 4 bits 2 lineas caracter 5*8
	LCD_Tout = 1;
	//while (LCD_Tout);
    for(aux=0; aux<65000; aux++);
    
	LCD_WriteCMD (0x0C);        //disp ON Cursor OFF Blink OFF
	LCD_Tout = 1;
	//while (LCD_Tout);
    for(aux=0; aux<65000; aux++);

	LCD_WriteCMD (0x01);        // borra el display
	LCD_Tout = 1;
	//while (LCD_Tout);
    for(aux=0; aux<65000; aux++);

	LCD_WriteCMD (0x06);        //Incrementar la pos auto SCROLL OFF
	LCD_Tout = 1;
	//while (LCD_Tout);
    for(aux=0; aux<65000; aux++);

	LCD_ReadBusy ();												// Esta rutina lee el bit de busy a ver si el LCD se liberó..
}

/**
 *	\fn         LCD_InitCGRAM
 *	\brief      Inicializa los caracteres de la CGRAM para el shield 2
 *  \details    Iicioaliza los caracteres creados por el usuario, solo debe llamar
 *              a esta función en el main y guardar sus caracteres en la tabla
 *              LCD_CharactersCGRAM[ ]
 *	\author     Nico?as Ferragamo
 *	\date       1 de octubre de 2019
*/
void LCD_InitCGRAM (void)
{
    uint8_t i = 0;

    LCD_WriteCMD(0x40); //envio a la CGRAM posicion 0 pero deberia ser 0 

    for (i = 0; i < 64; i++) //rellena las filas de la cgram con el vector definido arriba
    {
        LCD_Char2LCD(LCD_CharactersCGRAM[i]);
    }
    LCD_WriteCMD(0x80);  //vuelve a DDRAM
    LCD_SetCursor(0x00); //vuelve a posicion 1ra fila primer caracter
}

#endif