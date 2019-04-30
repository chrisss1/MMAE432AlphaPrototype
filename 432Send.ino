#include <SoftwareSerial.h>
#include <Servo.h>
#define setPin 4
int platPot = A0;     // select the input pin for the potentiometer
int indPot = A1;      // potentiometer pin for individual motor speed
int ledPin = 13;       // select the pin for the LED
int buttonPin = 8;    // push button pin 

Servo ESC1;

SoftwareSerial HC12(11, 10);              // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);                   // Open serial port to computer
  HC12.begin(9600);                     // Open serial port to HC12
  
  ESC1.attach(9);
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

  int val = digitalRead(buttonPin);         // read input value
  //Serial.println(val);
  int led = 0;
  if (val == HIGH) {                    // button pressed (HIGH)
    digitalWrite(ledPin, HIGH);          // turn LED ON
    led = 1;
  } else {
    digitalWrite(ledPin, LOW);         // turn LED OFF
    led = 0;
  }


  
  while (led == 1) 
  {
    
    int platformSpeed = analogRead(platPot);
    platformSpeed = map(platformSpeed, 0, 1023, 0, 90);
    
    int individualSpeed = analogRead(indPot);
    individualSpeed = map(individualSpeed, 0, 1023, 0, 90);
    
    Serial.println(platformSpeed);
    Serial.println(individualSpeed);
    HC12.println(individualSpeed);
    
    ESC1.write(platformSpeed);

    delay(100);
 
    int button = digitalRead(buttonPin);
    if (button == LOW)                      //button released (LOW)
    {                  
      digitalWrite(ledPin, HIGH);           // turn LED ON
    } 
    else 
    {
      digitalWrite(ledPin, LOW);            // turn LED OFF
      HC12.println(0);
      ESC1.write(0);
      led = 0;
      delay(200);
    }
    
  }

 }
