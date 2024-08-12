#include "flash.hpp"
#include "pins.hpp"
#include <SPI.h>

static void (*_onStatusChange)(bool) = 0;

void onStatusChangeInterrupt() {
    _onStatusChange(digitalRead(PIN_CD) == HIGH);
}

bool waitForReady() {
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(PIN_CS, LOW);
    SPI.transfer(0x05);
    uint16_t status = 1;
    while (status & 0b1) {
        status = SPI.transfer16(0);
        if (status & 0b100000) {
            digitalWrite(PIN_CS, HIGH);
            SPI.endTransaction();
            return false;
        }
        delayMicroseconds(1);
    }
    digitalWrite(PIN_CS, HIGH);
    SPI.endTransaction();
    delayMicroseconds(1);
    return true;
}

void writeEnable() {
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(PIN_CS, LOW);
    SPI.transfer(0x06);
    digitalWrite(PIN_CS, HIGH);
    SPI.endTransaction();
    waitForReady();
}

void Flash::begin(void (*onStatusChange)(bool)) {
    _onStatusChange = onStatusChange;
    attachInterrupt(digitalPinToInterrupt(PIN_CD), onStatusChangeInterrupt, CHANGE);
    pinMode(PIN_SEL, OUTPUT);
    pinMode(PIN_CD, INPUT);
    pinMode(PIN_CR, OUTPUT);
    pinMode(PIN_CS, OUTPUT);
    digitalWrite(PIN_SEL, HIGH);
    digitalWrite(PIN_CR, HIGH);
    digitalWrite(PIN_CS, HIGH);
    SPI.begin();
}

void Flash::end() {
    SPI.end();
}

void Flash::enable() {
    digitalWrite(PIN_CR, LOW);
    digitalWrite(PIN_SEL, LOW);

    writeEnable();
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(PIN_CS, LOW);
    SPI.transfer(0x60);
    digitalWrite(PIN_CS, HIGH);
    SPI.endTransaction();
    waitForReady();
}

void Flash::disable() {
    digitalWrite(PIN_SEL, HIGH);
    digitalWrite(PIN_CR, HIGH);
}

bool Flash::writeChunk(uint16_t chunkAddress, uint8_t* data) {
    writeEnable();
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(PIN_CS, LOW);
    SPI.transfer(0x02);
    SPI.transfer((chunkAddress >> 8) & 0xff);
    SPI.transfer(chunkAddress & 0xff);
    SPI.transfer(0);
    for (int i = 0; i < 256; i++) {
        SPI.transfer(data[i]);
    }
    digitalWrite(PIN_CS, HIGH);
    SPI.endTransaction();
    return waitForReady();
}

void Flash::readChunk(uint16_t chunkAddress, uint8_t* data) {
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(PIN_CS, LOW);
    SPI.transfer(0x03);
    SPI.transfer((chunkAddress >> 8) & 0xff);
    SPI.transfer(chunkAddress & 0xff);
    SPI.transfer(0);
    for (int i = 0; i < 256; i++) {
        data[i] = SPI.transfer(0);
    }
    digitalWrite(PIN_CS, HIGH);
    SPI.endTransaction();
}
