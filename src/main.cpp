#include <Arduino.h>

#include "FileManager.h"


void setup(){     
  Serial.begin(115200);
  delay(1000);
  Serial.println("starting");
  
  FileManager mgr = FileManager();
  
  File one = mgr.makeFile(FileManager::fileFormat::PPT); 
  one.close();

  // uint8_t i = mgr.getFileCount(FileManager::fileFormat::PPT);
  // File file = mgr.openFile(FileManager::fileFormat::PPT, i);
  // while(file.available()){
  //   Serial.print(file.read());
  //   Serial.print(' ');
  // }
  // file.close();
}



void loop() {
  // delay(500);
  // Serial.println("main loop");
}

