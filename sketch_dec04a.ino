  
  #include <dht.h>
  #include <LiquidCrystal.h>
  const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  //PIN-uri ramase: 8, 6, 2, 1
  dht DHT;
  #define DHT11_PIN 7

void setup() {
  lcd.begin(16,2);
  pinMode(13, INPUT);
  pinMode(10, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9 , INPUT);
  pinMode(2, OUTPUT); 
}

void loop() {
  int temp = 24;
  int fan = 2;
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Set: ");
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(8,1);
  lcd.print(" Fan:");
  delay(2000);
  if(DHT.temperature >= temp)
    {
      digitalWrite(10, HIGH);
    }
   else
    {
      digitalWrite(10, LOW); 
    }
  if(digitalRead(13)== HIGH)
    {
      temp=temp+1;
      delay(500);
    }
  if(digitalRead(10)== HIGH)
    {
      temp=temp-1;
      delay(500);
    }
  if(digitalRead(6) == HIGH)
    {
      fan++;
      if(fan==1){
        lcd.setCursor(14,1);
        lcd.print((char)219);
      }
      if(fan==2){
        lcd.setCursor(15,1);
        lcd.print((char)219);
      }
      delay(500);
      if(fan==3) {
        lcd.setCursor(14,1);
        lcd.print("  ");
        fan=0;
      }
      while((fan==1) || (fan==2))
      {
        digitalWrite(8, HIGH); 
      }
    }
  while((digitalRead(13)== LOW) && (digitalRead(9)== LOW))
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Umiditate: ");
      lcd.print(DHT.humidity);
      lcd.print("%");
      delay(2000);
    }
    
}
