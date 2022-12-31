#include <Arduino.h>
#include <Circular_Gauge.h>
#include <HX711.h>


#define gaugeMin -100
#define gaugeMax 300

Adafruit_SSD1306 Display;
Circular_Gauge Gauge(gaugeMin, gaugeMax, true);
HX711 Probe;

_lock_t loadLock;

TaskHandle_t ScreenUpdateTaskHandle;
TaskHandle_t mainTaskHandle;

uint32_t count = 0;
uint32_t startTime;
int inc = 1;
boolean increase = true;

long lastLoad;


// #define OLED_RESET 4
// Adafruit_SSD1306 *display(OLED_RESET);



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
    Serial.println(val);
    Gauge.drawGaugeData(val);
    vPortYield();
  }
}


void mainTask(void * parameter){
  while(1){
    // Serial.println("main task");
    if(Probe.is_ready()){
      count ++;
      _lock_acquire(&loadLock);
      lastLoad = Probe.get_units(1);
      _lock_release(&loadLock);

      Serial.print("samples per second: ");
      Serial.println(count / ((millis() - startTime) / (float)1000) );  
    }

    vPortYield();
  }
}


void setup()   {                
  Serial.begin(115200);

  _lock_init(&loadLock);
  delay(2000);
  Serial.println("here");

  Display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)


  Gauge.begin(&Display);

  Probe.begin(26, 25, 60);
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
  delay(500);
  Serial.println("main loop");
}

