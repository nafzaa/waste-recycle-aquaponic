#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

int relay = 4; //D2 //gpio4
#include <Servo.h>

String timer1;
String timer2;
String timer3;
String timer4;
String timer5;

String currentTime;
String minit;
String minitawal;

String noti;

Servo servo;

int state = 0;

int statenoti = 0;

int Hour;
int Minute;
int Minuteoff;

String Hourstring;
String Minutestring;
String Minutestringoff;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "AxHYAMM_5R0Z61kw8_DBxZG8V-kpnD7y";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "aresh";
char pass[] = "20051999";                           

BlynkTimer timer;

WidgetRTC rtc;

// Digital clock display of the time
void clockDisplay()
{
  // You can call hour(), minute(), ... at any time
  // Please see Time library examples for details
  Hour = hour();
  Minute = minute();
  Minuteoff = minute() + 1;

  if (Hour <= 9){
    Hourstring = "0" + String(Hour);
    }
  else {
    Hourstring = String(Hour);
    }

  if (Minute <= 9){
    Minutestring = "0" + String(Minute);
    Minutestringoff = "0" + String(Minuteoff);
    }

  else {
    Minutestring = String(Minute);
    Minutestringoff = String(Minuteoff);
    }

  currentTime = Hourstring + ":" + Minutestring;
  minitawal = Minutestring;
  
  
  Serial.print("Current time: ");
  Serial.println(currentTime);
  Serial.println (minitawal);
  //Serial.println (minit);

  if (currentTime == timer4 && state == 0){
    digitalWrite(relay, LOW);
    Serial.println ("on");
    minit = Minutestringoff;
    state = 1;
    statenoti = 1;
    noti = "light on";
    notis();
    delay (2000);
    statenoti = 0;
    notis();
    }

  if (currentTime == timer5 && state == 0){
    digitalWrite(relay, HIGH);
    Serial.println ("off");
    minit = Minutestringoff;
    state = 1;
    statenoti = 2;
    noti = "light off";
    notis();
    delay (2000);
    statenoti = 0;
    notis();
    }

  if (currentTime == timer1 && state == 0){
    servo.write(90);

    delay(5000); //5 sec

    servo.write(0);
    minit = Minutestringoff;
    Serial.println (minit);
    state = 1;
    statenoti = 3;
    noti = "feeding on";
    notis();
    delay (2000);
    statenoti = 0;
    notis();

}

if (currentTime == timer2 && state == 0){
    servo.write(90);

    delay(5000); //5 sec

    servo.write(0);
    minit = Minutestringoff;
    Serial.println (minit);
    state = 1;
    statenoti = 3;
    noti = "feeding on";
    notis();
    delay (2000);
    statenoti = 0;
    notis();

}

if (currentTime == timer3 && state == 0){
    servo.write(90);

    delay(5000); //5 sec

    servo.write(0);
    minit = Minutestringoff;
    Serial.println (minit);
    state = 1;
    statenoti = 3;
    noti = "feeding on";
    notis();
    delay (2000);
    statenoti = 0;
    notis();

}

  if (minitawal == minit){
    state = 0;
    }
  
}

void notis(){
  Blynk.virtualWrite(V6, noti);
  Blynk.virtualWrite(V7, statenoti);
  }


BLYNK_WRITE(V1)
{
  timer1 = param.asStr(); 
 
  Serial.print("timer1=");
  Serial.print(" ");
  Serial.println(timer1);
}

BLYNK_WRITE(V2)
{
 timer2 = param.asStr(); 
 
  Serial.print("timer2=");
  Serial.print(" ");
  Serial.println(timer2);
}

BLYNK_WRITE(V3)
{
 timer3 = param.asStr(); 
 
  Serial.print("timer3=");
  Serial.print(" ");
  Serial.println(timer3);
}

BLYNK_WRITE(V4)
{
 timer4 = param.asStr(); 
 
  Serial.print("timer4=");
  Serial.print(" ");
  Serial.println(timer4);
}

BLYNK_WRITE(V5)
{
 timer5 = param.asStr(); 
 
  Serial.print("timer5=");
  Serial.print(" ");
  Serial.println(timer5);
}

BLYNK_CONNECTED() {
  // Synchronize time on connection
  rtc.begin();
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode (relay, OUTPUT);

  digitalWrite(relay, HIGH);
  servo.attach(5); //D1
  servo.write(0);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Other Time library functions can be used, like:
  //   timeStatus(), setSyncInterval(interval)...
  // Read more: http://www.pjrc.com/teensy/td_libs_Time.html

  setSyncInterval(10 * 60); // Sync interval in seconds (10 minutes)

  // Display digital clock every 10 seconds
  timer.setInterval(1000L, clockDisplay);

  Blynk.notify("Device started");
}

void loop()
{
  Blynk.run();
  timer.run();
}
