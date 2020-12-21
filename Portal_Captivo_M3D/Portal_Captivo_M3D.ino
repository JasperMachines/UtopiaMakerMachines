/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <WiFi.h>
#include <Servo.h>


//#include "index.h"

Servo myservo;  // create servo object to control a servo
Servo myservo2;// twelve servo objects can be created on most boards
Servo myservo3;  // create servo object to control a servo
Servo myservo4;// twelve servo objects can be created on most boards

// GPIO the servo is attached to
static const int servoPin = 14;
static const int servoPin2 = 27;
static const int servoPin3 = 12;
static const int servoPin4 = 13;

// Replace with your network credentials
const char* ssid     = "MARTHA";
const char* password = "futbol1234";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Decode HTTP GET value
String valueString = String(5);
String valueString2 = String(5);
String valueString3 = String(5);
String valueString4 = String(5);
int pos1 = 0;
int pos2 = 0;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
//
//void handleRoot() {
//// String s = MAIN_page; //Read HTML contents
// server.send(200, "text/html", s); //Send web page
//}
//void handleADC() {
// int a = analogRead(A0);
// String adcValue = String(a);
// 
// server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
//}

void setup() {
  Serial.begin(115200);

  myservo.attach(servoPin);  // attaches the servo on the servoPin to the servo object
 myservo2.attach(servoPin2); 
   myservo3.attach(servoPin3);  // attaches the servo on the servoPin to the servo object
 myservo4.attach(servoPin4); 
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
 
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=0.7\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences            
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");         
            client.println("input[type=\"range\"] {-webkit-appearance: slider-vertical; height:260px;width:100px}");
            client.println(".horizontal  *{display: inline-block; margin-top: 10px; margin-left: 1px;}"); 
            client.println(".vertical  > *{display :block; width: 100%;}");
            client.println(".butbank {background-color: #1B6B6F; border-radius: 8px; height:60px; width:120px padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 24px;}"); 
            client.println(".butopt {background-color: #4CAF50; border-radius: 8px; height:60px; width:200px padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 24px;}"); 
            client.println(".servonumber {background-color: #7EC867; border: none; height:50px; width:100px padding: 15px 32px; text-align: center; text-decoration: none; font-size: 24px;}</style>"); 

            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");    
            // Web Page
            client.println("</head><body><h1>M3D MYO HAND CONTROL</h1>");
               
         
client.println("<div><form><button class=\"butbank\" name=\"button1\" button=\"\" value=\"Bank 0\" type=\"submit\">Bank A</button>"); 
client.println("<button class=\"butbank\" name=\"button2\" button=\"\" value=\"OFF\" type=\"submit\">Bank B</button>"); 
client.println("<button class=\"butbank\" name=\"button3\" button=\"\" value=\"ON\" type=\"submit\">Bank C</button>"); 
client.println("<button class=\"butbank\" name=\"button4\" button=\"\" value=\"OFF\" type=\"submit\">Bank D</button></form></div>"); 

client.println("<div><form><button name=\"button5\" class=\"butbank\" value=\"ON\" type=\"submit\">Bank E</button>"); 
client.println("<button class=\"butbank\" name=\"button6\" button=\"\"  value=\"OFF\" type=\"submit\">Bank F</button>"); 
client.println("<button class=\"butbank\" name=\"button7\" button=\"\"  value=\"ON\" type=\"submit\">Bank G</button>"); 
client.println("<button class=\"butbank\" name=\"button8\" button=\"\" value=\"OFF\" type=\"submit\">Bank H</button></form> </div>"); 


            client.println("<div class=\"horizontal\"><form>");
            client.println("<div class=\"vertical\"><input type=\"number\" class=\"servonumber\" name=\"TXTPUL\" min=\"0\" max=\"180\" value=\"0\" <script="">");
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider\" oninput=\"this.form.TXTPUL.value=this.value\" onchange=\"servo(this.value)\" value=\""+valueString+"\"/></div>");
        
            client.println("<div class=\"vertical\"><input type=\"number\" class=\"servonumber\" name=\"TXTIND\" min=\"0\" max=\"180\" value=\"0\" <script="">");
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider2\" oninput=\"this.form.TXTIND.value=this.value\" onchange=\"servo2(this.value)\" value=\""+valueString2+"\"/></div>");
        
            client.println("<div class=\"vertical\"><input type=\"number\" class=\"servonumber\" name=\"TXTMED\" min=\"0\" max=\"180\" value=\"0\" <script="">");
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider3\" oninput=\"this.form.TXTMED.value=this.value\"onchange=\"servo3(this.value)\" value=\""+valueString3+"\"/></div>");
        
            client.println("<div class=\"vertical\"><input type=\"number\" class=\"servonumber\" name=\"TXTANU\" min=\"0\" max=\"180\" value=\"0\" <script="">");
             client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider4\" oninput=\"this.form.TXTANU.value=this.value\"onchange=\"servo4(this.value)\" value=\""+valueString4+"\"/></div>");
            client.println("</form></div>");

client.println("<div class=\"horizontal\"><button class=\"butopt\" name=\"buttonsave\" button=\"\" value=\"SAVE\" type=\" submit\" >Save Bank</button>"); 
client.println("<button class=\"butopt\" name=\"buttondelete\" button=\"\" style=\"background-color:#F01D08;\" value=\"DELETE\" type=\"submit\" >Delete Bank</button></div>"); 
             
            client.println("<script>var slider = document.getElementById(\"servoSlider\");");
            client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
            client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
            client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");
            
            client.println("<script>var slider2 = document.getElementById(\"servoSlider2\");");
            client.println("var servoP2 = document.getElementById(\"servoPos2\"); servoP2.innerHTML = slider2.value;");
            client.println("slider2.oninput = function() { slider2.value = this.value; servoP2.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo2(pos) { ");
            client.println("$.get(\"/?value2=\" + pos + \"&\"); {Connection: close};}</script>");

            client.println("<script>var slider3 = document.getElementById(\"servoSlider3\");");
            client.println("var servoP32 = document.getElementById(\"servoPos3\"); servoP3.innerHTML = slider3.value;");
            client.println("slider3.oninput = function() { slider3.value = this.value; servoP3.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo3(pos) { ");
            client.println("$.get(\"/?value3=\" + pos + \"&\"); {Connection: close};}</script>");

            client.println("<script>var slider4 = document.getElementById(\"servoSlider4\");");
            client.println("var servoP4 = document.getElementById(\"servoPos4\"); servoP4.innerHTML = slider4.value;");
            client.println("slider4.oninput = function() { slider4.value = this.value; servoP4.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo4(pos) { ");
            client.println("$.get(\"/?value4=\" + pos + \"&\"); {Connection: close};}</script>");
            
            client.println("</body></html>");     
            
            //GET /?value=180& HTTP/1.1
            if(header.indexOf("GET /?value=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1+1, pos2);
              
              //Rotate the servo
              myservo.write(valueString.toInt());
              //delay(100);
              Serial.println(valueString); 
            }         
             if(header.indexOf("GET /?value2=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString2 = header.substring(pos1+1, pos2);
              
              //Rotate the servo
              myservo2.write(valueString2.toInt());
              //delay(100);
              Serial.println(valueString2); 
            }         
            if(header.indexOf("GET /?value3=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString3 = header.substring(pos1+1, pos2);
              
              //Rotate the servo
              myservo3.write(valueString3.toInt());
              //delay(100);
              Serial.println(valueString3); 
            }    
            if(header.indexOf("GET /?value4=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString4 = header.substring(pos1+1, pos2);
              
              //Rotate the servo
              myservo4.write(valueString4.toInt());
              //delay(100);
              Serial.println(valueString4); 
            }              
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
