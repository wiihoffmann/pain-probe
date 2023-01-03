#ifndef _Circular_Gauge_H_
#define _Circular_Gauge_H_

#include <Adafruit_SSD1306.h>

class Circular_Gauge {
    public:
        Circular_Gauge(int min, int max);
        Circular_Gauge(int min, int max, bool includeRenderTime);

        // void begin(Adafruit_SSD1306 *disp);
        // void drawGaugeData(float value);
        void set_min_max(int min, int max);
        void set_margin(int lower, int upper);

        void begin();
        void drawGaugeData(float value, float display_value);
};

#endif

