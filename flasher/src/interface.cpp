#include "interface.hpp"

extern HardwareSerial Serial;

static void (*_onInput)(Interface::InputMessage, uint8_t*) = 0;

void Interface::begin(uint32_t baudrate, void (*onInput)(InputMessage, uint8_t*)) {
    _onInput = onInput;
    Serial.begin(baudrate);
}

void Interface::end() {
    Serial.end();
}

void Interface::update() {
    if (!Serial.available()) {
        return;
    }

    switch (Serial.read()) {
    case START: {
        _onInput(START, 0);
    } break;
    case STOP: {
        _onInput(STOP, 0);
    } break;
    case WRITE: {
        uint8_t data[2 + 256];
        uint16_t offset = 0;
        while (offset < 2 + 256) {
            if (!Serial.available()) {
                continue;
            }
            offset += Serial.readBytes(data + offset, 2 + 256 - offset);
        }
        _onInput(WRITE, data);
    } break;
    case READ: {
        uint8_t data[2];
        uint16_t offset = 0;
        while (offset < 2) {
            if (!Serial.available()) {
                continue;
            }
            offset += Serial.readBytes(data + offset, 2 - offset);
        }
        _onInput(READ, data);
    } break;
    default: {
        send(ERROR);
    } break;
    }
}

void Interface::send(OutputMessage message, uint8_t* data) {
    Serial.write(message);
    switch (message) {
    case DATA:
        Serial.write(data, 256);
        break;
    }
}
