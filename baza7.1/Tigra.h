



const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<title>Air quality control system</title>

  <style>
  /* Градієнт кольору */
  body {
    background: linear-gradient(to bottom,#212121, #575757); /* Вертикальний градієнт зеленого до жовтого */
  }
     
    table {
      position: relative;
      width:100%;
      border-spacing: 0px;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      height: 20px;
      padding: 3px 15px;
      background-color: #343a40;  /*dark-blue*/
      color: #FFFFFF !important;  /*White ffffff*/
      }
    td {
      height: 20px;
       padding: 3px 15px;
    }
	  /* Стилі для рядка */
    .row {
       display: flex;
       justify-content: space-between;
       margin-bottom: 20px; /* Простий відступ між рядками */
    }
	
    .tabledata {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height:   25px;
      border-radius: 5px;
      color: #FFFFFF;  /*white*/
      line-height: 20px;
      transition: all 200ms ease-in-out;
      background-color: "grey"; /*light-grey*/
    }
    .tempslider {
      width: 300px;
      height: 55px;
      outline: none;
      height: 25px;
	  
    }
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
	  color: #AAAAAA; /*light-grey*/
    }
	 .bodytext2 {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 16px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
	  margin-right: 120px;
    }
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #AAAAAA;  /*white*/
      color: #000000;      /*black*/
      border-bottom: 5px solid #293578;
    }
    .fixed-top {
      position: fixed;
      top: 0;
      right: 0;
      left: 0;
      z-index: 1030;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
   .navheading {
     position: fixed;
     left: 60%;
     height: 50px;
     font-family: "Verdana", "Arial", sans-serif;
     font-size: 20px;
     font-weight: bold;
     line-height: 20px;
     padding-right: 20px;
   }
   .navdata {
      justify-content: flex-end;
      position: fixed;
      left: 70%;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      line-height: 20px;
      padding-right: 20px;
   }
    .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 32px;
      line-height: 50px;
      padding: 20px 10px 0px 10px;
      color: #62f406; /*green-light*/ /*#000000; black*/
    }
    .heading {
	  display: grid;
      place-items: center;
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: normal;
      font-size: 18px;
      text-align: center;
	  color: #AAAAAA; !important;  /*White ffffff*/
	   margin-left: 2px;
    }
      .cube {
      background-color: #AAAAAA; /*light-grey*/
      border: none;
      color: white;
      padding: 30px 10px;
	  //font-family: "Lilita One", sans-serif;
      font-weight: normal;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 20px;
      margin-left: 1px;
      cursor: pointer;
	  border-radius: 7px; /* Округлення кутів */
	 
    }
	
	
    .btn {
      background-color: #424242; /*peachpuff +25%dark*/
      border: none;
      color: white;
	  justify-content: center;

      padding: 15px 35px;*/
	  font-family: "Lilita One", sans-serif;
      font-weight: normal;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 20px;
      cursor: pointer;
	  border-radius: 7px; /* Округлення кутів */
	  margin-left: 1px; /* Відстань зліва до кнопки */
    }
	.btn:hover {
     background-color: #616161; /*peachpuff */
    }
	#airQ {
	  //background-color: #411bc9; /*peachpuff +25%dark*/
	  justify-content: center;
      border: none;
      color: white;
      font-weight: normal;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 18px;
      //margin: 4px 2px;
      cursor: pointer;

	}
	#square {
	  width: 120px;
      height: 30px;
      background-color: #5960e8;  /*white*/
	  transition: background-color 0.5s ease;/*плавне змінення кольору*.

	}
	.enabled{                    /* batton on */
	  background-color: #4CAF50;
	}
	
	 /* Стилі для красивого вигляду кнопки */
    .btnres {
      padding: 10px 20px;
      font-size: 16px;
      background-color: #45a049; /*green */
      color: #c8e1f2; /*колір кнопок*/
      border: none;
      cursor: pointer;
	  border-radius: 20px; /* Округлення кутів */
    }

    .btnres:hover {
     background-color: #62f406; /*green-light*/
    }
	
    .foot {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      position: relative;
      height:   30px;
      text-align: center;   
      color: #AAAAAA;  /*light-grey*/
      line-height: 20px;
    }
    .container {
      max-width: 1800px;
      margin: 0 auto;
	 /*display: flex;*/
      flex-direction: column; /* Колонка */
      /*align-items: center;*/ /* Центрування елементів по горизонталі */
	  
    }
	  /* Стилі для контейнера */
    .container2 {
     display: flex;
     justify-content: center;
     align-items: center;
     height: 10vh; /* Висота контейнера на весь екран */
	 
    }
	
    table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }
    
  </style>

  <body  onload="process()"> 
  
    <header>
      <div class="navbar fixed-top">
          <div class="container">
            <div class="navtitle">Air Quality Monitor</div>
            <div class="navdata" id = "date">mm/dd/yyyy</div>
            <div class="navheading">DATE</div><br>
            <div class="navdata" id = "time">00:00:00</div>
            <div class="navheading">TIME</div>
            
          </div>
      </div>
    </header>
  
    <main class="container" style="margin-top:70px">
      <div class="category">sensor readings</div>
      <div style="border-radius: 10px !important;">
      <table style="width:50%">
      <colgroup>
        <col span="1" style="background-color:rgb(95,95,95); width: 200; color:#000000 ;">
        <col span="1" style="background-color:rgb(100,100,100); width: 80; color:#000000 ;">
        <col span="1" style="background-color:rgb(105,105,105); width: 80; color:#000000 ;">
		<col span="1" style="background-color:rgb(110,110,110); width: 100; color:#000000 ;">
		<col span="1" style="background-color:rgb(115,115,115); width: 50; color:#000000 ;">
      </colgroup>
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
	  <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
	  <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <tr>
        <th colspan="1"><div class="heading">Parameter</div></th>
        <th colspan="1"><div class="heading">Value</div></th>
        <th colspan="1"><div class="heading">Name #</div></th>
		<th colspan="1"><div class="heading">Charge %</div></th>
		<th colspan="1"><div class="heading">Climat control</div></th>
      </tr>
      <tr>
        <td><div class="bodytext">CO2 PPM</div></td>
        <td><div class="tabledata" id = "a0"></div></td>
        <td><div class="tabledata" id = "b0"></div></td>
		<td><div class="tabledata" id = "c0"></div></td>
		<td><div class="cube" id = "airQ" ></div></td>

      </tr>
      <tr>
        <td><div class="bodytext">Humidity %</div></td>
        <td><div class="tabledata" id = "a1"></div></td>
        <td><div class="tabledata" id = "b1"></div></td>
		<td><div class="tabledata" id = "c1"></div></td>
		<td><div  ></div></td>
      </tr>
	  <tr>
        <td><div class="bodytext">Air Temperature C </div></td>
        <td><div class="tabledata" id = "a2"></div></td>
        <td><div class="tabledata" id = "b2"></div></td>
		<td><div class="tabledata" id = "c2"></div></td>
        <td><div class="cube" id = "square">safety color</div></td>
		</tr>
        <tr>
        <td><div class="bodytext">Auto control</div></td>
        <td><div class="tabledata" id = "a3"></div></td>
	    <td><div class="tabledata" id = "b3"></div></td>
		<td><div class="tabledata" id = "c3"></div></td>
		<td><button type="button" class = "btn" id = "btn0" onclick="ButtonPress0()">Toggle</button></td>
      </tr>
	   </tr>
        <tr>
        <td><div class="bodytext">Air control</div></td>
        <td><div class="tabledata" id = "a4"></div></td>
	    <td><div class="tabledata" id = "b4"></div></td>
		<td><div class="tabledata" id = "c4"></div></td>
		<td><button type="button" class = "btn" id = "btn1" onclick="ButtonPress1()">Toggle</button></td>
      </tr>
        <tr>
        <td><div class="bodytext">Conditioner</div></td>
        <td><div class="tabledata" id = "a5"></div></td>
	    <td><div  ></div></td>
		<td><div  ></div></td>
		<td><button type="button" class = "btn" id = "btn2" onclick="ButtonPress2()">Toggle</button></td>
      </tr>
    </table>
    </div>
    
    <br>
    <br>
    <div class="bodytext">Conditioner Control (C: <span id="airtemp"></span>)</div>
	<br>
        <span class="bodytext2">18</span>
		<span class="bodytext2">24</span>
		<span class="bodytext2">30</span>
	<br>
    <input type="range" class="tempslider" min="0" max="255" value = "0" width = "0%" oninput="UpdateSlider(this.value)"/>
    <br>
    <br>
    <br>
	
	<div class="container2">
    <div class="row">
	<button type="button" class = "btnres" id = "reloadButton">reboot page</button>
	<br>
	<br>
    <button type="button" class = "btnres" id = "reloadBtnESP" onclick="ButtonPress3()">reboot system</button>
    </div>
    </div>
	
	
	
  </main>

  <footer div class="foot" id = "temp" >ESP32 Web Page</div></footer>
  
  </body>


  <script type = "text/javascript">
  
    /* global variable visible to all java functions*/
    var xmlHttp=createXmlHttpObject();
    var btnflag = 0;
	var btn0flag = document.getElementById("btn0");
	
	// Отримуємо елемент квадрату за його id
    var square = document.getElementById("square");

   
	
    /* function to create XML object*/
    function createXmlHttpObject(){
      if(window.XMLHttpRequest){
        xmlHttp=new XMLHttpRequest();
      }
      else{
        xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
      }
      return xmlHttp;
    }

	
    function ButtonPress0() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "BUTTON_0", false);
      xhttp.send();
    }


    function ButtonPress1() {
      var xhttp = new XMLHttpRequest(); 
      xhttp.open("PUT", "BUTTON_1", false);
      xhttp.send(); 
    }
	
	function ButtonPress2() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "BUTTON_2", false);
      xhttp.send();
    }
	function ButtonPress3() { /*reload esp*/
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "BUTTON_3", false);
      xhttp.send();
    }
    
    function UpdateSlider(value) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          // update the web based on reply from  ESP
          document.getElementById("airtemp").innerHTML=this.responseText;
        }
      }
	  

      xhttp.open("PUT", "UPDATE_SLIDER?VALUE="+value, true);
      xhttp.send();
    }

    /* function to handle the response from the ESP*/
    function response(){
      var message;
      var barwidth;
      var currentsensor;
      var xmlResponse;
      var xmldoc;
      var dt = new Date();
      var color = "#e8e8e8";
     
	  
	  
      /* get the xml stream*/
      xmlResponse=xmlHttp.responseXML;
  
      /* get host date and time*/
      document.getElementById("time").innerHTML = dt.toLocaleTimeString();
      document.getElementById("date").innerHTML = dt.toLocaleDateString();
  
    
      
     
	   
      xmldoc = xmlResponse.getElementsByTagName("a0"); //value for co2
      message = xmldoc[0].firstChild.nodeValue;
	  
	 
      document.getElementById("a0").innerHTML=message;
      
	  
	  if (message >= 0 && message < 600) {
       square.style.backgroundColor = "#62f406"; /*green*/
	   document.getElementById("airQ").innerHTML="GOOD QUALITY AIR";
       } else if (message >= 600 && message < 1000) {
       square.style.backgroundColor = "#dae015"; /*yelow*/
	   document.getElementById("airQ").innerHTML="PERMISSIBLE QUALITY AIR";

       } else if (message >= 1000 && message < 1500) {
        square.style.backgroundColor = "orange";
		document.getElementById("airQ").innerHTML="LIMITED PERMISSIBLE QUALITY AIR";

       } else {
        square.style.backgroundColor = "red";
		document.getElementById("airQ").innerHTML="HARMFUL AIR";

       }
	  
	
	  
	  xmldoc = xmlResponse.getElementsByTagName("b0"); /*value for # name 1*/
      message = xmldoc[0].firstChild.nodeValue;	  
      document.getElementById("b0").innerHTML=message;  
	  xmldoc = xmlResponse.getElementsByTagName("c0"); /*value for charge %*/
      message = xmldoc[0].firstChild.nodeValue;
	   if (message < 10){
      color = "#aa0000";/*red*/
      } else if (message >= 10 && message < 50) {
		  color = "#dae015";/*yello*/
      }else {
        color = "#55b668";/*green*/
      } 
	  
	  width = message / 1;
      document.getElementById("c0").innerHTML=message;  
      document.getElementById("c0").style.width=(width+"%");
      document.getElementById("c0").style.backgroundColor=color;
      document.getElementById("c0").style.borderRadius="5px";
	 
	  
	 
      xmldoc = xmlResponse.getElementsByTagName("a1"); /*value for Humiditi %*/
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("a1").innerHTML=message;  
  
      
      xmldoc = xmlResponse.getElementsByTagName("b1");  /*value for # name 2*/
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("b1").innerHTML=message;
      
	  xmldoc = xmlResponse.getElementsByTagName("c1"); /*value for charge %*/
      message = xmldoc[0].firstChild.nodeValue;
	   if (message < 10){
      color = "#aa0000";/*red*/
      } else if (message >= 10 && message < 50) {
		  color = "#f3fb53";/*yello*/
      } else {
        color = "#55b668";/*green*/
      } 
	  
	  width = message / 1;
      document.getElementById("c1").innerHTML=message;  
      document.getElementById("c1").style.width=(width+"%");
      document.getElementById("c1").style.backgroundColor=color;
	  
      xmldoc = xmlResponse.getElementsByTagName("a2");  /*value for airtemp*/
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("a2").innerHTML=message;
      
	  xmldoc = xmlResponse.getElementsByTagName("b2"); /*value for # name 3*/
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("b2").innerHTML=message;
 
      xmldoc = xmlResponse.getElementsByTagName("c2"); /*value for charge %*/
      message = xmldoc[0].firstChild.nodeValue;
	   if (message < 10){
      color = "#aa0000";/*red*/
      } else if (message >= 10 && message < 50) {
		  color = "#f3fb53";/*yello*/
      } else {
        color = "#55b668";/*green*/
      } 
	  
	  width = message / 1;
      document.getElementById("c2").innerHTML=message;   
      document.getElementById("c2").style.width=(width+"%");
      document.getElementById("c2").style.backgroundColor=color;
      document.getElementById("c2").style.borderRadius="5px";
	  
      xmldoc = xmlResponse.getElementsByTagName("a3"); /*LED1*/
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("a3").style.backgroundColor="rgb(95,95,95)"; 
      /* update the text in the table*/
      if (message == 0){
        document.getElementById("a3").innerHTML="OFF";
        document.getElementById("btn0").innerHTML="Turn ON";
		document.getElementById("btn0").style.color="#FFFFFF"; //white
        document.getElementById("a3").style.color="#00AA00"; //green value
		btnflag = 0;
      } else {
        document.getElementById("a3").innerHTML="ON";
        document.getElementById("btn0").innerHTML="Turn OFF";
		document.getElementById("btn0").style.color="#f83939"; //red
        document.getElementById("a3").style.color="#e40004"; //red value
		btnflag = 1;
      } 
	  
	 /* Робимо  кнопкu неактивнi*/
	   if(btnflag == 1){
      btn1.style.display = "none";
	  btn2.style.display = "none";
	  btn0flag.classList.add("enabled");
	 } else {
	  btn1.style.display = "block";
	  btn2.style.display = "block";
	  btn0flag.classList.remove("enabled");
      }
	   
      
      xmldoc = xmlResponse.getElementsByTagName("b3");  /*value for # name 3*/
      message = xmldoc[0].firstChild.nodeValue
      document.getElementById("b3").innerHTML=message;
 
      xmldoc = xmlResponse.getElementsByTagName("c3"); /*value for charge %*/
      message = xmldoc[0].firstChild.nodeValue;
	  
       if (message < 10){
      color = "#aa0000";/*red*/
      } else if (message >= 10 && message < 50) {
		  color = "#f3fb53";/*yello*/
      } else {
        color = "#55b668";/*green*/
      } 
	  
	  width = message / 1;
      document.getElementById("c3").innerHTML=message;   
      document.getElementById("c3").style.width=(width+"%");
      document.getElementById("c3").style.backgroundColor=color;
      document.getElementById("c3").style.borderRadius="5px";	  
      
	  xmldoc = xmlResponse.getElementsByTagName("a4");  /*LED2*/
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("a4").style.backgroundColor="rgb(95,95,95)";
      /* update the text in the table*/
      if (message == 0){
        document.getElementById("a4").innerHTML="OFF";
        document.getElementById("btn1").innerHTML="Turn ON";
        document.getElementById("a4").style.color="#00AA00"; /* #00AA00 green*/
      } else {
        document.getElementById("a4").innerHTML="ON";
        document.getElementById("btn1").innerHTML="Turn OFF";
        document.getElementById("a4").style.color="red"; /* #e40004; red*/
      }
      
      xmldoc = xmlResponse.getElementsByTagName("b4");  /*value for # name 4*/
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("b4").innerHTML=message;
 
      xmldoc = xmlResponse.getElementsByTagName("c4"); /*value for charge %*/
      message = xmldoc[0].firstChild.nodeValue;
	   if (message < 10){
      color = "#aa0000";/*red*/
      } else if (message >= 10 && message < 50) {
		  color = "#f3fb53";/*yello*/
      } else {
        color = "#55b668";/*green*/
      } 
	  
	  width = message / 1;
      document.getElementById("c4").innerHTML=message;   
      document.getElementById("c4").style.width=(width+"%");
      document.getElementById("c4").style.backgroundColor=color;
      document.getElementById("c4").style.borderRadius="5px";
	  
	  xmldoc = xmlResponse.getElementsByTagName("a5");  /*LED3*/
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("a5").style.backgroundColor="rgb(95,95,95)";
      /* update the text in the table*/
      if (message == 0){
        document.getElementById("a5").innerHTML="OFF";
        document.getElementById("btn2").innerHTML="Turn ON";
        document.getElementById("a5").style.color="#00AA00"; 
      }
      else {
        document.getElementById("a5").innerHTML="ON";
        document.getElementById("btn2").innerHTML="Turn OFF";
        document.getElementById("a5").style.color="#e40004";
      }
	  
     }

    
    function process(){
     
     if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
        xmlHttp.open("PUT","xml",true);
        xmlHttp.onreadystatechange=response;
        xmlHttp.send(null);
      }       
        // you may have to play with this value, big pages need more porcessing time, and hence
        // a longer timeout
        setTimeout("process()",200);
    }
     /*Функція, яка буде виконуватися при кліку на кнопку*/
    function reloadPage() {
    /* Виклик функції перезавантаження сторінки*/
         location.reload();
    }
    
    // Отримання кнопки за допомогою її ідентифікатора
    var button = document.getElementById("reloadButton");
    /*Додавання обробника подій для кліку на кнопку*/
     button.addEventListener("click", reloadPage);
	  /* Отримання кнопки за допомогою її ідентифікатора
    var button = document.getElementById("reloadBtnESP");*/
    /* Додавання обробника подій для кліку на кнопку&/
    /* button.addEventListener("click", reloadPage);*/
  </script>

</html>


)=====";