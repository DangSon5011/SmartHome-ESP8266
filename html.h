const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Smart Home</title>
        <meta name = "viewport" content="width=device-width, initial-scale = 1">
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
              background-image: url();
              background-attachment: fixed;
              background-repeat: no-repeat;
              background-position: center;
              background-size: cover;
            }
            div{
                padding: 2%;
                align-items: center;
                display: inline;
            }
            td{
                width: 20%;
                align-items: center;
                text-align: center;
            }
            table{
                border: 1%;
                align-items: center;
            }
          </style>
    </head>

    <body>
        <h2 align="center" style="background: red;color: #FFF;padding-top: 20px;padding-bottom: 20px;" id="tieude"><Span style ="color: black; font-family: Arial; font-size: 28px"><STRONG>Hệ thống điều khiển và giám sát thiết bị trong nhà</STRONG> </span></h2>
        <div>
            <table align="center" border="1">
                <tr>
                    <th colspan="3">Sân vườn</th>
                </tr>
                <tr>
                   <td >Cổng</td>
                   <td >
                       <a href="/mocong"><button class='b'>Mở</button></a>
                       <a href="/dongcong"><button class='t'>Đóng</button></a>
                   </td>
                   <td id = "Cong"></td>
                </tr>
                <tr>
                    <td >Cửa nhà</td>
                    <td>
                        <a href="/mocuanha"><button class='b'>Mở</button></a>
                        <a href="/dongcuanha"><button class='t'>Đóng</button></a>
                    </td>
                    <td id="CuaNha" ></td> 
                </tr>
                <tr>
                    <td>Giàn phơi đồ</td>
                    <td>
                        <a href="/mogianphoi"><button class='b'>Mở</button></a>
                        <a href="/donggianphoi"><button class='t'>Thu</button></a>
                    </td>
                    <td id='GianPhoi'></td>
                </tr>
            </table>
        </div>
        
        <div class ='PhongKhach'>
            <table   align="center" border="1">
                <tr>
                    <th colspan="3">Phòng Khách</th>
                </tr>
                <tr>
                    <td colspan="3">
                        <p align="center"> 
                        <span  style ="color: red; font-family: Arial; font-size: 15px"> <Strong><u>Nhiệt độ hiện tại là :</u></Strong></span> 
                        <span id="temperature">0</span>°C<br>
                      </p>
                      <p align="center"> 
                        <span  style ="color: red; font-family: Arial; font-size: 15px"> <Strong><u>Độ ẩm hiện tại là  :</u></Strong></span>
                        <span id="humidity">0</span>%<br>
                      </p>
                    </td>  
                </tr>
                <tr>
                    <td class="units" width="20%" align="center">Đèn</td>
                    <td class="units" width="20%" align="center">
                        <a href="/batdenkhach"><button class="b">Bật</button></a>
                        <a href="/tatdenkhach"><button class="t">Tắt</button></a>
                    </td>
                    <td id = "DenKhach"></td>
                </tr>
                <tr>
                    <td class="units" width="20%" align="center">Cửa Sổ</td>
                    <td class="units" width="20%" align="center">
                        <a href="/mocuasokhach"><button class='b'>Mở</button></a>
                        <a href="/dongcuasokhach"><button class='t'>Đóng</button></a>
                    </td>
                    <td id ='CuaSoKhach'></td>
                </tr>
            </table>
        </div>

        <div>
            <table   align="center" border="1">
                <tr>
                    <th colspan="3">Phòng ăn</th>
                </tr>
                <tr>

                    <th colspan="3">
                        <p align="center"> 
                        <span  style ="color: red; font-family: Arial; font-size: 15px"> <Strong><u>Cảnh báo khí gas  :</u></Strong></span>
                        <span id="gas">0</span><br>
                      </p></th>
                </tr>
                
                <tr>
                    <td class="units" width="20%" align="center">Đèn</td>
                    <td class="units" width="20%" align="center">
                        <a href="/batdenphongan"><button class='b'>Bật</button></a>
                        <a href="/tatdenphongan"><button class='t'>Tắt</button></a>
                    </td>
                    <td id='DenAn'></td>
                </tr>
                <tr>
                    <td class="units" width="20%" align="center">Cửa sổ</td>
                    <td class="units" width="20%" align="center">
                        <a href="/mocuasophongan"><button class='b'>Mở</button></a>
                        <a href="/dongcuasophongan"><button class='t'>Đóng</button></a>
                    </td>
                    <td id = 'CuaSoAn'></td>
                </tr>
                <tr>
                    <td>Quạt</td>
                    <td>
                        <a href="/moquatphongan"><button class='b'>Bật</button></a>
                        <a href="/dongquatphongan"><button class='t'>Tắt</button></a>  
                    </td>
                    <td id = 'QuatAn'></td>
                </tr>
            </table>
        </div>

        <div>
            <table align="center" border="1">
               
                <tr>
                    <th colspan="3">Phòng ngủ 1</th>
                </tr>
                <tr>
                    <td>Đèn</td>
                    <td>
                        <a href="/batdenphongngu1"><button class='b'>Bật</button></a>
                        <a href="/tatdenphongngu1"><button class='t'>Tắt</button></a>
                    </td>
                    <td id = 'DenNgu1'></td>
                </tr>
                <tr>
                    <td>Cửa sổ</td>
                    <td>
                        <a href="/mocuasophongngu1"><button class='b'>Mở</button></a>
                        <a href="/dongcuasophongngu1"><button class='t'>Đóng</button></a>
                    </td>
                    <td id ='CuaSoNgu1'></td>
                </tr>
                <tr>
                    <th colspan="3">Phòng ngủ 2</th>
                </tr>
                <tr>
                    <td>Đèn</td>
                    <td >
                        <a href="/batdenphongngu2"><button class='b'>Bật</button></a>
                        <a href="/tatdenphongngu2"><button class='t'>Tắt</button></a>
                    </td>
                    <td id = 'DenNgu2'></td>
                </tr>
                <tr>
                    <td>Cửa sổ</td>
                    <td>
                        <a href="/mocuasophongngu2"><button class='b'>Mở</button></a>
                        <a href="/dongcuasophongngu2"><button class='t'>Đóng</button></a>
                    </td>
                    <td id ='CuaSoNgu2'></td>
                </tr>
                <tr>
                    <th colspan="3">Phòng ngủ 3</th>
                </tr>
                <tr>
                    <td>Đèn</td>
                    <td >
                        <a href="/batdenphongngu3"><button class='b'>Bật</button></a>
                        <a href="/tatdenphongngu3"><button class='t'>Tắt</button></a>
                    </td>
                    <td id = 'DenNgu3'></td>
                </tr>
                <tr>
                    <td>Cửa sổ</td>
                    <td>
                        <a href="/mocuasophongngu3"><button class='b'>Mở</button></a>
                        <a href="/dongcuasophongngu3"><button class='t'>Đóng</button></a>
                    </td>
                    <td id ='CuaSoNgu3'></td>
                </tr>
            </table>
            <table align="center" border="1">
                <tr>
                    <th colspan="3">Nhà vệ sinh 1</th>
                </tr>
                <tr>
                    <td>Đèn</td>
                    <td >
                        <a href="/batdenvs1"><button class='b'>Bật</button></a>
                        <a href="/tatdenvs1"><button class='t'>Tắt</button></a>
                    </td>
                    <td id ='Denvs1'></td>
                </tr>
                <tr>
                    <th colspan="3">Nhà vệ sinh 2</th>
                </tr>
                <tr>
                    <td>Đèn</td>
                    <td >
                        <a href="/batdenvs2"><button class='b'>Bật</button></a>
                        <a href="/tatdenvs2"><button class='t'>Tắt</button></a>
                    </td>
                    <td id ='Denvs2'></td>
                </tr>
                <tr>
                    <th colspan="3">Nhà vệ sinh 2</th>
                </tr>
                <tr>
                    <td>Nhà Tắm</td>
                    <td >
                        <a href="/batdentam"><button class='b'>Bật</button></a>
                        <a href="/tatdentam"><button class='t'>Tắt</button></a>
                    </td>
                    <td id ='DenTam'></td>
                </tr>
            </table>
        </div>
    </body>
    <script>
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("Cong").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/Cong", true);
        xhttp.send();
        }, 1000) ;

        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("CuaNha").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/CuaNha", true);
        xhttp.send();
        }, 1000) ;

        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("GianPhoi").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/GianPhoi", true);
        xhttp.send();
        }, 1000) ;
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
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("DenKhach").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/DenKhach", true);
        xhttp.send();
        }, 1000) ;

        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("CuaSoKhach").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/CuaSoKhach", true);
        xhttp.send();
        }, 1000) ;

        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("DenAn").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/DenAn", true);
        xhttp.send();
        }, 1000) ;
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("gas").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/gas", true);
        xhttp.send();
        }, 1000 ) ;
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("CuaSoAn").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/CuaSoAn", true);
        xhttp.send();
        }, 1000) ;

        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("QuatAn").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/QuatAn", true);
        xhttp.send();
        }, 1000) ;
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("DenNgu1").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/DenNgu1", true);
        xhttp.send();
        }, 1000) ;
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("CuaSoNgu1").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/CuaNgu1", true);
        xhttp.send();
        }, 1000) ;
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("DenNgu2").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/DenNgu2", true);
        xhttp.send();
        }, 1000) ;
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("CuaSoNgu2").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/CuaNgu2", true);
        xhttp.send();
        }, 1000) ;
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("DenNgu3").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/DenNgu3", true);
        xhttp.send();
        }, 1000) ;
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("CuaSoNgu3").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/CuaNgu3", true);
        xhttp.send();
        }, 1000) ;
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("Denvs1").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/Denvs1", true);
        xhttp.send();
        }, 1000) ;
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("Denvs2").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/Denvs2", true);
        xhttp.send();
        }, 1000) ;
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("Denvs3").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/Denvs3", true);
        xhttp.send();
        }, 1000) ;
        setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("DenTam").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/DenTam", true);
        xhttp.send();
        }, 1000) ;
</script>
</html>
)rawliteral";
