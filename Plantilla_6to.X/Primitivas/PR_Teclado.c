/**********************************************************************************************************
*                                               Teclado
*               			Módulo encargado del manejo del teclado
*
*                                             <Copyright>
*
*                                       <Copyright or distribution terms>
*
*
*********************************************************************************************************/

/*********************************************************************************************************
*                                               <File description>
*
* Filename	: PR_Teclado.c
* Version	: 1.0.0					
* Programmer(s) : NEF
**********************************************************************************************************
*  Note(s):  Definiciones del hardware según conexión del teclado, las FILAS 
*  (deben estar inicializadas como entradas en el MCU. Deben de ser lineas con 
*  interrupción externa disponible

*
*
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		PR_Teclado.C
 * \brief		Módulo encargado del manejo del teclado, contiene las primitivas necesarios
 * \date		13 de junio de 2019
 * \author		Nicolas Ferragamo nferragamo@est.frba.utn.edu.ar
 * \version     1.0.0
*********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/

#include "PR_Teclado.h"
#include "FW_Teclado.h"

/*********************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
*********************************************************************************************************/
enum STATUS_KB {
	TDO_LIBRE,           //en espera de que se presione una tecla
	TDO_ESPERA,          //un tiempo necesario para evitar rebotes
	TDO_DETECTA,         //barribo del puerto en busqueda de la tecla
	TDO_LIBERA,          //un tiempo de espera y una condición para iniciar 
                        //nuevamente el ciclo
};
/*********************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
*********************************************************************************************************/
#ifdef ResASCII
//Resultado ASCII, util para usarse con LCDs o con puerto serie
const uint8_t teclas[4][3]={
 {'1','2','3'},{'4','5','6'},{'7','8','9'},{'E','0','C'}
};
#else
//Resultados binarios útiles para cualquier tipo de uso
const uint8_t teclas[4][4]={
 {1,2,3,'A'},{4,5,6,'B'},{7,8,9,'C'},{'*',0,'+','D'}
};
#endif

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

#if SHIELD_ACTIVO == __SHIELD1
/** 
 *  \fn         uint8_t TDO_Tecla(void); 
 *  \brief      Debuelve la tecla seleccionada
 *  \details    Función que devuelve una tecla presionada o TDO_NO_TECLA = 0xFF      
 *              si no hay novedad. El dato puede configurarse como binario o 
 *              como ASCII  definiendo o no ResASCII   
 *	\author     Esteban Lemos
 *	\date 
 *  \param [out] 	Devuelve la tecla presionada
 *	\return tipo 	Devuelve la tecla presionada
 * 
*/
uint8_t TDO_Tecla(void)
{
	static enum STATUS_KB status_kb = TDO_LIBRE;
	uint8_t tecla_kb           = TDO_NO_TECLA;

	/**************************************************************************
     * Cada vez que se llama a la función tecla() se evalúa el estado de la 
     * variable status_KB, la misma irá evolucionando según se vayan cumpliendo
     * las distintas condiciones                                             
     **************************************************************************/
    switch (status_kb){                     

		case TDO_LIBRE:
			if (TDO_flag_kb){                   //ocurrida la interrupción
				TDO_flag_kb = TDO_FALSE;            //se inicializan las variables     
				TDO_fila = TDO_NO_FILA;             //que luego contenbdrán    
				TDO_col = TDO_NO_COL;               //el valor de la tecla presionada    
				tecla_kb = TDO_NO_TECLA;
				TDO_delay_kb = TDO_DLY_DEBOUNCE;    //se establece un tiempo de esta_
				status_kb = TDO_ESPERA;      //bilidad y se evoluciona al
                                            //próximo valor de la máquina de 
                                            //estado                 
			}//En caso contrario se vuelkve a la funcion anterior
			break;
		
		case TDO_ESPERA:
            
			if (!TDO_delay_kb){                 //simplemente se espera un tiempo
                status_kb = TDO_DETECTA;     //para evolucionar al próximo estado                
            }                               //de esta manera se estabiliza
			break;                          //el valor del pulsador
			
		/**********************************************************************
         *Se procede a barrer el puerto para detectar cual es la tecla que    *
         *se ha presionado                                                    *
         **********************************************************************/
        case TDO_DETECTA:                    
            
			if (!TDO_FILA1){        //Primera fila en 0
                TDO_fila = 0;
               
            }
			else if (!TDO_FILA2){   //Segunda fila en 0
                TDO_fila = 1;
                
            }
			else if (!TDO_FILA3){   //Tercera fila en 0
                TDO_fila = 2;
               
            }
			else if (!TDO_FILA4){   //Cuarta fila en 0
                TDO_fila = 3;
                
            }
			/******************************************************************
             * Si ninguna fila se ha presionado se presupone que la detección *
             * constituye un falso dato, por lo que se procede a reiniciar    *
             ******************************************************************/
            if (TDO_fila == TDO_NO_FILA){
                status_kb = TDO_LIBRE;                
            }
            /******************************************************************
             * En caso contrario se barren todas las columnas para identificar*
             * la tecla que se ha presionado                                  *                                                                    
             ******************************************************************/    
			else{
				TDO_COL1 = 1;       //Se fuerza un estado alto en la columna 1
		        TDO_LittleDelay();       
                
				if (TDO_FILA1 && TDO_FILA2 && TDO_FILA3 && TDO_FILA4){
					TDO_col = 0;    //Si la multiplicación booleana de todas las 
                                //filas es verdadera, significa que se ha 
                                //forzado la entrada de la fila que corresponde 
                                //a la tecla presionada a un estado alto    
                }else{
                    TDO_COL2 = 1;
                    TDO_LittleDelay();
                  
					if (TDO_FILA1 && TDO_FILA2 && TDO_FILA3 && TDO_FILA4){
						TDO_col = 1;  
					}else{
                        TDO_COL3 = 1;
                        TDO_LittleDelay();
                     
						if (TDO_FILA1 && TDO_FILA2 && TDO_FILA3 && TDO_FILA4){
							TDO_col = 2;
                            
						}
                        else{
                        TDO_COL4 = 1;
                        TDO_LittleDelay();
			         
						if (TDO_FILA1 && TDO_FILA2 && TDO_FILA3 && TDO_FILA4){
							TDO_col = 3;
                            
						}
                        }
					}
				}
                //Se vuelve a forzar a todas las columna a 0
				TDO_COL1=0;
				TDO_COL2=0;
				TDO_COL3=0;
                TDO_COL4=0;
                
                if (TDO_col == TDO_NO_COL){         //Si ninguna columna cumplió la 
                    status_kb =TDO_LIBRE;   //condición se devuelve el valor
                                            //NO_TECLA
                }
                /**************************************************************
                 * Si por el contrario se reconoce una tecla se devuelve el   *
                 * valor de la misma y se retiene la detección de teclado por *
                 * un tiempo para evitar rebotes en el proceso                *
                 * ************************************************************/
				else{                           
					TDO_delay_kb = TDO_DLY_RELEASE;
					status_kb = TDO_LIBERA;
					tecla_kb = teclas[TDO_fila][TDO_col];
                    
				}
			}
        break;
			
		case TDO_LIBERA:
			
            if ((TDO_FILA1 && TDO_FILA2 && TDO_FILA3 && TDO_FILA4)&&(!TDO_delay_kb)) status_kb = TDO_LIBRE;
			break;
			
		default:
            /******************************************************************
            * Si por algún motivo la máquina de estados entro en un estado    *
            *no válido, se define una condición de reingreso a la máquina     *
            *******************************************************************/
			TDO_fila = TDO_NO_FILA;
			TDO_col = TDO_NO_COL;
			tecla_kb = TDO_NO_TECLA;
			status_kb = TDO_LIBRE;
			break;
	}

	return (tecla_kb) ;
    
}

#endif
