#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi objek
RTC_DS1307 rtc; 
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int buzzerPin = 10; 
const int servoPin = 9;

//jadwal pemberian makan (jam, menit)
const int schedules[][2] = {
  {19, 8},  
  {10, 9},  
  {16, 30}  
};
const int scheduleCount = sizeof(schedules) / sizeof(schedules[0]); 

bool feedingSuccess[scheduleCount] = {false}; 

void setup() {
  Serial.begin(9600);

  // Inisialisasi RTC
  if (!rtc.begin()) {
    Serial.println("RTC tidak terdeteksi!");
    while (1);
  }

  // Jika RTC belum disetel waktu, set waktu sekarang (hanya sekali)
  if (!rtc.isrunning()) {
    Serial.println("Setting RTC waktu sekarang...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  }

  // Inisialisasi Servo
  servo.attach(servoPin);
  servo.write(0); 

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Pemberi Makan");
  lcd.setCursor(0, 1);
  lcd.print("Otomatis Ready!");

  delay(2000); 
  lcd.clear();

  // Inisialisasi Buzzer
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); 
}

void loop() {
  DateTime now = rtc.now();

  // Tampilkan waktu di LCD
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());

  // Periksa semua jadwal
  for (int i = 0; i < scheduleCount; i++) {
    if (now.hour() == schedules[i][0] && now.minute() == schedules[i][1]) {
      // Jika jadwal cocok
      if (!feedingSuccess[i]) {
        feed(i); 
      } else {
        
        lcd.setCursor(0, 1);
        lcd.print("Feeding OK! ke ");
        lcd.print(i + 1);
        
        delay(2000); 
        
        lcd.clear();
      }
    }
  }

  delay(1000);
}

void feed(int scheduleIndex) {
  lcd.setCursor(0, 1);
  lcd.print("Feeding... ke ");
  lcd.print(scheduleIndex + 1);
  Serial.print("Memberikan makan ke ");
  Serial.println(scheduleIndex + 1);

  // Nyalakan buzzer untuk indikasi pemberian makan
  digitalWrite(buzzerPin, HIGH);

  // Gerakkan servo
  servo.write(90); 
  delay(5000);     
  servo.write(0);  

  feedingSuccess[scheduleIndex] = true; 

  // Matikan buzzer setelah selesai
  digitalWrite(buzzerPin, LOW);

  lcd.setCursor(0, 1);
  lcd.print("Feeding Done!   ");
  Serial.println("Pemberian makan selesai.");
  delay(2000);
  lcd.clear();
}
