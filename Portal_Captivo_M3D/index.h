const char MAIN_page[] PROGMEM = R"=====(
<html><head><meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
<style>body { text-align: center; font-family: "Trebuchet MS", Arial; margin-left:auto; margin-right:auto;}
.slider { width: 300px; }</style>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
</head><body><h1>M3D Bionic Hand Control</h1>
<p>Muneca: <span id="servoPos">133</span></p>
<input type="range" min="40" max="180" class="slider" id="servoSlider" onchange="servo(this.value)" value="144">
<p>Pulgar: <span id="servoPos2">99</span></p>
<input type="range" min="0" max="180" class="slider" id="servoSlider2" onchange="servo2(this.value)" value="122">
<script>var slider = document.getElementById("servoSlider");
var servoP = document.getElementById("servoPos"); servoP.innerHTML = slider.value;
slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }
$.ajaxSetup({timeout:1000}); function servo(pos) { 
$.get("/?value=" + pos + "&"); {Connection: close};}</script>
<script>var slider2 = document.getElementById("servoSlider2");
var servoP2 = document.getElementById("servoPos2"); servoP2.innerHTML = slider2.value;
slider2.oninput = function() { slider2.value = this.value; servoP2.innerHTML = this.value; }
$.ajaxSetup({timeout:1000}); function servo2(pos) { 
$.get("/?value2=" + pos + "&"); {Connection: close};}</script>
</body></html>



)=====";
