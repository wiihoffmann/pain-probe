#include <Interface.h>


Interface::Interface(Adafruit_SSD1306 *disp){
    display = disp;

}

void Interface::ShowSetupMenu(){
    display->clearDisplay();
    display->println(F("scroll"));
}
