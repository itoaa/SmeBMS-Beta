#ifndef FILTER_H
#define FILTER_H

#include "stdint.h" // for int16_t and uint8_t

class Filter {
public:
    Filter(); 

    void addValue(int16_t value);
    int16_t getAverage() const;

private:
    int16_t values[5]; 
    uint8_t nextIndex = 0; // Changed to uint8_t
    int16_t minValue, maxValue; 
};

#endif // FILTER_H

