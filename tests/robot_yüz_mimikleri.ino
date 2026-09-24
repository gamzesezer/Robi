#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
                                   // RESET PİNİ YOKSA -1 KULLANILIR
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

void setup(){
  // ekranı baslat(0x3C standart adrestir)

  Wire.begin(8,9);
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    for(;;);      // baglantı yoksa burda kalır
    
  }
  display.clearDisplay();              // ilk gözlerinin çizim kod
  display.display();
}
// GÖZLER çizen fonksiyon
void drawFace(bool gozAck,int myType){
  display.clearDisplay();  // her seferinde ekranı temizle 
  // gözlerin komutu
   if(gozAck){
  display.fillCircle(40,25,12,SSD1306_WHITE);  // SOL GÖZ İÇİN
  display.fillCircle(88,25,12,SSD1306_WHITE);
   }else{
    // kapalı gözler(kısa çizgiler)
    display.fillRect(28,23,24,4,SSD1306_WHITE);  // SOL GÖZ
    display.fillRect(76,23,24,4,SSD1306_WHITE);// SAĞ GÖZ
   }
   // AĞIZ İÇİN KODLAR
   if(myType==1){
                            // gülümswyen Agız (genis gülümseme)
    display.fillRoundRect(44,48,40,10,5,SSD1306_WHITE);
   }
   
  else if (myType==2){                 
    // saşkın /küçük agız için 
    display.fillCircle(64,52,6,SSD1306_WHITE);
  }
  else{    // düz ciddi
    display.fillRect(44,50,40,4,SSD1306_WHITE);
  }
  display.display();   // çizilenleri ekrana gönder
}
void loop(){
  // animasyonlar döngü halinde burda olusacak 
// 1.durum mutlu ve gözler acık
drawFace(true,1);
    delay(random(4000,7000));  //  4 ile 7 sn arası gözler acık
    //2.durum göz kırp ve agzı küçültür
    drawFace(false,1);      // gözler kapalı ,mutlu yüz
    delay(500);          //200 mili sn kIPSIN kalsın
    //3.durum gözler açıkama düz ağız(düsünme vibe)
    drawFace(true,0);
    delay(2000);
   // 4.DURUM Arada bir şaşırsın
    drawFace(true,2);     // 2sn saskın bakar
    delay(2000);
}
