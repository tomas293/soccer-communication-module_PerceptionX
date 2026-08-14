#include <Arduino.h>
#include "functions.h"

HardwareSerial TelemetrySerial(1);

void telemetry_init()
{
    // RX = GPIO24, TX = GPIO25
    TelemetrySerial.begin(
        115200,
        SERIAL_8N1,
        24,
        25
    );
}

void telemetry_update()
{
    static uint32_t last_send = 0;

    if (millis() - last_send < 50)
        return;

    last_send = millis();

    TelemetrySerial.printf(
        "GAME,%u,%u,%u\n",
        module_get_my_score(),
        module_get_opponent_score(),
        module_get_remaining_time()
    );
}