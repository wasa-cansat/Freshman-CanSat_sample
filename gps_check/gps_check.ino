#include <TinyGPS++.h>
#include <HardwareSerial.h>

TinyGPSPlus gps;
HardwareSerial gpsSerial(1);  // UART1を使用

void setup() {
  Serial.begin(115200);      // デバッグ用シリアルモニタ
  Serial.println("init");

  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);  // GPSモジュール用シリアル（TX=17, RX=16）

  Serial.println("GPSの初期化完了");
}

void loop() {
  Serial.println(gpsSerial.available());
  
  if (gpsSerial.available() <= 0) {
    Serial.println("Can't connect GPS");
  }

  while (gpsSerial.available() > 0) {
    //Serial.println("Connect Success");
    gps.encode(gpsSerial.read());  // GPSデータの読み取りと解析

      Serial.print("緯度: ");
      Serial.println(gps.location.lat(), 6);  // 緯度を6桁で表示

      Serial.print("経度: ");
      Serial.println(gps.location.lng(), 6);  // 経度を6桁で表示

    if (gps.location.isUpdated()) {
    }
  }

  delay(1000);
}