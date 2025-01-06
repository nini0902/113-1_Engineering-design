#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Wi-Fi 設定
const char* ssid = "Nicouole";       // 替換為您的 Wi-Fi 名稱
const char* password = "12345678"; // 替換為您的 Wi-Fi 密碼

ESP8266WebServer server(80);

// 馬達控制腳位
#define LEFT_FORWARD D1
#define LEFT_BACKWARD D2
#define RIGHT_FORWARD D5
#define RIGHT_BACKWARD D6

int speedValue = 1023; // 默認速度，範圍 0-1023

void setup() {
  Serial.begin(115200);

  // 連接 Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // 顯示 IP 位址
  Serial.print("HTTP server started at: http://");
  Serial.println(WiFi.localIP());

  // HTTP 路由設定
  server.on("/", handleRoot);
  server.on("/forward", moveForward);
  server.on("/backward", moveBackward);
  server.on("/left", turnLeft);
  server.on("/right", turnRight);
  server.on("/stop", stopMotors);
  server.on("/setSpeed", setSpeed);

  // 啟動 HTTP 伺服器
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

void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Car Control with Speed Adjustment</title>
      <style>
        body {
          font-family: 'Courier New', Courier, monospace;
          background-color: #1a1a2e;
          color: #eaeaea;
          margin: 0;
          padding: 0;
          display: flex;
          flex-direction: column;
          align-items: center;
          justify-content: center;
          height: 100vh;
        }
        h1 {
          color: #00d4ff;
          font-size: 2.5rem;
          margin-bottom: 20px;
        }
        .button-container {
          display: flex;
          flex-direction: row;
          justify-content: center;
          align-items: center;
          margin: 10px 0;
        }
        button {
          width: 120px;
          height: 60px;
          margin: 10px;
          font-size: 18px;
          font-weight: bold;
          color: #fff;
          background-color: #27293d;
          border: 2px solid #00d4ff;
          border-radius: 8px;
          cursor: pointer;
          transition: all 0.3s ease;
        }
        button:hover {
          background-color: #00d4ff;
          color: #27293d;
        }
        button:active {
          transform: scale(0.95);
        }
        .grid-container {
          display: grid;
          grid-template-columns: repeat(3, 1fr);
          gap: 10px;
        }
        .grid-item {
          display: flex;
          justify-content: center;
          align-items: center;
        }
        .slider-container {
          margin: 20px;
          text-align: center;
        }
        input[type="range"] {
          width: 300px;
        }
        footer {
          margin-top: 20px;
          font-size: 0.9rem;
          color: #777;
        }
      </style>
    </head>
    <body>
      <h1>NodeMCU Car Control</h1>
      <div class="grid-container">
        <div class="grid-item"></div>
        <div class="grid-item">
          <button onclick="sendCommand('forward')">&uarr; Forward</button>
        </div>
        <div class="grid-item"></div>
        <div class="grid-item">
          <button onclick="sendCommand('left')">&larr; Left</button>
        </div>
        <div class="grid-item">
          <button onclick="sendCommand('stop')">&#9632; Stop</button>
        </div>
        <div class="grid-item">
          <button onclick="sendCommand('right')">&rarr; Right</button>
        </div>
        <div class="grid-item"></div>
        <div class="grid-item">
          <button onclick="sendCommand('backward')">&darr; Backward</button>
        </div>
        <div class="grid-item"></div>
      </div>
      <div class="slider-container">
        <label for="speed">Speed:</label>
        <input type="range" id="speed" min="0" max="1023" value="1023" oninput="updateSpeed(this.value)">
        <p>Speed Value: <span id="speedValue">1023</span></p>
      </div>
      <footer>
        Control your car like a pro! Powered by NodeMCU and Web Interface.
      </footer>
      <script>
        function sendCommand(cmd) {
          fetch('/' + cmd)
            .then(response => {
              if (!response.ok) {
                throw new Error('Network response was not ok');
              }
              return response.text();
            })
            .then(data => console.log(data))
            .catch(error => console.error('Error:', error));
        }

        function updateSpeed(value) {
          document.getElementById('speedValue').innerText = value;
          fetch('/setSpeed?value=' + value)
            .then(response => {
              if (!response.ok) {
                throw new Error('Network response was not ok');
              }
              return response.text();
            })
            .then(data => console.log('Speed updated:', data))
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
  analogWrite(LEFT_FORWARD, 0);
  analogWrite(LEFT_BACKWARD, 0);
  analogWrite(RIGHT_FORWARD, 0);
  analogWrite(RIGHT_BACKWARD, 0);
}

// 馬達控制功能
void moveForward() {
  stopMotors();
  analogWrite(LEFT_FORWARD, speedValue);
  analogWrite(RIGHT_FORWARD, speedValue);
  server.send(200, "text/plain", "Moving Forward");
}

void moveBackward() {
  stopMotors();
  analogWrite(LEFT_BACKWARD, speedValue);
  analogWrite(RIGHT_BACKWARD, speedValue);
  server.send(200, "text/plain", "Moving Backward");
}

void turnLeft() {
  stopMotors();
  analogWrite(RIGHT_FORWARD, speedValue);
  server.send(200, "text/plain", "Turning Left");
}

void turnRight() {
  stopMotors();
  analogWrite(LEFT_FORWARD, speedValue);
  server.send(200, "text/plain", "Turning Right");
}

void stopMotors() {
  stopAllMotors();
  delay(10);
  server.send(200, "text/plain", "Stopped");
}

// 設定速度
void setSpeed() {
  if (server.hasArg("value")) {
    speedValue = server.arg("value").toInt();
    if (speedValue < 0) speedValue = 0;
    if (speedValue > 1023) speedValue = 1023;
    server.send(200, "text/plain", "Speed set to " + String(speedValue));
  } else {
    server.send(400, "text/plain", "Missing speed value");
  }
}
