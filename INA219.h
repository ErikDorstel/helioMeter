#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

struct ina219Struct {
  float rfactor=11; // 0.1 Ohm parallel 0.01 Ohm => Rpar = 1/((1/0.1)+(1/0.01)) = 0.00909 Ohm => rfactor = 0.1 Ohm / Rpar = 11
  float busvoltage=0;
  float shuntvoltage=0;
  float loadvoltage=0;
  float current=0;
  float power=0;
  float buspower=0;
  float busresistance=0; };

struct ina219Struct ina219Data;

uint32_t ina219Timer=0;

void initINA219() { ina219.begin(); }

void ina219Worker() {
  if (millis()>=ina219Timer) { ina219Timer=millis()+1000;
    ina219Data.busvoltage=ina219.getBusVoltage_V();
    ina219Data.shuntvoltage=ina219.getShuntVoltage_mV();
    ina219Data.loadvoltage=ina219Data.busvoltage+(ina219Data.shuntvoltage/1000);
    ina219Data.current=ina219.getCurrent_mA()*ina219Data.rfactor;
    ina219Data.power=ina219.getPower_mW()*ina219Data.rfactor;
    ina219Data.buspower=ina219Data.busvoltage*ina219Data.current;
    if (ina219Data.current!=0) { ina219Data.busresistance=ina219Data.busvoltage/ina219Data.current*1000; }
    else { ina219Data.busresistance=0; } } }
