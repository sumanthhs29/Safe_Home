#include<SoftwareSerial.h>                   //For GSM
SoftwareSerial mySerial(1,0);                //For GSM
int sms_count=0;
int Switch=6;
int sensor=7;
int buzzer=8;
int IN1=9;
int sensor_value;

void setup() {
  // put your setup code here, to run once:
pinMode(sensor,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(Switch,INPUT);
pinMode(IN1,OUTPUT);
Serial.begin(9600);

}


void loop() {
  // put your main code here, to run repeatedly:
sensor_value=digitalRead(sensor);
int S=digitalRead(Switch);
if(S==HIGH)
    {
      if(sensor_value==LOW)
          Light();
    }
else
  {
    if(sensor_value==LOW)
    {
      Check_Burglar();
      Check_Reset();
    }
  }
}

void Light()
{
  digitalWrite(IN1,HIGH);
  delay(2000);
  digitalWrite(IN1,LOW);
  
}
void Check_Burglar()
{
  sensor_value=digitalRead(sensor);
  if(sensor_value==LOW)           //IR Gives LOW value on detection 
  {

    tone(8, 1000, 500);
    while(sms_count<1)
    {
      SendTextMessage();
    }
  }
}

void Check_Reset()
{
  sms_count=0;
}

void SendTextMessage()
{
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+919620554255\"\r");
  delay(1000);
  mySerial.println("Intruder Alert");
  delay(200);
  mySerial.println((char)26);
  delay(1000);
  sms_count++;
  Serial.println("Message Sent");
}
