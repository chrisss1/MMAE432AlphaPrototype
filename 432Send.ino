#include <SoftwareSerial.h>
#include <Servo.h>
#define setPin 4
int platPot = A0;     // select the input pin for the potentiometer
int indPot = A1;      // potentiometer pin for individual motor speed
int ledPin = 13;       // select the pin for the LED
int buttonPin = 8;    // push button pin
int val = 0; 

Servo ESC1;

SoftwareSerial HC12(11, 10);              // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);                   // Open serial port to computer
  HC12.begin(9600);                     // Open serial port to HC12
  
  ESC1.attach(8,1000,2000);
  ESC1.write(0);
  
  pinMode(ledPin, OUTPUT);              // declare LED as output
  pinMode(buttonPin, INPUT);            // declare pushbutton as input
  //pinMode(setPin, OUTPUT);
  
  //digitalWrite(setPin, LOW);
  //delay(250);
  //HC12.write("AT+DEFAULT");
  //delay(250);
  //digitalWrite(setPin, HIGH);           // HC-12 normal, transparent mode
}

void loop() 
{

  val = digitalRead(buttonPin);         // read input value
  if (val == HIGH) {                    // check if the input is HIGH (button released)
    digitalWrite(ledPin, HIGH);          // turn LED ON
  } else {
    digitalWrite(ledPin, LOW);         // turn LED OFF
  }
  
  while (ledPin == 1) 
  {
    
    int platformSpeed = analogRead(platPot);
    platformSpeed = map(platformSpeed, 0, 1023, 0, 180);
    
    int individualSpeed = analogRead(indPot);
    indiviudalSpeed = map(individualSpeed, 0, 1023, 0, 180);
    
    Serial.println(platformSpeed);
    Serial.println(individualSpeed);
    HC12.println(individualSpeed);
    
    ESC1.write(platformSpeed);
    
    button = digitalRead(buttonPin);
    if (val == HIGH)                        // check if the input is HIGH (button released)
    {                  
      digitalWrite(ledPin, LOW);            // turn LED OFF
      HC12.println(0);
      ESC1.write(0);
    } 
    else 
    {
      digitalWrite(ledPin, HIGH);           // turn LED ON
    }
    
  }

 }
