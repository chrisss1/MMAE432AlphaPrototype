#include <SoftwareSerial.h>
#include <Servo.h>
#define setPin 4
int platPot = A0;                                               // select the input pin for the potentiometer
int indPot = A1;                                                // potentiometer pin for individual motor speed
int ledPin = 13;                                                // select the pin for the LED
int buttonPin = 8;                                              // push button pin 

Servo ESC1;                                                     //Initialize ESC1 as Servo

SoftwareSerial HC12(11, 10);                                    // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);                                           // Open serial port to computer
  HC12.begin(9600);                                             // Open serial port to HC12
  
  ESC1.attach(9);                                               //Connect ESC1 to pin 9
  ESC1.write(0);                                                //Write a speed of 0 to ESC1
  
  pinMode(ledPin, OUTPUT);                                      // declare LED as output
  pinMode(buttonPin, INPUT);                                    // declare pushbutton as input
  
  //pinMode(setPin, OUTPUT);
  //digitalWrite(setPin, LOW);
  //delay(250);
  //HC12.write("AT+DEFAULT");
  //delay(250);
  //digitalWrite(setPin, HIGH);                                 // HC-12 normal, transparent mode
}

void loop() 
{

  int val = digitalRead(buttonPin);                             // read input value
  //Serial.println(val);
  int led = 0;
  if (val == HIGH) {                                            // button pressed (HIGH)
    digitalWrite(ledPin, HIGH);                                 // turn LED ON
    led = 1;
  } else {                                                      // ELSE, i.e. button released (LOW)
    digitalWrite(ledPin, LOW);                                  // turn LED OFF
    led = 0;
  }


  
  while (led == 1)                                              //While the led is on, do this loop
  {
    
    int platformSpeed = analogRead(platPot);                    //Read the first potentiometer value
    platformSpeed = map(platformSpeed, 0, 1023, 0, 90);         //Convert it from 10 bit binary 0 ~ 180 (limited to 90)
    
    int individualSpeed = analogRead(indPot);                   //Read the second potentiometer value
    individualSpeed = map(individualSpeed, 0, 1023, 0, 90);     //Convert it from 10 bit binary 0 ~ 180 (limited to 90)
    
    Serial.println(platformSpeed);                              //Printing on Serial monitor on PC for verification
    Serial.println(individualSpeed);                            //Printing on Serial monitor on PC for verification
    HC12.println(individualSpeed);                              //Sending the desired value via the HC12 module
    
    ESC1.write(platformSpeed);                                  //Write the desired speed to the large motor

    delay(100);                                                 //Delay for better Serial communication
 
    int button = digitalRead(buttonPin);                        //Check button state 
    if (button == LOW)                                          //button released (LOW)
    {                  
      digitalWrite(ledPin, HIGH);                               // leave LED ON, WHILE loop will continue
    } 
    else                                                        //Button IS pressed, i.e. want to turn off stirrer 
    {
      digitalWrite(ledPin, LOW);                                // turn LED OFF
      HC12.println(0);                                          //Send a speed of 0 to the other HC12 module
      ESC1.write(0);                                            //Write a speed of 0 to the big motor
      led = 0;                                                  //Change value of led so that WHILE loop is stopped
      delay(200);                                               
    }
    
  }

 }
