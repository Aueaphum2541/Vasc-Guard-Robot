#include <Wire.h>
#include "DFRobot_BloodOxygen_S.h"

// Define I2C address for DFRobot variant
#define I2C_ADDRESS 0x57
DFRobot_BloodOxygen_S_I2C MAX30102(&Wire, I2C_ADDRESS);

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println("Initializing MAX30102 Sensor...");

  // Initialize the I2C bus on the default XIAO pins
  Wire.begin();

  // Attempt communication verification
  while (false == MAX30102.begin())
  {
    Serial.println("Sensor initialization failed! Check wiring or I2C address.");
    delay(1000);
  }

  Serial.println("Sensor initialized successfully.");
  Serial.println("Starting data collection...");

  // Start the underlying sensor collection routines
  MAX30102.sensorStartCollect();
}

void loop()
{
  // Query data from the onboard sensor MCU
  MAX30102.getHeartbeatSPO2();

  Serial.print("SpO2: ");
  Serial.print(MAX30102._sHeartbeatSPO2.SPO2);
  Serial.println(" %");

  Serial.print("Heart Rate: ");
  Serial.print(MAX30102._sHeartbeatSPO2.Heartbeat);
  Serial.println(" BPM");

  Serial.print("Board Temp: ");
  Serial.print(MAX30102.getTemperature_C());
  Serial.println(" C");

  Serial.println("---------------------------------");

  // The onboard algorithm updates data approximately every 4 seconds
  delay(4000);
}