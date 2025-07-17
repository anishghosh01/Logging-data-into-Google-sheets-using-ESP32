#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "PEEC Lab 2.4G";
const char* password = "PEECLab@RW";

// Google Apps Script Web App URL
String GOOGLE_SCRIPT_URL = "https://script.google.com/macros/s/AKfycbwbp5Qy9HS6y5adG3lXtSnCffISTUt1JOAzDIJ_QjlPMNuelykCmnR0z8Ag41dKDeT6/exec";

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0)); // Seed random number generator

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  // Generate 3 random voltages between 210.00 and 250.99
  float voltage1 = random(210, 251) + random(0, 100) / 100.0;
  float voltage2 = random(210, 251) + random(0, 100) / 100.0;
  float voltage3 = random(210, 251) + random(0, 100) / 100.0;

  Serial.print("Voltage 1: "); Serial.println(voltage1);
  Serial.print("Voltage 2: "); Serial.println(voltage2);
  Serial.print("Voltage 3: "); Serial.println(voltage3);

  // Construct URL with three voltage values
  String url = GOOGLE_SCRIPT_URL + "?voltage1=" + String(voltage1, 2) +
                                     "&voltage2=" + String(voltage2, 2) +
                                     "&voltage3=" + String(voltage3, 2);

  HTTPClient http;
  http.begin(url.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  int httpCode = http.GET();

  if (httpCode > 0) {
    String response = http.getString();
    Serial.println("Response: " + response);
  } else {
    Serial.print("HTTP error code: ");
    Serial.println(httpCode);
  }

  http.end();
  delay(5000); // Send data every 5 seconds
}
