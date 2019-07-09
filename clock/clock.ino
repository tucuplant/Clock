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
int hora;


void setup() {
  Serial.begin(9600);
  
   rtc.begin();
   //BUCLE DE TIEMPO
   int count=0,v,h,m,s;
   char* command = strtok(__TIME__, ":");
   while (command != 0) {
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
  
  lcd.begin(16, 2); 
}

void handleIntervalo(int hora){
   if((hora<21 && hora>7)){
    luz=true;
    }else {
    luz=false;
  }
}

void loop() {
  bool switche=false;
  lcd.setCursor(0, 0);
  lcd.print("Hora:");
  lcd.setCursor(5, 0);
  // print the number of seconds since reset:
  lcd.print(rtc.getTimeStr());
  lcd.setCursor(0, 1);

  handleIntervalo(rtc.getTime().hour);
 
    if(luz==true){
      lcd.print("Encendido");
      if(digitalRead(9) == LOW)
      digitalWrite(9, HIGH);//LUZ ENCENDIDA
    }else if(luz==false){
      lcd.print("Apagado");
      if(digitalRead(9) == HIGH)
      digitalWrite(9, LOW);//LUZ ENCENDIDA
  }
   
  

}
