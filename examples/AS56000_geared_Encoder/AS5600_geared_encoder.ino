//
//    FILE: AS5600_geared_encoder.ino
//  AUTHOR: Magnus Gaunt
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AS5600
//
//  Examples may use AS5600 or AS5600L devices.
//  Check if your sensor matches the one used in the example.
//  Optionally adjust the code.


#include "AS5600.h"


// Uncomment the line according to your sensor type
AS5600L as5600;   //  use default Wire
// AS5600 as5600;   //  use default Wire


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);
  Serial.println();

  Wire.begin();

  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  //  default, just be explicit.

  Serial.println(as5600.getAddress());

  //  as5600.setAddress(0x40);  //  AS5600L only

  int b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);

  delay(1000);

  as5600.setOffset(1000);
  as5600.setRatio(4);
  as5600.zeroCumulativeToOffset();
}

void loop()
{
  static uint32_t lastTime = 0;

  as5600.getScaledAngle();

  if (millis() - lastTime >= 500)
  {
    lastTime = millis();
    Serial.print("the real encoder pos: ");
    Serial.println(as5600.realAngle());
    Serial.print("the module pos: ");
    Serial.println(as5600.getScaledAngle());
    Serial.println();
  }
}


//  -- END OF FILE --
