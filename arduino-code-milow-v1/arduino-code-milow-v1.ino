


#include <avr/pgmspace.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

//Display





//Four wheel drive module by Jonas.J

//Controls from keyboard
//
// space        -   Stop all motors
//
// up_arrow     -   Forward all motors
// down-arrow   -   Reverse all motors
// left_arrow   -   forward on both right side Motors M4 & M3
// right_arrow  -  forward on both left side Motors M1 & M2
//
//Later implementations
// 1			- 	slow speed
// 2			- 	medium speed
// 3			- 	full speed
//


//Declaration of pins on arduino for Motors

//speed
int speedPin = 6;

// Left Motors (1 and 2)
int forwardPinL = 2;
int reversePinL = 3;

// Right Motors (3 and 4)
int forwardPinR = 4;
int reversePinR = 5;

int i=1;
long stack[100][2];
long time;
int speed = 130;                 //init speed

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete



// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
int row = 0;


//Stopwatch
class StopWatch
{
   public:
      long startTime;   	
      long stopTime;  		
      long elapsedTime;
      int direc;   	
};

StopWatch stopWatchF;

void startClock(int type){
	stopWatchF.startTime = millis();
        stopWatchF.direc = type;
}
void stopClock(){
	stopWatchF.stopTime = millis();
}

long elapsedTime(){
	stopWatchF.elapsedTime = stopWatchF.stopTime - stopWatchF.startTime;
	return stopWatchF.elapsedTime;
}

void store(long time){
  stack[0][0] = 0;
  stack[0][1] = 0;
  long dirVector[2] = {stopWatchF.direc,time};
  stack[i][0] = dirVector[0];
  stack[i][1] = dirVector[1];
  i = i + 1;
}

void forward(){
  digitalWrite(forwardPinL, HIGH);
	digitalWrite(forwardPinR, HIGH);
};

void turnLeft(){
	digitalWrite(forwardPinR, HIGH);
};

void turnRight(){
	digitalWrite(forwardPinL, HIGH);
};

void reverse(){
	digitalWrite(reversePinL, HIGH);
	digitalWrite(reversePinR, HIGH);
};

void revLeft(){
	digitalWrite(reversePinR, HIGH);
};

void revRight(){
	digitalWrite(reversePinL, HIGH);
};

void increaseSpeed(){
  speed = speed + 10;
  analogWrite(speedPin,speed);
};

void decreaseSpeed(){
  speed = speed - 10;
  analogWrite(speedPin,speed);
};

void stop(){
	digitalWrite(forwardPinL, LOW);
	digitalWrite(reversePinL, LOW);
	digitalWrite(forwardPinR, LOW);
	digitalWrite(reversePinR, LOW);
};

void prnt(String output){
  if(row % 4 == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    }
  int set = (row%4);
  lcd.setCursor(0,set);
  lcd.print(output);
  row ++;
  }

void setup() {
// put your setup code here, to run once:
// initialize serial communication @ 115200 baud:
	Serial.begin(74880);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

 
  
//Define arduino pins
	pinMode(forwardPinL, OUTPUT);
	pinMode(reversePinL, OUTPUT);
	pinMode(forwardPinR, OUTPUT);
	pinMode(reversePinR, OUTPUT);
  pinMode(speedPin, OUTPUT);
  
  analogWrite(speedPin,speed);

//displayports
lcd.begin(20,4);     // initialize the lcd for 20 chars 4 lines and turn on backlight
lcd.backlight(); // finish with backlight on  


lcd.setCursor(0,0); //Start at character 0 on line 0
lcd.print("Milow ON");
}

void loop() {
// put your main code here, to run repeatedly:

  if (stringComplete) {
      Serial.println(inputString);
      inputString.trim();
      prnt(inputString);
      if (inputString == "F1" || inputString.endsWith("F1")){
        forward();
         
      }
      if (inputString == "F0" || inputString.endsWith("F0")){
        stop();
        //prnt(inputString);
      }
  
  
      if (inputString == "l1" || inputString.endsWith("l1")){
        turnLeft();
        //prnt(inputString);
      }
      if (inputString == "l0" || inputString.endsWith("l0")){
        stop();
        //prnt(inputString);
      }
  
  
      if (inputString == "r1" || inputString.endsWith("r1")){
        turnRight();
        //prnt(inputString);
      }
      if (inputString == "r0" || inputString.endsWith("r0")){
        stop();
        //prnt(inputString);
      }
  
  
      if (inputString == "R1" || inputString.endsWith("R1")){
        reverse();
        //prnt(inputString);
      }
      if (inputString == "R0" || inputString.endsWith("R0")){
        stop();
        //prnt(inputString);
      }
      
      // clear the string:
      inputString = "";
      stringComplete = false;
    }
  }


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  
}
