#include <Arduino.h>

const int atFloorLedPin = 3;
const int IC1 = 4;
const int IC2 = 5;
const int upLedPin = 6;
const int downLedPin = 7;
const int upButtonPin = 8;
const int downButtonPin = 9;
const int latchPin = 10;
const int clockPin = 11;
const int dataPin = 12;
const int sensorPin = 13;

int elevatorAtFloor = false;
int doorsOpen = false;
int elevatorCalledUp = false;
int elevatorCalledDown = false;
/*=======================================================================================================
//display 0,1,2,3,4,5,6,7,8
Number 0 :  00000011     3 
Number 1 :  10101111     159 
Number 2 :  00100101     37
Number 3 :  00001101     13
Number 4 :  10011001     153
Number 5 :  01001001     73
Number 6 :  01000001     65
Number 7 :  00011111     31
Number 8 :  00000001     1

To display the dot, simply subtract 1.
example : 1 - 1 = 0  or b0000000 0x0 to display 8
*/
/*In order to display zero your array has decimal number 3. However using the shift register
it is actuall the binary number that is uploaded into the resitsre: zie the table above for zero: 00000011. 
*/
int datArray[9] = {3, 159, 37, 13, 153, 73, 65, 31, 1}; // array without the decimal


//routine for when the elevator gets called up
//currently only lights up the led. when the master code
//works this will also send a request for the elevator to the
//master.
void callElevatorUp() {
    digitalWrite(upLedPin, HIGH);
}

//same as callElevatorUp routine but then for going down
void callElevatorDown() {
    digitalWrite(downLedPin, HIGH);
}

//simulates opening the doors.
//this function in conjunction with
//the closeDoors routine will
//make sure the elevator is
//held at our floor using a delay
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
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  pinMode(upLedPin, OUTPUT);
  pinMode(downLedPin, OUTPUT);
}

void loop()
{
  //checks if the elevator cage is at our floor
  //by checking the sensor output
  if(digitalRead(sensorPin) == LOW) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,datArray[1]);
    digitalWrite(latchPin, HIGH);
    //disables the light for elevator up
    if(elevatorCalledUp) {
      digitalWrite(upLedPin, LOW);
    }
    //disables the light for elevator down
    if(elevatorCalledDown) {
      digitalWrite(downLedPin, LOW);
    }

    digitalWrite(atFloorLedPin, HIGH);

    elevatorAtFloor = true;
    openDoors();
    closeDoors();
  }


  //if elevator has left again this gets triggered to reset all
  //variables
  if(elevatorAtFloor && digitalRead(sensorPin) == HIGH) {
    digitalWrite(atFloorLedPin, LOW);
    elevatorAtFloor = false;
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,datArray[0]);
    digitalWrite(latchPin, HIGH);
    Serial.print("ELEVATOR LEAVING\n");
  }

  //routine for handling if the going up button is pressed
  if(digitalRead(upButtonPin) == LOW) {
    Serial.print("Requested direction: UP\n");
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
}

