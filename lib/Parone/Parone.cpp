#include <stdlib.h>
#include <Arduino.h>
#include <Wire.h>

#include "Parone.h"


Level* initLevel(int id) {
    Level *level_ptr = (Level*)malloc(sizeof(Level));
    level_ptr->id = id;
    level_ptr->status = 0;
    level_ptr->elevatorAtMe = 0;
    return level_ptr;
}

int fieldsToMessage(int a, int b) {
    int base = 0;
    base = a;
    a << 1;
    a += b;
    return base;
}

void evalTransmission(Level *level, Transmission *transmission) {
    switch(transmission->message) {
        case 0x0A:
            //tell the master the current level
            Serial.print("Requesting current level\n");
            level->transmit(fieldsToMessage(level->id, 1));
            break;
        case 0x0B:
            break;
            //direction change up
            level->elevator_direction = 1;
            Serial.print("Reporting direction change up\n");
        case 0x0C:
            //direction change down
            level->elevator_direction = 0;
            Serial.print("Reporting direction change down\n");
            break;
        case 0x0D:
        case 0x0E:
            //random
            Serial.print("Requesting non defined message\n");
            break;
        case 0x0F:
            //hard reset
            level->status = 0;
            level->elevatorAtMe = 0;
            Serial.print("Reporting hard reset\n");
            break;
    } 
}