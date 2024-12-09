//直進校正
// 設定馬達速度 (0-255)
int motor1Speed = 255; // 左馬達速度 (0為停止，255為最快)
int motor2Speed = 248; // 右馬達速度 (0為停止，255為最快)

//原地左轉
  analogWrite(motor1Pin1, 0);         // 左馬達停止正轉
  analogWrite(motor1Pin2, motor1Speed); // 左馬達反轉

  analogWrite(motor2Pin1, motor2Speed); // 右馬達正轉
  analogWrite(motor2Pin2, 0);         // 右馬達停止反轉

  delay(375); // 左轉約 0.375 秒 

//原地右轉
 analogWrite(motor1Pin1, motor1Speed); // 左馬達正轉
  analogWrite(motor1Pin2, 0);         // 左馬達停止反轉

  analogWrite(motor2Pin1, 0);         // 右馬達停止正轉
  analogWrite(motor2Pin2, motor2Speed); // 右馬達反轉

  delay(380); // 右轉約 0.38 秒

//向後校正
  analogWrite(motor1Pin1, 0);  // 停止馬達1的正向
  analogWrite(motor1Pin2, motor1Speed);  // 控制馬達1的反向速度

  analogWrite(motor2Pin1, 0);  // 停止馬達2的正向
  analogWrite(motor2Pin2, motor2Speed);  // 控制馬達2的反向速度
