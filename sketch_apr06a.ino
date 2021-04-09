#include <Servo.h>
//#include <AFMotor.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>
 
//AF_DCMotor motor(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor = AFMS.getMotor(1);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


int pos = 0;
String state = "INIT";

const int pingPin = 6; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor0

int servoPos = 90;
int sPeed = 200;

const int increment = 10;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal

   // Ultrasonic sensor
   pinMode(pingPin, OUTPUT);
   pinMode(echoPin, INPUT);
   
   myservo.attach(10);
   Serial.println("Motor test!");
    
   AFMS.begin();
   motor->setSpeed(sPeed);     // set the speed to 200/255
}

void loop() {
   long result = ultra();

   if (Serial.available() > 0) {
    // read the incoming byte:
    state = Serial.readString();
    Serial.print("Current state ");
    Serial.print(state);
  }

  
  if (result < 6){
    for (int i = 0; i < 10; i++){
      motor->run(BACKWARD);
      delay(100); 
    }
    motor->run(RELEASE);
  }
  if ((state == "INIT")){
    myservo.write(90);
    servoPos = 90;
    motor->run(RELEASE);
  } 
  else if (state == "FARRIGHT"){
    servoPos = 160;
  }
  else if (state == "FARLEFT"){
    servoPos = 20;
  }
  else if (state == "RIGHT"){
    servoPos = 120;
  }
  else if (state == "LEFT"){
    servoPos = 60;
  }
  else if (state == "FORWARD"){
    motor->run(FORWARD); 
  }
  else if (state == "BACKWARD"){
    motor->run(BACKWARD); 
  }
  else if (state == "SPEEDUP"){
    sPeed++;
    motor->setSpeed(sPeed);
  }
  else if (state == "STOP"){
    motor->run(RELEASE);
  }
  delay(100);

  myservo.write(servoPos);
//   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);
//    Serial.print("Servo position: ");
//    Serial.print(pos);
//    Serial.println(" degree");// tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos); 
//    Serial.print("Servo position: ");
//    Serial.print(pos);
//    Serial.println(" degree");// tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//
//  Serial.print("Forward");
//  
//  motor->run(FORWARD);      // turn it on going forward
//  delay(1000);
// 
//  Serial.print("Backward");
//  motor->run(BACKWARD);     // the other way
//  delay(1000);
//  
//  Serial.print("Stop");
//  motor->run(RELEASE);      // stopped
//  delay(1000);

}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

long ultra(){
   long duration, cm;
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   delay(100);
   return cm;
}
