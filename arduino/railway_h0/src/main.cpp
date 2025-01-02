#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const int button0 = 16;
const int button1 = 5;
const int button2 = 4;
const int button3 = 0;
const int button4 = 12;
const int ledStrip = 14;
const int LED_COUNT = 16;
const long int intervalFire = 100;
const long int intervalSignalBlinkFire = 500;
const char* ssid = "SNASA";  // Enter SSID here
const char* password = "DumDidelDumm!!1!";  //Enter Password here
ESP8266WebServer server(80);

enum class Leds
{
  HOUSE = 0,
  SIGNAL_0_T,
  SIGNAL_0_B,
  SIGNAL_1_T,
  SIGNAL_1_B,
  SIGNAL_FRONT_L,
  SIGNAL_FRONT_R,
  TUNNEL_C_0,
  TUNNEL_C_1,
  TUNNEL_C_2,
  TUNNEL_C_3,
  TUNNEL_C_4,
  TUNNEL_C_5,
  TUNNEL_C_6,
  SIGNAL_REAR_L,
  SIGNAL_REAR_R
};

class Color
{
  public:
    Color(const uint8_t r, const uint8_t g, const uint8_t b): _r(r), _g(g), _b(b){}
    Color(): _r(0), _g(0), _b(0){}
    const Color& operator=(const Color& var)
    {
      _r = var.r();
      _g = var.g();
      _b = var.b();
      return *this;
    }
    virtual ~Color(){}
    uint8_t r(void)const{return _r;}
    uint8_t g(void)const{return _g;}
    uint8_t b(void)const{return _b;}
  private:  
    uint8_t _r;
    uint8_t _g;
    uint8_t _b;
};

class Flanks
{
  public:
  Flanks(){}
  virtual ~Flanks(){}
  void setSignals(const bool button0Current, const bool button1Current, const bool button2Current, const bool button3Current, const bool button4Current)
  {
    if(!button0Current && _button0Last)
      _button0Rising = true;
    else
      _button0Rising = false;
    if(!button1Current && _button1Last)
      _button1Rising = true;
    else
      _button1Rising = false;
    if(!button2Current && _button2Last)
      _button2Rising = true;
    else
      _button2Rising = false;
    if(!button3Current && _button3Last)
      _button3Rising = true;
    else
      _button3Rising = false;
    if(!button4Current && _button4Last)
      _button4Rising = true;
    else
      _button4Rising = false;          

    _button0Last = button0Current;  
    _button1Last = button1Current;  
    _button2Last = button2Current;  
    _button3Last = button3Current;  
    _button4Last = button4Current;  
  }
  const bool button0Rising(void)const{return _button0Rising;}
  const bool button1Rising(void)const{return _button1Rising;}
  const bool button2Rising(void)const{return _button2Rising;}
  const bool button3Rising(void)const{return _button3Rising;}
  const bool button4Rising(void)const{return _button4Rising;}
  private:
    bool _button0Last = false;
    bool _button1Last = false;
    bool _button2Last = false;
    bool _button3Last = false;
    bool _button4Last = false;
    bool _button0Rising = false;
    bool _button1Rising = false;
    bool _button2Rising = false;
    bool _button3Rising = false;
    bool _button4Rising = false;
};

void handle_OnConnect();
String SendHTML(void);
void handle_NotFound();
void handleColor();

Adafruit_NeoPixel strip(LED_COUNT, ledStrip, NEO_RGB + NEO_KHZ800);
Flanks flanks;
//Tunnel
bool stateSignalFront = false;
bool stateSignalRear = false;
bool stateFire = false;

bool stateSignal0 = false;
bool stateSignal1= false;

const Color signalRed(60, 0, 0);
const Color signalYellow(60, 40, 0);
const Color signalGreen(0, 60, 0);
const Color white(80, 80, 80);

void setup() 
{
  Serial.begin(9600);
  pinMode(button0, INPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(ledStrip, OUTPUT);
  strip.setPixelColor(static_cast<int>(Leds::HOUSE), 255, 255, 255);
  strip.show();
  delay(100);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
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
  server.on("/color", handleColor);
  server.begin();
  
  Serial.println("HTTP server started");
}

void loop() 
{
  server.handleClient();
  static long int timerFire = 0;
  static long int timerSignalBlink = 0;
  static bool blink = false;
  flanks.setSignals(digitalRead(button0), digitalRead(button1), digitalRead(button2), digitalRead(button3), digitalRead(button4));
  if(flanks.button0Rising())
    stateSignal0 = !stateSignal0;
  if(flanks.button1Rising())
    stateSignal1 = !stateSignal1;
  if(flanks.button4Rising())
    stateSignalFront = !stateSignalFront;
  if(flanks.button3Rising())
    stateSignalRear = !stateSignalRear;
  if(flanks.button2Rising())
  {
    stateFire = !stateFire;
    if(stateFire)   //fire has just been switched on
    {
      timerFire = millis();
      timerSignalBlink = millis();
    }
  }
  if(flanks.button1Rising())
    Serial.println("Button1");      
  if(flanks.button0Rising())
    Serial.println("Button0");  
  if(stateSignal0)
  {
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_0_T), signalYellow.r(), signalYellow.g(), signalYellow.b());
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_0_B), signalYellow.r(), signalYellow.g(), signalYellow.b()); 
  }
  else
  {
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_0_T), signalGreen.r(), signalGreen.g(), signalGreen.b());
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_0_B), signalGreen.r(), signalGreen.g(), signalGreen.b());
  }

  if(stateSignal1)
  {
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_1_T), signalYellow.r(), signalYellow.g(), signalYellow.b());
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_1_B), signalYellow.r(), signalYellow.g(), signalYellow.b()); 
  }
  else
  {
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_1_T), signalGreen.r(), signalGreen.g(), signalGreen.b());
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_1_B), signalGreen.r(), signalGreen.g(), signalGreen.b());
  }

  //tunnel
  if(stateSignalFront)
  {
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_FRONT_L), signalYellow.r(), signalYellow.g(), signalYellow.b());
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_FRONT_R), signalYellow.r(), signalYellow.g(), signalYellow.b()); 
  }
  else
  {
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_FRONT_L), signalGreen.r(), signalGreen.g(), signalGreen.b());
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_FRONT_R), signalGreen.r(), signalGreen.g(), signalGreen.b());
  }
  if(stateSignalRear)
  {
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_REAR_L), signalYellow.r(), signalYellow.g(), signalYellow.b());
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_REAR_R), signalYellow.r(), signalYellow.g(), signalYellow.b()); 
  }
  else
  {
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_REAR_L), signalGreen.r(), signalGreen.g(), signalGreen.b());
     strip.setPixelColor(static_cast<int>(Leds::SIGNAL_REAR_R), signalGreen.r(), signalGreen.g(), signalGreen.b());
  }
  
  if(stateFire)
  {
    if(millis() - timerFire >= intervalFire)
    {
      timerFire = millis();
      for(int i = static_cast<int>(Leds::TUNNEL_C_0); i < static_cast<int>(Leds::TUNNEL_C_6); i++)
      {
       const uint8_t randomR = static_cast<uint8_t>(random(256));
       //const uint8_t randomY = static_cast<uint8_t>(random(256));
       strip.setPixelColor(i, 10, randomR, 0);
      }
    }
    if(millis() - timerSignalBlink >= intervalSignalBlinkFire)
    {
      blink = !blink;
      timerSignalBlink = millis();
    }
      if(blink)
      {
        strip.setPixelColor(static_cast<int>(Leds::SIGNAL_FRONT_L), signalRed.r(), signalRed.g(), signalRed.b());
        strip.setPixelColor(static_cast<int>(Leds::SIGNAL_FRONT_R), signalRed.r(), signalRed.g(), signalRed.b());
        strip.setPixelColor(static_cast<int>(Leds::SIGNAL_REAR_L), signalRed.r(), signalRed.g(), signalRed.b());
        strip.setPixelColor(static_cast<int>(Leds::SIGNAL_REAR_R), signalRed.r(), signalRed.g(), signalRed.b());
      }
      else
      {
        strip.setPixelColor(static_cast<int>(Leds::SIGNAL_FRONT_L), 0, 0, 0);
        strip.setPixelColor(static_cast<int>(Leds::SIGNAL_FRONT_R), 0, 0, 0);
        strip.setPixelColor(static_cast<int>(Leds::SIGNAL_REAR_L), 0, 0, 0);
        strip.setPixelColor(static_cast<int>(Leds::SIGNAL_REAR_R), 0, 0, 0);
      }
  }
  else
  {
    for(int i = static_cast<int>(Leds::TUNNEL_C_0); i < static_cast<int>(Leds::TUNNEL_C_6); i++)
      strip.setPixelColor(i, white.r(), white.g(), white.b());
  }


  /*if(digitalRead(button0))
  {
    strip.setPixelColor(static_cast<int>(Leds::SIGNAL_FRONT_L), 255, 0, 0);
    strip.setPixelColor(static_cast<int>(Leds::SIGNAL_FRONT_R), 255, 0, 0);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_0), 200, 200, 200);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_1), 200, 200, 200);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_2), 200, 200, 200);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_3), 200, 200, 200);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_4), 200, 200, 200);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_5), 200, 200, 200);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_6), 200, 200, 200);
    strip.setPixelColor(static_cast<int>(Leds::SIGNAL_REAR_L), 255, 0, 0);
    strip.setPixelColor(static_cast<int>(Leds::SIGNAL_REAR_R), 255, 0, 0);
  }
  else
  {
    Serial.println("Button0");
    strip.setPixelColor(static_cast<int>(Leds::SIGNAL_FRONT_L), 0, 255, 0);
    strip.setPixelColor(static_cast<int>(Leds::SIGNAL_FRONT_R), 0, 255, 0);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_0), 0, 0, 255);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_1), 0, 0, 255);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_2), 0, 0, 255);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_3), 0, 0, 255);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_4), 0, 0, 255);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_5), 0, 0, 255);
    strip.setPixelColor(static_cast<int>(Leds::TUNNEL_C_6), 0, 0, 255);
    strip.setPixelColor(static_cast<int>(Leds::SIGNAL_REAR_L), 0, 255, 0);
    strip.setPixelColor(static_cast<int>(Leds::SIGNAL_REAR_R), 0, 255, 0);
  }
  if(!digitalRead(button1))
    Serial.println("Button1");
  if(!digitalRead(button2))
    Serial.println("Button2");
  if(!digitalRead(button3))
    Serial.println("Button3");
  if(!digitalRead(button4))
    Serial.println("Button4");*/

  strip.show();
 delay(10);
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
  ptr +="<h1>Antons Eisenbahn</h1>\n";
  ptr +="<h3>Kontrolle</h3>\n";
  
  ptr += "<form action=\"/color\" accept-charset=\"utf-8\">";
  ptr +="<label for=\"favcolor\">Select your favorite color:</label>";
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
    strip.setPixelColor(static_cast<int>(Leds::HOUSE), r, g, b);
    strip.show(); 
    server.send(200, "text/html", SendHTML()); 
}
