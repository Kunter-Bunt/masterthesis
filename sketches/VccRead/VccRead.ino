extern "C" {
#include "user_interface.h"
#include "gpio.h"
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
  /*
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U , FUNC_GPIO15);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
  GPIO_DIS_OUTPUT(BIT15);
  PIN_PULLUP_EN(PERIPHS_IO_MUX_MTDO_U); 
  
  if (!GPIO_INPUT_GET(15)) Serial.println("LOW");
  */
  if(digitalRead(2) == LOW) digitalWrite(15, HIGH);//Serial.println("LOW");

  delay(1000);
  digitalWrite(15, HIGH);
}

