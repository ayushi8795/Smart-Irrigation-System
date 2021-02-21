/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  =>
  =>          USB HOWTO: http://tiny.cc/BlynkUSB
  =>

  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT DebugSerial


// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX



#include <BlynkSimpleStream.h>
BlynkTimer timer; 
BlynkTimer timer2;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "nOkFZQFkTevl55Z6urOs9OZTapKMpFw4";

int relay=13;
// soil code 
int val = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor 
int soilPower = 7;//Variable for Soil moisture Power
//Rather than powering the sensor through the 3.3V or 5V pins, 
//we'll use a digital pin to power the sensor. This will 
//prevent corrosion of the sensor as it sits in the soil. 

void soilsensor()
{
/*for(int x=0;x<3;x++){
  digitalWrite(relay, HIGH); 
  delay(100);
   digitalWrite(relay, LOW); 
   delay(100);}*/
//Serial.print("Soil Moisture = ");    
//get soil moisture value from the function below and print it
//Serial.println(readSoil());
if (readSoil()<=511){
//Serial.print("Dry soil");
 digitalWrite(relay, LOW);
 delay(1000);
 digitalWrite(relay, HIGH);
}
else {
//Serial.print("Wet soil");
digitalWrite(relay, HIGH);
}
//This 1 second timefrme is used so you can test the sensor and see it change in real-time.
//For in-plant applications, you will want to take readings much less frequently.
delay(100);//take a reading every second 
  
  
  }


 int readSoil()
{
    digitalWrite(soilPower, HIGH);//turn D7 "On"
    delay(10);//wait 10 milliseconds 
    val = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return val;//send current moisture value
}


//send data
void sensorDataSend()
{
   digitalWrite(soilPower, HIGH);//turn D7 "On"
  int sensorValue = analogRead(soilPin);         // reading sensor from analog pin
  String val;
  if (readSoil()<=511)
  val="ON";
else 

val="OFF";

  Blynk.virtualWrite(V5, sensorValue);  // sending sensor value to Blynk app
  Blynk.virtualWrite(V6, val);  // sending sensor value to Blynk a
}


void setup()
{ 
  // Debug console
  DebugSerial.begin(9600);
 

  // Serial.begin(9600);   // open serial over USB
  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
   pinMode(relay,OUTPUT);
   pinMode(soilPin,INPUT);
   digitalWrite(relay, HIGH);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
// pinMode(relay,OUTPUT);
 //digitalWrite(relay, HIGH);
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
   // Setup a function to be called every second
  timer.setInterval(1000L,soilsensor);
timer2.setInterval(1000L,sensorDataSend); 
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
timer2.run(); // Initiates BlynkTimer
}
