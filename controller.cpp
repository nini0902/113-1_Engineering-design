#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Wi-Fi 設定
const char* ssid = "YourWiFiSSID";       // 替換為您的 Wi-Fi 名稱
const char* password = "YourWiFiPassword"; // 替換為您的 Wi-Fi 密碼

ESP8266WebServer server(80);

// 馬達控制腳位
#define LEFT_FORWARD D1
#define LEFT_BACKWARD D2
#define RIGHT_FORWARD D5
#define RIGHT_BACKWARD D6

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

  // HTTP 路由
  server.on("/", handleRoot);
  server.on("/forward", moveForward);
  server.on("/backward", moveBackward);
  server.on("/left", turnLeft);
  server.on("/right", turnRight);
  server.on("/stop", stopMotors);

  server.begin();
  Serial.println("HTTP server started");

  // 初始化 GPIO
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACKWARD, OUTPUT);

  // 停止所有馬達
  stopMotors();
}

void loop() {
  server.handleClient();
}

// 處理主頁介面
void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Car Control</title>
      <style>
        body {
          font-family: Arial;
          text-align: center;
          margin-top: 50px;
        }
        .button-container {
          display: flex;
          flex-direction: row;
          justify-content: center;
          align-items: center;
        }
        button {
          width: 100px;
          height: 50px;
          margin: 10px;
          font-size: 16px;
        }
      </style>
    </head>
    <body>
      <h1>NodeMCU Car Control</h1>
      <div class="button-container">
        <button onclick="sendCommand('forward')">Forward</button>
      </div>
      <div class="button-container">
        <button onclick="sendCommand('left')">Left</button>
        <button onclick="sendCommand('stop')">Stop</button>
        <button onclick="sendCommand('right')">Right</button>
      </div>
      <div class="button-container">
        <button onclick="sendCommand('backward')">Backward</button>
      </div>
      <script>
        function sendCommand(cmd) {
          fetch('/' + cmd) // 使用 Fetch 發送 AJAX 請求
            .then(response => {
              if (!response.ok) {
                throw new Error('Network response was not ok');
              }
              return response.text();
            })
            .then(data => console.log(data)) // 打印伺服器回應
            .catch(error => console.error('Error:', error));
        }
      </script>
    </body>
    </html>
  )rawliteral";
  server.send(200, "text/html", html);
}

// 停止所有馬達的通用函式
void stopAllMotors() {
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);
}

// 馬達控制功能
void moveForward() {
  stopAllMotors(); // 先停止所有動作
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW);
  server.send(200, "text/plain", "Moving Forward");
}

void moveBackward() {
  stopAllMotors(); // 先停止所有動作
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, HIGH);
  server.send(200, "text/plain", "Moving Backward");
}

void turnLeft() {
  stopAllMotors(); // 先停止所有動作
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW);
  server.send(200, "text/plain", "Turning Left");
}

void turnRight() {
  stopAllMotors(); // 先停止所有動作
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);
  server.send(200, "text/plain", "Turning Right");
}

void stopMotors() {
  stopAllMotors(); // 停止所有動作
  server.send(200, "text/plain", "Stopped");
}
