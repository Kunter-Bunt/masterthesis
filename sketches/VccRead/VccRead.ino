extern "C" {
#include "user_interface.h"
}

//ADC_MODE(ADC_VCC);

int vdd;
int bat;
int level;

void setup() {
  Serial.begin(115200);
  while (!Serial); 
  Serial.println();
}

void loop() {
  //what comes from battery
  bat = analogRead(A0);
  //level = map(level, 580, 774, 0, 100);
  //Serial.print("Battery level: "); Serial.print(level); Serial.println("%");
  Serial.println(bat);
  //what gets to the chip, needs ADC_MODE(ADC_VCC); but that breaks the code above
  /*
  vdd = ESP.getVcc();
  Serial.println(vdd);
  */
  
  delay(1000);
}

