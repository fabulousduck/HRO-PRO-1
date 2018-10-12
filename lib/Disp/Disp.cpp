#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Disp.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

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

void initDisplay() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setRotation(3);
    display.clearDisplay();
}

void rerenderDisplay() {
    display.display();
}
