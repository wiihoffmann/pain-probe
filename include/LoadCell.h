#include <Arduino.h>
#include <HX711.h>

class LoadCell {
    public:
        // This is how clients can access the single instance
        static LoadCell* getInstance();

        void setValue(int val) {value_ = val;}
        int  getValue()           {return(value_);}

    protected:
        int value_;

    private:
        static LoadCell* inst_;   // The one, single instance
        LoadCell() : value_(0) {} // private constructor
        LoadCell(const LoadCell&);
        LoadCell& operator=(const LoadCell&);
};