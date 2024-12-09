// 設定控制腳位
const int motor1Pin1 = D1; // IN1
const int motor1Pin2 = D2; // IN2
const int motor2Pin1 = D5; // IN3
const int motor2Pin2 = D6; // IN4

void setup() {
  // 設定馬達控制腳位為輸出模式
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
}

void loop() {
  // 向前移動
  digitalWrite(motor1Pin1, HIGH); // 開啟馬達1的正向
  digitalWrite(motor1Pin2, LOW);  // 停止馬達1的反向

  digitalWrite(motor2Pin1, HIGH); // 開啟馬達2的正向
  digitalWrite(motor2Pin2, LOW);  // 停止馬達2的反向

  delay(2000); // 讓車輛行駛 2 秒

  // 停止
  digitalWrite(motor1Pin1, LOW);  // 停止馬達1
  digitalWrite(motor1Pin2, LOW);  // 停止馬達1

  digitalWrite(motor2Pin1, LOW);  // 停止馬達2
  digitalWrite(motor2Pin2, LOW);  // 停止馬達2

  delay(2000); // 停止 2 秒
}
