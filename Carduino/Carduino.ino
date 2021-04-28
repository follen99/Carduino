#include <AFMotor.h> //includo la libreria
#include <Stepper.h>

//################ MOTORS ################
AF_DCMotor motor1(1);  //creo la variabile del motore1, ovvero il sx del retro.
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
#define SPEED 200
#define ROTATION_SPEED 255
#define ROTATION_TIME 1250
//################ MOTORS ################


//################ SENSORE ################
#define STEPS 100
Stepper stepper(STEPS, A0, A1, A2, A3, A4); //inizializzo lo stepper (da cambiare assolutamente con un servo)
const int TrigPin = 2;    //pin per effettuare il pulse
const int EchoPin = A5;   //pin per effettuare l'echo del sensore
float distance;           //distanza calcolata

float distanceToUse;
//################ SENSORE ################




String command;
void setup() {
  Serial.begin(9600);

  //################ MOTORS ################
  motor1.setSpeed(SPEED);    //velocità del motore
  motor2.setSpeed(SPEED);    //velocità del motore
  motor3.setSpeed(SPEED);    //velocità del motore
  motor4.setSpeed(SPEED);    //velocità del motore
  stopMotors();
  //################ MOTORS ################

  //################ SENSORE ################
  stepper.setSpeed(300);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  delay(1000);

  //################ SENSORE ################


  delay(1000);


  //turn(1,ROTATION_TIME);



}


void loop() {
  distanceToUse = getDistance();
  Serial.println(distanceToUse);


  //codice scritto con i piedi
  if (distanceToUse < 20 || distanceToUse > 300) {
    delay(50);    //doppio controllo per essere sicuro
    if (getDistance() < 20 || getDistance() > 300) {
      stopMotors();
      goBackward();
      delay(1000);

      turn(1, ROTATION_TIME);

      if (getDistance() > 50) {
        goForward();
      } else {
        turn(0, ROTATION_TIME);
        turn(0, ROTATION_TIME);
        if (getDistance() > 50) {
          goForward();
        } else {
          turn(1, ROTATION_TIME);
          goBackward();
          delay(1000);
        }
      }
    }
  }

  delay(50);
}




float watchLeft() {
  stepper.step(1200);

  float distance = getDistance();

  //stepper.step(-1000);

  return distance;
}

float watchRight() {
  stepper.step(-1200);

  float distance = getDistance();

  //stepper.step(-1000);

  return distance;
}

void turnLeft() {
  stepper.step(150);
}
void turnRight() {
  stepper.step(-150);
}



float getDistance() {
  //genero un pulse di 10us
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  //leggo la grandezza del pulse e calcolo la distanza

  distance = pulseIn(EchoPin, HIGH) / 58.00;
  //Serial.print(distance);
  //Serial.print("cm");
  //Serial.println();

  return distance;
}


void goForward() {
  runMotor(3, 1);
  runMotor(2, 1);
  runMotor(1, 1);
  runMotor(4, 1);
}

void goBackward() {
  runMotor(3, 0);
  runMotor(2, 0);
  runMotor(1, 0);
  runMotor(4, 0);
}

void stopMotors() {
  motor1.run(RELEASE);     //stato di stop
  motor2.run(RELEASE);     //stato di stop
  motor3.run(RELEASE);     //stato di stop
  motor4.run(RELEASE);     //stato di stop
}

/**
  boolean: 0 left 1 right
*/
void turn(boolean directionToTurn, int amount) {

  motor1.setSpeed(ROTATION_SPEED);    //velocità del motore
  motor2.setSpeed(ROTATION_SPEED);    //velocità del motore
  motor3.setSpeed(ROTATION_SPEED);    //velocità del motore
  motor4.setSpeed(ROTATION_SPEED);    //velocità del motore


  stopMotors();

  if (directionToTurn) { //giro a destra
    delay(100);   //aspetto che la macchina si fermi

    runMotor(3, 0);
    runMotor(2, 0);
    runMotor(1, 1);
    runMotor(4, 1);

    delay(amount); //mezzo secondo
  } else {   //giro a sinistra
    delay(100);   //aspetto che la macchina si fermi

    runMotor(3, 1);
    runMotor(2, 1);
    runMotor(1, 0);
    runMotor(4, 0);

    delay(amount); //mezzo secondo
  }

  stopMotors();
  motor1.setSpeed(SPEED);    //velocità del motore
  motor2.setSpeed(SPEED);    //velocità del motore
  motor3.setSpeed(SPEED);    //velocità del motore
  motor4.setSpeed(SPEED);    //velocità del motore
}

/**
  int motore : motore da muovere
  bool dir : direzione del motore 1 avanti 0 indietro
*/
void runMotor(int motore, bool dir) {
  if (motore == 1) {
    if (dir) {
      motor1.run(FORWARD);
    } else motor1.run(BACKWARD);
  } else if (motore == 2) {
    if (dir) {
      motor2.run(BACKWARD);
    } else motor2.run(FORWARD);
  } else if (motore == 3) {
    if (dir) {
      motor3.run(BACKWARD);
    } else motor3.run(FORWARD);
  } else if (motore == 4) {
    if (dir) {
      motor4.run(BACKWARD);
    } else motor4.run(FORWARD);
  }
  return;
}





/*if(Serial.available()){
    command = Serial.readStringUntil('\n');
    command.trim();
    if(command.equals("turnLeft")){

    }else if(command.equals("turnRight")){

    }else if(command.equals("go")){
      goForward();
      delay(1000);

      stopMotors();
    }else if(command.equals("back")){
      goBackward();
      delay(1000);

      stopMotors();
    }else if(command.equals("left")){
      turnLeft();
    }else if(command.equals("right")){
      turnRight();
    }else if(command.equals("watch_l")){
      Serial.println(watchLeft());
      stepper.step(-1200);
    }else if(command.equals("watch_r")){
      Serial.println(watchRight());
      stepper.step(1200);
    }else if(false){

    }else{
      Serial.println("comando non riconosciuto");
    }
  }*/
