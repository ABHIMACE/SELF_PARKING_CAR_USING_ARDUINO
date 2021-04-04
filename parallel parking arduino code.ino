
#include <AFMotor.h>
    #include <Servo.h> 
    Servo servo1;
AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
    AF_DCMotor motor2(4, MOTOR12_64KHZ);
int distance;
   long duration;
   #define echoPin A2 // attach pin D2 Arduino to pin Echo of HC-SR04
  #define trigPin A3
  int distance1;
   long duration1;
   #define echoPin1 A5 // attach pin D2 Arduino to pin Echo of HC-SR04
  #define trigPin1 A4
  int distance2;
  long duration2;
   #define echoPin2 A1 // attach pin D2 Arduino to pin Echo of HC-SR04
  #define trigPin2 A0
  double  parkingspace;
   double  sidespace;
void setup() {
  servo1.write(90);
   servo1.attach(10);

  // put your setup code here, to run once:
pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT);
  motor1.setSpeed(250); 
      motor2.setSpeed(250);
      spacefind();
      Serial.begin(9600);
      
      
}


void loop() {
  
  // put your main code here, to run repeatedly:

}

double backdistance()
{ digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
   
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Serial.print("Distance: ");
  Serial.print(distance);
  return distance;
}

double sidedistance()
{ digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
   
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Serial.print("Distance: ");
  Serial.print(distance1);
  return distance1;
}

double frontdistance()
{ digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
   
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Serial.print("Distance: ");
  Serial.print(distance2);
  return distance2;
}

void spacefind()
{
  sidespace=sidedistance();
      servo1.write(90);
      delay(900);

 while(sidespace>10) 
  {     
  sidespace=sidedistance();
      
       motor1.setSpeed(250); 
      motor2.setSpeed(250);
      motor1.run(FORWARD);
      
      motor2.run(FORWARD);
      
  }

  
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(600);
    reversedrive();
  }
void reversedrive() 
{     
      parkingspace = sidedistance();
servo1.write(10);
delay(900);
 while(parkingspace<12) 
  {     parkingspace=sidedistance();
        
        motor1.setSpeed(254); 
      motor2.setSpeed(150);
      motor1.run(BACKWARD);
      
      motor2.run(BACKWARD);
      delay(300);
    
  }

   
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(600);
    servo1.write(90);
    delay(900);
     parkingspace = backdistance();
    while(parkingspace>14) 
  {     parkingspace = backdistance();
        
        motor1.setSpeed(250); 
      motor2.setSpeed(200);
      motor1.run(BACKWARD);
      
      motor2.run(BACKWARD);
     
  }
 motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(600);
   
    sidedrive();
    
     
}
void sidedrive() 
{     
      parkingspace = backdistance();
      sidespace=sidedistance();
      servo1.write(150);
      delay(900);

 while(parkingspace>5 && sidespace>2) 
  {

parkingspace = backdistance();
  sidespace=sidedistance();
      
        motor1.setSpeed(180); 
      motor2.setSpeed(250);
      motor1.run(BACKWARD);
      
      motor2.run(BACKWARD);
      
  }

  
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(600);
    servo1.write(90);
    
    frwddrive();
     
}

void frwddrive() 
{     
      parkingspace = frontdistance();
      sidespace=sidedistance();
      servo1.write(80);
      delay(900);

 while(parkingspace >5) 
  {     parkingspace = frontdistance();
  sidespace=sidedistance();
      
        motor1.setSpeed(250); 
      motor2.setSpeed(250);
      motor1.run(FORWARD);
      
      motor2.run(FORWARD);
      
  }

  
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(600);
    servo1.write(90);
    
    
     
}