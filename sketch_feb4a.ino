#include <WiFi.h>
#include <ESP32Servo.h>

const char *ssid = "OnePlus Nord 3 5G"; // Replace with your WiFi SSID
const char *password = "12345678"; // Replace with your WiFi password

Servo servo1;
int servoPin = 18; // Pin where the servo is connected

WiFiServer server(80); // Create a server that listens on port 80

void setup() {
  Serial.begin(115200);
  servo1.attach(servoPin); // Attach the servo to the pin

  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin(); // Start the server
}

void loop() {
  WiFiClient client = server.available(); // Check for incoming clients

  if (client) { // If a client connects
    Serial.println("New Client.");
    String currentLine = ""; // String to hold incoming data

    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); // Read a byte from the client
        Serial.write(c); // Print it out in the serial monitor

        if (c == '\n') { // If the byte is a newline character
          if (currentLine.length() == 0) {
            // Send HTTP response headers
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // HTML content
            client.print("Click <a href=\"/rotate\">here</a> to rotate the servo.<br>");
            client.println();
            break;
          } else {
            currentLine = ""; // Clear currentLine
          }
        } else if (c != '\r') {
          currentLine += c; // Add to currentLine
        }

        // Check if the request was "GET /rotate"
        if (currentLine.endsWith("GET /rotate")) {
          rotateServo(); // Call function to rotate servo
        }
      }
    }
    client.stop(); // Close the connection
    Serial.println("Client Disconnected.");
  }
}

void rotateServo() {
  servo1.write(90); // Rotate to position
  delay(1000); // Wait for one second
  servo1.write(0); // Rotate back to initial position
  delay(1000);
}

