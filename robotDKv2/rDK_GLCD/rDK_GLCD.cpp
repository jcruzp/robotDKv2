//************************************************************************************
//* Serial Graphics LCD Utility functions
//* Modificaci�n a la libreria de SparkFun.
//* Realizada por Jose Cruz el 31/01/2013
//* See http://www.sparkfun.com/datasheets/LCD/SerLCD_V2_5.PDF for further information
//************************************************************************************

#include <Arduino.h>
#include <SoftwareSerial.h>    // Serial Communication Port Library
#include "rDK_GLCD.h"

//Indicacion de envio de comando al LCD
#define LCD_COMANDO 0x7C
//Comandos utilizados en el Serial Graphic LCD LCD-09351 de Sparkfun
#define LCD_CLEARSCREEN 0x00
#define LCD_BACKLIGHT 0x02
#define LCD_BAUDRATE 0x07
#define LCD_COLUMNA 0x18
#define LCD_FILA 0x19

//Se utiliza para borrar alguna linea en el GLCD
#define LINEA_BLANCO "                     "

//Calcula el valor en pixeles para la columna. Basado en 21 car por fila de 6 pixeles cada uno. Columna entre 1 y 21 
#define lcdCol(col) (min(max(col,1),21)*6-6)
//Calcula el valor en pixeles para la fila. Basado en 8 filas de 8 pixeles cada una. Fila entre 1 y 8
#define lcdFila(fila) ((9-min(max(fila,1),8))*8-1)
//Delay para el LCD
#define lcdDelay() (delay(10))   
 

rDK_GLCD::rDK_GLCD(uint8_t rx, uint8_t tx):SoftwareSerial(rx,tx)
{

}


// Inicializa el LCD ajustando pines de comunicacion y colocando pantalla inicial
void rDK_GLCD::Setup(){
  
  //LCD Serial Port setup
  pinMode(LCD_PIN, OUTPUT); // Set the LCD Pin in Output mode
  SoftwareSerial::begin(115200); // Inicializa la libreria serial para que trabaje a 115200 Baud
  //Inicializa el baud rate en el GLCD
  SoftwareSerial::write(LCD_COMANDO);
  SoftwareSerial::write(LCD_BAUDRATE);
  SoftwareSerial::write("6"); // Indica al GLCD que estara trabajando a 115200
}

/* Basada en la documentación de Sparkfun */
void rDK_GLCD::GotoPosition(uint8_t col, uint8_t fila) 
{ 
  SoftwareSerial::write(LCD_COMANDO);
  SoftwareSerial::write(LCD_COLUMNA);
  SoftwareSerial::write(col);
  SoftwareSerial::write(LCD_COMANDO);
  SoftwareSerial::write(LCD_FILA);
  SoftwareSerial::write(fila);
  lcdDelay();
}

/*
* Nueva versión de este metodo para calcular posición en cada fila de arriba hacia abajo
 * fila 1=pixel 63, fila 2= pixel 55, fila 3= pixel 47 ....
 */
void rDK_GLCD::GotoLine(uint8_t fila)
{ 	
  GotoPosition(0,lcdFila(fila));
}

/*
* Posiciona cursor en fila y columna
 * fila: (9-fila)*8-1 (basado en 8 pixeles de alto por caracter)
 * columna: col*6-6 (basado en 6 pixeles de ancho por caracter)
 */
void rDK_GLCD::Goto(uint8_t col,uint8_t fila)
{
  GotoPosition(lcdCol(col),lcdFila(fila));
}

//Clear LCD
void rDK_GLCD::Clear()
{
  SoftwareSerial::write(LCD_COMANDO); // Modo comando
  SoftwareSerial::write(byte(LCD_CLEARSCREEN)); // comando clear LCD
  lcdDelay();
}

// LCD Backlight On
void rDK_GLCD::BacklightON()
{  //turns on the backlight
  SoftwareSerial::write(LCD_COMANDO); // Command 0x7C Set the LCD Display in command mode
  SoftwareSerial::write(LCD_BACKLIGHT);
  SoftwareSerial::write(byte(50)); // Switch On backlight
  lcdDelay();
}

// LCD Backlight Off
void rDK_GLCD::BacklightOFF()
{  //turns off the backlight
  SoftwareSerial::write(LCD_COMANDO); // Command 0x7C Set the LCD Display in command mode
  SoftwareSerial::write(LCD_BACKLIGHT);
  SoftwareSerial::write(byte(0)); //Switch Off backlight
  lcdDelay();
}

// LCD Backlight Off
void rDK_GLCD::ClearLine(uint8_t fila)
{  
    GotoLine(fila);
    SoftwareSerial::print(LINEA_BLANCO);
}

void rDK_GLCD::PrintLine(uint8_t fila, const char str[])
{
    GotoLine(fila);
    SoftwareSerial::print(str);
}

//====================================================================
