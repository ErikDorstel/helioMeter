const char *index_html=R"(

<!DOCTYPE html>
<html lang="en"><head>
<title>helioMeter</title>
<meta name="author" content="Erik Dorstel">
<meta name="generator" content="vi">
<meta name="repository" content="https://github.com/ErikDorstel/helioMeter">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<style>
html   { font-family:Arial; }
div    { background-color:#e0e0e0; color:#000000; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
select { background-color:#f0f0f0; color:#000000; font-size:1.0em; border:0px; padding:0px; margin:0px; }
table  { margin-left:auto; margin-right:auto; }
td     { text-align:right; }
.x0a   { background-color:#c2d5ed; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b   { background-color:#c2d5ed; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0    { background-color:#c2d5ed; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1    { background-color:#f0f0f0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1a   { background-color:#e0e0e0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2    { background-color:#e0e0e0; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3    { background-color:#e0e0e0; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4    { background-color:#e0e0e0; padding:0.3em 0em; width:24%; font-size:1.4em; }
</style>
<script>

function webUIinit() {
  appName="&nbsp;"; appDesc="&nbsp;"; busvoltage=0; shuntvoltage=0; loadvoltage=0; current=0; power=0; resistance=0; charge=0; energy=0; runtime=0;
  ajaxObj=[]; requestAJAX('appName'); getValues(); doDisplay(); pollValuesID=false; pollValues(); }

function doDisplay() {
  id("busvoltage").innerHTML="Bus Voltage: "+doAutoRange(busvoltage," V");
  id("shuntvoltage").innerHTML="Shunt Voltage: "+doAutoRange(shuntvoltage," mV");
  id("loadvoltage").innerHTML="Load Voltage: "+doAutoRange(loadvoltage," V");
  id("current").innerHTML="Current: "+doAutoRange(current," mA");
  id("power").innerHTML="Power: "+doAutoRange(power," mW");
  id("resistance").innerHTML="Resistance: "+doAutoRange(resistance," &Omega;");
  id("charge").innerHTML="Charge: "+doAutoRange(charge," mAh");
  id("energy").innerHTML="Energy: "+doAutoRange(energy," mWh");
  id("runtime").innerHTML="Running Time: "+doAutoTime(runtime); }

function pollValues() { if (pollValuesID) { window.clearInterval(pollValuesID); } pollValuesID=window.setInterval("getValues();",5000); }
function getValues() { requestAJAX('getValues'); }
function resetValues() { id("resetValues").style.color="#ffffff"; requestAJAX('resetValues'); pollValues(); getValues(); }
function loadValues() { id("loadValues").style.color="#ffffff"; requestAJAX('loadValues'); pollValues(); getValues(); }
function saveValues() { id("saveValues").style.color="#ffffff"; requestAJAX('saveValues'); pollValues(); getValues(); }

function doAutoRange(value,unit) {
  if (Math.abs(value)>1500000) { value/=1000000;
    if (unit==" mAh") { unit=" kAh"; }
    if (unit==" mWh") { unit=" kWh"; } }
  if (Math.abs(value)>1500) { value/=1000;
    if (unit==" mA") { unit=" A"; }
    if (unit==" mW") { unit=" W"; }
    if (unit==" &Omega;") { unit=" k&Omega;"; }
    if (unit==" mAh") { unit=" Ah"; }
    if (unit==" mWh") { unit=" Wh"; } }
  if (Math.abs(value)<1.5) { value*=1000;
    if (unit==" mV") { unit=" &mu;V"; }
    if (unit==" V") { unit=" mV"; }
    if (unit==" mA") { unit=" &mu;A"; }
    if (unit==" mW") { unit=" &mu;W"; }
    if (unit==" &Omega;") { unit=" m&Omega;"; }
    if (unit==" mAh") { unit=" &mu;Ah"; }
    if (unit==" mWh") { unit=" &mu;Wh"; } }
  value=Math.round(value*100)/100;
  return value+unit; }

function doAutoTime(value) {
  days=Math.floor(value/86400); value-=days*86400;
  hours=Math.floor(value/3600); value-=hours*3600;
  minutes=Math.floor(value/60); value-=minutes*60;
  return days+" days "+hours.toString().padStart(2,'0')+":"+minutes.toString().padStart(2,'0')+":"+value.toString().padStart(2,'0'); }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded"); ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="appName") {
      id("appName").innerHTML=event.target.responseText.split(",")[0];
      id("appDesc").innerHTML=event.target.responseText.split(",")[1]; }
    else if (event.target.url=="resetValues") { id("resetValues").style.color="#000000"; }
    else if (event.target.url=="loadValues") { id("loadValues").style.color="#000000"; }
    else if (event.target.url=="saveValues") { id("saveValues").style.color="#000000"; }
    else if (event.target.url=="getValues") {
      busvoltage=event.target.responseText.split(",")[0]*1;
      shuntvoltage=event.target.responseText.split(",")[1]*1;
      loadvoltage=event.target.responseText.split(",")[2]*1;
      current=event.target.responseText.split(",")[3]*1;
      power=event.target.responseText.split(",")[4]*1;
      resistance=event.target.responseText.split(",")[5]*1;
      charge=event.target.responseText.split(",")[6]*1;
      energy=event.target.responseText.split(",")[7]*1;
      runtime=event.target.responseText.split(",")[8]*1; doDisplay(); } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="webUIinit();">

<div><div class="x0a" id="appName">&nbsp;</div></div>
<div><div class="x0b" id="appDesc">&nbsp;</div></div>

<div><div class="x1a" onclick="location.replace('/chooseAP');">Choose WLAN AP</div></div>

<div>
<div><div class="x1" id="busvoltage"></div></div>
<div><div class="x1" id="shuntvoltage"></div></div>
<div><div class="x1" id="loadvoltage"></div></div>
<div><div class="x1" id="current"></div></div>
<div><div class="x1" id="power"></div></div>
<div><div class="x1" id="resistance"></div></div>
<div><div class="x1" id="charge"></div></div>
<div><div class="x1" id="energy"></div></div>
<div><div class="x1" id="runtime"></div></div>
<div><div class="x3" id="resetValues" onclick="resetValues();">Reset</div>
     <div class="x3" id="loadValues" onclick="loadValues();">Load</div>
     <div class="x3" id="saveValues" onclick="saveValues();">Save</div></div>
</div>

</body></html>

)";
