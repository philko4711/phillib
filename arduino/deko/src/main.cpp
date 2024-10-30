#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED_PIN  5
#define LED_COUNT 2

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
const char* ssid = "SNASA";  // Enter SSID here
const char* password = "DumDidelDumm!!1!";  //Enter Password here

ESP8266WebServer server(80);
void handle_OnConnect();
String SendHTML(void);
void handle_NotFound();
void handleColor();

void setup() 
{
  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  delay(100);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());
  
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  // server.on("/ledon", handle_ledOn);
  // server.on("/ledoff", handle_ledOff);
  server.on("/color", handleColor);
  server.begin();
  strip.setPixelColor(0, 255, 0, 0);
  strip.setPixelColor(1, 255, 0, 0);
  strip.show();
  
  Serial.println("HTTP server started");
}

void loop() 
{
  server.handleClient();
  delayMicroseconds(200);
}

void handle_OnConnect()
{
  Serial.println("On Connect");
  server.send(200, "text/html", SendHTML());
}

String SendHTML(void)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Dekoration</h1>\n";
  ptr +="<h3>Skelett</h3>\n";
  ptr += "<form action=\"/color\" accept-charset=\"utf-8\">";
  //ptr +="<label for=\"favcolor\">Select your favorite color:</label>";
  ptr +="<input type=\"color\" id=\"favcolor\" name=\"favcolor\" value=\"#ff0000\">";
  ptr +="<input type=\"submit\" value = \"setColor\"/>";
  ptr +="</form>";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

 void handle_NotFound()
 {
   server.send(404, "text/plain", "Not found");
 }

 void handleColor()
{
    Serial.println("Got Color");
    Serial.println(server.arg("favcolor"));
    const String colorStr = server.arg("favcolor"); 
    String sub = colorStr.substring(1, 3);
    Serial.println(sub);
    const uint8_t r = static_cast<uint8_t>(strtol(sub.c_str(), NULL, 16));
    sub = colorStr.substring(3, 5);
    Serial.println(sub);
    const uint8_t g = static_cast<uint8_t>(strtol(sub.c_str(), NULL, 16));
    sub = colorStr.substring(5, 7);
    Serial.println(sub);
    const uint8_t b = static_cast<uint8_t>(strtol(sub.c_str(), NULL, 16));
    Serial.print(r);
    Serial.print(" ");
    Serial.print(g);
    Serial.print(" ");
    Serial.print(b);
    Serial.print("\n");
    strip.setPixelColor(0, r, g, b);
    strip.setPixelColor(1, r, g, b);
    strip.show(); 
    server.send(200, "text/html", SendHTML()); 
}