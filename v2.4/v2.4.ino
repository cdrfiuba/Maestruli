/*Definicion de los pines necesarios para el funcionamiento de los sensores de ultrasonido.*/ 
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

const int Vel_MotorR_adelante = 41;
const int Vel_MotorL_adelante = 42;

/*Definicion de varibles varias, necesarias para el desarrollo del código*/
int Diferencia; 
int duration;

const int debugMode = 0;

void setup() {
  
/*Iniciallizacion de pines como entradas o salidas*/
  
  pinMode(TriggerPinA, OUTPUT);
  pinMode(EchoPinA, INPUT);
  pinMode(TriggerPinB, OUTPUT);
  pinMode(EchoPinB, INPUT);
  pinMode(TriggerPinC, OUTPUT);
  pinMode(EchoPinC, INPUT);

  pinMode(ledV, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledA, OUTPUT);
  
  if (debugMode) {
    Serial.begin(9600);
  }


/*Inicializacion de variables, primera escritura*/ 

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

void Prueba_Led (bool R, bool V, bool A) {
  digitalWrite(ledR,R);
  digitalWrite(ledV,V);
  digitalWrite(ledA,A);
}

 
void loop() {
  
 /*Lectura de la distancia de los sensores ultrasónicos con la pared*/ 
  DistanceA_mm = readSensor(TriggerPinA, EchoPinA);
  delay (55);
  DistanceB_mm = readSensor(TriggerPinB, EchoPinB);
  delay (55);
  DistanceC_mm = readSensor(TriggerPinC, EchoPinC);
 
/*Cálculo de la diferencia de lectura entre los sensores laterales*/  
  Diferencia = DistanceB_mm - DistanceC_mm;

/*Separacion por caso según resultado de la variable anterior*/

/*Caso 1: los sensores estan a una distancia de la pared izquierda entre 6,5 y 9 cm, la diferencia entre sensores es menor a 2 cm y mayor a -2 cm, el sensor delantero mide una distancia mayor a 70 cm*/

  if ( (Diferencia <= 20) && (Diferencia >= -20) && (DistanceB_mm >= 65) && (DistanceB_mm <= 90) && (DistanceC_mm >= 65) && (DistanceC_mm <= 90) && (DistanceA_mm >= 70) ) {
      //Los motores deben avanzar derecho
        analogWrite(kMotorLP, Vel_MotorL_adelante); 
        analogWrite(kMotorLN, 0); 
        analogWrite(kMotorRP, Vel_MotorR_adelante); 
        analogWrite(kMotorRN, 0);
        if (debugMode) {
          Serial.print("caso_1_Diferencia = ");
          Serial.println(Diferencia, DEC);
          delay(500);
        }
      Prueba_Led (LOW, LOW, LOW);
  }

 /*Caso 5: llega a una T */

  else if ( (DistanceA_mm >= 300) && ( (DistanceB_mm >= 250) && (DistanceC_mm >= 250) ) ) {
    if ( (DistanceA_mm <= DistanceB_mm) && (DistanceA_mm <= DistanceC_mm) ) {
       // gira a la izquierda 
      analogWrite(kMotorLP, 0); 
      analogWrite(kMotorLN, Vel_MotorL_adelante); 
      analogWrite(kMotorRP, Vel_MotorR_adelante); 
      analogWrite(kMotorRN, 0);
      delay(520);
      //Los motores deben avanzar derecho
      analogWrite(kMotorLP, Vel_MotorL_adelante); 
      analogWrite(kMotorLN, 0); 
      analogWrite(kMotorRP, Vel_MotorR_adelante); 
      analogWrite(kMotorRN, 0);
      delay(1000);
      if (debugMode) {
        Serial.print("caso_5a_A = ");
        Serial.println(DistanceA_mm, DEC);
        Serial.print("caso_5a_B = ");
        Serial.println(DistanceB_mm, DEC);
        Serial.print("caso_5a_C = ");
        Serial.println(DistanceC_mm, DEC);
        delay(500);
      }      
      Prueba_Led (HIGH, LOW, LOW); 
    }
    
    else {
      //Los motores deben avanzar derecho
      analogWrite(kMotorLP, Vel_MotorL_adelante); 
      analogWrite(kMotorLN, 0); 
      analogWrite(kMotorRP, Vel_MotorR_adelante); 
      analogWrite(kMotorRN, 0);
      delay(1000);
      if (debugMode) {
        Serial.print("caso_5b_A = ");
        Serial.println(DistanceA_mm, DEC);
        Serial.print("caso_5b_B = ");
        Serial.println(DistanceB_mm, DEC);
        Serial.print("caso_5b_C = ");
        Serial.println(DistanceC_mm, DEC);
        delay(500);
      }
      Prueba_Led (HIGH, HIGH, LOW);
    }
  }

/*Caso 2: algún sensor lateral esta más lejos que 9 cm de la pared izquierda*/

  else if ( ( (DistanceB_mm > 90) || (DistanceC_mm > 90) ) && ( (DistanceB_mm <= 250) || (DistanceC_mm <= 250) ) && (DistanceA_mm >= 70) )  {

/*Caso 2_a: la diferencia es mayor que 0, por ende DistanceC_mm es menor que DistanceB_mm.*/
    if (Diferencia > 0) {
        //El motor izquierdo debe ir más rápido para "enderezar" el robot
        analogWrite(kMotorLP, Vel_MotorL_adelante - 5); 
        analogWrite(kMotorLN, 0); 
        analogWrite(kMotorRP, Vel_MotorR_adelante - 10); 
        analogWrite(kMotorRN, 0);
        if (debugMode) {
          Serial.print("caso_2a_Diferencia = ");
          Serial.println(Diferencia, DEC);
          Serial.print("caso_2a_B = ");
          Serial.println(DistanceB_mm, DEC);
          Serial.print("caso_2a_C = ");
          Serial.println(DistanceC_mm, DEC);
          delay(500);
        }
        Prueba_Led (LOW, HIGH, LOW);
    }

/*Caso 2_b: la diferencia es menor que 0, por ende DistanceC_mm es mayor que DistanceB_mm.*/
    if ((Diferencia <= 0) && (Diferencia >= -250)) {
        //El motor derecho debe ir más rápido para "enderezar" el robot
        analogWrite(kMotorLP, Vel_MotorL_adelante - 10); 
        analogWrite(kMotorLN, 0); 
        analogWrite(kMotorRP, Vel_MotorR_adelante - 5); 
        analogWrite(kMotorRN, 0);
        if (debugMode) {
            Serial.print("caso_2b_Diferencia = ");
            Serial.println(Diferencia, DEC);
            Serial.print("caso_2b_B = ");
            Serial.println(DistanceB_mm, DEC);
            Serial.print("caso_2b_C = ");
            Serial.println(DistanceC_mm, DEC);
            delay(500);
        }
        Prueba_Led (HIGH, LOW, HIGH);
    }
  }

/*Caso 3: algún sensor lateral esta a menos de 6,5 cm de la pared izquierda*/

  else if ( ( (DistanceB_mm < 65) || (DistanceC_mm < 65) ) && (DistanceA_mm >= 70) ) {

/*Caso 3_a: la diferencia es mayor que 0, por ende DistanceC_mm es menor que DistanceB_mm.*/
      if (Diferencia > 0) {
        //Hace un pequeño giro corrector y luego avanza para cambiar de estado
        analogWrite(kMotorLP, Vel_MotorL_adelante); 
        analogWrite(kMotorLN, 0); 
        analogWrite(kMotorRP, 0); 
        analogWrite(kMotorRN, Vel_MotorR_adelante);
        delay(125);
        analogWrite(kMotorLP, Vel_MotorL_adelante); 
        analogWrite(kMotorLN, 0); 
        analogWrite(kMotorRP, Vel_MotorR_adelante); 
        analogWrite(kMotorRN, 0);
        delay(350);        
        if (debugMode) {
          Serial.print("caso_3a_Diferencia = ");
          Serial.println(Diferencia, DEC);
          Serial.print("caso_3a_B = ");
          Serial.println(DistanceB_mm, DEC);
          Serial.print("caso_3a_C = ");
          Serial.println(DistanceC_mm, DEC);
          delay(500);
        }
        Prueba_Led (LOW, LOW, HIGH);
      }

/*Caso 3_b: la diferencia es menor que 0, por ende DistanceC_mm es mayor que DistanceB_mm.*/
      if (Diferencia <= 0) {
        //Hace un pequeño giro corrector y luego vanza para cambiar de estado.
        analogWrite(kMotorLP, 0); 
        analogWrite(kMotorLN, Vel_MotorL_adelante); 
        analogWrite(kMotorRP, Vel_MotorR_adelante); 
        analogWrite(kMotorRN, 0);
        delay(100);
        analogWrite(kMotorLP, Vel_MotorL_adelante); 
        analogWrite(kMotorLN, 0); 
        analogWrite(kMotorRP, Vel_MotorR_adelante); 
        analogWrite(kMotorRN, 0);
        delay(350);        
        if (debugMode) {
            Serial.print("caso_3b_Diferencia = ");
            Serial.println(Diferencia, DEC);
            Serial.print("caso_3b_B = ");
            Serial.println(DistanceB_mm, DEC);
            Serial.print("caso_3b_C = ");
            Serial.println(DistanceC_mm, DEC);
            delay(500);
        }
        Prueba_Led (LOW, HIGH, HIGH);
      }
  }

/*Caso 4: se llega a una esquina, por ende debe girar*/
 
  else if ( (DistanceA_mm <= 80) && ( (DistanceB_mm < 135) && (DistanceC_mm < 135) ) ) {
    // gira a la derecha 
    analogWrite(kMotorLP, Vel_MotorL_adelante); 
    analogWrite(kMotorLN, 0); 
    analogWrite(kMotorRP, 0); 
    analogWrite(kMotorRN, Vel_MotorR_adelante);
    delay (500);
    if (debugMode) {
        Serial.print("caso_4a_A = ");
        Serial.println(DistanceA_mm, DEC);
        Serial.print("caso_4a_B = ");
        Serial.println(DistanceB_mm, DEC);
        Serial.print("caso_4a_C = ");
        Serial.println(DistanceC_mm, DEC);
        delay(500);
    }
    Prueba_Led (HIGH, HIGH, HIGH);    
  }
  
  else if ( (DistanceA_mm <= 80) && ( (DistanceB_mm >= 135) && (DistanceC_mm >= 135) ) ) {
    // gira a la izquierda 
    analogWrite(kMotorLP, 0); 
    analogWrite(kMotorLN, Vel_MotorL_adelante); 
    analogWrite(kMotorRP, Vel_MotorR_adelante); 
    analogWrite(kMotorRN, 0);
    delay(520);
    //Los motores deben avanzar derecho
    analogWrite(kMotorLP, Vel_MotorL_adelante); 
    analogWrite(kMotorLN, 0); 
    analogWrite(kMotorRP, Vel_MotorR_adelante); 
    analogWrite(kMotorRN, 0);
    delay(1000);
    if (debugMode) {
      Serial.print("caso_4b_A = ");
      Serial.println(DistanceA_mm, DEC);
      Serial.print("caso_4b_B = ");
      Serial.println(DistanceB_mm, DEC);
      Serial.print("caso_4b_C = ");
      Serial.println(DistanceC_mm, DEC);
      delay(500);
    } 
  }
/*Fin del código*/
}
