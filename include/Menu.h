#ifndef _Menu_
    #define _Menu_

    #include <Adafruit_SSD1306.h>

    struct menuItem{
        const char* name;
        void (*selectedAction)();
    };

    class Menu{
        public:
            Menu(Adafruit_SSD1306* display);
            void showMenu(menuItem* items, uint8_t size);
            void next();
            void previous();
            void select();

        private:
            static Adafruit_SSD1306 *display;
            menuItem* items;
            uint8_t itemCount = 0;
            uint8_t selectedItem = 0;
    };
#endif