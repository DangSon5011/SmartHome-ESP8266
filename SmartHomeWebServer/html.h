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
