#include <AFMotor.h>
#include <Servo.h> 

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
Servo servo1;
Servo servo2;

int ch1,ch2,ch3,ch4, ltrack, rtrack;
const int in1 = A0, in2 = A1, in3 = A2, in4 = A3;

void setup() {
  Serial.begin(9600);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(in3, INPUT);
  pinMode(in4, INPUT);
  servo1.attach(9);
  servo2.attach(10);
  motor1.setSpeed(255);
  motor1.run(RELEASE);
  motor2.setSpeed(255);
  motor2.run(RELEASE);
}

void loop() {
  ch1 = pulseIn(in1, HIGH, 35000); 
  ch2 = pulseIn(in2, HIGH, 35000);
  ch3 = pulseIn(in3, HIGH, 35000);
  ch4 = pulseIn(in4, HIGH, 35000);

  if(ch1 != 0 || ch2 != 0 || ch3 != 0 || ch4 != 0){
    ch1 = constrain(ch1, 970, 1990);
    ch2 = constrain(ch2, 970, 1990);
    ch3 = constrain(ch3, 970, 1990);
    ch4 = constrain(ch4, 970, 1990);
    ch1 = map(ch1, 970, 1990, -100, 100);
    ch2 = map(ch2, 970, 1990, -100, 100);
    ch3 = map(ch3, 970, 1990, -100, 100);
    ch4 = map(ch4, 970, 1990, 100, -100);

    Serial.print(ch3);

    Serial.print(" || ");

    Serial.println(ch4);
    if((ch4 > 40)||(ch4 < -40)){
      servo1.write(60);
    } else {
      servo1.write(90);
    }

    servo2.write(map(ch3, -100, 100, 0, 45));
    ltrack = ch2 + ch1;
    rtrack = ch2 - ch1;
    ltrack = constrain(ltrack, -100, 100);
    rtrack = constrain(rtrack, -100, 100);
    
    if(ltrack > 5){
      motor1.run(FORWARD);
      motor1.setSpeed(map(ltrack, 6, 100, 0, 255));
    } else if(ltrack < -5){
      motor1.run(BACKWARD);
      motor1.setSpeed(map(ltrack, -6, -100, 0, 255));
    } else {
      motor1.run(RELEASE);
    }

    if(rtrack > 5){
      motor2.run(FORWARD);
      motor2.setSpeed(map(rtrack, 6, 100, 0, 255));
    } else if(rtrack < -5){
      motor2.run(BACKWARD );
      motor2.setSpeed(map(rtrack, -6, -100, 0, 255));
    } else {
      motor2.run(RELEASE);
    }

  } else {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    servo1.write(90);
    servo2.write(0);
  }
}
