/*
This code will reset the corresponding EEPROM used by DFRobot Gravity pH Meter V2, SKU: SEN0161-V2.
When uploaded this code, please open the serial monitor of the Ardino IDE. The correct value of the EEPROM block should be 255.
*/
#include <EEPROM.h>
#define PHADDR 0x00
void setup()
{
  Serial.begin(115200);
  for (int i = 0; i < 8; i++)
  {
    EEPROM.write(PHADDR + i, 0xFF); // write defaullt value to the EEPROM
    delay(10);
  }
}
void loop()
{
  static int a = 0, value = 0;
  value = EEPROM.read(PHADDR + a);
  Serial.print(PHADDR + a, HEX);
  Serial.print(":");
  Serial.print(value); // print the new value of EEPROM block used by EC meter. The correct is 255.
  Serial.println();
  delay(10);
  a = a + 1;
  if (a == 8)
    while (1)
      ;
}