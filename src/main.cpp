#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Disp.h>
#include <Parone.h>



const int atFloorLedPin = 3;
const int upLedPin = 6;
const int downLedPin = 10;
const int upButtonPin = 8;
const int downButtonPin = 9;
const int sensorPin = 12;

int elevatorAtFloor = false;
// int doorsOpen = false;
int elevatorCalledUp = false;
int elevatorCalledDown = false;


//routine for when the elevator gets called up
//currently only lights up the led. when the master code
//works this will also send a request for the elevator to the
//master.
void callElevatorUp() {
    digitalWrite(upLedPin, HIGH);
}

// //same as callElevatorUp routine but then for going down
void callElevatorDown() {
    digitalWrite(downLedPin, HIGH);
}

// simulates opening the doors.
// this function in conjunction with
// the closeDoors routine will
// make sure the elevator is
// held at our floor using a delay
void openDoors() {
  if(elevatorAtFloor) {
    int doorsOpen = true;
  }
}

//see openDoors routine
void closeDoors() {
  if(elevatorAtFloor) {
    int doorsOpen = true;
  }
}



void setup ()
{
  //set pins to output
  Serial.begin(9600);

  pinMode(atFloorLedPin, OUTPUT);
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  pinMode(upLedPin, OUTPUT);
  pinMode(downLedPin, OUTPUT);

  initDisplay();

  Level * level = initLevel(0);

}

void loop()
{
  //checks if the elevator cage is at our floor
  //by checking the sensor output
  if(digitalRead(sensorPin) == LOW) {
    // //disables the light for elevator up
    if(elevatorCalledUp) {
      digitalWrite(upLedPin, LOW);
      displayResetArrowUp();
    }
    // //disables the light for elevator down
    if(elevatorCalledDown) {
      digitalWrite(downLedPin, LOW);
      displayResetArrowDown();
    }

    displaySetSideBar('0');
    displaySetFloor('0');
    rerenderDisplay();
    digitalWrite(atFloorLedPin, HIGH);

    elevatorAtFloor = true;
  }

  if(digitalRead(sensorPin) == HIGH) {
    displaySetSideBar('5');
    displaySetFloor('?');
  }



  // if elevator has left again this gets triggered to reset all
  // variables
  if(elevatorAtFloor && digitalRead(sensorPin) == HIGH) {
    digitalWrite(atFloorLedPin, LOW);
    elevatorAtFloor = false;
    Serial.print("ELEVATOR LEAVING\n");
  }

  //routine for handling if the going up button is pressed
  if(digitalRead(upButtonPin) == LOW) {
    Serial.print("Requested direction: UP\n");
    displaySetArrowUp();
    digitalWrite(upLedPin, HIGH);
    elevatorCalledUp = true;
    callElevatorUp();
  }
  
  //routine for handling if the going up button is pressed
  if(digitalRead(downButtonPin) == LOW) {
    Serial.print("Requested direction: DOWN\n");
    displaySetArrowDown();
    digitalWrite(downLedPin, HIGH);
    elevatorCalledDown = true;
    callElevatorDown();
  }
  rerenderDisplay();

}

