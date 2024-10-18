#include <Wire.h>
#include <LiquidCrystal_I2C.h>      // Khai báo thư viện LCD sử dụng I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 địa chỉ LCD, 16 cột và 2 hàng
#include <Keypad.h>// Khai báo thư viện Keypad
const int buzzerPin = 7;
int wrongAttemps = 0;
const byte ROWS = 4; // Bốn hàng
const byte COLS = 4; // Ba cột
int relay = 5;
char keys[ROWS][COLS] ={
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'}, 
    {'*', '0', '#', 'D'}
    };
byte rowPins[ROWS] = {10, 11, 12, 13};
byte colPins[COLS] = {9, 8, A0, A1};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

char STR[4] = {'3', '1', '0', '5'}; // Cài đặt mật khẩu tùy ý
char str[4] = {' ', ' ', ' ', ' '};
int i, j, count = 0;
 
void setup() {
  pinMode(buzzerPin, OUTPUT); // Khai báo chân buzzer là chân OUTPUT
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  lcd.init();        // Khai báo sử dụng LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.print(" Enter Password");
  Serial.begin(9600);
}
 void loop() {
  char key = keypad.getKey(); // Ký tự nhập vào sẽ gán cho biến Key
  if (key) // Nhập mật khẩu
  {
    if (i == 0) {
      str[0] = key;
      lcd.setCursor(6, 1);
      lcd.print(str[0]);
      delay(100); // Ký tự hiển thị trên màn hình LCD trong 0.1s
      lcd.setCursor(6, 1);
      lcd.print("*"); // Ký tự được che bởi dấu *
    }
    if (i == 1) {
      str[1] = key;
      lcd.setCursor(7, 1);
      lcd.print(str[1]);
      delay(100);
      lcd.setCursor(7, 1);
      lcd.print("*");
    }
    if (i == 2) {
      str[2] = key;
      lcd.setCursor(8, 1);
      lcd.print(str[2]);
      delay(100);
      lcd.setCursor(8, 1);
      lcd.print("*");
    }
    if (i == 3) {
      str[3] = key;
      lcd.setCursor(9, 1);
      lcd.print(str[3]);
      delay(100);
      lcd.setCursor(9, 1);
      lcd.print("*");
      count = 1;
    }
    i = i + 1;
  }
  if (count == 1) {
    if (str[0] == STR[0] && str[1] == STR[1] && str[2] == STR[2] &&
        str[3] == STR[3]) {
      lcd.clear();
      lcd.print("    Correct!");
      delay(3000);
  
      digitalWrite(relay, HIGH);
      lcd.clear();
      lcd.print("      Opened!");
      delay(5000);
      digitalWrite(relay, LOW);
      i = 0;
      count = 0;
      wrongAttemps = 0;
    } else {
      lcd.clear();
      lcd.print("   Incorrect!");
      delay(3000);
      wrongAttemps++;
      lcd.clear();
      lcd.print("   Try Again!");
      delay(3000);
      lcd.clear();
      lcd.print(" Enter Password");
      i = 0;
      count = 0;
    }
    if (wrongAttemps>=3){
        digitalWrite(buzzerPin, HIGH);
        delay(200);
        digitalWrite(buzzerPin, LOW);
        delay(100);
         digitalWrite(buzzerPin, HIGH);
        delay(200);
        digitalWrite(buzzerPin, LOW);
        delay(100);
        digitalWrite(buzzerPin, HIGH);
        delay(1000);
        digitalWrite(buzzerPin, LOW);
        delay(200);
      }
    }
  switch (key) {
  case '#':
    lcd.clear();
    digitalWrite(buzzerPin, HIGH);
    lcd.print("     Closed!");//Đóng cửa
    delay(10000);
    lcd.clear();
    lcd.print(" Enter Password");
    i = 0;
    break;
  }
}