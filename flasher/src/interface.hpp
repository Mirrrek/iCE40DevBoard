#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <Arduino.h>

namespace Interface {
    enum InputMessage {
        START,
        STOP,
        WRITE
    };

    enum OutputMessage {
        WRITE_ERROR,
        CONFIGURING,
        CONFIGURED,
        ERROR,
        OK
    };

    void begin(uint32_t baudrate, void (*onInput)(InputMessage, uint8_t*));
    void end();
    void update();
    void send(OutputMessage message);
};

#endif
