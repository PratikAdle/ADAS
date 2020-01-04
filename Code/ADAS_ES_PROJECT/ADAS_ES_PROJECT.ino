#include <Servo.h>
Servo servo1;
int i;

// Declaring pins for dc Motor 
int rm1 = 8;
int rm2 = 9;
int lm1 = 11;
int lm2 = 10;

// Trigger and Echo pins for Ultrasonic Sensor (US1) present on front
int TriggerPIN1 = 3;  
int EchoPIN1 = 4;

// Trigger and Echo pins for Ultrasonic Sensor (US2) present on right at back 
int TriggerPIN2 = 6;  
int EchoPIN2 = 7;

// Trigger and Echo pins for Ultrasonic Sensor (US3) present on left at back 
int TriggerPIN3 = 12;  
int EchoPIN3 = 13;
 
int safe_distance = 10; // safe distance in cm

void setup() {
  // put your setup code here, to run once:
  servo1.attach(2);
  servo1.write(0);
  Serial.begin(9600);

  
  pinMode(TriggerPIN1,OUTPUT);
  pinMode(EchoPIN1,INPUT);
  pinMode(TriggerPIN2,OUTPUT);
  pinMode(EchoPIN2,INPUT);
  pinMode(TriggerPIN3,OUTPUT);
  pinMode(EchoPIN3,INPUT);
  //pinMode(motor, OUTPUT);

  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
}

void loop() {

  // US1 on Servo Motor points in front
  servo1.write(90);
  delay(1000);

  // Calculating distance of car from obstacle using US1
  digitalWrite(TriggerPIN1,LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPIN1,HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPIN1,LOW);
  
  long timedelay1 = pulseIn(EchoPIN1,HIGH);
  int distance1 = 0.0343 * (timedelay1/2);
  Serial.println("distance1: ");
  Serial.print(distance1);
  
  
  delayMicroseconds(2);


  // Calculating distance of car from obstacle using US2
  digitalWrite(TriggerPIN2,LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPIN2,HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPIN2,LOW);
  
  long timedelay2 = pulseIn(EchoPIN2,HIGH);
  int distance2 = 0.0343 * (timedelay2/2);
  Serial.println("distance2:");
  Serial.print(distance2);
  
  delayMicroseconds(2);

  // Calculating distance of car from obstacle using US3
  digitalWrite(TriggerPIN3,LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPIN3,HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPIN3,LOW);
  
  long timedelay3 = pulseIn(EchoPIN3,HIGH);
  int distance3 = 0.0343 * (timedelay3/2);
  Serial.println("distance3: ");
  Serial.print(distance3);
  
  
   
  if (distance1 < 10)
  {
    // If distance from obstacle detected by US1 is less than 
    // 10 cm then stop the car
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, LOW);
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, LOW);
  
    if (distance2 < 20)
    {
      // If obstacle detected by US2 then stop the car  
      Serial.println("Danger"); 
    }
    else
    {
      // If obstacle not detected by US2 then check if obstacle
      // is there on front right side
      servo1.write(30);
      delay(4000);

      // Calculating distance of car from obstacle using US1 again
      // for front right side
      digitalWrite(TriggerPIN1,LOW);
      delayMicroseconds(2);
      digitalWrite(TriggerPIN1,HIGH);
      delayMicroseconds(10);
      digitalWrite(TriggerPIN1,LOW);
      
      long timedelay1 = pulseIn(EchoPIN1,HIGH);
      int distance1 = 0.0343 * (timedelay1/2);
      Serial.println(distance1);
      servo1.write(90); // come back to the straight position
      
      if (distance1 < 10)
      {
        // If obstacle is detected then stop
        Serial.println("Stop");
        servo1.write(90);

  
        servo1.write(150);
        delay(4000);

        // Calculating distance of car from obstacle using US1 again
        // for front left side 
        digitalWrite(TriggerPIN1,LOW);
        delayMicroseconds(2);
        digitalWrite(TriggerPIN1,HIGH);
        delayMicroseconds(10);
        digitalWrite(TriggerPIN1,LOW);
        
        long timedelay1 = pulseIn(EchoPIN1,HIGH);
        int distance1 = 0.0343 * (timedelay1/2);
        Serial.println(distance1);
        servo1.write(90); // come back to the straight position
  
        if (distance3 < 20 )
        {
          Serial.println("Stop");
        }
  
        else
        {
              if (distance1  < 10)
              {
                Serial.println("Stop");
              }
              
              else
              {
                  // If no obstacle on front left side and back lefgt side 
                  // Change lane to left lane
                  Serial.println("Overtake");
                  servo1.write(90);
      
                  digitalWrite(rm1, LOW);
                  digitalWrite(rm2, LOW);
                  digitalWrite(lm1, HIGH);
                  digitalWrite(lm2, LOW);
                  delay(5000); 
      
                  digitalWrite(rm1, HIGH);
                  digitalWrite(rm2, LOW);
                  digitalWrite(lm1, LOW);
                  digitalWrite(lm2, LOW);
                  delay(3000);
              }
        }
      }
      
      else
      {
        // If no obstacle on front right side and back right side 
        // Change lane to right lane
        Serial.println("Overtake");
        servo1.write(90);
        digitalWrite(rm1, HIGH);
        digitalWrite(rm2, LOW);
        digitalWrite(lm1, LOW);
        digitalWrite(lm2, LOW);
        delay(5000);
        
        digitalWrite(rm1, LOW);
        digitalWrite(rm2, LOW);
        digitalWrite(lm1, HIGH);
        digitalWrite(lm2, LOW);
        delay(3000);
      }
    }
    
  }
  else{
    // If no obstacle on front side then don't stop the car
    digitalWrite(rm1, HIGH);
    digitalWrite(rm2, LOW);
    digitalWrite(lm1, HIGH);
    digitalWrite(lm2, LOW);
  }
}
