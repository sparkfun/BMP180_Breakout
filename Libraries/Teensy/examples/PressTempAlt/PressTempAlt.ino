/*
 *  BMP180    Teensy 3.5
 *
 *  For Wire,
 *  SDA       18
 *  SCL       19
 *
 *  For Wire1,
 *  SDA       38
 *  SCL       37
 *
 *
 *  For Wire2,
 *  SDA       4
 *  SCL       3
 *
 *  For WireX,
 *  You can see interfaces on the pinouts page: https://www.pjrc.com/teensy/pinout.html*
 *
 *
 */
#include <Teensy_BMP180.h>
double baseline;
double bmpValues[2]; //0: Temperature, 1:Pressure
Teensy_BMP180 bmp180(&Wire);
//Teensy_BMP180 bmp180(&Wire1); //If BMP180 is connected to Wire1 bus
//Teensy_BMP180 bmp180(&Wire2); //If BMP180 is connected to Wire2 bus

void setup() {
  bmp180.begin();
  if(getPressure()){
    baseline=bmpValues[1];
  }

}

void loop() {
  if(getPressure()){
    double altVal=bmp180.altitude(bmpValues[1],baseline);
    Serial.print(bmpValues[0]);
    Serial.print(" C | ");
    Serial.print(bmpValues[1]);
    Serial.print(" mb | ");
    Serial.print(altVal);
    Serial.println(" cm");
  }
  delay(100);
}

boolean getPressure()
{
  if (bmp180.startTemperature() != 0)
  {
    if (bmp180.getTemperature(bmpValues[0]) != 0)
    {
      if (bmp180.startPressure() != 0)
      {
        if (bmp180.getPressure(bmpValues[1],bmpValues[0]) != 0)
        {
          return(1);
        }
      }
    }
  }
  return(0);
}
