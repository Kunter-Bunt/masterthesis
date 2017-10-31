#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float sum_mA = 0;
float avg_mA = 0;
int steps = 0;
int step_width = 1;


void setup(void) 
{
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  uint32_t currentFrequency;
    
  Serial.begin(115200);
  ina219.begin();
  ina219.setCalibration_16V_400mA();
}

void loop(void) 
{
  //shuntvoltage = max(ina219.getShuntVoltage_mV(), 0);
  //busvoltage = ina219.getBusVoltage_V();
  current_mA = max(ina219.getCurrent_mA(), 0);
  //loadvoltage = busvoltage + (shuntvoltage / 1000);
  sum_mA += current_mA;
  steps++;
  avg_mA = sum_mA / steps;
  //if (current_mA > 10.0) steps = 0;

  if (steps % 1000 == 0) {
     Serial.print(avg_mA); Serial.print(" "); Serial.println(steps);
  }
  
  //if (current_mA > 13.0) {
    //Serial.print(current_mA); Serial.print(" "); Serial.print(sum_mA); Serial.print(" "); Serial.print(avg_mA); Serial.print(" "); Serial.print(steps); Serial.println(" ");
    Serial.print(steps*3); Serial.print(","); Serial.println(current_mA);
  //}
  
  /*
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.println("");
  */
  delay(step_width);
}
