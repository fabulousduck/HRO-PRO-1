#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

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

void displaySetSideBar(char floorNumber){
    display.fillRect(25, 1, 9, 127, BLACK);
    display.drawChar(26, 10, '4', WHITE, BLACK, 1);
    display.drawChar(26, 35, '3', WHITE, BLACK, 1);
    display.drawChar(26, 60, '2', WHITE, BLACK, 1);
    display.drawChar(26, 85, '1', WHITE, BLACK, 1);
    display.drawChar(26, 110, '0', WHITE, BLACK, 1);

    int floorNumberInt = floorNumber - 48;
    int textY = 110 - 25 * floorNumberInt;
    int blockY = textY - 3;

    display.fillRect(25, blockY, 8, 13, WHITE);
    display.drawChar(26, textY, floorNumber, BLACK, WHITE, 1);
}

void displaySetFloor(char floorNumber){
    display.fillRect(1, 50, 1, 90, BLACK);
    display.drawChar(1, 50, floorNumber, WHITE, BLACK, 4);
}

void displaySetArrowUp(){
    display.fillRect(9, 20, 5, 15, WHITE);
    display.fillTriangle(11, 10, 5, 20, 17, 20, WHITE);
}

void displayResetArrowUp(){
    display.fillRect(9, 20, 5, 15, BLACK);
    display.fillTriangle(11, 10, 5, 20, 17, 20, BLACK);
}

void displaySetArrowDown(){
    display.fillRect(9, 92, 5, 15, WHITE);
    display.fillTriangle(11, 117, 5, 107, 17, 107, WHITE);
}

void displayResetArrowDown(){
    display.fillRect(9, 92, 5, 15, BLACK);
    display.fillTriangle(11, 117, 5, 107, 17, 107, BLACK);
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

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(3);
  display.clearDisplay();

}

void loop()
{
  //checks if the elevator cage is at our floor
  //by checking the sensor output
  if(digitalRead(sensorPin) == LOW) {
    // //disables the light for elevator up
    if(elevatorCalledUp) {
      digitalWrite(upLedPin, LOW);
    }
    // //disables the light for elevator down
    if(elevatorCalledDown) {
      digitalWrite(downLedPin, LOW);
    }

    displaySetSideBar('0');
    displaySetFloor('0');
    display.display();
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
    digitalWrite(downLedPin, HIGH);
    elevatorCalledDown = true;
    callElevatorDown();
  }
    display.display();

}

