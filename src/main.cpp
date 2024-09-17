#include <Arduino.h>

float calcTemp(int resistance);

void setup() {
    pinMode(A4, INPUT);
    Serial.begin(9600);
}

const float STEP = 5.0 / 1024;
const uint16_t RESISTOR = 2700;

void loop() {
    static unsigned long value = 0;
    static int count = 0;
    static int lastMillis = millis();
    static int measured = false; 

    uint16_t measurement = analogRead(A4);
    float voltage = STEP * measurement;
    float current =  (5 - voltage) / RESISTOR;
    int temp = (calcTemp(voltage / current) - 273.15);
    count++;
    value += temp;

    if (millis() - lastMillis > 5000 && !measured) {
        Serial.println((float) value / count);
        Serial.println(count);
        measured = true;
    }
}

// ohne serial println 10977
// mit serial println 1219

const float BETA = 3977;
const float T_25 = 298; 
const float R_25 = 2875;
float calcTemp(int resistance) {
    float value =  1/T_25 + 1/BETA * log10(resistance / R_25);

    return 1/value;
}
