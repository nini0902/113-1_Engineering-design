const int motor1Pin1 = D1; // IN1
const int motor1Pin2 = D2; // IN2
const int motor2Pin1 = D5; // IN3
const int motor2Pin2 = D6; // IN4

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
}

void loop() {
  digitalWrite(motor1Pin1, HIGH); // 開啟馬達1正轉
  digitalWrite(motor1Pin2, LOW);  // 停止馬達1反轉

  digitalWrite(motor2Pin1, HIGH); // 開啟馬達2正轉
  digitalWrite(motor2Pin2, LOW);  // 停止馬達2反轉

  delay(2000); // 向前移動2秒
}
