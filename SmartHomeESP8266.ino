#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Hash.h>
const char*ssid = "TP-LINK_E57E";
const char*password = "12341234";
const long interval = 10000; //Thời gian update tự động giá trị trên server
unsigned long preMillis = 0; //Thời gian lưu giá trị update trước đó
float temp = 0, humi = 0;
/**************** Web Server ESP8266 ***********/
/*******************               *************/
AsyncWebServer server(80); // Tạo đối tượng AsyncWebServer object on port 80
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset = "utf-8">
  <title>Smart Home</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    .b{width: 60px;height: 25px;font-size: 13px;color: #FFF;background-color:#4caf50;border-radius: 30px;}
    .t{width: 60px;height: 25px;font-size: 13px;color: #FFF;background-color:#f44336;border-radius: 30px;}
  </style>
  <style>
    p.big{ line-height: 1.8;}
    p.small{line-height: 0.5;}
  </style>
</head>
<body>
  <table align="center">
    <h2 align="center" style="background: red;color: #FFF;padding-top: 20px;padding-bottom: 20px;" id="tieude"><Span style ="color: black; font-family: Arial; font-size: 28px"><STRONG>Hệ thống điều khiển và giám sát thiết bị trong nhà</STRONG> </span></h2>
    <p align="center"> <span style ="color: black; font-family: Arial; font-size: 20px"> <STRONG><u>Phòng khách</u></STRONG> </span> </p>
    
    <p align="center"> 
      <span  style ="color: red; font-family: Arial; font-size: 15px"> <Strong><u>Nhiệt độ hiện tại là :</u></Strong></span> 
      <span id="temperature">%TEMPERATURE%</span>
      <sup class="uints">&deg;C</sup>
    </p>
    <p align="center"> 
      <span  style ="color: red; font-family: Arial; font-size: 15px"> <Strong><u>Độ ẩm hiện tại là  :</u></Strong></span>
      <span id="humidity">%HUMIDITY%</span>
      <sup class="uints">&#37;</sup>
    </p>
   </table>
   <div align="center">
   <Span align="center" style ="color: red; font-family: Arial; font-size: 18px"><Strong>Đèn</Strong></span> 
      <button class="b"><a href="/batden1">ON</a></button>
      <button class="t"><a href="/tatden1">OFF</a></button>
   </div>  
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 1000) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 1000 ) ;
</script>
</html>
)rawliteral";

/******** Thay giá trị biến trong html *******/
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return String(temp);
  }
  else if(var == "HUMIDITY"){
    return String(humi);
  }
  return String();
}

void setup() {
/********* Setup Serial Baudrate *****/
  Serial.begin(115200);
/****** Setup WiFi begin **********/
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print("...");
  }
  Serial.print("WiFi connected to ");
  Serial.println(ssid);
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
/*********** Setup WiFi end ************/

/*********** Route for root /web page ******/
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(temp).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(humi).c_str());
  });
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if (currentMillis - preMillis >= interval){
    preMillis = currentMillis;
    
    //Read Temperature
    float newTemp = temp+1;
    if (isnan(newTemp)){
      Serial.println("Failed to read from DHT sensor!");
    }
    else{
      temp = newTemp;
      Serial.println(temp);
    }
    //Read Humidity
    float newHumi = humi+1;
    if(isnan(newHumi)){
      Serial.println("Failed to read from DHT sensor!");
    }
    else{
      humi = newHumi;
      Serial.println(humi);
    }
    
  }
}
