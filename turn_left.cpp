const int motor1Pin1 = D1; // IN1
const int motor1Pin2 = D2; // IN2
const int motor2Pin1 = D5; // IN3
const int motor2Pin2 = D6; // IN4
int motor1Speed = 255; 
int motor2Speed = 248;

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
}

void loop() {
  analogWrite(motor1Pin1, 0);          // 停止左馬達正轉
  analogWrite(motor1Pin2, motor1Speed); // 左馬達反轉

  analogWrite(motor2Pin1, motor2Speed); // 右馬達正轉
  analogWrite(motor2Pin2, 0);          // 停止右馬達反轉

  delay(375); // 左轉約 0.375 秒
}
