#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <driver/i2s.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define I2S_MIC_SCK  2  
#define I2S_MIC_WS   3  
#define I2S_MIC_SD   4   

void setupI2S() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 8000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 512
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_MIC_SCK,
    .ws_io_num = I2S_MIC_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_MIC_SD
  };

  i2s_driver_install((i2s_port_t)0, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)0, &pin_config);
  i2s_zero_dma_buffer((i2s_port_t)0);
}

void robiiYuzGoster(String durum) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  if (durum == "Dinliyor") {
    display.setCursor(25, 25);
    display.println(" (-.-) !"); 
  } else if (durum == "Normal") {
    display.setCursor(30, 25);
    display.println(" (^.^) "); 
  }
  display.display();
}

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED ekran bulunamadi!"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Robi Kulak Aktif.");
  display.display();
  delay(1000);

  setupI2S();
  robiiYuzGoster("Normal");
}

void loop() {
  int32_t ses_ornekleri[32];
  size_t bytesRead = 0;
  
  i2s_read((i2s_port_t)0, (void*)ses_ornekleri, sizeof(ses_ornekleri), &bytesRead, 0);
  
  long sesToplam = 0;
  for (int i = 0; i < 32; i++) {
    sesToplam += abs(ses_ornekleri[i]);
  }
  long ortalamaSes = sesToplam / 32;

  Serial.print("Ses Seviyesi: ");
  Serial.println(ortalamaSes);

  // Gelen devasa sayılara göre eşik belirleyelim (Örn: 10 milyon üzeri ses)
  if (ortalamaSes > 10000000) { 
    robiiYuzGoster("Dinliyor");
    delay(1000);
    robiiYuzGoster("Normal");
  }
  
  delay(50);
}
