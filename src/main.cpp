#include <Arduino.h>
#include <TFT.h>
#include <SPI.h>
#include <Wire.h>

#define CS 53
#define DC 9
#define RST 8

TFT TFTscreen = TFT(CS,DC,RST);

char buffer[96];

void receiveEvent(int);

void setup() {
  TFTscreen.begin();
  TFTscreen.background(0x0000);
  TFTscreen.stroke(0xFFFF);
  TFTscreen.setTextSize(2);
  TFTscreen.text("WAITING....",10,0);
  Wire.begin(0x04);
  Wire.onReceive(receiveEvent);
}

void loop() {
  delay(100);
}

void receiveEvent(int howMany) {
  int count = 0;
  while(0 < Wire.available()) {
    buffer[count] = Wire.read();
    count++;
  }
  buffer[count] = 0x00;
  TFTscreen.background(0x0000);
  TFTscreen.stroke(0xFFFF);
  TFTscreen.setTextSize(2);
  TFTscreen.text(buffer,10,0);
}