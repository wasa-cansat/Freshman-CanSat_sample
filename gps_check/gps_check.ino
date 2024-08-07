#include <TinyGPSPlus.h>
// GPS baud
static const uint32_t GPSBaud = 9600;
// The TinyGPSPlus object
TinyGPSPlus gps;
// Tiny GPS Custom object
TinyGPSCustom gps_tim (gps, "GNGGA", 1); // 時刻
TinyGPSCustom gps_alt (gps, "GNGGA", 9); // 高度
TinyGPSCustom gps_sat (gps, "GNGGA", 7); // 衛星数
TinyGPSCustom gps_qlt (gps, "GNGGA", 6); // 測位モード
TinyGPSCustom gps_spd (gps, "GNRMC", 7); // 速度（ノット）
TinyGPSCustom gps_dir (gps, "GNRMC", 8); // 方位
// 方位の定義。16番目は WAIT
static const char *c_dir[17] = {
  "  N   ",
  "N-N-E ",
  " N-E  ",
  "E-N-E ",
  "  E   ",
  "E-S-E ",
  " S-E  ",
  "S-S-E ",
  "  S   ",
  "S-S-W ",
  " S-W  ",
  "W-S-W ",
  "  W   ",
  "W-N-W ",
  " N-W  ",
  "N-N-W ",
  "WAIT  "};
// 前回方位保管用
float f_olddir = 999;
// 前回分保管用
int i_oldmin = 999;

void setup() {
  Serial.begin(9600);
  Serial2.begin(GPSBaud); // TX=16,RX=17 がデフォルト
}

void loop() {
  // 変数宣言
  float f_alt;
  float f_spd;
  float f_dir;
  int i_dir;
  int i_qlt;
  int i_hour;
  int i_min;
  char hour[5];
  char min[5];
  char buf[100];
  // 時刻の取得とJSTへの変換
  strcpy(buf, gps_tim.value());
  strncpy(hour, buf, 2);
  strncpy(min, buf + 2, 2);
  i_hour = atoi(hour);
  i_hour = i_hour + 9;
  if (i_hour > 23) {
    i_hour = i_hour - 24;
  }
  i_min = atoi(min);
  // 更新があったときのみ表示を変更する
  if (i_min != i_oldmin || gps_alt.isUpdated() || gps_sat.isUpdated() || gps_qlt.isUpdated() || gps_spd.isUpdated() || gps_dir.isUpdated()) {
    // 標高を数値に変換  
    f_alt = atof(gps_alt.value());
    // 速度を数値に変更してkm/h換算
    f_spd = atof(gps_spd.value()) * 1.852;
  
    // 速度が 8km/h 以上で方位を更新する
    if (f_spd >= 8.0) {
      // 方位を元に配列引数を算出
      f_dir = atof(gps_dir.value());
    } else {
      f_dir = f_olddir;
    }
    // 方位を元に方位文字配列引数を算出
    if (f_dir < 360) {
      float f_tmp = f_dir + 11.25;
      if (f_tmp >= 360.0) {
        f_tmp -= 360.0;
      }
      i_dir = (int)(f_tmp / 22.5);
    } else {
      i_dir = 16;
    }
    // 方位を保存
    f_olddir = f_dir;
    
    // パソコン画面（シリアルモニター）に表示
    Serial.println("===================================");
    // 速度表示
    dtostrf(f_spd, 4, 0, buf);
    Serial.print("Spd : "); Serial.print(buf); Serial.println(" km/h");
    
    // 方位表示
    if (f_dir > 360) {
      Serial.println("Dir : WAIT");
    } else {
      dtostrf(f_dir, 4, 0, buf);
      Serial.print("Dir : "); Serial.print(buf); Serial.print(" deg  ");
      Serial.println(c_dir[i_dir]);
    }
    
    // 高度表示
    dtostrf(f_alt, 4, 0, buf);
    Serial.print("Alt : "); Serial.print(buf); Serial.println(" m");
    
    // 時間表示
    sprintf(buf, "%02d:%02d", i_hour, i_min);
    Serial.print("JST : "); Serial.println(buf);
    
    i_oldmin = i_min;
    
    // 衛星数表示
    sprintf(buf, "%02s", gps_sat.value());
    Serial.print("Sat : "); Serial.println(buf);
    
    // 測位方式表示
    i_qlt = atoi(gps_qlt.value());
    Serial.print("Quality : "); Serial.println(i_qlt);
  }
  // delay付きのGPS受信
  smartDelay(1000);
}

// delay付きのGPS受信
static void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (Serial2.available())
      gps.encode(Serial2.read());
  } while (millis() - start < ms);
}