#ifndef FLASH_HPP
#define FLASH_HPP

#include <Arduino.h>
#include <functional>

namespace Flash {
    void begin(std::function<void(bool)> onStatusChange);
    void end();
    void enable();
    void disable();
    void writeChunk(uint16_t chunkAddress, uint8_t *data);
}

#endif
