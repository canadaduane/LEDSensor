#include <LEDSensor.h>

LEDSensor led;
long counter = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Start LED Sensor");
  led.attach(2);
  counter = millis();
}

void loop()
{
  if (millis() - counter >= 1000) {
    Serial.println(led.value());
    counter = millis();
  }

  LEDSensor::refresh();
}