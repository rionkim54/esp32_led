#include "kproject_gfx.h"

#include <SoftwareSerial.h>
SoftwareSerial soft(2,3);

kproject_gfx kproject(soft, 64, 32);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  soft.begin(9600);

  kproject.begin();

  kproject.fillScreen(KPROJECT_BLACK);
  
  // delay(0);
  //kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(0, 0);
  kproject.setTextColor(KPROJECT_RED, KPROJECT_BLACK);
  kproject.print_string("제로윈텍");
  kproject.refresh();
}

int i = 0; 

void loop() {


  char temp[16] = { 0x00, };
  sprintf(temp, "%02d:%02d:%02d", i / 3600, i % 3600 / 60, i % 60);
  
  kproject.fillScreen(KPROJECT_BLACK);

  kproject.setCursor(0, 0);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("제로윈텍");
  // kproject.refresh();
  
  kproject.setCursor(0, 16);
  kproject.setTextColor(KPROJECT_RED, KPROJECT_BLACK);
  kproject.print_string(temp); // "11:11:11");
  kproject.refresh();
  delay(500);

  kproject.fillScreen(KPROJECT_BLACK);
  
  kproject.setCursor(0, 0);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("제로윈텍");
  // kproject.refresh();
  
  sprintf(temp, "%02d %02d %02d", i / 3600, i % 3600 / 60, i % 60);
  kproject.setCursor(0, 16);
  kproject.setTextColor(KPROJECT_RED, KPROJECT_BLACK);
  kproject.print_string(temp); // "11:11:11");
  kproject.refresh();
  delay(500);
  i += 1;
}
