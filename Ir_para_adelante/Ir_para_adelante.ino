int kMotorLP = 9;
int kMotorLN = 10;
int kMotorRP = 5;
int kMotorRN = 6;
/* Configuramos los pines en cero para apagar el motor */

void setup(){

digitalWrite(kMotorLP, LOW);
digitalWrite(kMotorLN, LOW);
digitalWrite(kMotorRP, LOW);
digitalWrite(kMotorRN, LOW);

}

void loop(){

  analogWrite(kMotorLP, 42); 
  analogWrite(kMotorLN, 0); 
  analogWrite(kMotorRP, 42); 
  analogWrite(kMotorRN, 0);

delay(1000);

}
