Arduino LED Sensor Library
--------------------------

This library detects light using LEDs wired in reverse. It is based on april's AmbientLightSensor code [1] which in turn is based on Scott Daniel's article [2].

The main difference between this library and other LED light-sensing libraries is that it allows for concurrent (non-blocking) readings from many LEDs at once. This may be useful if, for example, you are using different colored LEDs to sense light at different wavelengths, if you need multi-directional light sensing, or if you need to do other things (such as move servos) while waiting for data.

Getting Started
---------------

Here is some sample code to get you started. Note that the "Serial.prinln" call is asynchronous, called every second. Darker lighting conditions will update the internal reading less frequently, but you can still process other things whil you wait for the update.

```Arduino
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
```

License
-------

MIT

[1] http://forum.arduino.cc/index.php?topic=128556.0
[2] http://provideyourown.com/2011/cheap-alternative-for-hard-to-find-cds-light-sensor/