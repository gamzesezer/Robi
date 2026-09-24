

# Robi - Masaüstü Asistan Robotu 🤖

![Status](https://img.shields.io/badge/Status-In_Development-orange)
![Board](https://img.shields.io/badge/Board-ESP32-blue)
![Language](https://img.shields.io/badge/Language-C%2FC%2B%2B-green)

**Robi**, ESP32 mikrodenetleyicisi tabanlı, donanım ve yazılım entegrasyonu süreçleri devam eden interaktif bir masaüstü asistan robotu projesidir.

> ⚠️ **Not:** Bu proje aktif olarak geliştirilme aşamasındadır. Kodlar ve donanım mimarisi modüler testler üzerinden geliştirilmektedir.

---

## 🛠️ Donanım Bileşenleri & Mimarisi
- **Ana Mikrodenetleyici:** ESP32-C3 Development Board
- **Ses & Ses İşleme:** MAX98357A I2S Amfi + 8 Ohm 3W Hoparlör & INMP441 I2S Dijital Mikrofon
- **Ekran / Arayüz:** 0.96 inç OLED Ekran & Kapasitif Touch Switch (Dokunmatik Anahtar)
- **Güç & Şarj Yönetimi:** 3000 mAh Li-Po Batarya, TP4056 Şarj Modülü, Ayarlanabilir Yükseltici (Step-Up) Regülatör & IC125B Mini Anahtar
- **Mekanik & Prototipleme:** Özel lehimleme, güç hatları optimizasyonu ve devre montajı
-
---

## 📁 Proje Yapısı
- `/tests`: Bileşenlerin tekil test kodları (Sensör, Servo, Ses denemeleri)
- `/src`: Entegre edilmiş ana kontrol kodları

---

## 🚀 Durum ve Yol Haritası
- [x] Bileşenlerin lehimlenmesi ve donanım montajı
- [x] Sensör ve motor birim testleri (C/C++)
- [ ] Modüler kodların tek bir ana kontrol döngüsünde birleştirilmesi
- [ ] Gövde tasarımı / 3D entegrasyon

---

## 👤 Geliştirici
**Gamze Sezer**  
[LinkedIn](https://linkedin.com/in/gamze-sezer) | Mekatronik Mühendisliği Öğrencisi @ Fırat Üniversitesi