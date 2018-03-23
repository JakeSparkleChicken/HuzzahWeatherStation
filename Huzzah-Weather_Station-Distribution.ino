#include <Wire.h>

#include <Adafruit_MPL3115A2.h>

#include <Adafruit_Sensor.h>

//Give the barometer a nicer name
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

#include "DHT.h"

#include <ESP8266WiFi.h>

//Fill this in with your real wifi settings! 
const char* ssid     = "SSID";
const char* password = "PASSWORD";
 
const char* host = "IP Address or FQDN";

//Whatever pin you're using for the temp sensor
//Remember that the HUZZAH's pins are funky
#define DHTPIN 13     

//Set this as either DHT22, DHT11 or DHT21 depending on what
//you're using
#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE);

//The barometer occasionally gives a super low reading.
//Since I didn't spontaneously lose consciousness, I know
//that it was spurious.  The prevPress variable makes sure that
//you can safely discard those wacky ones.  I defined it as
//something sane for where I live just in case the very first
//reading is weird. You shoud change it to something that makes
//sense for your area.
float prevPress = 987.44;

float pressure;
void setup() {

//All of the Serial.print stuff is just for troubleshooting.
//You can safely remove all of it once your station is ready
//to deploy.
  Serial.begin(9600);
  Serial.println("DHTxx test!");

//With a regular Arduino, you can just use the defaults for I2C
//communication with the sensors.  The HUZZAH uses pins 4 and 5
//for SDA and SCL so it has to be explicitely defined.
  Wire.pins(4,5);
  
  dht.begin();
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  delay(2000);
  baro.begin();
  
  float h = dht.readHumidity();
  
  float t = dht.readTemperature();
  
  
  float pascals = baro.getPressure();

  //This is the sanity check for the barometer.  Throwing out
  //values lower than 80000 will work for anyone living at an
  //altitude lower than 1500m/5000ft.  If you live at a higher
  //altitude, change the value to 70000.
  if (pascals < 80000) {

  //Here's where that prevPress comes into play.  If your value
  //is not something that makes sense, it submits the last one.
    pressure = prevPress;
    
  }
  else {

  //First of all, we're reporting the pressure in millibars
  //instead of straight pascals so we need to divide the pascals
  //by 100.  Then we assign prevPress.
    pressure = pascals/100;
    prevPress = pressure;
  }
  
  //The DHT library has a nifty built in function to determine
  //the heat index, so we use that here.
  float hic = dht.computeHeatIndex(t, h);

  //Magically transmitting the information across the air!
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  
  String url = "/weather/process.php";
  Serial.println(pascals);
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  Serial.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: IP Address or FQDN\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: 62\r\n\r\n" +
               "temperature="+t+"&humidity="+h+"&pressure="+pressure+"&heatindex="+hic+"\r\n");
               
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: IP Address or FQDN\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: 62\r\n\r\n" +
               "temperature="+t+"&humidity="+h+"&pressure="+pressure+"&heatindex="+hic+"\r\n"); 
  
 
  delay(500);
  
  
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  
  delay(300000);
  
}

