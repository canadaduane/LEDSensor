#include "LEDSensor.h"

#include <Arduino.h>

LEDSensor* LEDSensor::first = 0;

void LEDSensor::attach(int ledPin) {
  mLedPin = ledPin;
  next = first;
  first = this;
}

void LEDSensor::setAnalogMeasurement(int thresholdLevel) {
  mAnalogThresholdLevel = thresholdLevel;
  mMeasureAnalog = true;
}

void LEDSensor::setDigitalMeasurement() {
  mMeasureAnalog = false;
}

long LEDSensor::value() {
  return mTimeDelta;
}

void LEDSensor::charge() {
  // Apply reverse voltage, charge up the pin and led capacitance
  pinMode(mLedPin, OUTPUT);
  digitalWrite(mLedPin, HIGH);
}

void LEDSensor::discharge() {
  // Isolate the diode
  pinMode(mLedPin, INPUT);
  digitalWrite(mLedPin, LOW); // turn off internal pull-up resistor, see http://arduino.cc/en/Tutorial/DigitalPins
}

bool LEDSensor::isDischarged() {
  bool digitalDischarged = (!mMeasureAnalog && digitalRead(mLedPin) == 0);
  bool analogDischarged = (mMeasureAnalog && analogRead(mLedPin) < mAnalogThresholdLevel);
  return digitalDischarged || analogDischarged;
}

bool LEDSensor::isTimedOut() {
  return (millis() - mStartTime) >= mMaxDelta;
}

void LEDSensor::measure() {
  if (mStartTime == -1 || isTimedOut()) {
    charge();
    delay(1); // charge it up
    discharge();

    mStartTime = millis();
  } else if (isDischarged()) {
    mTimeDelta = millis() - mStartTime;
    mStartTime = -1;
  }
}

void LEDSensor::refresh() {
  static unsigned long lastRefresh = 0;
  unsigned long m = millis();
  LEDSensor* sensor;

  if ( m >= lastRefresh && m < lastRefresh + 20) return;
  lastRefresh = m;

  for ( sensor = first; sensor != 0; sensor = sensor->next ) {
    sensor->measure();
  }
}
