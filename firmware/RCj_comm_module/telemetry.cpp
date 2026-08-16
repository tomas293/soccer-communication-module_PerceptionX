#include <Arduino.h>
#include "functions.h"
#include "state_machine.h"

HardwareSerial TelemetrySerial(1);

void telemetry_init()
{
    // RX = GPIO24, TX = GPIO25
    TelemetrySerial.begin(
        115200,
        SERIAL_8N1,
        4,
        5
    );
}

void telemetry_update()
{
    static uint32_t last_send = 0;

    if (millis() - last_send < 50)
        return;

    last_send = millis();

    bool is_playing = (stm_get_state() == STM_PLAY);
    
    TelemetrySerial.printf(
        "GAME,%u,%u,%u,%u\n",
        module_get_my_score(),
        module_get_opponent_score(),
        stm_get_remaining_time(),
        is_playing ? 1 : 0 //PLAY 1, STOP 0
    );
}
