#ifndef FLASH_HPP
#define FLASH_HPP

#include <Arduino.h>

namespace Flash {
    void begin(void (*onStatusChange)(bool));
    void end();
    void enable();
    void disable();
    bool writeChunk(uint16_t chunkAddress, uint8_t *data);
    void readChunk(uint16_t chunkAddress, uint8_t *data);
}

#endif
