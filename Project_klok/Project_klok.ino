//#include <WiFi.h>                     
#include <ESP32Time.h>
#include <ESPEssentials.h>   
#include <pwmWrite.h>
ESP32Time rtc;

void setup() {
  Serial.begin(115200);
  toggleColor();
  ESPEssentials::init("Project Klok");
  WebServerRoutes();
  InitializeTime();
}

void loop() {
  ESPEssentials::handle();
  struct tm timeinfo = rtc.getTimeStruct();
  if(ESPEssentials::Wifi.getWLStatusString() == "WL_CONNECTED"){
    HandleDigits();
  }
}