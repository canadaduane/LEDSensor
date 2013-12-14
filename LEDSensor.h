#ifndef LEDSensor_h
#define LEDSensor_h

class LEDSensor {
private:
  class LEDSensor* next;
  static LEDSensor* first;

public:
  LEDSensor() :
    mLedPin(0), mMeasureAnalog(false), next(0),
    mMaxDelta(2000), mStartTime(-1), mTimeDelta(0) {}

  void attach(int ledPin);
  void setAnalogMeasurement(int thresholdLevel); // measure from an analog pin
  void setDigitalMeasurement(); // measure from a digital pin (default)

  long value();

  static void refresh();

protected:
  int mLedPin;
  bool mMeasureAnalog;
  int mAnalogThresholdLevel; // (0 to 1023)

  long mMaxDelta;
  long mStartTime;
  long mTimeDelta;
 
  void measure();
  void charge();
  void discharge();

  bool isDischarged();
  bool isTimedOut();
};

#endif //LEDSensor_h