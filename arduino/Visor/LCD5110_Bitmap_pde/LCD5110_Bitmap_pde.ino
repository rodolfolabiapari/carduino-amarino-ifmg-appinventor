// LCD5110_Bitmap (C)2013 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of how to use bitmaps.
// You can also see how to use invert().
//
// This program requires a Nokia 5110 LCD module.
//
// It is assumed that the LCD module is connected to
// the following pins using a levelshifter to get the
// correct voltage to the module.
//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12
//
#include <LCD5110_Basic.h>

LCD5110 myGLCD(8,9,10,11,12);

const int buttonNaveg = 7;
const int buttonOK = 6;
int buttonStateNaveg = 0;
int buttonStateOK = 0;
int led = 5;
int buttonStateLED = 0;
int tela = 0;
int op = 1;
int cont = 0;
int cont2 = 0;

extern uint8_t arduino_logo[];
extern uint8_t bluetooth[];
extern uint8_t bluetooth_off[];
extern uint8_t farol_on[];
extern uint8_t farol_off[];
extern uint8_t principal_limpa[];
extern uint8_t principal_luzes[];
extern uint8_t principal_sensores[];
extern uint8_t limpa[];
extern uint8_t combinacao10[];
extern uint8_t combinacao20[];
extern uint8_t combinacao30[];
extern uint8_t combinacao40[];
extern uint8_t combinacao01[];
extern uint8_t combinacao02[];
extern uint8_t combinacao03[];
extern uint8_t combinacao04[];
extern uint8_t C2ISC[];
extern uint8_t IFMG[];
extern uint8_t pf[];

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

void imprimeCabecalho()
{
  myGLCD.drawBitmap(0, 0, IFMG, 84, 48);
  delay(2000);
  
  myGLCD.drawBitmap(0, 0, C2ISC, 84, 48);
  delay(2000);
  
  myGLCD.clrScr();
  
  myGLCD.print("CARDUINO",CENTER,0);
  delay(1000);
  
  myGLCD.print("Joao P. FCC",LEFT,20);
  delay(1000);
  myGLCD.clrScr();
  
  myGLCD.print("CARDUINO",CENTER,0);
  myGLCD.print("Rodolfo LMG",CENTER,30);
  delay(1000);
  myGLCD.clrScr();
  
  myGLCD.print("CARDUINO",CENTER,0);
  myGLCD.print("Tarlei A",RIGHT,40); 
  delay(1000);
  myGLCD.clrScr();
  
  myGLCD.print("CARDUINO",CENTER,0);
  myGLCD.print("Otavio SMG",CENTER,35);
  delay(1000);
  myGLCD.clrScr();
  
  myGLCD.print("CARDUINO",CENTER,0);
  myGLCD.print("Rafael TN",CENTER,35); 
  delay(1000);
  myGLCD.clrScr();
}
  
void setup()
{
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  pinMode(buttonNaveg, INPUT);
  pinMode(buttonOK, INPUT);
  pinMode(led, OUTPUT);
  
  digitalWrite(led, LOW);
 
  imprimeCabecalho();
 
  myGLCD.drawBitmap(0, 0, principal_luzes, 84, 48);
    
}

void Set_farol_on()
{
  myGLCD.drawBitmap(3, 5, farol_on, 5, 8);
}

void Set_farol_off()
{
  myGLCD.drawBitmap(3, 5, farol_off, 5, 8);
}

void Set_bluetooth_on()
{
  myGLCD.drawBitmap(74, 1, bluetooth, 5, 8);
}

void Set_bluetooth_off()
{
  myGLCD.drawBitmap(74, 1, bluetooth_off, 5, 8);
}

void reimprime(int *i)
{
  
  int temp = 20;
  int humi = 70;
  int dist = 150;
  
  switch (*i)
  {
    case 0:
    {
       Set_bluetooth_on(); 
       Set_farol_on();
       break;  
    } 
    case 1:
    {
     Set_bluetooth_on();
     Set_farol_off();
     break;  
    }
   case 2:
   {
     *i = 0;
     Set_bluetooth_off();
     Set_farol_on();
     break;  
   } 
  }
  
  myGLCD.printNumI(temp, CENTER, 16);
  myGLCD.printNumI(humi, CENTER, 30);
  myGLCD.printNumI(dist, CENTER, 36);
  
  (*i)++;
}

void loop()
{ 
  int i = 0;
  
  buttonStateNaveg = digitalRead(buttonNaveg);
  buttonStateOK = digitalRead(buttonOK);

  if(buttonStateNaveg == HIGH)
  {
     
    if(tela == 0)
    {
         cont++; 
         if(op == 0)
          {
            op = 1;
            myGLCD.drawBitmap(0, 0, principal_luzes, 84, 48);
            delay(700);
          }
          else
          {
            op = 0;
            myGLCD.drawBitmap(0, 0, principal_sensores, 84, 48);
            delay(700);
          }  
      
    }
    
   else
   {   
     op = 0;
     tela = 0;
     myGLCD.drawBitmap(0, 0, principal_luzes, 84, 48);     
   }    
  }
  
  else if (buttonStateOK == HIGH)
  {
      cont2++;
      if(op == 1)
      {
        if(buttonStateLED == 0)
        {
          buttonStateLED = 1;
          digitalWrite(led, HIGH);
        }
        else
        {
          buttonStateLED = 0;
          digitalWrite(led, LOW);
        }
      }
      else if(tela == 0)
      {
         myGLCD.drawBitmap(0, 0, limpa, 84, 48);
         tela = 1;
         cont = -1;
         cont2 = 0;
      }    
    
      delay(700);
    
   }
  
   if((cont == 6) && (cont2 == 5))
   {
     myGLCD.drawBitmap(0, 0, pf, 84, 48);
     delay(2000);
     cont = 0;
     cont2 = 0; 
     myGLCD.drawBitmap(0, 0, principal_luzes, 84, 48);
   }     
 
}
