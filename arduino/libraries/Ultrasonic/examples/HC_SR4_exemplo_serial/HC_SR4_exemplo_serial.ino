#include "Ultrasonic.h"
#define echoPin 13 // Pino 13 -> Echo
#define trigPin 12 // Pino 12 -> Trig
Ultrasonic ultrasonic(trigPin,echoPin);

void setup() {
  Serial.begin(9600);
  Serial.println("Testando HC-SR4...");
  delay(1000);
}

void loop(){
  Serial.print("Distancia do Objeto: ");
  Serial.print(ultrasonic.Ranging(CM));
  Serial.println("cm");
  delay(500);
}




