// Doc cam bien DHT11 tren ESP32 (ESP-WROOM-32D) chan DATA = GPIO15
// Wiring (module DHT11 co 3 chan):
//  VCC -> 5V (hoac 3.3V). Neu dung 5V, dam bao chan DATA khong keo len 5V truc tiep vao ESP32
//  GND -> GND chung
//  DATA -> GPIO13 (nen dung dien tro keo len 10K len 3.3V neu board DHT11 khong san pull-up)

#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 15      // GPIO15
#define DHTTYPE DHT11  // Loai cam bien

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Khoi dong cam bien DHT11...");
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();       // Do C
  float f = dht.readTemperature(true);   // Do F

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Loi: Khong doc duoc du lieu tu DHT11");
  } else {
    // Tinh heat index (theo do C)
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print("Nhiet do: "); Serial.print(t); Serial.print(" *C  (");
    Serial.print(f); Serial.print(" *F)  Do am: "); Serial.print(h); Serial.print(" %  HI: ");
    Serial.print(hic); Serial.println(" *C");
  }

  delay(2000); // Doc moi 2s
}