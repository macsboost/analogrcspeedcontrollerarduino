//pin 9 - servo
//pin 7 - reverse, shorted to ground for forward.
//pin A0 - analog input from hall effect pedal.

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
int dir;   //direction pin 1 = rev
int lastdir;
const int ledPin =13;
const int threshold = 25;
const int directionchangedelay = 500;
const int minchangeeffort = 150;
const int mineffort = 75;
int directionchangeeffort = 0;
int maxthrottle = 1023;

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
myservo.write(90);
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
digitalWrite(7, HIGH);
Serial.println("Hello, sending zero calibration pulse");
delay(1250);

} 
 
void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
    //Serial.println(val);
    if (val > threshold) {
      digitalWrite(ledPin, HIGH);
    } 
  else {
    digitalWrite(ledPin,LOW); 
  }
  
  dir = digitalRead(7);
  if (dir != lastdir) {
    myservo.write(90);
    delay(directionchangedelay);
    directionchangeeffort = minchangeeffort;
  }
    lastdir = dir;
    
  //reduce throttle slew rate after direction change
  directionchangeeffort = directionchangeeffort +1;
  if (directionchangeeffort > maxthrottle) {
    directionchangeeffort = maxthrottle;
  }
  
  Serial.println(dir);
  val = map(val, 0, 1023, mineffort, directionchangeeffort);
  
  if (dir == 0) {
    val = map(val, 0, 1023, 90, 180);     // scale it to use it with the servo (value between 0 and 180) 
  } else {
    val = map(val, 0, 1023, 90, 0);
  }
  
  
  myservo.write(val);                  // sets the servo position according to the scaled value 
 Serial.println(val);
  delay(2);                           // waits for the servo to get there 
}
