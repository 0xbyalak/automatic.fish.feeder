# IoT Automatic Fish Feeder

Proyek ini merupakan sistem pemberi makan ikan otomatis berbasis mikrokontroler **Arduino UNO**, yang menggunakan **RTC DS1307**, **LCD 16x2**, dan **servo motor** untuk mengatur jadwal dan mekanisme pemberian pakan. Proyek ini disimulasikan menggunakan **Wokwi**.

## Tujuan Proyek

- Mengotomatisasi proses pemberian makan ikan berdasarkan waktu tertentu.
- Menampilkan waktu real-time pada LCD 16x2.
- Menggerakkan servo untuk membuka wadah pakan sesuai jadwal.
- Memberi sinyal bunyi menggunakan buzzer saat feeding.

## Komponen yang Digunakan

- Arduino UNO
- RTC Module DS1307
- LCD 16x2 (dengan I2C)
- Servo motor (SG90)
- Buzzer
- Kabel jumper

## Struktur Direktori

```
iot-fish-feeder/
├── rangkaian.png
├── main.ino
├── README.md                                    
```

## Cara Kerja

1. RTC DS1307 memberikan data waktu ke Arduino melalui I2C.
2. Arduino menampilkan waktu pada LCD 16x2.
3. Jika waktu saat ini cocok dengan waktu feeding (misalnya 07:00 dan 17:00), maka:
   - Servo akan bergerak membuka wadah pakan.
   - Buzzer akan berbunyi sebagai notifikasi feeding.
4. Setelah beberapa detik, servo kembali ke posisi semula.


## Simulasi

Proyek ini disimulasikan menggunakan [Wokwi](https://wokwi.com/), platform simulasi Arduino online. Untuk menjalankan simulasi:

1. Buka situs [https://wokwi.com](https://wokwi.com)
2. Buat project baru dan salin kode dari `main.ino`
3. Upload gambar rangkaian jika ingin referensi visual
4. Klik "Start Simulation"

## Catatan

- Pastikan pengaturan waktu RTC sudah benar jika menggunakan perangkat fisik.
- Kamu bisa menambahkan fitur WiFi atau logging online jika menggunakan ESP8266/ESP32.
- Waktu feeding dapat diubah pada bagian kode sesuai kebutuhan.
