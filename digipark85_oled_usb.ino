#include <DigiUSB.h>
#include "CustomOLED.h"

const char* temp_char = "*C";
byte lastRead;
char cpuTemp[] = "00";
char gpuTemp[] = "00";

void setup() {
  // put your setup code here, to run once:
  DigiUSB.begin();
  oled.begin();
}

void get_input() {
  while (true) { // loop forever
    if (DigiUSB.available()) {
      // something to read
      lastRead = DigiUSB.read();
      //DigiUSB.write(lastRead);
      if (lastRead == '>'){
        lastRead = DigiUSB.read();
        if (lastRead == 'C'){
          cpuTemp[0] = DigiUSB.read();
          cpuTemp[1] = DigiUSB.read();
        }
        if (lastRead == 'G'){
          gpuTemp[0] = DigiUSB.read();
          gpuTemp[1] = DigiUSB.read();
        }
      }
      if (lastRead == '\n') {
        break; // when we get a newline, break out of loop
      }
    }
    
    // refresh the usb port for 10 milliseconds
    DigiUSB.delay(200);
  }
}
void loop() {
  oled.setCursor(0, 0); //top left
  oled.print(F("CPU: ")); 
  oled.print(cpuTemp); 
  oled.println(temp_char);
  oled.print(F("GPU: "));
  oled.print(gpuTemp); 
  oled.println(temp_char);
  
  get_input();
}
