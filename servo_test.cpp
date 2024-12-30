#include <Servo.h>

// 定義舵機控制腳位
#define SERVO_PIN D8

Servo myServo;  // 創建 Servo 物件來控制舵機
String inputString = "";  // 用於儲存輸入的字串

void setup() {
  Serial.begin(115200);  // 初始化串口通訊
  myServo.attach(SERVO_PIN, 0, 10000);  // 將舵機物件綁定到 D8 腳位

  Serial.println("Servo Test");
  Serial.println("Please enter an angle (0 to 180):");
}

void loop() {
  // 檢查是否有新的串口資料
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();  // 讀取每個字元
    if (inChar == '\n' || inChar == '\r') {
      // 碰到換行符號時，處理輸入
      if (inputString.length() > 0) {
        int angle = inputString.toInt();  // 將輸入字串轉為整數
        if (angle >= 0 && angle <= 180) {
          myServo.write(angle);  // 讓舵機轉到指定角度
          Serial.print("Moving to angle: ");
          Serial.println(angle);
        } else {
          Serial.println("Invalid angle! Please enter a value between 0 and 180.");
        }
      }
      inputString = "";  // 清空輸入字串
    } else {
      inputString += inChar;  // 累積輸入字串
    }
  }
}
