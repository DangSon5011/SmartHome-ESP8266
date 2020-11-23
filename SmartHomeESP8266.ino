#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html.h"
const char*ssid = "TP-LINK_E57E";
const char*password = "12341234";
const long interval = 10000; //Thời gian update tự động giá trị trên server
float temp = 0, humi = 0;

ESP8266WebServer server(80); // Tạo đối tượng WebServer object on port 80

void setup() {
  pinMode(16,OUTPUT);
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
server.on("/",mainPage);
server.on("/temperature",readTemp);
server.on("/humidity",readHumi);
server.on("/batden1",on_D1);
server.on("/tatden1",off_D1);
server.begin();
}

void loop() {
  server.handleClient();
}
void mainPage(){
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void readTemp(){
  temp = temp +0.01;
  if(isnan(temp)){
    server.send(200,"text/plane","Cảm biến không hoạt động");
  }else{
    server.send(200,"text/plane",String(temp));
  }
}

void readHumi(){
  humi = humi +0.01;
  if (isnan(humi)){
   server.send(200,"text/plane","Cảm biến không hoạt động");
  }else{
    server.send(200,"text/plane",String(humi));
  }
}
void on_D1(){
  digitalWrite(16,LOW);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}

void off_D1(){
  digitalWrite(16,HIGH);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
