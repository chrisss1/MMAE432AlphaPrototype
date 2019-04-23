#include <SoftwareSerial.h>
#define setPin 4
int platPot = A0;     // select the input pin for the potentiometer
int indPot = A1;      // potentiometer pin for individual motor speed
int ledPin = 8;       // select the pin for the LED
int buttonPin = 7;    // push button pin
int val = 0; 

SoftwareSerial HC12(3, 2);              // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);                   // Open serial port to computer
  HC12.begin(9600);                     // Open serial port to HC12
  
  pinMode(ledPin, OUTPUT);              // declare LED as output
  pinMode(buttonPin, INPUT);            // declare pushbutton as input
  pinMode(setPin, OUTPUT);
  
  digitalWrite(setPin, LOW);
  delay(250);
  HC12.write("AT+DEFAULT");
  delay(250);
  digitalWrite(setPin, HIGH);           // HC-12 normal, transparent mode
}

void loop() 
{

  val = digitalRead(buttonPin);         // read input value
  if (val == HIGH) {                    // check if the input is HIGH (button released)
    digitalWrite(ledPin, LOW);          // turn LED OFF
  } else {
    digitalWrite(ledPin, HIGH);         // turn LED ON
  }
  delay(20)
  
  while (ledPin == 1) 
  {
    
    int platformSpeed = analogRead(platPot);
    platformSpeed = map(platformSpeed, 0, 1023, 0, 180);
    
    int individualSpeed = analogRead(indPot);
    indiviudalSpeed = map(individualSpeed, 0, 1023, 0, 180);
    
    Serial.println(individualSpeed);
    HC12.println(individualSpeed);
    
    delay(50);
    
    button = digitalRead(buttonPin);
    if (val == HIGH)                        // check if the input is HIGH (button released)
    {                  
      digitalWrite(ledPin, HIGH);           // turn LED OFF
    } 
    else 
    {
      digitalWrite(ledPin, LOW);            // turn LED ON
    }
    
  }

 }
