#include <Arduino.h>
#include <WiFiManager.h>
#include <WebServer.h>


WebServer server(80);

void handle_Get();
void handle_NotFound();



void setup()
{

  Serial.begin(921600);
  Serial.println("Starting setup");
  delay(10);

  WiFiManager wifiManager;


  // Tries to connect to last known WiFi details
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("WiFiManagerAP", "password")) {
    Serial.println("failed to connect and hit timeout");
  
    // TODO reset and try again, or maybe put it to deep sleep

    ESP.restart();

    delay(1000);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // defined paths
  server.on("/get_data", handle_Get);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

// return fake data
void handle_Get() {
  String stranka = "{\n";
  stranka += F("\"Hysteresis\":");
  stranka += "100";
  stranka += F(",\n");
  stranka += F("\"Target_Temperature\":");
  stranka += "100";
  stranka += F(",\n");
  stranka += F("\"Actual_Temperature\":");
  stranka += "100";
  stranka += F("}\n");
  server.send(200, "application/json", stranka);
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
