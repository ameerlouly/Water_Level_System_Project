#include <Arduino.h>
#include "Water_Level/Water_Level.h"
#include "ESPNOW_Sender/Sender.h"
#include "Sensors/temp_sensor.h"

SensorData data;
Sensor_Type CurrentSensor = HCSR04;

void setup()
{
  Sensor_init(CurrentSensor);
  ESPNOW_Sender_Init();
  Temp_init();
  Serial.begin(9600);
}

void loop()
{
  data.water_level = getDepth_Average_cm(CurrentSensor); // Measure Water Level
  data.temperature = Temp_getTempC();
  // Todo: Add measure temprature

  Serial.println(data.water_level);
  Serial.println(data.temperature);
  delay(500);

  ESPNOW_SendData(&data, sizeof(data));

  // ESP NOW Send Data
}


