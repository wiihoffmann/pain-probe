#include <Arduino.h>

#include "FileManager.h"


void setup(){     
  Serial.begin(115200);
  delay(1000);
  Serial.println("starting");
  
  FileManager mgr = FileManager();
  
  File one = mgr.makeFile(FileManager::fileFormat::PPT);
  Serial.println("first file created");
  File two = mgr.makeFile(FileManager::fileFormat::TS);
  Serial.println("second file created");
  File three = mgr.makeFile(FileManager::fileFormat::VAS);
  Serial.println("third file created");

  uint32_t time = millis();
  uint32_t bytes = 0;
  while(millis() < time+1000){
    one.write(bytes ++);
  }
  Serial.print("wrote ");
  Serial.print(bytes);
  Serial.println(" bytes in one second.");

  Serial.print("free space: ");
  Serial.println(SPIFFS.totalBytes());
  Serial.println(SPIFFS.usedBytes());
  Serial.println(one.size());
  
  one.seek(0);
  while(one.available()){
    Serial.print(one.read());
    Serial.print(' ');
  }

  
}



void loop() {
  // delay(500);
  // Serial.println("main loop");
}

