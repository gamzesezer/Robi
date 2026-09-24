void setup() {
 Serial.begin(115200);                                        // konusma hızı haberlesme baslar 
 pinMode(8,OUTPUT);
 while(!Serial){
 delay(100);
 }                          // seri ekran acılılımını bekler 
delay(1000);
 Serial.println("/n...................................................................");
 Serial.println("Robi:selam Gamze,Bügünün nasıl gecti");
 Serial.println("Robi:Bügün Neler yapıyoruz yeni Şeyler denemeye Hazır mısın?");
 Serial.println("..........................................................");
}
void loop(){
  // bilgisayardan bir veri gelip gelmedigini kontrol eder
  if (Serial.available()>0){
    // 2.gelen yazı okunur 
    String cevap=Serial.readStringUntil('/n');
    cevap.trim();                                       // boslukları temizler 
    cevap.toLowerCase();             // büyük kücük harf duyarlılıgını kaldırır
    // cevap kontrölü (icinde iyi veya güzel geciyor mu 
    if (cevap.indexOf("iyi")!=-1||cevap.indexOf("güzel") !=-1||cevap.indexOf("mükemmel")!=-1){
      Serial.println("Robi: Harika! hadi bu enerji ile yeni projeler yapalım.");
      // mutluluktan ısıgı hızlıca yakar led dansı
      for (int i=0;i<10;i++){
 digitalWrite(8,LOW);
 delay(80);
 digitalWrite(8,HIGH);
 delay(80);
      }
    }
  else if(cevap.indexOf("kötü")!=-1||cevap.indexOf("fena değil")!=-1||cevap.indexOf("berbat")!=-1){
  Serial.println("Robi:Senin adına üzüldüm  o zaman hadi keyiflenmek icin bir seyler yapalım kod yazmaya ne dersin.");
  digitalWrite(8,LOW);  // teselli icin ısıgı sbt yansın
 }
  }
}
