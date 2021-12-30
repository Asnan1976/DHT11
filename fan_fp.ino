#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 2
#define DHTTYPE DHT11
const int relay1 = 14;
const int relay2 = 13;
 
int relayON = LOW; //relay nyala
int relayOFF = HIGH; //relay mati

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, relayOFF);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay2, relayOFF);

  lcd.backlight();
  lcd.begin();
  
  Serial.println("CLEARSHEET");
 Serial.println("LABEL, Tanggal, Waktu, Suhu, Kelembapan");

  lcd.setCursor(0,0);
  lcd.print("SMART EGG");
  lcd.setCursor(0,1);
  lcd.print("INKUBATOR");
  delay(5000);
  lcd.clear();
  dht.begin();
}

void loop() {
  lcd.clear();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t)||isnan(h)){
    Serial.println("gagal membaca");
    return;
  }
 
  lcd.setCursor(0,0);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.print(" 'C");

  if (t >= 30){
    digitalWrite(relay1, relayON);
    digitalWrite(relay2, relayOFF);
  }else{
    digitalWrite(relay1, relayOFF);
    digitalWrite(relay2, relayON);
  }

  lcd.setCursor(0,1);
  lcd.print("Hum : ");
  lcd.print(h);
  lcd.print(" %");
  delay(1000);

Serial.print("Data,"); 
 Serial.print("DATE"); //UNTUK MENAMPILKAN TANGGAL
 Serial.print(",");
 Serial.print("TIME"); //UNTUK MENAMPILKAN WAKTU
 Serial.print(","); 

 Serial.print(t);
 Serial.print(" C"); //UNTUK MENAMPILKAN SUHU
 Serial.print(",");
  Serial.print(h);
 Serial.print(" HUM"); //UNTUK MENAMPILKAN SUHU
 Serial.print(",");
 Serial.println(" ");
 delay(1000);
 }
