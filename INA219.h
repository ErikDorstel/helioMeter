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
  float resistance=0;
  float charge=0;
  float energy=0;
  uint32_t runtime; };

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
    if (ina219Data.current!=0) { ina219Data.resistance=fabs(ina219Data.busvoltage*1000/ina219Data.current); }
    else { ina219Data.resistance=0; }
    ina219Data.charge+=ina219Data.current/3600;
    ina219Data.energy+=ina219Data.power/3600;
    ina219Data.runtime++; } }
