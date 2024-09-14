#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
const char* ssid     = "wifi007";
const char* password = "12345678";

const char* host = "iotprojects.org";
const char* streamId   = "....................";
const char* privateKey = "....................";
#define SENSOR_PIN A0 // LM35 sensor connected to analog pin A0
int pulse=D5;
int btrate,flg,count=0;
int hb=0;
int heartRate = 0;
unsigned long lastHeartbeatTime = 0;
unsigned long currentHeartbeatTime = 0;
unsigned long heartbeatInterval = 0;
unsigned long heartbeatCount = 0;
unsigned long startTime = 0;

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  pinMode(SENSOR_PIN, INPUT); // Set LM35 sensor pin as input
  pinMode(pulse, INPUT); // Set heart rate sensor pin as input
  startTime = millis(); // Record the start time


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
   
  delay(2000);
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN); // Read the analog value from LM35
  float voltage = sensorValue * ((3.3 / 1023.0) * 8); // Convert the analog value to voltage (ESP8266 operates at 3.3V)
  float temperature = voltage * 100.0; // LM35 outputs 10mV per degree Celsius change

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  count=0;
  for(int i=0;i<1000;i++)
  {
    if(digitalRead(pulse)==HIGH && flg==0)
    {
      count+=1;
      flg=1;
    }
  if(digitalRead(pulse)==LOW)
      flg=0; 
  delay(10);
  }
  btrate=count*5;
Serial.print("heartbeat=");
Serial.println(btrate);
  Serial.print("connecting to ");
  Serial.println(host);
  

WiFiClientSecure client;
client.setInsecure();  // Disable SSL certificate validation
const int httpsPort = 443;

if (!client.connect(host, httpsPort)) {
  Serial.println("connection failed");
  return;
}

String url = "GET https://iotprojects.org/Smart_guardian/Get2.php?hb="; // Getting info from my online database through my online website
url+=btrate;
url += " HTTP/1.1\r\nHost: iotprojects.org\r\nConnection: close\r\n\r\n";
client.print(url);

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    char a=client.read();
    //String line = client.readStringUntil('\r');
    //Serial.print(line);
   
    Serial.print(a);
      
    } 
    
  Serial.println();  
}
