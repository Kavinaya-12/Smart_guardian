#include <Wire.h>

const int MPU6050_addr = 0x68;  // I2C address of the MPU6050 accelerometer

void setup() {
  Serial.begin(115200);
  Wire.begin();
pinMode(D6,OUTPUT);
digitalWrite(D6,HIGH);
digitalWrite(D8,LOW);
  initializeMPU6050();
}

void loop() {
  int xValue = readAccelerometerValue(MPU6050_addr, 0x3B); // Read X-axis value
  int yValue = readAccelerometerValue(MPU6050_addr, 0x3D); // Read Y-axis value
  int zValue = readAccelerometerValue(MPU6050_addr, 0x3F); // Read Z-axis value

  Serial.print("X-axis value: ");
  Serial.print(xValue);
  Serial.print("\tY-axis value: ");
  Serial.print(yValue);
  Serial.print("\tZ-axis value: ");
  Serial.println(zValue);

 
if(zValue>20000)
{
  digitalWrite(D6,LOW);
  
  }
  else
  {
    digitalWrite(D6,HIGH);
    }
  delay(1000);  // Wait for a second before reading again
}

void initializeMPU6050() {
  // Initialize MPU6050
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // Wake up the MPU6050
  Wire.endTransmission(true);
}

int readAccelerometerValue(int deviceAddress, int registerAddress) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(registerAddress);
  Wire.endTransmission(false);

  Wire.requestFrom(deviceAddress, 2, true);
  
  int value = Wire.read() << 8 | Wire.read();

  return value;
}
