#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <secret_example.h>

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected to Wi-Fi");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.print("Authenticating");

  while (auth.token.uid == "") {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nAuthenticated with Firebase UID: " + String(auth.token.uid.c_str()));


  if (Firebase.RTDB.setString(&fbdo, "/test/message", "Hello from ESP32!")) {
    Serial.println("Data written successfully:");
    Serial.println(fbdo.to<const char*>());
  } else {
    Serial.println("Failed to write:");
    Serial.println(fbdo.errorReason().c_str());
  }


  if (Firebase.RTDB.getString(&fbdo, "/test/message")) {
    Serial.println("Data read successfully:");
    Serial.println(fbdo.to<const char*>());
  } else {
    Serial.println("Failed to read:");
    Serial.println(fbdo.errorReason().c_str());
  }
}

void loop() {
  // Nothing here for now
}
