#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "html.h"
const char*ssid = "TP-LINK_E57E";
const char*password = "12341234";
const long interval = 10000; //Thời gian update tự động giá trị trên server
unsigned long preMillis = 0; //Thời gian lưu giá trị update trước đó
float temp = 0, humi = 0;
ESP8266WebServer server(80);

void ketnoi(){
  String s = index_html;
  server.send(200,"text/html",s);
}
void docdulieunhietdo(){
  temp = temp +0.01;
  String stemp = String(temp);
  if( isnan(temp)){
    server.send(200,"text/plain","Cảm biến không hoạt động");
  }else{
    server.send(200,"text/plain",stemp);
  }
}

void docdulieudoam(){
  humi = humi+0.01;
  String shumi = String(humi);
  if(isnan(humi)){
    server.send(200,"text/plain","Cảm biến không hoạt động");
  }else
  {
    server.send(200,"text/plain",shumi);
  }
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

server.on("/",ketnoi);
server.on("/temperature",docdulieunhietdo);
server.on("/himidity",docdulieudoam);
server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
}
