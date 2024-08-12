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

    uint8_t message = Serial.peek();

    switch (message) {
    case START:
        Serial.read();
        _onInput(START, 0);
        break;
    case STOP:
        Serial.read();
        _onInput(STOP, 0);
        break;
    case WRITE:
        if (Serial.available() < 1 + 2 + 256) {
            return;
        }
        Serial.read();
        uint8_t data[2 + 256];
        Serial.readBytes(data, 2 + 256);
        _onInput(WRITE, data);
        break;
    default:
        Serial.read();
        send(ERROR);
    }
}

void Interface::send(OutputMessage message) {
    Serial.write(message);
}
