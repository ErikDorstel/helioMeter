boolean debug=true;

const char* appName="helioMeter";
const char* appDesc="PV Powermeter";

#include "WLAN.h"
#include "DNS.h"
#include "INA219.h"
#include "HTTP.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initWLAN();
  initDNS();
  initHTTP();
  initINA219(); }

void loop() { wlanWorker(); httpWorker(); dnsWorker(); ina219Worker(); }
