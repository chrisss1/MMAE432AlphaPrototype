#include <SoftwareSerial.h>
#include <Servo.h>
#define setPin 4

Servo ESC1;                                       //Initialize ESC1 as a Servo
Servo ESC2;                                       //Initialize ESC1 as a Servo
SoftwareSerial HC12(11, 10);                      // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);                             // Open serial port to computer
  HC12.begin(9600);                               // Open serial port to HC12

  ESC1.attach(8);                                 //Connect ESC1 to pin 8           
  ESC1.write(0);                                  //Write a speed of 0 to ESC1
  
  delay(100);                                     //Delay for initialization time
  
  ESC2.attach(9);                                 //Connect ESC2 to pin 9   
  ESC2.write(0);                                  //Write a speed of 0 to ESC2
  
  //pinMode(setPin, OUTPUT);
  //digitalWrite(setPin, LOW);
  //delay(250);
  //HC12.write("AT+DEFAULT");
  //delay(250);
  //digitalWrite(setPin, HIGH);                   // HC-12 normal, transparent mode
}

void loop() 
{

  while( HC12.available())                        //If there is data in the HC12 Serial
  {

    int input = HC12.parseInt();                  //converts string to integer

    Serial.println(input);                        //Print it on the serial monitor for torubleshooting with PC
    ESC1.write(input);                            //Write desired speed to ESC1
    ESC2.write(input);                            //Write desired speed to ESC2

    
  }

  //delay(10);                                  //Delay for reading stability



}
