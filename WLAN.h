#include <WiFi.h>
#include <Preferences.h>
Preferences preferences;

struct wlanConfigStruct {
  const char* ssidAP=appName;
  const char* passwordAP="";
  String ssidStation="";
  String passwordStation="";
  boolean statusStation=false; };

struct wlanConfigStruct wlanConfig;

uint32_t wlanTimer=millis()+10000;

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  preferences.begin("wlanAuth",false); String ssidStationOld=preferences.getString("ssidStation",""); String passwordStationOld=preferences.getString("passwordStation",""); preferences.end();
  if (ssidStationOld!=wlanConfig.ssidStation || passwordStationOld!=wlanConfig.passwordStation) {
    preferences.begin("wlanAuth",false); preferences.putString("ssidStation",wlanConfig.ssidStation); preferences.putString("passwordStation",wlanConfig.passwordStation); preferences.end(); }
  wlanConfig.statusStation=true; if (debug) { Serial.println("WLAN Station " + wlanConfig.ssidStation + " Client with IP address " + WiFi.localIP().toString() + " connected."); } }

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  wlanConfig.statusStation=false; WiFi.disconnect(); if (debug) { Serial.println("WLAN Station " + wlanConfig.ssidStation + " disconnected."); } }

void initWLAN() {
  preferences.begin("wlanAuth",false); wlanConfig.ssidStation=preferences.getString("ssidStation",""); wlanConfig.passwordStation=preferences.getString("passwordStation",""); preferences.end();
  WiFi.mode(WIFI_AP_STA);
  WiFi.onEvent(WiFiStationConnected,ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFiStationDisconnected,ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  WiFi.softAPConfig(IPAddress(192,168,4,1),IPAddress(192,168,4,1),IPAddress(255,255,255,0)); WiFi.softAP(wlanConfig.ssidAP,wlanConfig.passwordAP);
  WiFi.setHostname(wlanConfig.ssidAP); WiFi.begin(wlanConfig.ssidStation.c_str(),wlanConfig.passwordStation.c_str());
  if (debug) { Serial.println("WLAN AP " + String(wlanConfig.ssidAP) + " with IP address " + WiFi.softAPIP().toString() + " enabled."); } }

void reconnectWLAN() {
  if (wlanConfig.statusStation) { WiFi.disconnect(); delay(250); }
  WiFi.begin(wlanConfig.ssidStation.c_str(),wlanConfig.passwordStation.c_str()); }

void wlanWorker() {
  if (millis()>=wlanTimer) { wlanTimer=millis()+10000;
    if (!wlanConfig.statusStation) {
      preferences.begin("wlanAuth",false); String ssidStationOld=preferences.getString("ssidStation",""); String passwordStationOld=preferences.getString("passwordStation",""); preferences.end();
      if (ssidStationOld==wlanConfig.ssidStation && passwordStationOld==wlanConfig.passwordStation && WiFi.softAPgetStationNum()==0) { WiFi.begin(wlanConfig.ssidStation.c_str(),wlanConfig.passwordStation.c_str()); } } } }
