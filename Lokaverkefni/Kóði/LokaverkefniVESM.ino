#include <AccelStepper.h>
#include <Servo.h>
#define FULLSTEP 4
AccelStepper myStepper(FULLSTEP,  8,  10,  9,  11);
Servo myservo;   
int pos  =  50;   
bool direction  =  true; 
void setup()  {
    myStepper.setMaxSpeed(1000.0);
    myStepper.setAcceleration(50.0);
    myStepper.setSpeed(200);
    myStepper.moveTo(400);
    myservo.attach(7);   
}
void loop()  {
    if  (myStepper.distanceToGo()  ==  0)
    myStepper.moveTo(-myStepper.currentPosition());
    myStepper.run();
    if (direction) {
        pos++;
    } else  {
        pos--;
    }
    if (pos  ==  50  ||  pos  ==  120) {
        direction  =  !direction;
    }
    myservo.write(pos);
    delay(15);
}
