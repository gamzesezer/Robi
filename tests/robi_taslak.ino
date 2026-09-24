#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <driver/i2s.h>
#include <time.h>

// --- 1. EKRAN VE SENSÖR AYARLARI ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TOUCH_PIN 6 // Touch Sensörü Pin 6

// Ortak I2S Saat Pinleri (Amfi ve Mikrofon bu pinleri paylaşacak)
#define I2S_COMMON_BCLK 2 // Amfi BCLK ve Mikrofon SCK ortak pini
#define I2S_COMMON_LRC  3 // Amfi LRC ve Mikrofon WS ortak pini

// Ayrılmış I2S Veri Hatları
#define I2S_SPEAKER_DOUT 1 // Sadece Hoparlör Amfisinin Veri pini
#define I2S_MIC_SD       4 // Sadece Mikrofonun Veri pini

// --- 2. ZAMAN VE SUNUCU AYARLARI ---
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 10800; // GMT+3 (Türkiye)
const int daylightOffset_sec = 0;

unsigned long sonVeriZamani = 0;
const long guncellemeAraligi = 60000;

// --- 3. SES SİSTEMİ YAPILANDIRMASI (KOMBİNE MOD: TX + RX) ---
i2s_config_t i2s_config = {
  .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
  .sample_rate = 8000,
  .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
  .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
  .communication_format = I2S_COMM_FORMAT_STAND_I2S,
  .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
  .dma_buf_count = 8,
  .dma_buf_len = 64
};

i2s_pin_config_t pin_config = {
  .bck_io_num = I2S_COMMON_BCLK,
  .ws_io_num = I2S_COMMON_LRC,
  .data_out_num = I2S_SPEAKER_DOUT,
  .data_in_num = I2S_MIC_SD
};

WiFiMulti wifiMulti;
const char* api_key = "SENIN_GEMINI_API_KEYIN";

// Fonksiyon Prototipleri
void robiIfadeDegistir(String durum);
void anaEkranGuncelle();
void geminiSoruSor(String soru);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED ekran bulunamadi!"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Robi Aciliyor...");
  display.display();

  pinMode(TOUCH_PIN, INPUT);

  // Kombine I2S sürücüsünü yükle
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
  i2s_zero_dma_buffer(I2S_NUM_0);

  // Wi-Fi Ağları (Şifreler boş bırakıldı)
  wifiMulti.addAP("wifi ismi", " wifi şifresi");
  wifiMulti.addAP("yedek wifi ismi ", "wifi şifresi");

  display.println("WiFi bekleniyor...");
  display.display();

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  Serial.println("\nRobi: Tum sistemler senkronize.");
  display.clearDisplay();
  display.setCursor(0, 20);
  display.println("Robi Hazir! ^_^");
  display.display();
  delay(1500);
}

void loop() {
  if (wifiMulti.run() != WL_CONNECTED) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("WiFi Baglantisi...");
    display.display();
    return;
  }

  // 1. Dokunmatik Sensör Kontrolü (Pin 6)
  if (digitalRead(TOUCH_PIN) == HIGH) {
    Serial.println("Robi: Gidiklaniyorum!");
    robiIfadeDegistir("Mutlu");
    delay(2000);
    sonVeriZamani = 0; // Ekranı hemen güncellemesi için resetle
  }

  // 2. Ekran Yenileme Döngüsü
  unsigned long suan = millis();
  if (suan - sonVeriZamani >= guncellemeAraligi || sonVeriZamani == 0) {
    sonVeriZamani = suan;
    anaEkranGuncelle();
  }
}

void robiIfadeDegistir(String durum) {
  display.clearDisplay();
  display.setTextSize(2);
  if (durum == "Mutlu") {
    display.setCursor(30, 25);
    display.println("(^_^) <3");
  } else if (durum == "Uyanik") {
    display.setCursor(35, 25);
    display.println("(o_o) !");
  }
  display.display();
}

void anaEkranGuncelle() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Saat cekilemedi!");
    return;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);

  display.print("Saat: ");
  display.printf("%02d:%02d\n", timeinfo.tm_hour, timeinfo.tm_min);

  display.println("\n--- Elazig ---");
  display.println("Robi Hazir!");

  display.display();
}

void geminiSoruSor(String soru) {
  // Sesli asistan fonksiyonu altyapısı
}
