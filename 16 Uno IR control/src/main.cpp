// /**
//  *
//  *****************************************************************
//  * IOT Challenges - https://instagram.com/iotchallenges          *
//  *****************************************************************
//  * Evandro Fruhauf                                               *
//  *  GitHub - https://github.com/evandrodp                        *
//  *  LinkedIn - http://linkedin.com/in/evandrofruhauf             *
//  *****************************************************************
//  * This code can contain parts from other open-sources projects, *
//  * whenever possible it will be quoted.                          *
//  *****************************************************************
//  *
//  * IR Control
//  *
//  * Challenge: Read the IR Control and control the Leds
//  *
//  * This source is using the IRLib2. (In the Lib folder)
//  *
//  * This code is an example from IRLib2 library.
//  *
//   **/
#include <Arduino.h>

#include "IRLibAll.h"

// Set LEDs pins
#define LED_RED 8
#define LED_YELLOW 9
#define LED_GREEN 10
#define LED_BLUE 11

// Initialise the status vars for the leds
int statusRed = LOW;
int statusYellow = LOW;
int statusGreen = LOW;
int statusBlue = LOW;

IRrecvPCI myReceiver(2); // initialise IR receiver 2 pin
IRdecode myDecoder; // create decoder

uint16_t myBuffer[RECV_BUF_LENGTH]; // buffer auxiliar

void changeLedStatus(int led, int& status);
void changeLedsOnOff();
void changeLedsStatus(int value);

void setup() {
  Serial.begin(9600);

  // initialise LEDs  digital pin as an output.
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  myReceiver.enableAutoResume(myBuffer); // enable auto resume and pass it the address of your extra buffer
  myReceiver.enableIRIn(); // enable the receiver
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode(); // decode it
    switch (myDecoder.value) {
      case 0xFFA25D: // Power
        changeLedsOnOff();
        break;
      case 0xFF30CF: // 1
        changeLedStatus(LED_RED, statusRed);
        break;
      case 0xFF18E7: //2
        changeLedStatus(LED_YELLOW, statusYellow);
        break;
      case 0xFF7A85: // 3
        changeLedStatus(LED_GREEN, statusGreen);
        break;
      case 0xFF10EF: // 3
        changeLedStatus(LED_BLUE, statusBlue);
        break;
      case 0xFFB04F: // C
        changeLedsStatus(LOW);
        changeLedStatus(LED_RED, statusRed);
        changeLedStatus(LED_YELLOW, statusYellow);
        changeLedStatus(LED_GREEN, statusGreen);
        changeLedStatus(LED_BLUE, statusBlue);
        break;
    }
    Serial.print(F("Code Received: "));
    Serial.println(myDecoder.value, HEX); // show the value on the serial
    myReceiver.enableIRIn(); // restart receiver
  }
}

void changeLedStatus(int led, int& status) {
  status = !status;
  digitalWrite(led, status);
}

void changeLedsOnOff() {
  int status = statusRed + statusYellow + statusGreen + statusBlue;
  if (status > 0) { // check if any led is on
    changeLedsStatus(LOW); // turn all off
  } else {
    changeLedsStatus(HIGH); // turn all on
  }
  changeLedStatus(LED_RED, statusRed);
  changeLedStatus(LED_YELLOW, statusYellow);
  changeLedStatus(LED_GREEN, statusGreen);
  changeLedStatus(LED_BLUE, statusBlue);
}

void changeLedsStatus(int value) {
  value = !value; // invert the status
  statusRed = value;
  statusYellow = value;
  statusGreen = value;
  statusBlue = value;
}
