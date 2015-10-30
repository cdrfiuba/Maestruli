/*Definicion de los pines necesarios para el funcionamiento de los sensores de ultrasonido.*/ 
/*Deficion de los pines necesarios para el funcionamiento del motor*/
int kMotorLP = 9;
int kMotorLN = 10;
int kMotorRP = 5;
int kMotorRN = 6;

const int Vel_MotorR_adelante = 41;
const int Vel_MotorL_adelante = 42;

void setup() {
  
/*Inicializacion de variables, primera escritura*/ 

  digitalWrite(kMotorLP, LOW);
  digitalWrite(kMotorLN, LOW);
  digitalWrite(kMotorRP, LOW);
  digitalWrite(kMotorRN, LOW);
}

void loop() {
  
    // gira a la derecha 
    analogWrite(kMotorLP, Vel_MotorL_adelante); 
    analogWrite(kMotorLN, 0); 
    analogWrite(kMotorRP, 0); 
    analogWrite(kMotorRN, Vel_MotorR_adelante);
    delay (500);
/*
    // gira a la izquierda 
    analogWrite(kMotorLP, 0); 
    analogWrite(kMotorLN, Vel_MotorL_adelante); 
    analogWrite(kMotorRP, Vel_MotorR_adelante); 
    analogWrite(kMotorRN, 0);
    delay(525);
*/
    //Stop
    digitalWrite(kMotorLP, LOW);
    digitalWrite(kMotorLN, LOW);
    digitalWrite(kMotorRP, LOW);
    digitalWrite(kMotorRN, LOW);
    delay (2000);


}
