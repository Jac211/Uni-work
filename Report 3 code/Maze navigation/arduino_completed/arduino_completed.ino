    //ARDUINO CODE
    
#include <Encoder.h>
#include <Wire.h> // Library for I2C communication

#define I2C_SLAVE_ADDR 0x04
#include <Servo.h>    //Library for servo
#define servoPin 4
Servo myservo;        // create servo object to control a servo
float steeringAngle;


 

//Analog motor pins
#define INa A0  //Left Motor
#define INb A1  //Left Motor 
#define INc A2  //Right Motor 
#define INd A3  //Right Motor 
#define enA 5   
#define enB 6  

byte speedSetting = 0;  

Encoder myEnc(2, 3); //enable pins with interrupt capability

//lcd display settings
/*LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); */
char key = 0;
/*char distanceCm = 0;
bool menuType = false;*/

void setup() {
  //initialising servo and motors
  myservo.attach(servoPin,0,90);
  pinMode(INa, OUTPUT);
  pinMode(INb, OUTPUT);
  pinMode(INc, OUTPUT);
  pinMode(INd, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);  
  
  //initialising I2C communication
  Wire.begin(I2C_SLAVE_ADDR);
  //Wire.begin(21,22);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);


  speedSetting = 255;   //initial motor speed
  myservo.write(123);   //servo default angle (straight)

  motors(speedSetting, speedSetting);

}

void receiveEvent(){
  
  key = Wire.read();  
  Serial.println(key); 
    /*
  distanceCm = Wire.read();
  Serial.println(distanceCm);*/
}

void loop() {

 if(key){    //if a key is pressed, complete following command
    
  if(key == '2') {    //2 = forward for 10cm then stop
      
    goForwards();
   
    delay(1000);

    }
    
  if(key == '8') {    //8 = backwards for 10cm then stop
        
    goBackwards();
   
    delay(1000);
    }
    
  if(key == '4') {    //4 = left for 90 degrees then stop
      
    left90();
   
    delay(1000);   
    }
    
  if(key == '6') {    //6 = right for 90 degrees then stop
   
    right90();
   
    delay(1000);
    }
    
   if(key == '#') {   //# = stop all commands
   
    stopMotors();
    delay(1000);
    }

   if(key == '*') {     //# = stop all commands
   
    stopMotors();
    delay(1000);
   }    
  }
 }
    
 void motors(int leftSpeed, int rightSpeed)
{

 // leftSpeed = 240;
 // rightSpeed = 200;

  analogWrite(enA, leftSpeed);
  analogWrite(enB, rightSpeed);
}

void goForwards() {
  void motors();
  myservo.write(123);
  digitalWrite(INa, HIGH);
  digitalWrite(INb, LOW);
  digitalWrite(INc, HIGH);
  digitalWrite(INd, LOW);    
  delay(1000);
  stopMotors();
}


void goBackwards() {
  void motors();
  myservo.write(123);
  digitalWrite(INa, LOW);
  digitalWrite(INb, HIGH);
  digitalWrite(INc, LOW);
  digitalWrite(INd, HIGH);    
  delay(1100);
  stopMotors();
}

void left90() {
  myservo.write(95);
  
  digitalWrite(INa, HIGH);
  digitalWrite(INb, LOW);
  digitalWrite(INc, HIGH);
  digitalWrite(INd, LOW); 

  delay(1175);
  stopMotors();
}

void right90() {
  myservo.write(175);
  
  digitalWrite(INa, HIGH);
  digitalWrite(INb, LOW);
  digitalWrite(INc, HIGH);
  digitalWrite(INd, LOW); 

  delay(700);
  stopMotors(); 
}

void stopMotors() {
  digitalWrite(INa, LOW);
  digitalWrite(INb, LOW);
  digitalWrite(INc, LOW);
  digitalWrite(INd, LOW);
  key = 123;
}
 
