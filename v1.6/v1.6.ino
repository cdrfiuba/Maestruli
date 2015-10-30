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
int kMotorLP = 9;
int kMotorLN = 10;
int kMotorRP = 5;
int kMotorRN = 6;

const int Vel_MotorR_adelante = 45;
const int Vel_MotorL_adelante = 47;

/*Definicion de varibles varias, necesarias para el desarrollo del código*/
int Diferencia; 
int outA;
int outB; 
int outC;
int duration;

const int debugMode = 0;


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
  delay (60);
  DistanceB_mm = readSensor(TriggerPinB, EchoPinB);
  delay (60);
  DistanceC_mm = readSensor(TriggerPinC, EchoPinC);
 
  outA = map(DistanceA_mm, 0, 1023, 120, 255);
//  analogWrite(ledR, outA);
  outB = map(DistanceB_mm, 0, 1023, 0, 255);
//  analogWrite(ledA, outB);
  outC = map(DistanceC_mm, 0, 1023, 0, 255);
//  analogWrite(ledV, outC);

/*Cálculo de la diferencia de lectura entre los sensores laterales*/  
  Diferencia = DistanceB_mm - DistanceC_mm;

/*Separacion por caso según resultado de la variable anterior*/

/*Caso 1: los sensores estan a una distancia de la pared izquierda entre 5 y 9 cm, la diferencia entre sensores es menor a 2 cm*/

  if ( (Diferencia < 20) && (DistanceB_mm > 50) && (DistanceB_mm < 90) && (DistanceC_mm > 50) && (DistanceB_mm < 90) && (DistanceA_mm > 70) ) {
      //Los motores deben avanzar derecho
        analogWrite(kMotorLP, Vel_MotorL_adelante); 
        analogWrite(kMotorLN, 0); 
        analogWrite(kMotorRP, Vel_MotorR_adelante); 
        analogWrite(kMotorRN, 0);
        if (debugMode) {
          Serial.print("caso_1 = ");
          Serial.println(Diferencia, DEC);
          delay(500);
        }
 }

/*Caso 2: algún sensor esta más lejos que 9 cm de la pared izquierda*/

  else if ( ((DistanceB_mm > 90) || (DistanceC_mm > 90)) && (DistanceA_mm > 70) ) {

/*Caso 2_a: la diferencia es mayor que 0, por ende DistanceC_mm es menor que DistanceB_mm.*/
      if (Diferencia > 0) {
        //El motor izquierdo debe ir más rápido para "enderezar" el robot
        analogWrite(kMotorLP, Vel_MotorL_adelante - 5); 
        analogWrite(kMotorLN, 0); 
        analogWrite(kMotorRP, Vel_MotorR_adelante - 5); 
        analogWrite(kMotorRN, 0);
        if (debugMode) {
          Serial.print("caso_2a = ");
          Serial.println(Diferencia, DEC);
          delay(500);
        }
      }

/*Caso 2_b: la diferencia es menor que 0, por ende DistanceC_mm es mayor que DistanceB_mm.*/
    if (Diferencia < 0) {
      //El motor derecho debe ir más rápido para "enderezar" el robot
      analogWrite(kMotorLP, 0); 
      analogWrite(kMotorLN, 0); 
      analogWrite(kMotorRP, Vel_MotorR_adelante - 10); 
      analogWrite(kMotorRN, 0);
      if (debugMode) {
          Serial.print("caso_2b = ");
          Serial.println(Diferencia, DEC);
          delay(500);
        }
    }
    
  }

/*Caso 3: algún sensor esta a menos de 5 cm de la pared izquierda*/

  else if ( ((DistanceB_mm < 50) || (DistanceC_mm < 50)) && (DistanceA_mm > 70) ) {

/*Caso 3_a: la diferencia es mayor que 0, por ende DistanceC_mm es menor que DistanceB_mm.*/
     if (Diferencia > 0) {
        //El motor izquierdo debe ir más rápido para "enderezar" el robot
        analogWrite(kMotorLP, Vel_MotorL_adelante - 10); 
        analogWrite(kMotorLN, 0); 
        analogWrite(kMotorRP, 0); 
        analogWrite(kMotorRN, 0);
        if (debugMode) {
          Serial.print("caso_3a = ");
          Serial.println(Diferencia, DEC);
          delay(500);
        }
     }

/*Caso 3_b: la diferencia es menor que 0, por ende DistanceC_mm es mayor que DistanceB_mm.*/
     if (Diferencia < 0) {
      //El motor derecho debe ir más rápido para "enderezar" el robot
      analogWrite(kMotorLP, Vel_MotorL_adelante); 
      analogWrite(kMotorLN, 0); 
      analogWrite(kMotorRP, Vel_MotorR_adelante); 
      analogWrite(kMotorRN, 0);
      if (debugMode) {
          Serial.print("caso_3b = ");
          Serial.println(Diferencia, DEC);
          delay(500);
      }
     }
    
  }

/*Caso 4: se llega a una esquina, por ende debe girar*/
 
  else if ( (DistanceA_mm < 70) && ( (DistanceB_mm < 100) || (DistanceC_mm < 100) ) ) {
      while(DistanceA_mm<70){ 
        // gira a la derecha 
        analogWrite(kMotorLP, Vel_MotorL_adelante); 
        analogWrite(kMotorLN, 0); 
        analogWrite(kMotorRP, 0); 
        analogWrite(kMotorRN, Vel_MotorR_adelante);
        DistanceA_mm = readSensor(TriggerPinA, EchoPinA);
//        delay (15);
        if (debugMode) {
            Serial.print("caso_4a_A = ");
            Serial.println(DistanceA_mm, DEC);
            Serial.print("caso_4a_B = ");
            Serial.println(DistanceB_mm, DEC);
            delay(500);
        }    
      }
    }
    else {
      while(DistanceA_mm<70){ 
        // gira a la izquierda 
        analogWrite(kMotorLP, 0); 
        analogWrite(kMotorLN, Vel_MotorL_adelante); 
        analogWrite(kMotorRP, Vel_MotorR_adelante); 
        analogWrite(kMotorRN, 0);
        DistanceA_mm = readSensor(TriggerPinA, EchoPinA);
//        delay (15);
        if (debugMode) {
          Serial.print("caso_4b_A = ");
          Serial.println(DistanceA_mm, DEC);
          Serial.print("caso_4b_B = ");
          Serial.println(DistanceB_mm, DEC);
          delay(1000);
        }            
      }
      //Los motores deben avanzar derecho
      analogWrite(kMotorLP, Vel_MotorL_adelante); 
      analogWrite(kMotorLN, 0); 
      analogWrite(kMotorRP, Vel_MotorR_adelante); 
      analogWrite(kMotorRN, 0);
      delay (2000);    
   }

      
  //delay(20);
}

