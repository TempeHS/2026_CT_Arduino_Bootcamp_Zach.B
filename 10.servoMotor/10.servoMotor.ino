/*
  Author:

  Learning Intention:
  The students will learn how to connect and control a servo motor.

  Success Criteria:
    1.  I understand how to connect the servo motor
    2.  I can manually write different degrees of movement to the servo
    3.  I can map a potentiometer to a servo and control its movement
    4.  I understand that a 180deg servo angle of movement is set by a frequency signal sent from the microcontroller

  Student Notes: 

  Documentation:
    https://www.sparkfun.com/servos
    https://github.com/arduino-libraries/Servo <-- We are still using this library

  Schematic:
    https://www.tinkercad.com/things/lQ9RyYJRoLn?sharecode=MKlN0A7R0WGodkdTRKkPJO7I8PeI5L_GCR7pCclQ0qM
    https://github.com/TempeHS/TempeHS_Ardunio_Bootcamp/blob/main/10.servoMotor/Bootcamp-servoMotor.png
*/

// Includes for OLED Screen
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
// Includes for servo
#include <Servo.h>
// Includes for ultrasonic
#include "Ultrasonic.h"

unsigned static int servoPin = 6;
unsigned static int usPin = 5;

Servo myservo; // create servo object to control a servo
Ultrasonic us_sensor(usPin); //create ultrasonic object

int potpin = A1; // analog pin used to connect the potentiometer
int val; // variable to read the value from the analog pin                                                                                                         q

// Configure OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C OLED(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

void setup() {
  myservo.attach(servoPin);  // attaches the servo on pin 6 to the servo object
  Serial.begin(9600);
  Serial.println("Baud 9600");
  Serial.println("---------");
  OLED.begin();
}xkzzzzzzzzzz,nma

void loop()  {
  
  OLED.clearBuffer();
  unsigned long RangeInCm;
  RangeInCm = us_sensor.distanceRead();
  if (RangeInCm > 100) {
    RangeInCm = 100;
  }
  String distanceString = String(RangeInCm);
  int servoAngle = map(RangeInCm, 0, 100, 0, 180);
  myservo.write(servoAngle);
  String servoString = String(servoAngle);
  OLED.setFont(u8g2_font_6x12_tf);
  OLED.drawStr(0, 20, servoString.c_str());
  OLED.drawStr(0, 10, distanceString.c_str());
  OLED.nextPage();

  /*myservo.write(RangeInCm);
  Serial.print(RangeInCm);
  Serial.println(" cm"); 
  
  // oled write ultrasonic

  
  
  // potentiometer use with servo

  val = analogRead(potpin);            // reads the value of the potentiometer
  val = map(val, 0, 1023, 180, 0);     // scale it to use with the servo (val)
  myservo.write(val);                  // sets the servo position according to the potentiometer
  delay(15);                           // waits for the servo to get there
  */
} 