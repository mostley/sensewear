#include <Wire.h> //I2C Arduino Library
#include "SpiderMagnet.h"

// Hardware for Onewire is on Pins 4 & 5 on Nano, Uno

int number_of_outputs = 8;

int out_n = 2;
int out_no = 3;
int out_o = 6;
int out_so = 7;
int out_s = 8;
int out_sw = 9;
int out_w = 10;
int out_nw = 11;

int all_outputs[] = {2, 3, 4, 7, 8, 9, 10, 11};

int current_direction = 0;
int pin_angles[8];

int angle_epsilon = 10;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  magnetSetup();

  for (int i=0; i<8; i++)
  {
    pinMode(all_outputs[i], OUTPUT);
  }
  
  int angle_step = 360 / number_of_outputs;
  for (int i=0; i<number_of_outputs; i++)
  {
    pin_angles[i] = angle_step * i;
    Serial.println(pin_angles[i]);
  }
}

void disable_all()
{
  for (int i=0; i<8; i++)
  {
    digitalWrite(all_outputs[i], LOW);
  }
}

int mod(int a, int n)
{
  return (a % n + n) % n;
}

int angular_distance(int a, int b)
{
    int result = a - b;
    result = mod(result + 180, 360) - 180;
    return abs(result);
}
  
void show_direction(int dir)
{
  int closest_pin_index = 0;
  int current_closest_angle_distance = dir;
  
  int second_closest_pin_index = -1;
  int current_second_closest_angle_distance = -1;

  for (int i=0; i<number_of_outputs; i++)
  {
    int distance = angular_distance(pin_angles[i], dir);
    if (distance < current_closest_angle_distance)
    {
      second_closest_pin_index = closest_pin_index;
      current_second_closest_angle_distance = current_closest_angle_distance;
      
      closest_pin_index = i;
      current_closest_angle_distance = distance;
    }
    else if (distance < current_second_closest_angle_distance)
    {
      second_closest_pin_index = i;
      current_second_closest_angle_distance = distance;
    }
  }
  
  disable_all();
  digitalWrite(all_outputs[closest_pin_index], HIGH);
  if (second_closest_pin_index >= 0 && current_closest_angle_distance > angle_epsilon)
  {
    digitalWrite(all_outputs[second_closest_pin_index], HIGH);
  }
}

void loop()
{
  show_direction(current_direction);
  magnetLoop();
  
  current_direction = (current_direction + 1) % 360;
  
  delay(10);
}
