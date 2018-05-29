#include <MCP42010.h>
// SPI pins for Arduino UNO are CS=2, CLK=4, MOSI=5

MCP42010 digipot(2, 4, 5);

//set pin numbers
const int switchLED = 6;         //Pin 6 is the RED LED for switch activation
const int switchPin = 7;
const int accelBullPin = 3; ///////
const int gyroBullPin = 13; /////////
const int stopButtonPin = 8;
const int goButtonPin = 9;
const int easyButtonPin = 10;
const int medButtonPin = 11;

const int hardButtonPin = 12;

//variables will change
int switchState = 0;          //variables for reading the pushbutton status
boolean powerFlowState = false;
int gyroValue=0;
int gyroPower=0;
int accelValue=0; 
int accelPower=0;
int intensity=0;

void setup() {

  Serial.begin(9600);
  pinMode(switchLED, OUTPUT);    //initialize the LED pin as an output
  pinMode(switchPin, INPUT);  //initialize the pushbutton pin as an output
  pinMode(stopButtonPin, INPUT);
  pinMode(goButtonPin, INPUT);
  pinMode(easyButtonPin, INPUT);
  pinMode(medButtonPin, INPUT);
  pinMode(hardButtonPin, INPUT);
}

void loop() {
  checkPowerState();
  checkSwitchState(); //read the state of the mode switch value
  if(powerFlowState == true){
    while(powerFlowState == true){
      checkPowerState();
      if (switchState == HIGH) {            //check if the pushbutton is pressed
        intensity=0; //shut off buttonMode power
         checkSwitchState(); //read the state of the mode switch value
        //if it is, the buttonState is HIGH
        digitalWrite(switchLED, HIGH);         //turn LED on    
        Serial.println("LED ON +++++++"); 
    
        accelValue = analogRead(0);
        gyroValue = analogRead(1);
        
        accelPower = map(accelValue, 0, 1023, 0, 255);// scales from low to high  to A new low to high
        //Serial.print(accelPower);
        //Serial.println("");
        accelPower= (abs(accelPower-122.5)*2);
        if(accelPower>255)
          accelPower= 255;
        //Serial.print(accelPower);
        //Serial.println("");
        gyroPower = map(gyroValue, 0, 1023, 0, 255);
        
        analogWrite(gyroBullPin, gyroPower);
        analogWrite(accelBullPin, accelPower);
        //accelPower = 255-accelPower; /////////////////////////
        digipot.setPot(2, accelPower);  //digipot 2 is accel
        //digipot.setPot(1, gyro);
        digipot.setPot(1, accelPower);
        Serial.print(accelPower);
        Serial.println("");
        checkPowerState();
      }
      else {
        digitalWrite(switchLED, LOW);          // turn switchLED off to indicate buttonMode
        checkSwitchState(); //read the state of the mode switch value
        gyroPower= 0;
        accelPower= 0;
        analogWrite(gyroBullPin, gyroPower);
        analogWrite(accelBullPin, accelPower);
        digipot.setPot(2, gyroPower);  //digipot 2 is gyro
        digipot.setPot(1, accelPower);
        while(switchState == LOW) { 
        checkPowerState();
        checkIntensityState();
        }
      }
    }
  }
}

void checkPowerState(){
  //if (digitalRead(goButtonPin))
    powerFlowState = true;
/*  if (digitalRead(goButtonPin == LOW)){
    powerFlowState = false;
//      analogWrite(gyroBullPin, 0);
//      analogWrite(accelBullPin, 0);
    digipot.setPot(2, 0);  //digipot 2 is gyro
    digipot.setPot(1, 0);
    Serial.println("STOPPPED");*/
    //}
}

void checkIntensityState(){
  if (digitalRead(easyButtonPin)){
      gyroPower= 75;
      accelPower= 75;
//      analogWrite(gyroBullPin, gyroPower);
//      analogWrite(accelBullPin, accelPower);
        digipot.setPot(2, gyroPower);  //digipot 2 is gyro
        digipot.setPot(1, accelPower);
      Serial.print(accelPower);
      Serial.println("");
  }
  if (digitalRead(medButtonPin)){
      gyroPower= 150;
      accelPower= 150;
//      analogWrite(gyroBullPin, gyroPower);
//      analogWrite(accelBullPin, accelPower);
      digipot.setPot(2, gyroPower);  //digipot 2 is gyro
      digipot.setPot(1, accelPower);
      Serial.print(accelPower);
      Serial.println("");
  }
  if (digitalRead(hardButtonPin)){
      gyroPower= 255;
      accelPower= 255;
//      analogWrite(gyroBullPin, gyroPower);
//      analogWrite(accelBullPin, accelPower);
      digipot.setPot(2, gyroPower);  //digipot 2 is gyro
      digipot.setPot(1, accelPower);
      Serial.print(accelPower);
      Serial.println("");
  }
}

void checkSwitchState(){
  switchState = digitalRead(switchPin);
  if (switchState == HIGH){             //check if the switch is engaged
      digitalWrite(switchLED, HIGH);         //turn LED on   
      Serial.println("ON");
  }
  else {
      digitalWrite(switchLED, LOW);
      Serial.println("OFF");
      }
}

