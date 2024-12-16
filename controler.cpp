#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Wi-Fi 設定
const char* ssid = "Nicouole";       // 替換為您的 Wi-Fi 名稱
const char* password = "12345678"; // 替換為您的 Wi-Fi 密碼

// HTTP 伺服器埠號
ESP8266WebServer server(80);

// 馬達控制腳位
#define LEFT_FORWARD D1
#define LEFT_BACKWARD D2
#define RIGHT_FORWARD D5
#define RIGHT_BACKWARD D6

// 初始化設定
void setup() {
  Serial.begin(115200);

  // 連接 Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // 設定 HTTP 路由
  server.on("/", handleRoot);
  server.on("/forward", moveForward);
  server.on("/backward", moveBackward);
  server.on("/left", turnLeft);
  server.on("/right", turnRight);
  server.on("/stop", stopMotors);

  // 啟動 HTTP 伺服器
  server.begin();
  Serial.println("HTTP server started");

  // 設定馬達控制腳位為輸出
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACKWARD, OUTPUT);

  // 停止所有馬達
  stopMotors();
}

// 主迴圈
void loop() {
  server.handleClient();
}

// 處理首頁請求
void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Car Control</title>
      <style>
        body { font-family: Arial; text-align: center; margin-top: 50px; }
        button { width: 100px; height: 50px; margin: 5px; font-size: 16px; }
      </style>
    </head>
    <body>
      <h1>NodeMCU Car Control</h1>
      <button onclick="location.href='/forward'">Forward</button><br>
      <button onclick="location.href='/left'">Left</button>
      <button onclick="location.href='/stop'">Stop</button>
      <button onclick="location.href='/right'">Right</button><br>
      <button onclick="location.href='/backward'">Backward</button>
    </body>
    </html>
  )rawliteral";
  server.send(200, "text/html", html);
}

// 前進
void moveForward() {
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW);
  server.send(200, "text/plain", "Moving Forward");
}

// 後退
void moveBackward() {
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, HIGH);
  server.send(200, "text/plain", "Moving Backward");
}

// 左轉
void turnLeft() {
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW);
  server.send(200, "text/plain", "Turning Left");
}

// 右轉
void turnRight() {
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);
  server.send(200, "text/plain", "Turning Right");
}

// 停止
void stopMotors() {
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);
  server.send(200, "text/plain", "Stopped");
}
