#include <WiFi.h>

const char* ssid = "Pastushok";
const char* password = "F1dget5pinn3r";
uint8_t nullIP = 0;
byte i = 0;
byte animationSpeed = 2;
byte R,G,B,W;
byte prevR, prevG, prevB, prevW;

WiFiServer wifiServer(80);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
wifiCon();
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(18, OUTPUT);
pinMode(21, OUTPUT);
//pinMode(5, INPUT_PULLDOWN);
ledcSetup(1,120,8);
ledcAttachPin(4,0); //pin 4 as ledc channel 0
ledcAttachPin(5,1); //pin 5 as ledc channel 1
ledcAttachPin(18,2); //pin 18 as ledc channel 2
ledcAttachPin(21,3); //pin 21 as ledc channel 3

wifiServer.begin();

}

void wifiCon() {
  Serial.println(WiFi.scanNetworks());
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.status());
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  //WiFi.disconnect(true);
  //Serial.println(WiFi.localIP());
}

void fadeOn(byte R, byte G, byte B, byte W) {
//fade on function currently sinusoidal
Serial.print("fadeOn() begin: ");
  if (i == 0) {
    for (i == 0; i <= 255; i++) {
      if (R != 0) {
//      Serial.print("R=");
//      Serial.print(i);
        ledcWrite(0,sinVal(i));
      }
      if (G != 0) {
//      Serial.print(" G=");
//      Serial.print(i);
        ledcWrite(1,sinVal(i));
      }
      if (B != 0) {
//      Serial.print(" B=");
//      Serial.print(i);
        ledcWrite(2,sinVal(i));
      }
      if (W != 0) {
//      Serial.print(" W=");
//      Serial.print(i);
        ledcWrite(3,sinVal(i));
      }
//      Serial.println("");
    delay(animationSpeed);
    if (i == 255) {
      prevR = R;
      prevG = G;
      prevB = B;
      prevW = W;
        return;
        }
     }
  }
}

void fadeOff(byte R, byte G, byte B, byte W) {
  //fade off function currently sinusoidal
  for (i == 255; i >= 0; i--) {
      if (R < prevR) {
        ledcWrite(0,sinVal(i));
      }
//      else if (R <= i) {
//        return;
//      }
      if (G < prevG) {
        ledcWrite(1,sinVal(i));
      }
//      else if (G <= i) {
//        return;
//      }
      if (B < prevB) {
        ledcWrite(2,sinVal(i));
      }
//      else if (B <= i) {
//        return;
//      }
      if (W < prevW) {
        ledcWrite(3,sinVal(i));
      }
//      else if (W <= i) {
//        return;
//      }
//      Serial.print("R=");
//      Serial.print(ledcRead(0));
//      Serial.print(" G=");
//      Serial.print(ledcRead(1));
//      Serial.print(" B=");
//      Serial.print(ledcRead(2));
//      Serial.print(" W=");
//      Serial.print(ledcRead(3));
//      Serial.println("");
    delay(animationSpeed);
//    Serial.println(i);
    if (i == 0) {
      return;
    }
  }
}

void RGB(byte R, byte G, byte B, byte W) {
  ledcWrite(0,R);
  ledcWrite(1,G);
  ledcWrite(2,B);
  ledcWrite(3,W);
//  Serial.print("RGB=");
//  Serial.print(R);
//  Serial.print(", ");
//  Serial.print(G);
//  Serial.print(", ");
//  Serial.println(B);
}

int sinVal(byte) {
  //calculate the sine wave transformation for the fade and or fade out functions.
  const double pi = 3.141596;
  short s = sin((( i / pi ) / 25.8369 ) - ( pi / 2 ) ) * 127.5 + 127.5;
  return s;
}

void processRecievedValue(char command) {
  if (command == '1') {
    fadeOn(255,255,255,255);
  }
  else if (command == '0') {
    fadeOff(0,0,0,0);
  }
  else if (command == '2') {//red
    fadeOff(0,0,0,0);
    fadeOn(255,0,0,0);
  }
  else if (command == '3') {//green
    fadeOff(0,0,0,0);
    fadeOn(0,255,0,0);
  }
  else if (command == '4') {//blue
    fadeOff(0,0,0,0);
    fadeOn(0,0,255,0);
  }
  else if (command == '5') {//white
    fadeOff(0,0,0,0);
    fadeOn(0,0,0,255);
  }
  else if (command == '6') {//yellow
    fadeOff(0,0,0,0);
    fadeOn(255,255,0,0);
  }
  else if (command == '7') {//purple
    fadeOff(0,0,0,0);
    fadeOn(255,0,255,0);
  }
  else if (command == '8') { // cyan
    fadeOff(0,0,0,0);
    fadeOn(0,255,255,0);
  }
  else if (command == '9') { //dim full rgb white
    fadeOff(0,0,0,0);
    fadeOn(127,127,127,127);
  }
  return;
}

//int calculateStep(int prevValue, int endValue) {
//  int step = endValue - prevValue; // What's the overall gap?
//  if (step) {                      // If its non-zero, 
//    step = 1020/step;              //   divide by 1020
//  } 
//  return step;
//}
//
//int calculateVal(int step, int val, int i) {
//
//  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
//    if (step > 0) {              //   increment the value if step is positive...
//      val += 1;           
//    } 
//    else if (step < 0) {         //   ...or decrement it if step is negative
//      val -= 1;
//    } 
//  }
//  // Defensive driving: make sure val stays in the range 0-255
//  if (val > 255) {
//    val = 255;
//  } 
//  else if (val < 0) {
//    val = 0;
//  }
//  return val;
//}

void loop() {
WiFiClient client = wifiServer.available();
if (client) {
  //handle the reception of the data
  
}
while (client.connected()) {
  while (client.available() > 0) {
    char c = client.read();
    processRecievedValue(c);
    Serial.write(c);
  }
  delay(10);
}
client.stop();
}
