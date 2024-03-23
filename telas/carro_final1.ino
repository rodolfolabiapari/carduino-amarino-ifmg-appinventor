// INICIALIZAÇÃO do Nokia 5110 LCD module.
//
// It is assumed that the LCD module is connected to
// the following pins using a levelshifter to get the
// correct voltage to the module.
//      SCK  - Pin 39
//      MOSI - Pin 37
//      DC   - Pin 35
//      RST  - Pin 31
//      CS   - Pin 33
//      VCC  - Pin VCC
//      GND  - Pin GND
//      BL   - Pin 41

//biblioteca para a execuçao no LCD
#include "LCD5110_Basic.h"
LCD5110 myGLCD(39,37,35,31,33);

//#include <TimerOne.h>

#include "DHT.h"
#define DHTPIN 38 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

int aux=0;

#include "Ultrasonic.h"
#define echoPin 47 // Pino  -> Echo
#define trigPin 29// Pino  -> Trig
Ultrasonic ultrasonic(trigPin,echoPin);

#include "pitches.h"

#include "AFMotor.h"
AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);

int acel = 125;
char conectou = '0';
char parado = '0';

int dist;

const int buttonNaveg = 14;
const int buttonOK = 15;
int buttonStateNaveg = 0;
int buttonStateOK = 0;

int led1 = 25;
int led2 = 51;

int buttonStateLED = 0;
int tela = 0;
int op = 1;
int cont = 0;
int cont2 = 0;
int BL = 41;
int contBL = 0;
//int contSD = 0;
int buzzer = 48;

//BMPs

extern uint8_t arduino_logo[];
extern uint8_t bluetooth[];
extern uint8_t bluetooth_off[];
extern uint8_t farol_on[];
extern uint8_t farol_off[];
extern uint8_t principal_limpa[];
extern uint8_t principal_luzes[];
extern uint8_t principal_sensores[];
extern uint8_t limpa[];
extern uint8_t combinacao01[];
extern uint8_t combinacao02[];
extern uint8_t combinacao03[];
extern uint8_t combinacao04[];
extern uint8_t combinacao10[];
extern uint8_t combinacao11[];
extern uint8_t combinacao12[];
extern uint8_t combinacao13[];
extern uint8_t combinacao14[];
extern uint8_t combinacao20[];
extern uint8_t combinacao21[];
extern uint8_t combinacao22[];
extern uint8_t combinacao23[];
extern uint8_t combinacao24[];
extern uint8_t combinacao30[];
extern uint8_t combinacao31[];
extern uint8_t combinacao32[];
extern uint8_t combinacao33[];
extern uint8_t combinacao34[];
extern uint8_t combinacao40[];
extern uint8_t combinacao41[];
extern uint8_t combinacao42[];
extern uint8_t combinacao43[];
extern uint8_t combinacao44[];
extern uint8_t C2ISC[];
extern uint8_t IFMG[];
extern uint8_t pf[];

//Fontes

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];


//SplashScreen
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
  
//Imprime a imagem de farol ligado
void Set_farol_on()
{
  myGLCD.drawBitmap(3, 5, farol_on, 5, 8);
}

//Imprime a imagem de farol desligado
void Set_farol_off()
{
  myGLCD.drawBitmap(3, 5, farol_off, 5, 8);
}

//Imprime a imagem de bluetooth ligado
void Set_bluetooth_on()
{
  myGLCD.drawBitmap(74, 1, bluetooth, 5, 8);
}

//Imprime a imagem de bluetooth desligado
void Set_bluetooth_off()
{
  myGLCD.drawBitmap(74, 1, bluetooth_off, 5, 8);
}

//Imprime a tela correta de acordo com a leitura da temperatura e umidade
void atualizaIcones (float* temp, float* hum) {
  
  if ((*temp <= 10) && (*hum <= 34)) {
    myGLCD.drawBitmap(0, 0, limpa, 84, 48);
  } else 
    if ((*temp <= 20) && (*hum <= 34)) {
       myGLCD.drawBitmap(0, 0, combinacao10, 84, 48);
    } else
      if ((*temp <= 30) && (*hum <= 34)) {
        myGLCD.drawBitmap(0, 0, combinacao20, 84, 48);
      } else
       if ((*temp <= 40) && (*hum  <= 34)) {
         myGLCD.drawBitmap(0, 0, combinacao30, 84, 48);
       } else 
         if ((*temp <= 50) && (*hum <= 34)) {
            myGLCD.drawBitmap(0, 0, combinacao40, 84, 48); 
         } else 
         
         
          if ((*temp <= 10) && (*hum <= 48)) {
            myGLCD.drawBitmap(0, 0, combinacao01, 84, 48);
          } else 
            if ((*temp <= 20) && (*hum <= 48)) {
               myGLCD.drawBitmap(0, 0, combinacao11, 84, 48);
            } else
              if ((*temp <= 30) && (*hum <= 48)) {
                myGLCD.drawBitmap(0, 0, combinacao21, 84, 48);
              } else
               if ((*temp <= 40) && (*hum  <= 48)) {
                 myGLCD.drawBitmap(0, 0, combinacao31, 84, 48);
               } else 
                 if ((*temp <= 50) && (*hum <= 48)) {
                    myGLCD.drawBitmap(0, 0, combinacao41, 84, 48); 
                 } else
         
         
                  if ((*temp <= 10) && (*hum <= 62)) {
                    myGLCD.drawBitmap(0, 0, combinacao02, 84, 48);
                  } else 
                    if ((*temp <= 20) && (*hum <= 62)) {
                       myGLCD.drawBitmap(0, 0, combinacao12, 84, 48);
                    } else
                      if ((*temp <= 30) && (*hum <= 62)) {
                        myGLCD.drawBitmap(0, 0, combinacao22, 84, 48);
                      } else
                       if ((*temp <= 40) && (*hum  <= 62)) {
                         myGLCD.drawBitmap(0, 0, combinacao32, 84, 48);
                       } else 
                         if ((*temp <= 50) && (*hum <= 62)) {
                            myGLCD.drawBitmap(0, 0, combinacao42, 84, 48); 
                         } else
  
  
                          if ((*temp <= 10) && (*hum <= 76)) {
                              myGLCD.drawBitmap(0, 0, combinacao03, 84, 48);
                          } else 
                            if ((*temp <= 20) && (*hum <= 76)) {
                               myGLCD.drawBitmap(0, 0, combinacao13, 84, 48);
                            } else
                              if ((*temp <= 30) && (*hum <= 76)) {
                                myGLCD.drawBitmap(0, 0, combinacao23, 84, 48);
                              } else
                                if ((*temp <= 40) && (*hum  <= 76)) {
                                   myGLCD.drawBitmap(0, 0, combinacao33, 84, 48);
                               } else 
                                 if ((*temp <= 50) && (*hum <= 76)) {
                                    myGLCD.drawBitmap(0, 0, combinacao43, 84, 48); 
                                 } else
  
  
                                    if ((*temp <= 10) && (*hum <= 90)) {  
                                      myGLCD.drawBitmap(0, 0, combinacao04, 84, 48);
                                    } else 
                                      if ((*temp <= 20) && (*hum <= 90)) {
                                         myGLCD.drawBitmap(0, 0, combinacao14, 84, 48);
                                      } else
                                        if ((*temp <= 30) && (*hum <= 90)) {
                                          myGLCD.drawBitmap(0, 0, combinacao24, 84, 48);
                                        } else
                                          if ((*temp <= 40) && (*hum  <= 90)) {
                                            myGLCD.drawBitmap(0, 0, combinacao34, 84, 48);
                                          } else 
                                            if ((*temp <= 50) && (*hum <= 90)) {
                                              myGLCD.drawBitmap(0, 0, combinacao44, 84, 48); 
                                            }
  }

//Imprime a tela de sensores vazia
void preTelaSensores()
{
  myGLCD.drawBitmap(0, 0, limpa, 84, 48);//Desenha a tela de sensores
  tela = 1;  //Muda a flag, sinalizado tela atual(sensores)
  cont = 0; //Reseta contadores EE
  cont2 = 0;
}

//Procedimento que realiza uma rotina de alerta quando o carro está próximo de algum objeto
void alerta()
{
  contBL = 0;
  acendeBL();   //Liga o BL da tela
  preTelaSensores();
}

//Procedimento responsavel pelo som de alerta emitido pelo buzzer
void alarme(int dist)
{
  //if((dist > 2) && (dist <= 15))
  //{
    //tone(buzzer, 5000, 400);
   // noTone(buzzer);
   //  parar_motores();
    
    //Caso a tela atual seja o menu, ou a tela seja os sensores e o BL esteja apagado, chama procedimento de alerta
  //  if((tela == 0) || ((tela == 1) && (contBL == 61)))
   // {
   //   alerta();  
   // } 
  //}  
  
  if(dist <= 20)
  {
    if((tela == 0) || ((tela == 1) && (contBL == 61)))
    {
      alerta();
      parar_motores();
    }
    //tone(buzzer, 5000, 500); 
  }
  
}

//Procedimento responsavel por imprimir na tela o valor da distancia lido
void imprimeDist(int *dist)
{
  myGLCD.printNumF(*dist, 2, CENTER, 35);
  myGLCD.print("cm", 60, 35);
}

//Procedimento responsavel por realizar a leitura do sensor ultrassônico e retornar a distancia lida
int ultrassom()
{  
  dist = ultrasonic.Ranging(CM);
  alarme(dist);
  return dist;
}

//Procedimento responsavel por imprimir na tela os valores da temperatura e umidade lidos
void imprimeDHT(float *temp, float *hum)
{
  
  atualizaIcones(temp, hum);
  
  if (isnan(*temp) || isnan(*hum)) 
  {
    myGLCD.print("Falha", CENTER, 16);
    myGLCD.print("Falha", CENTER, 30);
  } 
  else
  {
    myGLCD.printNumF(*temp, 2, CENTER, 16);
    myGLCD.print("ºC", 57, 16);
    myGLCD.printNumF(*hum, 2, CENTER, 30);
    myGLCD.print("%", 60, 30);  
  }
    
}

//Protecao de tela
void screensaver()
{
  myGLCD.drawBitmap(0, 0, C2ISC, 84, 48);
}

//Procedimento que apaga a luz de BL
void apagaBL(int *contBL)
{
  digitalWrite(BL, LOW);
  *contBL = 61; //seta o valor do contaor de modo que esse não seja atualizado, desabilitando assim a contagem
}

//Procedimento que acende a luz de BL
void acendeBL()
{
  //Serial.println("ACENDEU");
  digitalWrite(BL, HIGH);
}

void verificaBotoes()
{

   if(buttonStateNaveg == HIGH)
   {   
     acendeBL();
     contBL = -1;
    
   if(tela == 0)
   {
     cont++; 
     if((op == 0) && (contBL <=60))
     {
       op = 1;
       myGLCD.drawBitmap(0, 0, principal_luzes, 84, 48);
     }
     else if ((op == 1) && (contBL <=60))
     {
       op = 0;
       myGLCD.drawBitmap(0, 0, principal_sensores, 84, 48);
     }  
   }
   else
   {   
     op = 1;
     tela = 0;
     myGLCD.drawBitmap(0, 0, principal_luzes, 84, 48);     
   }    
  }
  else if (buttonStateOK == HIGH)
  {
    acendeBL();
    cont2++;
      
    if(contBL == 61)
    {
      myGLCD.drawBitmap(0, 0, principal_luzes, 84, 48);    
    }
      
    if((op == 1) && (contBL <= 60) && (tela == 0))
    {
         
      if(buttonStateLED == 0)
      {
        buttonStateLED = 1;
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
      }
      else
      {
        buttonStateLED = 0;
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
      }
    }
      
    else if  ((op == 0) && (tela == 0) && (contBL <= 60))
    {
      preTelaSensores();
    }    
    
    contBL = -1;
  }
   
  //Pink Floyd
  if((cont == 6) && (cont2 == 5))
  {
    myGLCD.drawBitmap(0, 0, pf, 84, 48);
    delay(2000);
    cont = 0;
    cont2 = 0; 
    myGLCD.drawBitmap(0, 0, principal_luzes, 84, 48);
  }     
}

void verificaBL()
{
  if(contBL == 60)
  {
    apagaBL(&contBL);
    screensaver();
    contBL = 61;
  }
  else if (contBL < 60)
  {
    contBL++;
  } 
}

void limpa_serial(){

    while (Serial.read() != -1){
      //delay(10);
    }
}

void parar_motores(){
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);
  parado = '1';
}

void acel_motores(int acel){
  m1.setSpeed(acel);
  m2.setSpeed(acel);
  m3.setSpeed(acel);
  m4.setSpeed(acel);
}

void mov_motores(char op){
   dist = ultrassom();
   if(dist<=20)
     parar_motores();
   //Serial.println(op);
   int acel = op;
   if(acel>=1&&acel<=6){
     acel=(acel+4)*25;
     acel_motores(acel);
     Serial.print(acel); //
   //  Serial.print(" <-> "); //
   }
   Serial.println(op);
   switch(op){
     case 'U':
        Serial1.print(dist);
        //Serial.print(dist);
        //delay();
        break;
     case 'C':
        conectou = '1';
        break;
     case 'Z':
        conectou = '0';
        break;
     case 'D':
        acel_motores(200);
        m1.run(BACKWARD);
        m3.run(FORWARD);
        m2.run(BACKWARD);
        m4.run(FORWARD);
        delay(150);
        parar_motores();
        break;
     case 'E':
        acel_motores(200);
        m1.run(FORWARD);
        m3.run(BACKWARD);
        m2.run(FORWARD);
        m4.run(BACKWARD);
        delay(150);
        parar_motores();
        break;
     case 'P':
        parar_motores();
       break;
     case 'F': 
        m1.run(FORWARD);
        m2.run(FORWARD);
        m3.run(FORWARD);
        m4.run(FORWARD);  
        break;
     case 'T':
        m1.run(BACKWARD);
        m2.run(BACKWARD);
        m3.run(BACKWARD);
        m4.run(BACKWARD);      
        break;
     case 'L':
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        break;
     case 'M':
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        break;
     default: 
        parar_motores();
        break;
  }
}

//Procedimento não utilizado
void comunicacao()
{
  //  if((conectou == '1'))// && (parado == '0'))
  {
    //  dist = ultrassom();
      
     // if (dist <= 10)
      {
        //Serial.print("pitstop");
       // parar_motores();
      }
  }
  
  if (Serial1.available()) {  //Se tiver dados na porta serial para ler,
    char command=Serial1.read();
    
    //Serial.print(commandAux);
    //Serial.print("<-int  || char - >");
    mov_motores(command);
    
   // delay(5); //Intervalo de tempo para a próxima leitura
  }
}
  


void setup()
{
  //Inicializa Motores
  Serial1.begin(9600);//Inicia a comunicação serial
  Serial.begin(9600);
  //acel_motores(acel);
  //parar_motores();
  
  //Inicializa o visor
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  
  //Timer1.initialize(500000);
  //Timer1.attachInterrupt(); 
  
  //Inicializa os botoes
  pinMode(buttonNaveg, INPUT);
  pinMode(buttonOK, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(BL,OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  pinMode(23,OUTPUT);
  pinMode(34,OUTPUT);
  pinMode(36,OUTPUT);
  pinMode(38,INPUT); //dhtpin
 // pinMode(41,OUTPUT);
 // pinMode(43,OUTPUT); //bl
 // pinMode(45,OUTPUT);
  pinMode(50,OUTPUT);
  pinMode(53,OUTPUT);
  
  pinMode(27,OUTPUT);
  pinMode(49,OUTPUT);
  digitalWrite(27,HIGH);
  digitalWrite(49,LOW);
  
  digitalWrite(BL,HIGH); 
  digitalWrite(led1, LOW);
  
  digitalWrite(led2, LOW);
 
  digitalWrite(23,LOW);
  digitalWrite(34,LOW);
  digitalWrite(36,HIGH);
  
  //digitalWrite(41,HIGH); /bl
  //digitalWrite(43,LOW); //
  //digitalWrite(45,LOW);
  digitalWrite(50,LOW);
  digitalWrite(53,LOW);
  
  //Imprime Splahscreen
  imprimeCabecalho();
 
  //Imprime a tela inicial (menu)
  myGLCD.drawBitmap(0, 0, principal_luzes, 84, 48);
 
 //Inicializa sensor de Temperatura e Umidade
  dht.begin();
     
}

void loop()
{ 
  //aux=!aux;
  //digitalWrite(led1,aux);
  dist = ultrassom();
  
  comunicacao();
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if((tela == 1) && (contBL <= 60))
  {
    imprimeDHT(&t,&h);
    imprimeDist(&dist);
  }
  
  
  buttonStateNaveg = digitalRead(buttonNaveg);
  buttonStateOK = digitalRead(buttonOK);

  verificaBotoes();
  
  verificaBL();

  //contSD++;
}
