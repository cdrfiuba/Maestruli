int kMotorLP_D = 9;
int kMotorLN_D = 10;
int kMotorLP_I = 5;
int kMotorLN_I = 6;

const int TriggerPinB = A4;
const int EchoPinB = 2;
const int TriggerPinC = A5;
const int EchoPinC = 7;

long Duration_B = 0;
long Duration_C = 0;


void setup(){

  Serial.begin(9600);
  
/*Configuramos motores*/

  digitalWrite(kMotorLP_D, LOW);
  digitalWrite(kMotorLN_D, LOW);

  digitalWrite(kMotorLP_I, LOW);
  digitalWrite(kMotorLN_I, LOW);

/*Configuramos sensores*/

  pinMode(TriggerPinB, OUTPUT);
  pinMode(EchoPinB, INPUT);

  pinMode(TriggerPinC, OUTPUT);
  pinMode(EchoPinC, INPUT);

}

void loop () {

/*Hacemos funcion loop para los sensores*/

  digitalWrite(TriggerPinB, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPinB, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPinB, LOW);
  
  Duration_B = pulseIn(EchoPinB, HIGH);

  digitalWrite(TriggerPinC, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPinC, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPinC, LOW);
  
  Duration_C = pulseIn(EchoPinC, HIGH);
  
  //Calculamos la distancia en mm
  
  long Distance_mm_B = ((Duration_B /2.9) / 2);
  long Distance_mm_C = ((Duration_C /2.9) / 2);

 Serial.print("DistanciaB = "); 
 Serial.print(Distance_mm_B);
 Serial.print("DistanciaC = ");
 Serial.print(Distance_mm_C);
 delay(1000);
  
  while (Distance_mm_B < 200 && Distance_mm_C < 200) {
  /*Establesco velocidad del motor*/
  digitalWrite(kMotorLN_D, 60);
  digitalWrite(kMotorLN_I, 60);
  }
  
  while (Distance_mm_B > 200) {
  /*Establesco velocidad del motor*/
  digitalWrite(kMotorLN_D, 30);
  digitalWrite(kMotorLN_I, 30);
  }
  
  while (Distance_mm_B > 200 && Distance_mm_C > 200) {
      
  /*Establesco velocidad del motor*/
  digitalWrite(kMotorLN_D, LOW);
  digitalWrite(kMotorLN_I, LOW);
  
  /*Gira a la izquierda*/
  digitalWrite(kMotorLN_D, 0);
  digitalWrite(kMotorLN_I, 30);
  
  }
  
  
  
  
  
  
  
  
  
}
