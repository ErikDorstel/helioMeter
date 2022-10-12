String httpget(String request) {
  String response="";

  // webUI specific pages

  if (request.indexOf("/getValues")>=0) {
    response+=String(ina219Data.busvoltage,10) + ",";
    response+=String(ina219Data.shuntvoltage,10) + ",";
    response+=String(ina219Data.loadvoltage,10) + ",";
    response+=String(ina219Data.current,10) + ",";
    response+=String(ina219Data.power,10) + ",";
    response+=String(ina219Data.resistance,10) + ",";
    response+=String(ina219Data.charge,10) + ",";
    response+=String(ina219Data.energy,10) + ",";
    response+=String(ina219Data.runtime) + ","; }

  else if (request.indexOf("/resetValues")>=0) {
    ina219Data.charge=0;
    ina219Data.energy=0;
    ina219Data.runtime=0; }

  // WLAN Choose specific pages

  else if (request.indexOf("/appName")>=0) {
    response+=String(appName) + ",";
    response+=String(appDesc) + ","; }

  else if (request.indexOf("/chooseAP")>=0) { response=choose_html; }

  else if (request.indexOf("/statusAP")>=0) { if (wlanConfig.statusStation) { response="<div class=\"x1\">WLAN AP " + wlanConfig.ssidStation + " connected.</div>";
    response+="<div class=\"x1\">IP Address " + WiFi.localIP().toString() + "</div>"; } else { response="<div class=\"x1\">No WLAN AP connected.</div>"; } }

  else if (request.indexOf("/configAP")>=0) {
    if (WiFi.softAPgetStationNum()==0) { response=a2h(wlanConfig.ssidStation) + "," + a2h(wlanConfig.passwordStation) + ","; }
    else { response=a2h(wlanConfig.ssidStation) + ",,"; } }

  else if (request.indexOf("/scanAP")>=0) {
    wlanTimer=millis()+20000; int indexes=WiFi.scanNetworks(); for (int index=0;index<indexes;++index) { if (WiFi.SSID(index)!="") {
      response+="<div class=\"x1\" onclick=\"setAP(\'" + WiFi.SSID(index) + "\');\">" + WiFi.RSSI(index) + "&nbsp;dB&nbsp;&nbsp;&nbsp;&nbsp;" + WiFi.SSID(index) + "</div>"; } } }

  else if (request.indexOf("/connectAP")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1;
    if (!wlanConfig.statusStation || WiFi.softAPgetStationNum()==0) {
      wlanConfig.ssidStation=h2a(request.substring(a,b-1)); wlanConfig.passwordStation=h2a(request.substring(b)); wlanConfig.reconnectCount=0; reconnectWLAN(); }
    else { if (debug) { Serial.println("WLAN Station reconnect prevented."); } } }

  // Default page

  else { response=index_html; }

  return response; }
