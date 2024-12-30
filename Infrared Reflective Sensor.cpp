#define IR_SENSOR_PIN D3  // 定義紅外線模組的信號接腳

void setup() {
  pinMode(IR_SENSOR_PIN, INPUT);  // 將 D3 設為輸入模式
  Serial.begin(115200);          // 初始化串口通訊
  Serial.println("Infrared Tracking Module Test");
}

void loop() {
  int sensorValue = digitalRead(IR_SENSOR_PIN);  // 讀取紅外線模組的數值
  if (sensorValue == HIGH) {
    Serial.println("Line detected!");  // 偵測到線
  } else {
    Serial.println("No line detected!");  // 未偵測到線
  }
  delay(100);  // 增加延遲，避免輸出過快
}
