#ifndef _rDK_GLCD_h_
#define _rDK_GLCD_h_


#include <SoftwareSerial.h>


// Se utiliza este pin del Arduino Mega para el manejo del GLCD
#define LCD_PIN 23 

// Clase rDK_GLCD extiende de SoftwareSerial para agregar funciones de Graphic LCD
class rDK_GLCD : public SoftwareSerial{
public:

  rDK_GLCD(uint8_t, uint8_t);	
  void Setup();
  void GotoPosition(uint8_t, uint8_t);
  void GotoLine(uint8_t);
  void Goto(uint8_t, uint8_t);
  void Clear();
  void BacklightON();
  void BacklightOFF(); 
  void ClearLine(uint8_t);
  void PrintLine(uint8_t, const char[]);

};

#endif
