const int TriggerPinA = A3;
const int EchoPinA = 8;
const int TriggerPinB = A4;
const int EchoPinB = 2;
const int TriggerPinC = A5;
const int EchoPinC = 7;

// A=adelenate; B=lateral_atras; C=lateral_adelante;
 
int DistanceA_mm;
int DistanceB_mm;
int DistanceC_mm;
int Diferencia; 
const int ledA = 13;
const int ledR = 12;
const int ledV = 11;
int outA;
int outB; 
int outC;

// IN1 = P  / IN2 = L
int kMotorLP = 5;
int kMotorLN = 6;
int kMotorRP = 9;
int kMotorRN = 10;

// the setup function runs once when you press reset or power the board

void setup() {
  
  // initialize digital pin 13 as an output.
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
 
  digitalWrite(ledA,LOW);
  digitalWrite(ledR,LOW);
  digitalWrite(ledV,LOW);
 
  digitalWrite(kMotorLP, LOW);
  digitalWrite(kMotorLN, LOW);
  digitalWrite(kMotorRP, LOW);
  digitalWrite(kMotorRN, LOW);
}

int  readSensor(int trigger, int echo) {
   int duration;
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
  
  DistanceA_mm = readSensor(TriggerPinA, EchoPinA);
  DistanceB_mm = readSensor(TriggerPinB, EchoPinB);
  DistanceC_mm = readSensor(TriggerPinC, EchoPinC);
 
  outA = map(DistanceA_mm, 0, 1023, 120, 255);
  analogWrite(ledR, outA);
  outB = map(DistanceB_mm, 0, 1023, 0, 255);
  analogWrite(ledA, outB);
  outC = map(DistanceC_mm, 0, 1023, 0, 255);
  analogWrite(ledV, outC);

  Diferencia = DistanceB_mm - DistanceC_mm;

  if (Diferencia > 0) {
      // enderezar motor 
      analogWrite(kMotorLP, 25); 
      analogWrite(kMotorLN, 0); 
      analogWrite(kMotorRP, 100); 
      analogWrite(kMotorRN, 0);
      Serial.print("caso_1 = ");
      Serial.println(Diferencia, DEC);
//      delay(1000);
   }

  if (Diferencia < 0) {
      // enderezar motor 
      analogWrite(kMotorLP, 80); 
      analogWrite(kMotorLN, 0); 
      analogWrite(kMotorRP, 25); 
      analogWrite(kMotorRN, 0);
      Serial.print("caso_2 = ");
      Serial.println(Diferencia, DEC);
 //     delay(1000);
  }

  if (DistanceB_mm > 80) {
     // enderezar motor 
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

/*  if (DistanceA_mm < 75) {
    while(DistanceA_mm<75){ 
      // gira a la derecha 
      analogWrite(kMotorLP, 20); 
      analogWrite(kMotorLN, 60); 
      analogWrite(kMotorRP, 60); 
      analogWrite(kMotorRN, 20);
      Serial.print("ADELANTE = ");
      Serial.println(DistanceA_mm, DEC);
      delay(1000);
      DistanceA_mm = readSensor(TriggerPinA, EchoPinA);
      DistanceB_mm = readSensor(TriggerPinB, EchoPinB);
      DistanceC_mm = readSensor(TriggerPinC, EchoPinC);
    }
      delay(100);
  }  
*/
  delay(20);
}
