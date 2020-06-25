
#include <Wire.h>

// UltraSonic Pin Setup
const int relayPump = 5; // in1 Relay
const int relayLED = 6; // in2 Relay

const int uSonicTrigPin = 9; 
const int uSonicEchoPin = 8;

int BodyHigh; 

int limitHigh = 100; // Limit Minimum Body High
int sprayTime = 10;



void setup() {

  // UltraSonic 
  pinMode(uSonicTrigPin,OUTPUT); // pin 9 OUTPUT
  pinMode(uSonicEchoPin,INPUT); // pin 8 INPUT
  
  // Relay Pump & LED
  pinMode(relayPump,OUTPUT);
  pinMode(relayLED,OUTPUT);

  pumpOff();
  ledGreenOn();
  //ledRedOn();

  Serial.begin(9600); // For Monitor


}

void loop() {
 
 ChecknRun();
 
}


// ultra Sonic DistanceCal Function
void BodyHighCal(){
  
  long duration; // Time

  delay(300);

  
  digitalWrite(uSonicTrigPin, LOW);
  delayMicroseconds(2);
 
  digitalWrite(uSonicTrigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(uSonicTrigPin, LOW);
 
  duration = pulseIn(uSonicEchoPin, HIGH);
 
  BodyHigh = duration * 0.034 / 2;


  // For Monitor
  Serial.print("BodyHigh: ");
  Serial.println(BodyHigh - 200);
  
}



void ChecknRun(){
 
  BodyHighCal();
  
  if(BodyHigh < 200 - limitHigh && BodyHigh > 5 ){
    // Run 
    ledRedOn();
    delay(1000); // Wait for Ready
    pumpOn();
    
    delay(1000 * sprayTime);
  
    pumpOff();
    ledGreenOn();
    delay(10000); // Wait for Exit
  }

}


// Function Relay LED & Pump Controller

void ledGreenOn(){
  digitalWrite(relayLED,1);
}

void ledRedOn(){
  digitalWrite(relayLED,0);
}

void pumpOn(){
  digitalWrite(relayPump,0);
}

void pumpOff(){
  digitalWrite(relayPump,1);
}
