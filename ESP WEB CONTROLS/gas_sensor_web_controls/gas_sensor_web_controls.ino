#include <ESP8266WiFi.h>
const int sensorIn = A0;      // pin where the OUT pin from sensor is connected on Arduino
int Voltage;
// Replace with your network credentials
const char* ssid     = "";
const char* password = "";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
   
  Serial.println ("ACS712 current sensor"); 
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  // Set outputs to LOW
  pinMode(16,INPUT);
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  pinMode(A0,INPUT);
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
 
  Voltage = gasval();
  
  
  

delay (100);  
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
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
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("BedRoom on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("BedRoom off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("Hall on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("Hall off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
           client.println("<link rel='stylesheet' href='https://tradelink2022.000webhostapp.com/sas.css'");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
           // client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            //client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            //client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            //client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Gas leak detection</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
           // client.println("<p>Bedroom - State " + output5State+Watt + "</p>");
            // client.println("<p> watts ::" + Watt + "</p>");
              client.println("<p>Bedroom - State " + output5State + "</p>");
                   client.println(" <p id='dod'></p>");                


            // If the output5State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>Hall - State " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<marquee color='green'><u><h2>Sensor data<h2></u> </marquee>");
            client.println("<table><tr><th>GAS value");
            client.println("</th><th>");     
            client.println(Voltage);  
            client.println("</th></tr>");   

            client.println("<tr><th>value");
            client.println("</th><th>");     
            client.println(Voltage);  
            client.println("</th></tr></table>");              
            
          client.println("<form  id='frm' action='https://formsubmit.co/aravindmohan598@gmail.com' method='POST'>");
        client.println("<input type='text'id='nm' name='name' required>");
        client.println("<input type='text'id='bill' name='Gas leak:' required>");
        
        client.println("<input type='submit' value='send' id='fwd'>");
       client.println("</form>");
            client.println("<script>var a=0;window.onload = function(){setInterval(abc,1000);}");
            client.println("function abc(){document.getElementById('nm').value='bob'");
            client.println("document.getElementById('bill').value=");
            client.println(Voltage);
            client.println("");
            client.println("if(document.getElementById('bill').value > 400){");
            client.println("document.getElemntById('frm').submit;");
            //client.println("break;");
            client.println("}");
           // client.println("setTimeout('5000',location.reload());");
            client.println("}");
           
            client.println("</script>");
            client.println("</body></html>");
            
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




//elc


// initialize the LCD library with I2C address and LCD size


 

 
// ***** function calls ******
int gasval()
{
  
  int p = analogRead(A0);

 return p;




 }