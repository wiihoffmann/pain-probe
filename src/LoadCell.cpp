#include <Arduino.h>
#include "LoadCell.h"

// Define the static Singleton pointer
LoadCell* LoadCell::inst_ = NULL;

LoadCell* LoadCell::getInstance() {
   if (inst_ == NULL) {
        inst_ = new LoadCell();
   }
   return(inst_);
}   