#include "Circular_Gauge.h"


Circular_Gauge::Circular_Gauge(int min, int max, bool includeRenderTime) {
    float centerD = 270; //Angle where the center of the gauge will be
    float widthD = 40; //Angle that the gauge will be wide
    
    startAngleD = centerD - widthD;
    endAngleD   = centerD + widthD;
  
    centerX    = 63;//    Center of arc X (pixels)
    centerY    = 100;//    Center of arc Y (pixels)
    radius     = 65;//    Radious of arc (pixels)
  
    startAngle = startAngleD / 360 * pi2;
    endAngle   = endAngleD   / 360 * pi2;

    gaugeMin = min;
    gaugeMax = max;
    _includeRenderTime = includeRenderTime;
}


void Circular_Gauge::drawRenderTime() {
    if (!_includeRenderTime) return;

    display->setTextColor(INVERSE);
    display->setCursor(0,0);
    display->setTextSize(1);
    display->println(renderTime);
}


void Circular_Gauge::drawValue(float value) {
    display->setTextColor(INVERSE);
    display->setTextSize(1);
    display->setCursor(0,57);
    display->println(value);
}


float Circular_Gauge::scale(float inScaleMin, float inScaleMax, float outScaleMin, float outScaleMax, float value){
    return ((value - inScaleMin) / (inScaleMax - inScaleMin) * (outScaleMax-outScaleMin)) + outScaleMin;
} 


float Circular_Gauge::angleToXD(float centerX, float radius, float angleD) {
    float angle = (angleD / 360) * (pi2);
    return centerX+radius*cos(angle); // Calculate arc point (X)
}


float Circular_Gauge::angleToYD(float centerY, float radius, float angleD) {
    float angle = (angleD / 360) * (pi2);
    return centerY+radius*sin(angle); // Calculate arc point (Y)
}


void Circular_Gauge::drawArc(float startAngle, float endAngle, float segments, int centerX, int centerY, int radius) {
    float resolution = (endAngle-startAngle)/segments; // Calculates steps in arc based on segments
    float x = centerX+radius*cos(startAngle); // Calculate start point of arc (X)
    float y = centerY+radius*sin(startAngle); // Calculate start point of arc (Y)
    display->writePixel(x,y,WHITE); // Place starting point of arc
  
    for (float angle = startAngle; angle < endAngle; angle += resolution) { // Sweep arc
        x = centerX+radius*cos(angle); // Calculate arc point (X)
        y = centerY+radius*sin(angle); // Calculate arc point (Y)
        display->writePixel(x,y,WHITE);
    }
}


void Circular_Gauge::drawNeedle(float angle, float startAngle, float endAngle, float centerX, float centerY, int radius, int color){
    float leftX = angleToXD(centerX, radius+1, angle - 5);
    float leftY = angleToYD(centerY, radius+1, angle - 5);
  
    float rightX = angleToXD(centerX, radius+1, angle + 5);
    float rightY = angleToYD(centerY, radius+1, angle + 5);
  
    float topX = angleToXD(centerX, radius+30, angle);
    float topY = angleToYD(centerY, radius+30, angle);
  
    display->fillTriangle(leftX,leftY,topX,topY,rightX,rightY,color);
}


void Circular_Gauge::drawGaugeLines(float startAngle, float endAngle, float centerX, float centerY, int radius){
    drawArc(startAngle, endAngle, 150, centerX, centerY, radius + 30);
    drawArc(startAngle, endAngle, 110, centerX, centerY, radius - 1);
    drawArc(startAngle, endAngle, 110, centerX, centerY, radius - 4);
}


void Circular_Gauge::drawGaugeFrame() {
    display->clearDisplay();
    display->setTextColor(WHITE);
    display->setTextSize(1);

    display->setCursor(0, 0);
    display->println("LOW");
    display->setCursor(100, 0);
    display->println("HIGH");

    drawGaugeLines(startAngle, endAngle, centerX, centerY, 65);
}


void Circular_Gauge::drawGaugeData(float value) {
    float angle = scale(gaugeMin,gaugeMax,startAngleD,endAngleD,value); 
  
    drawValue(value);
    drawNeedle(angle, startAngle, endAngle, centerX, centerY, radius, INVERSE);
    renderTime = millis() - renderTime;
    drawRenderTime();  
    display->display();
    drawRenderTime();
    renderTime = millis();
    drawNeedle(angle, startAngle, endAngle, centerX, centerY, radius, INVERSE); //erase the needle
    drawValue(value);
}


void Circular_Gauge::begin(Adafruit_SSD1306 *disp) {
    display = disp;
    drawGaugeFrame();
}


void Circular_Gauge::set_min_max(int min, int max){
    gaugeMin = min;
    gaugeMax = max;
}


