/*Definicion de los pines necesrios para el funcionamiento de los sensores de ultrasonido.*/ 
/*Se determina su ubicacion de la siguiente manera: A=adelenate; B=lateral_atras; C=lateral_adelante*/ 
const int TriggerPinA = A3;
const int EchoPinA = 8;
const int TriggerPinB = A4;
const int EchoPinB = 2;
const int TriggerPinC = A5;
const int EchoPinC = 7;

/*Definicion de variables para medir la distancia de la pared con el sensor*/
int DistanceA_mm;
int DistanceB_mm;
int DistanceC_mm;

/*Definicion de los pines necesarios para el funcionamiento del led*/
const int ledA = 13;
const int ledR = 12;
const int ledV = 11;

/*Deficion de los pines necesarios para el funcionamiento del motor*/
int kMotorLP = 5;
int kMotorLN = 6;
int kMotorRP = 9;
int kMotorRN = 10;

/*Definicion de varibles varias, necesarias para el desarrollo del código*/
int Diferencia; 
int outA;
int outB; 
int outC;
int duration;

void setup() {
  
/*Iniciallizacion de pines como entradas o salidas*/
  pinMode(ledA, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledV,OUTPUT);
  
  pinMode(TriggerPinA, OUTPUT);
  pinMode(EchoPinA, INPUT);
  pinMode(TriggerPinB, OUTPUT);
  pinMode(EchoPinB, INPUT);
  pinMode(TriggerPinC, OUTPUT);
  pinMode(EchoPinC, INPUT);
  
  Serial.begin(9600);

/*Inicializacion de variables, primera escritura*/ 
  digitalWrite(ledA,LOW);
  digitalWrite(ledR,LOW);
  digitalWrite(ledV,LOW);
 
  digitalWrite(kMotorLP, LOW);
  digitalWrite(kMotorLN, LOW);
  digitalWrite(kMotorRP, LOW);
  digitalWrite(kMotorRN, LOW);
}

int readSensor(int trigger, int echo) {
   digitalWrite(trigger, LOW);
   delayMicroseconds(2);
   digitalWrite(trigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigger, LOW);
   
   duration = pulseIn(echo, HIGH);

   if (duration < 0) duration = 0;
   return ((duration / 2.9) / 2);
}
 
void loop() {
  
 /*Lectura de la distancia de los sensores ultrasónicos con la pared*/ 
  DistanceA_mm = readSensor(TriggerPinA, EchoPinA);
  DistanceB_mm = readSensor(TriggerPinB, EchoPinB);
  DistanceC_mm = readSensor(TriggerPinC, EchoPinC);
 
  outA = map(DistanceA_mm, 0, 1023, 120, 255);
  analogWrite(ledR, outA);
  outB = map(DistanceB_mm, 0, 1023, 0, 255);
  analogWrite(ledA, outB);
  outC = map(DistanceC_mm, 0, 1023, 0, 255);
  analogWrite(ledV, outC);

/*Cálculo de la diferencia de lectura entre los sensores laterales*/  
  Diferencia = DistanceB_mm - DistanceC_mm;

/*Separacion por caso según resultado de la variable anterior*/

/*ACLARACION IMPORTANTE: Los motores estan conectados al reves, por ende el Left es el motor derecho y Right es el motor izquierdo*/

/*Caso 1: la diferencia es mayor que 0, por ende DistanceC_mm es menor que DistanceB_mm.*/
  if (Diferencia > 0) {
      //El motor izquierdo debe ir más rápido para "enderezar" el robot
      analogWrite(kMotorLP, 25); 
      analogWrite(kMotorLN, 0); 
      analogWrite(kMotorRP, 100); 
      analogWrite(kMotorRN, 0);
      Serial.print("caso_1 = ");
      Serial.println(Diferencia, DEC);
//      delay(1000);
   }

/*Caso 2: la diferencia es menor que 0, por ende DistanceC_mm es mayor que DistanceB_mm.*/
  if (Diferencia < 0) {
      //El motor derecho debe ir más rápido para "enderezar" el robot
      analogWrite(kMotorLP, 80); 
      analogWrite(kMotorLN, 0); 
      analogWrite(kMotorRP, 25); 
      analogWrite(kMotorRN, 0);
      Serial.print("caso_2 = ");
      Serial.println(Diferencia, DEC);
 //     delay(1000);
  }

/*Caso 3: el sensor B mide una distancia superior a 80mm, por ende el robot está andando en diagonal*/
  if (DistanceB_mm > 80) {
        //El motor derecho debe ir más rápido para "enderezar" el robot 
        analogWrite(kMotorLP, 50); 
        analogWrite(kMotorLN, 0); 
        analogWrite(kMotorRP, 35); 
        analogWrite(kMotorRN, 0);
        Serial.print("caso_3 = ");
        Serial.println(DistanceB_mm, DEC);
//        delay(1000);
  }
 
  if (DistanceA_mm < 85 && DistanceB_mm < 100 && DistanceC_mm < 100) {
    while(DistanceA_mm<85){ 
      // gira a la derecha 
      analogWrite(kMotorLP, 20); 
      analogWrite(kMotorLN, 60); 
      analogWrite(kMotorRP, 60); 
      analogWrite(kMotorRN, 20);
      Serial.print("ESQUINA = ");
      Serial.println(DistanceA_mm, DEC);
//      delay(1000);
      DistanceA_mm = readSensor(TriggerPinA, EchoPinA);
      DistanceB_mm = readSensor(TriggerPinB, EchoPinB);
      DistanceC_mm = readSensor(TriggerPinC, EchoPinC);
    }
    delay(100);
  }

  delay(20);
}

