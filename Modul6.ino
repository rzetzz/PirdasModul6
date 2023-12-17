#include <MPU6050_tockn.h>
#include <HTTPClient.h>
#include <WiFi.h>
#define BUZZER 4
#define LED 26

MPU6050 mpu6050(Wire);

const char* ssid = "UpAndUp";
const char* pass = "11111111";
const char* serverName = "http://192.168.204.1/PirdasModul6/mpu.php";

void setup() {
   
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
  ledcSetup(0, 1000, 8);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi");
  }

  Serial.println();
  Serial.println("Connected to " + WiFi.SSID());
}

void loop() {

  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Wifi disconnected");
    delay(1000);
    setup();
  }

  mpu6050.update();
  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("\tangleZ : ");
  Serial.println(mpu6050.getAngleZ());

  String condition;
  String led;
  String buzzer;
  if(mpu6050.getAngleX() > 7 || mpu6050.getAngleX() < -7 || mpu6050.getAngleY() > 7 || mpu6050.getAngleY() < -7)
  {
    Serial.println("Miring");
    condition ="Miring";
    buzzer ="Mati";
    led = "Nyala";
    tone(BUZZER, 500);
    digitalWrite(LED,0);
  }
  else
  {
    Serial.println("Aman");
    condition ="Aman";
    buzzer ="Nyala";
    led = "Mati";
    noTone(BUZZER);
    digitalWrite(LED,1);
  }

  String url = serverName;
  url += "?kondisi=";
  url += String(condition);
  url += "&led=";
  url += String(led);
  url += "&buzzer=";
  url += String(buzzer);
  url += "&x=";
  url += String(mpu6050.getAngleX());
  url += "&y=";
  url += String(mpu6050.getAngleY());
  url += "&z=";
  url += String(mpu6050.getAngleZ());

  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0){
    Serial.println("Data send sucessfully");
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

}
