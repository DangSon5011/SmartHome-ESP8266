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
  <style>
    body{
      background-image: url('https://3.bp.blogspot.com/-kZ9ci5Yj4xM/WMOU2eh_BEI/AAAAAAAAAT8/4X18ukP49Bs1hfLt8NvetXzA9J03BtRGgCLcB/s1600/chinese_girl.jpg');
      background-attachment: fixed;
      background-repeat: no-repeat;
      background-position: center;
      background-size: cover;
    }
  </style>
</head>
<body>
  <h2 align="center" style="background: red;color: #FFF;padding-top: 20px;padding-bottom: 20px;" id="tieude"><Span style ="color: black; font-family: Arial; font-size: 28px"><STRONG>Hệ thống điều khiển và giám sát thiết bị trong nhà</STRONG> </span></h2>
  <table align="center">
    <tr align="center">
        <th colspan="2"><p class="small" align="center"> <Span style ="color: black; font-family: Arial; font-size: 20px"> <STRONG><u>Cửa cổng</u></STRONG> </span> </p></th>
        <th width="20%"></th>
        <th colspan="2"><p class="small" align="center"> <Span style ="color: black; font-family: Arial; font-size: 20px"> <STRONG><u>Cửa nhà</u></STRONG> </span> </p></th>
    </tr>
    <tr>
      <td class="units" width="20%" align="center"><a href="/mocong"><button class='b'>Đóng</button></a></td>
    <td width="20%" align="center"><a href="/dongcong"><button class='t'>Mở</button></a></td>
    <td width="20%"></td>
    <td width="20%" align="center"><a href="/mocuanha"><button class='b'>Đóng</button></a></td>
    <td width="20%" align="center"><a href="/dongcuanha"><button class='t'>Mở</button></a></td>
    </tr>
  </table>
  <table align="center">
    <p align="center"> <span style ="color: black; font-family: Arial; font-size: 20px"> <STRONG><u>Phòng khách</u></STRONG> </span> </p>   
    <p align="center"> 
      <span  style ="color: red; font-family: Arial; font-size: 15px"> <Strong><u>Nhiệt độ hiện tại là :</u></Strong></span> 
      <span id="temperature">0</span>°C<br>
    </p>
    <p align="center"> 
      <span  style ="color: red; font-family: Arial; font-size: 15px"> <Strong><u>Độ ẩm hiện tại là  :</u></Strong></span>
      <span id="humidity">0</span>%<br>
    </p>
   </table>
   <div align="center">
   <Span align="center" style ="color: red; font-family: Arial; font-size: 18px"><Strong>Đèn</Strong></span> 
      <button class="b"><a href="/batdenkhach">ON</a></button>
      <button class="t"><a href="/tatdenkhach">OFF</a></button>
   </div>  
   <table align="center">
   <tr>
      <td width="30%"> <p align="center"> <Span style ="color: red; font-family: Arial; font-size: 18px"><Strong>Cửa sổ</Strong></span> </p> </td>
      <td><a href="/mocuasokhach"><button class='b'>Mở</button></a><td>
      <td><a href="/dongcuasokhach"><button class='t'>Đóng</button></a><td>
        <td width="30%"> </td>
      <tr>  
  </table>

  
  <table>
  <p align="center"> <Span style ="color: black; font-family: Arial; font-size: 20px"> <STRONG><u>Phòng ăn</u></STRONG> </span> </p>
    <p align="center"> <Span style ="color: red; font-family: Arial; font-size: 15px"> <Strong>Trạng thái cảnh báo khí gas:</Strong></span> </p>
    <table align="center">
    <tr>
      <td width="30%"> <p align="center"> <Span style ="color: red; font-family: Arial; font-size: 18px"><Strong>Đèn</Strong></span> </p> </td>
      <td><a href="/batdenphongan"><button class='b'>Bật</button></a><td>
      <td><a href="/tatdenphongan"><button class='t'>Tắt</button></a><td>
      <td width="30%"> </td>
      <tr>  
  </table>
  <table align="center">
    <tr>
      <td width="30%"> <p align="center"> <Span style ="color: red; font-family: Arial; font-size: 18px"><Strong>Cửa sổ</Strong></span> </p> </td>
      <td><a href="/mocuasophongan"><button class='b'>Mở</button></a><td>
      <td><a href="/dongcuasophongan"><button class='t'>Đóng</button></a><td>
        <td width="30%"> </td>
      <tr>
      </tr> 
  </table>
  <table align="center">
  <tr>
    <th>
  <p align="center"> <Span style ="color: black; font-family: Arial; font-size: 20px"> <STRONG><u>Phòng ngủ số 1</u></STRONG> </span> </p>
  <table border="2" align="center">
    <tr><th>
    <table align="center">
    <tr>
      <td width="30%"> <p align="center"> <Span style ="color: red; font-family: Arial; font-size: 18px"><Strong>Đèn</Strong></span> </p> </td>
      <td><a href="/batdenphongngu1"><button class='b'>Bật</button></a><td>
      <td><a href="/tatdenphongngu1"><button class='t'>Tắt</button></a><td>
      <td width="30%"> </td>
      <tr>  
    </table>

  <th><table align="center">
    <tr>
      <td width="30%"> <p align="center"> <Span style ="color: red; font-family: Arial; font-size: 18px"><Strong>Cửa sổ</Strong></span> </p> </td>
      <td><a href="/mocuasophongngu1"><button class='b'>Mở</button></a><td>
      <td><a href="/dongcuasophongngu1"><button class='t'>Đóng</button></a><td>
        <td width="30%"> </td>
      <tr>  
  </table></th>
</table>
</th>
  <th>
  <p align="center"> <Span style ="color: black; font-family: Arial; font-size: 20px"> <STRONG><u>Phòng ngủ số 2</u></STRONG> </span> </p>
    <table border="2" align="center">
    <tr><th>
    <table align="center">
    <tr>
      <td width="30%"> <p align="center"> <Span style ="color: red; font-family: Arial; font-size: 18px"><Strong>Đèn</Strong></span> </p> </td>
      <td><a href="/batdenphongngu2"><button class='b'>Bật</button></a><td>
      <td><a href="/tatdenphongngu2"><button class='t'>Tắt</button></a><td>
        <td width="30%"> </td>
      <tr>
    </table></th>
  <th><table align="center">
    <tr>
      <td width="30%"> <p align="center"> <Span style ="color: red; font-family: Arial; font-size: 18px"><Strong>Cửa sổ</Strong></span> </p> </td>
      <td><a href="/mocuasophongngu2"><button class='b'>Mở</button></a><td>
      <td><a href="/dongcuasophongngu2"><button class='t'>Đóng</button></a><td>
        <td width="30%"> </td>
      <tr>  
  </table></th> 
  <tr>
  </table>
  </th>
  <th>
  <p align="center"> <Span style ="color: black; font-family: Arial; font-size: 20px"> <STRONG><u>Phòng ngủ số 3</u></STRONG> </span> </p>
    <table border="2" align="center">
  <tr><th>
    <table align="center">
    <tr>
      <td width="30%"> <p align="center"> <Span style ="color: red; font-family: Arial; font-size: 18px"><Strong>Đèn</Strong></span> </p> </td>
      <td><a href="/batdenphongngu3"><button class='b'>Bật</button></a><td>
      <td><a href="/tatdenphongngu3"><button class='t'>Tắt</button></a><td>
        <td width="30%"> </td>
      <tr>  
  </table>
</th>
  <th>
  <table align="center">
    <tr>
      <td width="30%"> <p align="center"> <Span style ="color: red; font-family: Arial; font-size: 18px"><Strong>Cửa sổ</Strong></span> </p> </td>
      <td><a href="/mocuasophongngu3"><button class='b'>Mở</button></a><td>
      <td><a href="/dongcuasophongngu3"><button class='t'>Đóng</button></a><td>
        <td width="30%"> </td>
      <tr>  
  </table>
</th>
  </table>
</th>
</tr>
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
