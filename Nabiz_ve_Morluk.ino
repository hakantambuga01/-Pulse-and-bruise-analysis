#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//#define S0 A6
//#define S1 A5
//#define S2 8
//#define S3 9
//#define sensorOut 7
#define S0 5
#define S1 13
#define S2 7
#define S3 6
#define sensorOut 8

int frequency = 0;
const int sensor = A7;
int periyot=20;
double alfa=0.75;
double yenileme=0.0;

int red=0;
int green=0;
int blue=0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(sensor,INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(2,0);
  lcd.print("MORLUK ANALIZ");
  lcd.setCursor(2,1);
  lcd.print("NABIZ OLCER");
  delay(2000);
  lcd.clear();
}
void loop() {
  sensor1();
  durum();
  nabiz();
  
 
}

void sensor1()
{
   // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  red = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(red);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  green = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(green);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  blue = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(blue);//printing RED color frequency
  Serial.println("  ");
  delay(100);
}

void durum()
{

  //     NORMAL  // 
  //red 12
  //green 15
  //blue 25
  if((red<30)&&(green<180)&&(blue<180))
  {
    Serial.println("DURUM: NORMAL");
    lcd.setCursor(2,0);
    lcd.print("DURUM: NORMAL");
    delay(2000);
    lcd.clear();
  }

  // ORTA DERECE //

  //red 70
  //green37
  //blue49

   if((red>70)&&(green<180)&&(blue<180))
  {
    Serial.println("DURUM: ORTA");
    lcd.setCursor(2,0);
    lcd.print("DURUM: ORTA");
    delay(2000);
    lcd.clear();
  }

  //red 60
  //green 93
  //blue 45
  //  RİSKLİ //

   if((red<180)&&(green>80)&&(blue<180))
  {
    Serial.println("DURUM: RISKLI");
    lcd.setCursor(2,0);
    lcd.print("DURUM: RISKLI");
    delay(2000);
    lcd.clear();
  }
}

void nabiz()
{
  static double oncekideger=0;
  static double oncekiyenileme=0;
 
int ritim=analogRead(sensor);
 
double deger=alfa*oncekideger+(0-alfa)*ritim;
yenileme=deger-oncekideger;
lcd.setCursor(2,1);
lcd.print("NABIZ:  ");
lcd.setCursor(8,1);
lcd.print(ritim/10);
Serial.println(ritim/10);
oncekideger=deger;
oncekiyenileme=yenileme;
delay(periyot*10);
}


