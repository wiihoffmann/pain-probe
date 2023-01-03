#include <Arduino.h>
#include <Circular_Gauge.h>
#include <Wire.h>
#include <HX711.h>


#define gaugeMin -200
#define gaugeMax 900

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


Adafruit_SSD1306 Display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT);
Circular_Gauge Gauge(gaugeMin, gaugeMax);
HX711 Probe;

_lock_t loadLock;

TaskHandle_t ScreenUpdateTaskHandle;
TaskHandle_t mainTaskHandle;

uint32_t count = 0;
uint32_t startTime;
int inc = 1;
boolean increase = true;

long lastLoad;



void ScreenUpdateTask( void * parameter) {
  float val;
  for(;;) {
    //  Serial.println("trying to get lock");
     _lock_acquire(&loadLock);
      val = lastLoad;
      // Serial.println("got the lock");
    _lock_release(&loadLock);

    // Serial.println("released the lock");

    // Serial.print("val: ");
    // Serial.println(val);
    Gauge.drawGaugeData(val);
    vPortYield();
  }
}


int16_t sweeper = 0;

void mainTask(void * parameter){
  while(1){
    // Serial.println("main task");
    if(Probe.is_ready()){
      count ++;
      _lock_acquire(&loadLock);
      lastLoad = Probe.get_units(1);
      _lock_release(&loadLock);

      // Serial.print("samples per second: ");
      // Serial.println(count / ((millis() - startTime) / (float)1000) );  
      Serial.print("GOT: ");
      Serial.println(lastLoad);
    }

      // _lock_acquire(&loadLock);
      // lastLoad = sweeper;
      // _lock_release(&loadLock);  

      // sweeper ++;
      // if(sweeper > 300) sweeper = -100;
      delay(10);

    vPortYield();
  }
}


void setup()   {                
  Serial.begin(115200);

  _lock_init(&loadLock);

  Display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)


  Gauge.begin(&Display);

  Probe.begin(26, 25, 128);
  Probe.set_scale(500);
  Probe.tare();

  startTime = millis();

  

  xTaskCreatePinnedToCore(
      ScreenUpdateTask, /* Function to implement the task */
      "screen task", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      1,  /* Priority of the task */
      &ScreenUpdateTaskHandle,  /* Task handle. */
      1); /* Core where the task should run */


  xTaskCreatePinnedToCore(
      mainTask, /* Function to implement the task */
      "main task", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      1,  /* Priority of the task */
      &mainTaskHandle,  /* Task handle. */
      1); /* Core where the task should run */
}



void loop() {
  // delay(500);
  // Serial.println("main loop");
}

