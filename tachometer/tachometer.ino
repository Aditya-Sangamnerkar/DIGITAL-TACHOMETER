#include <DS3231.h>
#include <SD.h>
#include<SPI.h>
DS3231 rtc(SDA,SCL);
float value=0;
float rev=0;
int rpm;
int oldtime=0;
int time;
int sum; 
int i;
File myFile;
void isr() 
{
rev++;
}
 
void setup()
{
Serial.begin(9600);
attachInterrupt(0,isr,RISING); 

rtc.begin();
Serial.print("Initializing SD card...");
if (!SD.begin(10)) {
Serial.println("initialization failed!");
while (1);
}
Serial.println("initialization done.");


}

/*char* filename()
{
    char fname[] = rtc.getDateStr();
    fname.concat(".txt");
    return fname;  
} */

void loop()
{
delay(10000);
detachInterrupt(0); 
time=millis()-oldtime; 
rpm = (rev/time)*60000;
oldtime=millis(); 
rev=0;
sum+=rpm;
i++;
if(i == 6)
{
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
 
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  
  Serial.print(rtc.getTimeStr());
  Serial.print(" --> ");
  Serial.println(sum/6);
  myFile = SD.open("test.txt", FILE_WRITE); 
  myFile.println(rtc.getTimeStr());
  myFile.print(" --> ");
  myFile.print(sum/6);
  myFile.close();
  sum=0;
  i=0;
  
}


attachInterrupt(0,isr,RISING);
}
