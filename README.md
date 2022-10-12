# helioMeter
ESP32 and INA219 based photovoltaic powermeter
#### Features
* uses TI INA219 as current/power sensor
* works as WLAN client and AP (AP chooser included)
* WebUI with IP address 192.168.4.1
* mDNS hostname heliometer.local
* DNS hostname heliometer.local (WLAN AP mode only)
* shunt resistors 0.1 Ohm and 0.01 Ohm parallel (Rpar = 0.00909 Ohm)
* measures up to 35 amps
* measures voltage, current, power, resistance, charge and energy
* charge, energy and running time are stored every 6 hours automatically or manually via web ui
#### I2C bus
* SDA - GPIO 21
* SCL - GPIO 22
* address - 0x40
#### Development Hardware
![IMAGE ALT TEXT HERE](https://www.dorstel.de/github/helioMeter_a_v1.0.png)
#### Web UI Screenshot
![IMAGE ALT TEXT HERE](https://www.dorstel.de/github/helioMeter_b_v1.1.png)
