#include"Menu.h"

Adafruit_SSD1306* Menu::display = nullptr;

Menu::Menu(Adafruit_SSD1306* disp){
    this->display = disp;

}

void Menu::showMenu(menuItem* items, uint8_t size){
    this->items = items;
    this->itemCount = size;
    uint8_t rows;
    uint16_t charHeight;
    // display->getTextBounds(F("A"), 0, 0, NULL, NULL, NULL, &charHeight);

    display->clearDisplay();
    display->setCursor(0,0);
    display->setTextSize(2);
    display->setTextColor(WHITE);
    rows = display->height() / 7;

    Serial.println(rows);
    
    for(int i = 0; i<size && i<rows; i++){
        display->println(items[i].name);
        
        Serial.println(items[i].name);
        items[i].selectedAction();
    }
    display->display();
}


void Menu::next(){

}

void Menu::previous(){

}

void Menu::select(){

}