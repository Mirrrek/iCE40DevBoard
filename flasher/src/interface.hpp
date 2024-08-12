#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <Arduino.h>

namespace Interface {
    enum InputMessage {
        START,
        STOP,
        WRITE,
        READ
    };

    enum OutputMessage {
        WRITE_ERROR,
        CONFIGURING,
        CONFIGURED,
        ERROR,
        OK,
        DATA
    };

    void begin(uint32_t baudrate, void (*onInput)(InputMessage, uint8_t*));
    void end();
    void update();
    void send(OutputMessage message, uint8_t* data = 0);
};

#endif
