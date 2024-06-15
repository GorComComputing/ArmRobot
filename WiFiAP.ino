#include "WiFiAP.hpp"

// Wi-Fi scan
void scanWiFi(){
  Serial.println("Scan Wi-Fi:");
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i){
    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));
    delay(10);
  }
  WiFi.scanDelete();
  WiFi.disconnect();
}


// 404 Page not Found
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "404 The page not found");
}


// Page processor
String processor(const String& var){
  if(var == "POST_SERVO3"){
    return String(position_3);
  }
  return String();
}