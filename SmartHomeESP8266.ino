#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html.h"
const char*ssid = "Redmi Note 8 Pro";
const char*password = "244466666";
const long interval = 10000; //Thời gian update tự động giá trị trên server
float temp = 0, humi = 0;
byte a= 0B00000000;


ESP8266WebServer server(80); // Tạo đối tượng WebServer object on port 80
void sendData(void)
{

  Serial.write(a);
}

void setup() {
  pinMode(16,OUTPUT);
/********* Setup Serial Baudrate *****/
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

/*********** Route for root /web page ***********/
/***************************************************/
server.on("/",mainPage);
/********* Phòng khách ********************/
server.on("/temperature",readTemp);
server.on("/humidity",readHumi);
server.on("/batdenkhach",on_ledKhach);
server.on("/tatdenkhach",off_ledKhach);
server.on("/mocuasokhach",open_CuaKhach);
server.on("/dongcuasokhach",close_CuaKhach);
/********* Cửa nhà và cổng ****************/
server.on("/mocong",open_Cong);
server.on("/dongcong",close_Cong);
server.on("/mocuanha",open_CuaNha);
server.on("/dongcuanha",close_CuaNha);
/********** Phòng Ăn *********************/
server.on("/gas",readGas);
server.on("/batdenphongan",on_ledAn);
server.on("/tatdenphongan",off_ledAn);
server.on("/mocuasophongan",open_CuaAn);
server.on("/dongcuasophongan",close_CuaAn);
/*********** Phòng ngủ 1 *****************/
server.on("/batdenphongngu1",on_ledNgu1);
server.on("/tatdenphongngu1",off_ledNgu1);
server.on("/mocuasophongngu1",open_CuaNgu1);
server.on("/dongcuasophongngu1",close_CuaNgu1);
/********** Phòng ngủ 2 ******************/
server.on("/batdenphongngu2",on_ledNgu2);
server.on("/tatdenphongngu2",off_ledNgu2);
server.on("/mocuasophongngu2",open_CuaNgu2);
server.on("/dongcuasophongngu2",close_CuaNgu2);
/********** Phòng ngủ 3 ******************/
server.on("/batdenphongngu3",on_ledNgu3);
server.on("/tatdenphongngu3",off_ledNgu3);
server.on("/mocuasophongngu3",open_CuaNgu3);
server.on("/dongcuasophongngu3",close_CuaNgu3);
/***************************************************/
server.begin();
}

void loop() {
  server.handleClient();
}

/************ Function route ***********************/
/***************** MAIN PAGE ***********************/
void mainPage(){
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/***************** Phòng Khách ******************************/
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
void on_ledKhach(){
  digitalWrite(16,LOW);
  a = a | (1<<5);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/*Bit |0   |1      |2        |3       |4     |5     |6      |7*/
/*    |Cổng|Cửa nhà|Đèn khách|sổ Khách|Đèn ăn|Cửa ăn|Đèn Ngủ|Cửa sổ|*/
void off_ledKhach(){
  digitalWrite(16,HIGH);
  a = a & ~(1<<5);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_CuaKhach(){
  digitalWrite(16,LOW);
  a = a | (1<<4);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_CuaKhach(){
  digitalWrite(16,HIGH);
  a = a & ~(1<<4);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/****************** Cửa nhà và cổng ****************************/
void open_Cong(){
  digitalWrite(16,LOW);
  a = a | (1<< 7);// & ~0;
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_Cong(){
  digitalWrite(16,HIGH);
  a = a & ~(1<<7);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_CuaNha(){
  digitalWrite(16,LOW);
  a = a | (1<<6);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_CuaNha(){
  digitalWrite(16,HIGH);
   a = a & ~(1<<6);
   Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/****************** Phòng Bếp **************************************/
void readGas(){
  
}
void on_ledAn(){
  digitalWrite(16,LOW);
  a = a | (1 << 3);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void off_ledAn(){
  digitalWrite(16,HIGH);
   a = a & ~(1 << 3);
   Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_CuaAn(){
  digitalWrite(16,LOW);
  a = a | (1 << 2);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_CuaAn(){
  digitalWrite(16,HIGH);
  a = a & ~(1 << 2);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/*********************** Phòng ngủ 1 *********************/
void on_ledNgu1(){
  digitalWrite(16,LOW);
  a = a | (1 << 1);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void off_ledNgu1(){
  digitalWrite(16,HIGH);
  a = a & ~(1<<1);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_CuaNgu1(){
  digitalWrite(16,LOW);
   a = a | (1 << 0);
   Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_CuaNgu1(){
  digitalWrite(16,HIGH);
  a = a & ~(1 << 0);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/******************* Phòng Ngủ 2 **********************/
void on_ledNgu2(){
  digitalWrite(16,LOW);
  Serial.println(a,BIN);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void off_ledNgu2(){
  digitalWrite(16,HIGH);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_CuaNgu2(){
  digitalWrite(16,LOW);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_CuaNgu2(){
  digitalWrite(16,HIGH);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/*************************Phòng ngủ 3 ***********************/
void on_ledNgu3(){
  digitalWrite(16,LOW);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void off_ledNgu3(){
  digitalWrite(16,HIGH);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_CuaNgu3(){
  digitalWrite(16,LOW);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_CuaNgu3(){
  digitalWrite(16,HIGH);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
