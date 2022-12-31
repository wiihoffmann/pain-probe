#ifndef INTERFACE
#define INTERFACE

#include "Adafruit_SSD1306.h"

class Interface{
    private:
        Adafruit_SSD1306 *display;

    public:
        Interface(Adafruit_SSD1306 *display);
        void ShowSetupMenu();
};

#endif