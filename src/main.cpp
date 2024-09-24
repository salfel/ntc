#include <Arduino.h>

float calcTemp(int resistance);

float calibrateTemp(float temp);

void setup() {
    pinMode(A4, INPUT);
    Serial.begin(9600);
}

const float BETA = 3977;
const float T_25 = 298; 
const float R_25 = 2875;
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
    int temp = (calcTemp(voltage / current) - 273.15) * 100;
    count++;
    value += temp;

    if (millis() - lastMillis > 5000 && !measured) {
        Serial.println(calibrateTemp(value / 100.0 / count));
        Serial.println(count);
        measured = true;
    }
}

float calcTemp(int resistance) {
    float value =  1/T_25 + 1/BETA * log10(resistance / R_25);

    return 1/value;
}

float calibrateTemp(float temp) {
    return 2.673557 * temp - 44.290;
}
