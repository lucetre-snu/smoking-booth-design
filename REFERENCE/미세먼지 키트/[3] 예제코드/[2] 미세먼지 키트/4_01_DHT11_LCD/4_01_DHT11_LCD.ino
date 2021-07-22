/*
 *  이 소스는 에듀이노(Eduino)에 의해서 번역, 수정, 작성되었고 소유권 또한 에듀이노의 것입니다. 
 *  소유권자의 허락을 받지 않고 무단으로 수정, 삭제하여 배포할 시 법적인 처벌을 받을 수 있습니다. 
 *  
 *  에듀이노 미세먼지 키트 기본예제 
 *  - 미세먼지 키트 활용예제 -
 *  미세먼지 측정 센서,온습도센서의 값을 LCD 1602(I2C)와 RGB LED 모듈로 출력하는 예제 코드입니다.
 *    
 */

#include <Wire.h>                        // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>        // LCD 1602 I2C용 라이브러리
#include <DHT.h>                      // 온습도 센서 사용을 위한 라이브러리
#define DHTPIN A1 // 온습도 센서 핀 지정
#define DHTTYPE DHT11 // DHT 타입 지정
DHT dht(DHTPIN, DHTTYPE); // DHT11의 타입, 핀을 dht로 지정

LiquidCrystal_I2C lcd(0x27,16,2);     // 접근주소: 0x3F or 0x27 1602 Display

 byte humi[8] = {     // 물컵모양 출력
  0b00000,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
};
 byte temp[8] = {     // 온도계 모양 출력
  0b00100,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b10001,
  0b11111,
  0b01110,
};
 byte char_temp[8] = {     // 온도 단위 출력
  0b10000,
  0b00110,
  0b01001,
  0b01000,
  0b01000,
  0b01000,
  0b01001,
  0b00110,
};

void setup(){
  lcd.init();                     // LCD 초기화
  lcd.backlight();                // 백라이트 켜기
  lcd.createChar(1, temp);          // 온도계모양 출력
  lcd.createChar(2, humi);          // 물컵 모양 출력
  lcd.createChar(3, char_temp);     // 온도 단위 출력

  Serial.begin(9600);            // 시리얼 모니터 시작, 속도는 9600  
}


void loop(){
  int humi = dht.readHumidity();
  int temp = dht.readTemperature();
  
    Serial.print("humidity:");          // ‘시리얼 플로터’ 사용위해 이부분 주석 필요
    Serial.print(humi);                  // 습도값 출력
    Serial.print("\t temperature:");       // ‘시리얼 플로터’ 사용위해 이부분 주석 필요
    Serial.println(temp);                  // 온도값 출력 
   
 
  Serial.println();
  
  lcd.setCursor(0,0);             // 1번째, 1라인  
  lcd.write(byte(1));             // 온도계 출력
  lcd.setCursor(2,0);             // 3번째, 1라인al
  lcd.print((int)temp);           // 온도 출력
  lcd.setCursor(5,0);              // 6번째 1라인
  lcd.write(byte(3));             // 온도 단위 출력
  
  lcd.setCursor(8,0);             // 9번째, 1라인
  lcd.write(byte(2));             // 물컵 출력
  lcd.setCursor(10,0);            // 11번째, 1라인
  lcd.print(humi);                // 습도 출력
  lcd.setCursor(13,0);            // 15번째, 1라인
  lcd.print("%");                 // % 출력
 
  delay(1000);
}
