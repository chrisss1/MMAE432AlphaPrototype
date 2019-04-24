#include <SoftwareSerial.h>
#include <Servo.h>
#define setPin 4

Servo ESC1;
Servo ESC2;
SoftwareSerial HC12(3, 2);              // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);                   // Open serial port to computer
  HC12.begin(9600);                     // Open serial port to HC12

  ESC1.attach(8,1000,2000);
  ESC1.write(0);
  ESC1.attach(9,1000,2000);
  ESC1.write(0);
  pinMode(setPin, OUTPUT);
  
  digitalWrite(setPin, LOW);
  delay(250);
  HC12.write("AT+DEFAULT");
  delay(250);
  digitalWrite(setPin, HIGH);           // HC-12 normal, transparent mode
}

void loop() 
{

  while( HC12.available == 0) 
  {

    if (HC12.available() > 1)               //If there is data in the buffer
    {

      int input = HC12.parseInt();              //converts string to integer
      
      ESC1.write(input);
      ESC2.write(input);
    }
    
  }

  delay(10);                                  //Delay for reading stability



}
