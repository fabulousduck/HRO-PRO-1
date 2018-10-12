#ifndef PARONE_H
#define PARONE_H


typedef struct transmission_t {
    int message;
    int params;
}Transmission;


typedef struct level_t {
    int id;
    int status;
    int elevator_direction;
    int elevatorAtMe;
    void transmit(int transmission) {
        Wire.write(transmission);
    };
}Level;

void evalTransmission(Level *, Transmission *);
Level* initLevel(int);
int fieldsToMessage(int, int);
#endif