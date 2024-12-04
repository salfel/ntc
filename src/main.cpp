#include <Arduino.h>
#include <math.h>

const int OUTPUT_PIN = 3;

const float A = -0.0315208;
const float B = 0.0080451;
const float C = -0.00006335;

const float STEP = 5.0 / 1024;
const uint16_t RESISTOR = 2700;

const float UPPER_TRESHHOLD = 27;
const float LOWER_TRESHHOLD = 26;

void setup() {
    pinMode(A4, INPUT);
    pinMode(OUTPUT_PIN, OUTPUT);
    Serial.begin(19200);

    digitalWrite(3, HIGH);
}


void loop() {
    static unsigned long lastMillis = millis();
    static int isHeating = HIGH;

    if (millis() - lastMillis < 500) {
        return;
    }

    uint16_t measurement = analogRead(A4);
    float voltage = 5.0 - (measurement * STEP);

    float resistance = (5.0 / voltage) * RESISTOR - RESISTOR;
    float temperature = 1 / (A + B * log(resistance) + C * pow(log(resistance), 3)) - 273.15;


    Serial.print(">temperature:");
    Serial.println(temperature);

    if (temperature > UPPER_TRESHHOLD) {
        isHeating = LOW;
    } else if (temperature < LOWER_TRESHHOLD){
        isHeating = HIGH;
    }

    digitalWrite(OUTPUT_PIN, isHeating);
    Serial.print(">output:");
    Serial.println(isHeating);

    lastMillis = millis();
}
