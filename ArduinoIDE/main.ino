#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>
#include <LiquidCrystal.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>

// Thông tin kết nối WiFi
const char* ssid = "duc anh";
const char* password = "ducanh.12345";
const char* serverUrl = "http://192.168.1.100/IoT/submit_rfid.php"; // URL API PHP xử lý RFID

#define SS_PIN 21
#define RST_PIN 5
#define SERVO_PIN 13
#define BUZZER_PIN 17
#define GREEN_LED_PIN 4
#define RED_LED_PIN 2
#define LCD_RS 14
#define LCD_ENABLE 27
#define LCD_D4 26
#define LCD_D5 25
#define LCD_D6 33
#define LCD_D7 32

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servo;
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
AsyncWebServer server(80);

String scannedRFIDs[100];
int scannedCount = 0;
int signalweb = 1;  // Tín hiệu mặc định
String StrUID; // Khai báo biến StrUID
HTTPClient http; // Khai báo đối tượng HTTPClient

void setup() {
  Serial.begin(115200);
  
  // Khởi tạo các phần cứng
  SPI.begin();
  mfrc522.PCD_Init();
  servo.attach(SERVO_PIN);
  servo.write(0);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("Xe trong bai: " + String(scannedCount));

  // Kết nối WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Đang kết nối WiFi...");
  }
  Serial.println("Đã kết nối WiFi");
  Serial.print("Địa chỉ IP ESP: ");
  Serial.println(WiFi.localIP());

  // Định nghĩa route cho nhận tín hiệu
  server.on("/receive_signal", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Đã nhận yêu cầu");
    if (request->hasParam("signal")) {
      signalweb = request->getParam("signal")->value().toInt();
      Serial.print("Đã nhận tín hiệu: ");
      Serial.println(signalweb);
      request->send(200, "text/plain", "Tín hiệu là: " + String(signalweb));
    } else {
      request->send(400, "text/plain", "Không nhận được tín hiệu.");
    }
  });

  // Khởi động server
  server.begin();
  Serial.println("Server sẵn sàng.");
}

void loop() {
  if (signalweb == 1) {
    // Code từ file barrier.ino
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      String rfid = getRFID();
      if (rfid != "") {
        lcd.clear();
        lcd.print("ID: " + rfid);
        String status = handleRFIDEvent(rfid);
        lcd.setCursor(0, 1);

        if (status == "Vao") {
          if (!isScanned(rfid)) {
            addRFID(rfid);
            turnOnGreenLed();
            servo.write(90); // Mở barrier
            lcd.print("Xin chao!");
            buzzBuzzer(300);
            delay(2000);
            servo.write(0); // Đóng barrier
            turnOffLed();
          }
        } else if (status == "Ra") {
          if (isScanned(rfid)) {
            removeRFID(rfid);
            turnOnGreenLed();
            servo.write(90); // Mở barrier
            lcd.print("Tam biet!");
            buzzBuzzer(300);
            delay(2000);
            servo.write(0);
            turnOffLed();
          }
        } else {
          turnOnRedLed();
          lcd.print("Khong hop le!");
          buzzBuzzer(2000);
          turnOffLed();
        }

        delay(1000);
        clearLCD();
      }
      mfrc522.PICC_HaltA();
    }
  } else if (signalweb == 2) {
    // Code từ file test.ino
    int readsuccess = getid();
    if (readsuccess) {
      String UIDresultSend = StrUID;
      String postData = "UIDresult=" + UIDresultSend;

      http.begin("http://192.168.1.100/IoT/getUID.php"); // Sử dụng địa chỉ URL trực tiếp
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      int httpCode = http.POST(postData);
      String payload = http.getString();

      Serial.println(UIDresultSend);
      Serial.println(httpCode);
      Serial.println(payload);

      http.end();
      delay(1000);
    }
  }
}

// Các hàm hỗ trợ

String getRFID() {
  String rfid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    rfid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  return rfid;
}

bool isScanned(String rfid) {
  for (int i = 0; i < scannedCount; i++) {
    if (scannedRFIDs[i] == rfid) {
      return true;
    }
  }
  return false;
}

void addRFID(String rfid) {
  if (scannedCount < 100) {
    scannedRFIDs[scannedCount] = rfid;
    scannedCount++;
  }
}

void removeRFID(String rfid) {
  for (int i = 0; i < scannedCount; i++) {
    if (scannedRFIDs[i] == rfid) {
      scannedRFIDs[i] = scannedRFIDs[scannedCount - 1];
      scannedCount--;
      break;
    }
  }
}

void buzzBuzzer(unsigned int duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
}

void turnOnGreenLed() {
  digitalWrite(GREEN_LED_PIN, HIGH);
}

void turnOnRedLed() {
  digitalWrite(RED_LED_PIN, HIGH);
}

void turnOffLed() {
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}

String handleRFIDEvent(String rfid) {
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String httpRequestData = "rfid=" + rfid;
  int httpResponseCode = http.POST(httpRequestData);
  String status = "";

  if (httpResponseCode > 0) {
    status = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(status);
  } else {
    Serial.print("Lỗi khi gửi POST: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  return status;
}

void clearLCD() {
  lcd.clear();
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("Xe trong bai: " + String(scannedCount));
}

int getid() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return 0;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return 0;
  }

  Serial.print("Thẻ đã quét có ID: ");
  StrUID = getRFID();  // Sử dụng getRFID() thay vì array_to_string()
  Serial.println(StrUID);
  mfrc522.PICC_HaltA();
  return 1;
}
