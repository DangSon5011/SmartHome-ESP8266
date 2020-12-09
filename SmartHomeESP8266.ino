#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html.h"
const char*ssid = "Redmi Note 8 Pro";
const char*password = "244466666";
//const char*ssid = "TP-LINK_E57E";
//const char*password = "12341234";
//const char*ssid = "waZex";
//const char*password = "hoang1030";
const long interval = 10000; //Thời gian update tự động giá trị trên server...
float temp = 0, humi = 0;
byte a[3]; //
byte b[7];
byte flagRx = 0;
int moc =0;
String data;
ESP8266WebServer server(80); // Tạo đối tượng WebServer object on port 80

void setup() {
  pinMode(16,OUTPUT);
/********* Setup Serial Baudrate *****/
/****** Setup WiFi begin **********/
  WiFi.begin(ssid,password);
  Serial.begin(115200);
 // Serial.print("Connecting");
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
server.on("/mogianphoi",open_GianPhoi);
server.on("/donggianphoi",close_GianPhoi);
/********** Phòng Ăn *********************/
server.on("/gas",readGas);
server.on("/batdenphongan",on_ledAn);
server.on("/tatdenphongan",off_ledAn);
server.on("/mocuasophongan",open_CuaAn);
server.on("/dongcuasophongan",close_CuaAn);
server.on("/moquatphongan",on_QuatAn);
server.on("/dongquatphongan",off_QuatAn);
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
/*********** Vệ sinh **********************/
server.on("/batdenvs1",on_ledVs1);
server.on("/tatdenvs1",off_ledVs1);
server.on("/batdenvs2",on_ledVs2);
server.on("/tatdenvs2",off_ledVs2);
server.on("/batdentam",on_ledTam);
server.on("/tatdentam",off_ledTam);
/***************************************************/
/***** Cập nhật trạng thái thiết bị ****************/
server.on("/Cong",readCong);
server.on("/CuaNha",readCuaNha);
server.on("/GianPhoi",readGianPhoi);
server.on("/DenKhach",readDenKhach);
server.on("/CuaSoKhach",readCuaSoKhach);
server.on("/DenAn",readDenAn);
server.on("/CuaSoAn",readCuaSoAn);
server.on("/QuatAn",readQuatAn);
server.on("/DenNgu1",readDenNgu1);
server.on("/CuaNgu1",readCuaNgu1);
server.on("/DenNgu2",readDenNgu2);
server.on("/CuaNgu2",readCuaNgu2);
server.on("/DenNgu3",readDenNgu3);
server.on("/CuaNgu3",readCuaNgu3);
server.on("/Denvs1",readvs1);
server.on("/Denvs2",readvs2);
server.on("/DenTam",readDenTam);
server.begin();
}

void loop() {
  server.handleClient();
  if (Serial.available()){
     readDataSTM32();
  }
 
}

void readDataSTM32(){
  data = Serial.readString();
  String t;
  if (data[0] == 'A'){
    for (int i =2; i< data.length();i++){
    if (data.charAt(i) != ','){
        t += data[i];
    }
    else {
      b[moc] = t.toInt();
      t = "";
      if ( moc++ >=6) moc=0;
    }
   }
  }
  
}
/************ Function route ***********************/
/***************** MAIN PAGE ***********************/
void mainPage(){
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/************** Cổng và sân ***********/
void readCong(){
  if ( b[0] & (1 << 7))
    server.send(200,"text/plane","Đang mở");
  else 
    server.send(200,"text/plane","Đang đóng");
}
void readCuaNha(){
  if ( b[0] & (1 << 6))
    server.send(200,"text/plane","Đang mở");
  else 
    server.send(200,"text/plane","Đang đóng");
}
void readGianPhoi(){
  if ( b[1] & (1 << 0))
    server.send(200,"text/plane","Phơi đồ");
  else 
    server.send(200,"text/plane","Thu đồ");
}
/***************** Phòng Khách ******************************/
void readDenKhach(){
  if ( b[0] & (1 << 5))
    server.send(200,"text/plane","Đang bật");
  else 
    server.send(200,"text/plane","Đang tắt");
}
void readCuaSoKhach(){
  if ( b[0] & (1 << 4))
    server.send(200,"text/plane","Đang mở");
  else 
    server.send(200,"text/plane","Đang đóng");
}
void readTemp(){
  String t = String(b[3])+"."+String(b[4]);
   server.send(200,"text/plane",t);
  //if(isnan(inTemp) || isnan(fTemp)){
   // server.send(200,"text/plane","Cảm biến không hoạt động");
  //}else{
   // server.send(200,"text/plane",t);
  //}
}
void readHumi(){
  String h =String(b[5])+"."+String(b[6]);
  server.send(200,"text/plane",h);
  //if (isnan(inHumi) || isnan(fHumi)){
  // server.send(200,"text/plane","Cảm biến không hoạt động");
  //}else{
   // server.send(200,"text/plane",h);
  //}
}
void readGas(){
  if ( b[2] & (1 << 1))
    server.send(200,"text/plane","Cảnh báo rò rỉ");
  else 
    server.send(200,"text/plane","Bình thường");
}
void readDenAn(){
  if ( b[0] & (1 << 3))
    server.send(200,"text/plane","Đang bật");
  else 
    server.send(200,"text/plane","Đang tắt");
}
void readCuaSoAn(){
  if ( b[0] & (1 << 2))
    server.send(200,"text/plane","Đang mở");
  else 
    server.send(200,"text/plane","Đang đóng");
}
void readQuatAn(){
  if ( b[1] & (1 << 1))
    server.send(200,"text/plane","Đang bật");
  else 
    server.send(200,"text/plane","Đang tắt");
}
void readDenNgu1(){
  if ( b[0] & (1 << 1))
    server.send(200,"text/plane","Đang bật");
  else 
    server.send(200,"text/plane","Đang tắt");
}
void readCuaNgu1(){
  if ( b[0] & (1 << 0))
    server.send(200,"text/plane","Đang mở");
  else 
    server.send(200,"text/plane","Đang đóng");
}
void readDenNgu2(){
  if ( b[1] & (1 << 2))
    server.send(200,"text/plane","Đang bật");
  else 
    server.send(200,"text/plane","Đang tắt");
}
void readCuaNgu2(){
  if ( b[1] & (1 << 3))
    server.send(200,"text/plane","Đang mở");
  else 
    server.send(200,"text/plane","Đang đóng");
}
void readDenNgu3(){
  if ( b[1] & (1 << 4))
    server.send(200,"text/plane","Đang bật");
  else 
    server.send(200,"text/plane","Đang tắt");
}
void readCuaNgu3(){
  if ( b[1] & (1 << 5))
    server.send(200,"text/plane","Đang mở");
  else 
    server.send(200,"text/plane","Đang đóng");
}
void readvs1(){
  if ( b[1] & (1 << 6))
    server.send(200,"text/plane","Đang bật");
  else 
    server.send(200,"text/plane","Đang tắt");
}
void readvs2(){
  if ( b[1] & (1 << 7))
    server.send(200,"text/plane","Đang bật");
  else 
    server.send(200,"text/plane","Đang tắt");
}
void readDenTam(){
  if ( b[2] & (1 << 0))
    server.send(200,"text/plane","Đang bật");
  else 
    server.send(200,"text/plane","Đang tắt");
}
/******** Điều khiển *************/
void on_ledKhach(){
  digitalWrite(16,LOW);
  a[0] = a[0] | (1<<5);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/*Bit |7   |6      |5        |4       |3     |2     |1      |0     | byte2|7   |6   |5         |4         |3         |2         |1       |0         | byte 3|0      |*/
/*    |Cổng|Cửa nhà|Đèn khách|sổ Khách|Đèn ăn|Cửa ăn|Đèn Ngủ|Cửa sổ|      | vs2| vs1| Cửa ngủ 3| Den ngu 3| Cua Ngu 2| Den ngu 2|Quạt Ăn |Giàn phơi |       |Den tam|*/
void off_ledKhach(){
  digitalWrite(16,HIGH);
  a[0] = a[0] & ~(1<<5);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_CuaKhach(){
  digitalWrite(16,LOW);
  a[0] = a[0] | (1<<4);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_CuaKhach(){
  digitalWrite(16,HIGH);
  a[0] = a[0] & ~(1<<4);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/****************** Cửa nhà và cổng ****************************/
void open_Cong(){
  digitalWrite(16,LOW);
  a[0] = a[0] | (1<< 7);// & ~0;
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_Cong(){
  digitalWrite(16,HIGH);
  a[0] = a[0] & ~(1<<7);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_CuaNha(){
  digitalWrite(16,LOW);
  a[0] = a[0] | (1<<6);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_CuaNha(){
  digitalWrite(16,HIGH);
   a[0] = a[0] & ~(1<<6);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/****************** Phòng Bếp **************************************/

void on_ledAn(){
  digitalWrite(16,LOW);
  a[0] =a[0] | (1 << 3);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void off_ledAn(){
  digitalWrite(16,HIGH);
   a[0] = a[0] & ~(1 << 3);
   Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_CuaAn(){
  digitalWrite(16,LOW);
  a[0] = a[0] | (1 << 2);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_CuaAn(){
  digitalWrite(16,HIGH);
  a[0] = a[0] & ~(1 << 2);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/*********************** Phòng ngủ 1 *********************/
void on_ledNgu1(){
  digitalWrite(16,LOW);
  a[0] = a[0] | (1 << 1);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void off_ledNgu1(){
  digitalWrite(16,HIGH);
  a[0] = a[0] & ~(1<<1);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_CuaNgu1(){
  digitalWrite(16,LOW);
   a[0] =a[0] | (1 << 0);
   Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_CuaNgu1(){
  digitalWrite(16,HIGH);
  a[0] = a[0] & ~(1 << 0);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/******************* Phòng Ngủ 2 **********************/
void on_ledNgu2(){
  digitalWrite(16,LOW);
  a[1] = a[1] | (1<< 2);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void off_ledNgu2(){
  digitalWrite(16,HIGH);
  a[1] = a[1] & ~(1 << 2);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_CuaNgu2(){
  digitalWrite(16,LOW);
  a[1] = a[1] | (1<< 3);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_CuaNgu2(){
  digitalWrite(16,HIGH);
  a[1] = a[1] & ~(1 << 3);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
/*************************Phòng ngủ 3 ***********************/
void on_ledNgu3(){
  digitalWrite(16,LOW);
  a[1] = a[1] | (1<< 4);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void off_ledNgu3(){
  digitalWrite(16,HIGH);
  a[1] = a[1] & ~(1 << 4);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_CuaNgu3(){
  digitalWrite(16,LOW);
  a[1] = a[1] | (1<< 5);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_CuaNgu3(){
  digitalWrite(16,HIGH);
  a[1] = a[1] & ~(1 << 5);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void open_GianPhoi(){
  digitalWrite(16,LOW);
  a[1] = a[1] | (1<< 0);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void close_GianPhoi(){
  digitalWrite(16,HIGH);
  a[1] = a[1] & ~(1 << 0);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void on_QuatAn(){
  digitalWrite(16,LOW);
  a[1] = a[1] | (1<< 1);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void off_QuatAn(){
  digitalWrite(16,HIGH);
  a[1] = a[1] & ~(1 << 1);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void on_ledVs1(){
  digitalWrite(16,LOW);
  a[1] = a[1] | (1<< 6);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void off_ledVs1(){
  digitalWrite(16,HIGH);
  a[1] = a[1] & ~(1 << 6);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void on_ledVs2(){
  digitalWrite(16,LOW);
  a[1] = a[1] | (1<< 7);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void off_ledVs2(){
  digitalWrite(16,HIGH);
  a[1] = a[1] & ~(1 << 7);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void on_ledTam(){
  digitalWrite(16,LOW);
  a[2] = a[2] | (1<< 0);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
void off_ledTam(){
  digitalWrite(16,HIGH);
  a[2] = a[2] & ~(1 << 0);
  Serial.write(a[0]);
  Serial.write(a[1]);
  Serial.write(a[2]);
  String s = FPSTR(index_html);
  server.send(200,"text/html",s);
}
