
#include <Arduino.h>
#include <Wire.h> //I2C Arduino Library

// code partially lent from https://www.sparkfun.com/tutorials/301

#define L883_ADDRESS 0x1E //0011110b, I2C 7bit address of HMC5883

void compassCalibrate()
{
  // the lazy way: 
  // Turn around for two full turns, gather min and max values for X and Y axis
  // then assume center is in the middle. 
  // The more sophisticated way contains self test and temperature compensation
  // as well as geographical values.
}

// Wrapper for all the magnet stuff we need. 
class compassL883
{
public:
  compassL883();
  void printCoordToSerial();

private: 
  // chip specific scaling for all axes, Z axis really has a different scaling. 
  int scaleX;
  int scaleY;
  int scaleZ; 

  // compass readings are not centered on zero
  // call calibrate() to calculate
  int centerX;
  int centerY;
  int centerZ;
};

compassL883::compassL883()
{
  scaleX = 1160;
  scaleY = 1160;
  scaleZ = 1080;

  centerX = 0;
  centerY = 0;
  centerZ = 0;

  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(L883_ADDRESS); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();

  return;
}

// for debug purposes
void compassL883::printCoordToSerial()
{
  int x,y,z; //triple axis data

  //Tell the HMC5883L where to begin reading data
  Wire.beginTransmission(L883_ADDRESS);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();

  //Read data from each axis, 2 registers per axis
  Wire.requestFrom(L883_ADDRESS, 6);
  if(6<=Wire.available())
  {
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }

  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);
}




