#include <ZumoShield.h>
#include <ZumoMotors.h>
#define maxspeed  300

ZumoMotors motor;
int distanc;
int distance1;
int distance2;
int val;
int val1;
int val2;
int error;
int diff;
int leftspeed;
int rightspeed;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  delay(1000);

}


void loop() {
 distanc = analogRead(A3); // Left Sensor
 val = map(distanc, 50, 400, 80, 10);
  

  distance1 = analogRead(A1); // middle
  val1 = map(distance1,50,400,80,10);
  
  distance2 = analogRead(A0); // Right sensor
  val2 = map(distance2,50,400,80,10);
  
  
  if(val1>30 && val>30&&val2>30){  // Keep going forward if no obstacles are present
    motor.setSpeeds(maxspeed,maxspeed);
  }
   if(val1<30 && val>30&&val2>30){  // If the the middle sensor detects an obstacle, move either right or left

    error = val1;
    diff = 7*error;
    leftspeed = maxspeed + diff;
    rightspeed = maxspeed - diff;
    motor.setSpeeds(leftspeed,rightspeed);
   
  }
  if(val<30 || val2<30){ // if either left or right sensors detect an obstacle , turn away
    error = val-val2;
    diff = 7*error;
    leftspeed = maxspeed - diff;
    rightspeed = maxspeed + diff;
    motor.setSpeeds(leftspeed,rightspeed);
  }
   if(val1<30 && val<30&&val2<30){  //Turn either left or right if a big obstacle is present
    int maxi = max(val,val2);
    diff = 7*error;
    leftspeed = maxspeed + diff;
    rightspeed = maxspeed - diff;
    motor.setSpeeds(leftspeed,rightspeed);
   }
   if(val1<-25 && val<-25&&val2<-25){ // Stop if its a dead end
    motor.setSpeeds(0,0); 
