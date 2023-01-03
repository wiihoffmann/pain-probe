#ifndef _Circular_Gauge_H_
    #define _Circular_Gauge_H_

    #include <Adafruit_SSD1306.h>

    #define pi 3.14159265359
    #define pi2 2 * pi

    class Circular_Gauge {
        public:
            Circular_Gauge(int min, int max, bool includeRenderTime = false);

            void begin(Adafruit_SSD1306 *disp);
            void drawGaugeData(float value);
            void set_min_max(int min, int max);

        private:
            void drawRenderTime();
            void drawValue(float value);
            float scale(float inScaleMin, float inScaleMax, float outScaleMin, float outScaleMax, float value);
            float angleToXD(float centerX, float radius, float angleD);
            float angleToYD(float centerY, float radius, float angleD);
            void drawArc(float startAngle, float endAngle, float segments, int centerX, int centerY, int radius);
            void drawNeedle(float angle, float startAngle, float endAngle, float centerX, float centerY, int radius, int color);
            void drawGaugeLines(float startAngle, float endAngle, float centerX, float centerY, int radius);
            void drawGaugeFrame();

            float startAngleD, startAngle;
            float endAngleD, endAngle;
            int centerX, centerY, radius;
            bool _includeRenderTime;
            unsigned long renderTime = 0;
            int gaugeMin, gaugeMax;
            Adafruit_SSD1306 *display;
    };

#endif

