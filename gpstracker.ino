#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <LiquidCrystal_I2C.h>    //If you don't have the LiquidCrystal_I2C library, download it and install it
LiquidCrystal_I2C lcd(0x27,16,2);
float lattitude,longitude; // create variable for latitude and longitude object 
SoftwareSerial gpsSerial(2,3);//tx,rx
SoftwareSerial gsmm(5, 4);//tx,rx
TinyGPSPlus gps;// create gps object
#define buttonPin 10
int ledPin = 13;
int buzz = 12;
int data;

void setup()
{
Serial.begin(9600);
Serial.print(9600);
  lcd.begin();
  lcd.backlight();// connect serial
//lcd.begin(16, 2);
 pinMode(ledPin, OUTPUT);
 pinMode(buzz, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  lcd.print("Women Safety");
  lcd.setCursor(0,1);
  lcd.print("    System      ");
  delay(2000);
  lcd.clear();
gpsSerial.begin(9600);
gpsSerial.listen();
 textgps();
   
 gsmm.begin(9600);


}
void loop()
{
  
  data = digitalRead(buttonPin);
   // float voltage= buttonPin * (5.0 / 1023.0);
  Serial.print(buttonPin);
  if (data == HIGH ) 
  {
     
      // turn LED off:
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzz, HIGH);
      lcd.setCursor(0,0);
lcd.print("Women in turbal");
lcd.setCursor(0,1);
lcd.print(" Please Help  ");
send_msgG();
 delay(500);
 gsmm.println("ATD+918126977055;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
    delay(2000); // wait for 2 seconds...
            
  } 
  else 
  {
 
    // turn LED on:
    digitalWrite(ledPin, LOW);
    digitalWrite(buzz, LOW);
    lcd.setCursor(0,0);
lcd.print("Everything's OK ");
lcd.setCursor(0,1);
lcd.print("Enjoy your day");
    //delay(1000);
  }
}

void textgps()
{

    while(1)
  {
   while (gpsSerial.available() > 0)
   { gps.encode(gpsSerial.read()); }

      if (gps.location.isUpdated())
      {
       Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
       Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
       lattitude=gps.location.lat();
       longitude=gps.location.lng();
      break;
      }
  
    
}

 Serial.print("LATTITUDE="); Serial.println(lattitude,6);
 Serial.print("LONGITUDE="); Serial.println(longitude,6);
 lcd.print("LAT ");lcd.print(lattitude,6);
 lcd.setCursor(0, 1);
 lcd.print("LONG ");lcd.print(longitude,6);
 delay(1000);
// lcd.clear();
}

 void send_msgG()
{
  delay(100);
  gsmm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsmm.println("AT+CMGS=\"+918126977055\"\r"); // Replace x with mobile number
  delay(1000);
  gsmm.println("Please Help i am in turbal");// The SMS text you want to send
  delay(100);
  gsmm.print("http://maps.google.com/maps?q=loc:  ");
      gsmm.print(gps.location.lat(), 6);
      gsmm.print(" , ");
      gsmm.print(gps.location.lng(), 6);
      delay(200);
  gsmm.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
//gsmm.println("ATD+919720255525;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
    //delay(2000); // wait for 20 seconds...
     lcd.clear();
  lcd.print("Message Sent");
  delay(2000);
  lcd.clear();
  }
  void lcd_status()
{
  lcd.clear();
  lcd.print("Message Sent");
  delay(2000);
  lcd.clear();
  lcd.print("System Ready");
   delay(2000);
 // return;
   lcd.clear();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    gsmm.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(gsmm.available()) 
  {
    Serial.write(gsmm.read());//Forward what Software Serial received to Serial Port
  }
}