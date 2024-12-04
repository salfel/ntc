#include <Arduino.h>
#include <math.h>

void setup() {
    pinMode(A4, INPUT);
    pinMode(3, OUTPUT);
    Serial.begin(19200);

    digitalWrite(3, HIGH);
}

const int OUTPUT_PIN = 3;

const float A = -0.0315208;
const float B = 0.0080451;
const float C = -0.00006335;

const float STEP = 5.0 / 1024;
const uint16_t RESISTOR = 2700;

const float UPPER_TRESHHOLD = 27;
const float LOWER_TRESHHOLD = 26;

void loop() {
    static unsigned long value = 0;
    static int count = 0;
    static int lastMillis = millis();
    static int measured = false; 

    uint16_t measurement = analogRead(A4);
    float voltage = 5.0 - (measurement * STEP);

    float resistance = (5.0 / voltage) * RESISTOR - RESISTOR;
    float temperature = 1 / (A + B * log(resistance) + C * pow(log(resistance), 3)) - 273.15;

    if (millis() - lastMillis > 500) {
        Serial.print(">temperature:");
        Serial.println(temperature);

        lastMillis = millis();
    }

    if (temperature > UPPER_TRESHHOLD) {
        digitalWrite(3, LOW);
    } else if (temperature < LOWER_TRESHHOLD){
        digitalWrite(3, HIGH);
    }
}
