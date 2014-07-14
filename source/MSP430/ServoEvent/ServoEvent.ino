#include <Servo.h>

/*
  Servo Event :
  When new serial data arrives, the data is parsed and the servo is moved accordingly.
  
*/
// set pin numbers:
const int buttonPin = PUSH2;     // the number of the pushbutton pin
const int ledPin =  GREEN_LED;      // the number of the LED pin

Servo myservo;  // create servo object to control a servo 
int pos = 0;    // variable to store the servo position 

String inputString = ""; // a string to hold incoming data
String outputString = "";
String stringKey = "joke";  
String stringKey2 = ".";  
int counter = 0;
int position = 1500;
boolean l_execute = false; // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  inputString.reserve(200);
  // servo in pos 11 (2.3)
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object 
  // configure led
  pinMode(ledPin, OUTPUT);
  // Button interruption
  attachInterrupt(PUSH2, buttonPressed, RISING );
}

void loop() {
  // check if something happened
  if (l_execute) {
    //increase counter;
    counter += 1;
    moveServo();
    Serial.println(counter);        
    l_execute = false;
  }
}

// Button interrupt results
void buttonPressed(){
   l_execute = true;
}
// Do something action
void moveServo() {
  noInterrupts();
  myservo.write(position);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  myservo.write(1000);
  interrupts();
}

/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX. This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      if ((inputString.substring(0,4).equals(stringKey)&&(inputString.substring(8).equals(stringKey2)))){
        l_execute = true;
        
        position = StringtoInt(inputString.substring(4,8));
      } 
     inputString = "";
    } else {
    inputString += inChar;    
    }
  }
}

// translates the string into an integer
int StringtoInt (String inputString) {
  int pos = SingleStringtoInt(inputString.substring(0,1));
  pos = pos*10 + SingleStringtoInt(inputString.substring(1,2));
  pos = pos*10 + SingleStringtoInt(inputString.substring(2,3));
  pos = pos*10 + SingleStringtoInt(inputString.substring(3)); 
  return pos;
}

// parses each character
int SingleStringtoInt (String input) {

   if ( input.equals( "1") ) {
   return 1;
   }else if ( input.equals( "2") ) {
   return 2;
   }else if ( input.equals( "3") ) {
   return 3;
   } else if ( input.equals( "4") ) {
   return 4;
   } else if ( input.equals( "5") ) {
   return 5;
   } else if ( input.equals( "6") ) {
   return 6;
   } else if ( input.equals( "7") ) {
   return 7;
   } else if ( input.equals( "8") ) {
   return 8;
   }  else if ( input.equals( "9") ) {
   return 9;
   } else {
   return 0;
   };
      
  }

