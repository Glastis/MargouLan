#include <Wire.h> 
#include "main.h"

//I2C/TWI success (transaction was successful).
static const uint8_t ku8TWISuccess                   = 0;
//I2C/TWI device not present (address sent, NACK received).
static const uint8_t ku8TWIDeviceNACK                = 2;
//I2C/TWI data not received (data sent, NACK received).
static const uint8_t ku8TWIDataNACK                  = 3;
//I2C/TWI other error.
static const uint8_t ku8TWIError                     = 4;

int           is_pressed(uint16_t all, uint16_t button)
{
  return ((all & button) == button);
}

int           get_address()
{
  int         address;

  address = 0x00;
  while (address < 0xff)
  {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == ku8TWISuccess)
    {
      Serial.println("device found:");
      Serial.println(address);
      return (address);
    }
    address += 1;
    if (address == 60)
    address += 1;
  }
  Serial.println("device not found");
  return (-1);
}

void          pcf8575_write(uint16_t dt, int address)
{
  uint8_t error;

  Wire.beginTransmission(address);
//  Wire.begin(IO_EXTENDER_SDA_PIN,IO_EXTENDER_SCL_PIN);
  Wire.write(lowByte(dt));
  Wire.write(highByte(dt));
  error = Wire.endTransmission();
  if(error == ku8TWISuccess)
  {
  
  }
  else
  {
    Serial.println("pcf8575_write: error");
  }
}

uint16_t      pcf8575_read(int address)
{
  uint8_t     error;
  uint8_t     hi;
  uint8_t     lo;

  Wire.beginTransmission(address);
//  Wire.begin(IO_EXTENDER_SDA_PIN,IO_EXTENDER_SCL_PIN);
  error = Wire.endTransmission();
  if(error == ku8TWISuccess)
  {
    Wire.requestFrom(address, 2); 
    if(Wire.available())
    {
      lo = Wire.read();
      hi = Wire.read();
      return(word(hi,lo));
    }
    else
    {
      Serial.print("pcf8575_read: error 1: ");
      Serial.println(error);
      return (0);
    }
  }
  else
  {
    Serial.print("pcf8575_read: error 2: ");
    Serial.println(error);
    return (0);
  }
}
