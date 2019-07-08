#include <Time.h>
#include <TimeLib.h>
#include <DS3231.h>
#include <LiquidCrystal.h> // Incluye la Libreria LiquidCrystal
//Objeto Liquid Crystal
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

DS3231  rtc(SDA, SCL);
time_t t;
int compiled_time[3];
bool luz=false,oxigenador=false;

/*int parseTime(char* times,int pos){
   
   int count=0,v;
   char* command = strtok(times, ":");
 
   while (command != 0) {

      if(count==pos){
        v=atoi(command); 
        Serial.println(command);

        return v; 
      }

      command = strtok(0, ":");
       Serial.println(command);
      count++;
   }
   
}*/

int pitidoPin = 9;
int luzPin = 3 ;

void setup() {
  Serial.begin(9600);
  
  pinMode(pitidoPin, OUTPUT);
  pinMode(luzPin, OUTPUT);
  
  rtc.begin();
  // set up the LCD's number of columns and rows:
   /*int h = parseTime(__TIME__,0);
   int m = parseTime(__TIME__,1);
   int s = parseTime(__TIME__,2);*/
  
 //lcd.print(rtc.getTimeStr());
 
   //BUCLE DE TIEMPO
   int count=0,v,h,m,s;
   char* command = strtok(__TIME__, ":");
   while (command != 0) {
 Serial.print(command);
      if(count==0){
        h=atoi(command); 
      }
      if(count==1){
        m=atoi(command); 
      }
      if(count==2){
        s=atoi(command); 
      }

      command = strtok(0, ":");
     
      count++;
   }
   //BUCLE DE TIEMPO

      
  rtc.setTime(h, m, s);
     
  //rtc.setDate(30, 5, 2019); 


  
}

void loop() {



 char *hello=rtc.getTimeStr();
  
 lcd.begin(16,2);// every second
 lcd.setCursor(0,0);
 lcd.print("Time ");
  //lcd.print(s_hora);
  
  
  lcd.setCursor(0,1);
  lcd.print(hello);
  delay(20);
  lcd.clear();
  
  int hora= rtc.getTime().hour;
  Serial.println(hora);
  if((hora<22 && hora>7)){
    //digitalWrite(9, HIGH);//LUZ ENCENDIDA
  }else {
    //digitalWrite(9, LOW);//LUZ APAGADA
  }
 

 

}
