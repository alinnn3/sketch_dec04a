  
  #include <dht.h> //librarie pentru senzorul de temperatura
  #include <LiquidCrystal.h> //librarie pentru ecran LCD
  const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // intializare ecran LCD
  dht DHT;
  #define DHT11_PIN 7  //definire pin care monitorizeaza temperatura si umiditatea
  int fa=0;
  int temp=0;
  float chk;
  int start = 0; 
  unsigned long previousTime = 0; //declarare variabile
void setup() {
  lcd.begin(16,2);
  pinMode(13, INPUT);
  pinMode(10, INPUT);
  pinMode(8, OUTPUT);
  pinMode(6 , INPUT);
  pinMode(52, OUTPUT); // definire pinului daca este de intrare sau iesire
  lcd.setCursor(0,0); 
 
}

void loop() {
if (start==2){
  start=0;
}
if(digitalRead(6)== HIGH && digitalRead(13)== HIGH){ // daca butonul 6 si butonul 13 sunt apasate simultan start primeste +1
   
  start++;
  delay(500);
  
 
}
if(start==1){ //daca start egal cu 1 porneste tot codul
 digitalWrite(8, HIGH);
if(digitalRead(6)== HIGH)
  {
    temp++;
    delay(300);
  }
 
 if(temp==36)
  {
  temp=35;
  }
  
if(digitalRead(10)== HIGH)
    {
      temp=temp-1;
     delay(500);
    }
  
if (temp==-1)
  {
    temp=0;
  }


  lcd.setCursor(0,0); // aici se seteaza de unde se incepe sa scrie
  lcd.print("Temp: "); // aici se scrie
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Set:");
  lcd.print(temp);
  lcd.setCursor(6,1);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(8,1);
  lcd.print(" Fan:");
  
  
if(digitalRead(13) == HIGH) //aici daca butonu 13 e apasat se fac urmatoarele fa primeste +1
    {
      fa++;
      delay(200);
    }
    
if(fa>=1)
     {   
      lcd.setCursor(13,1);
      lcd.print((char)219);
     }
     
if(fa>=2)
      {
        lcd.setCursor(14,1);
        lcd.print((char)219);
      }
     
if(fa>=3)
      {
        lcd.setCursor(15,1);
        lcd.print((char)219);
      }
    
   
if (fa==4){
      lcd.setCursor(13,1);
      lcd.print("   ");
      fa=0;
    }
  
if(digitalRead(6)== HIGH && digitalRead(10)== HIGH)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Umiditate:");
    lcd.print(DHT.humidity);
    lcd.print("%");
    delay(20);  
  }
else
  {
    lcd.setCursor(13,0);
    lcd.print("   ");
  }
  
unsigned long currentTime = millis();
if (currentTime - previousTime >= 2000){
  chk = DHT.read11(DHT11_PIN);
  
  previousTime = currentTime;
}
if (temp > DHT.temperature){
  digitalWrite(52, HIGH);
}
else{
  digitalWrite(52, LOW);
}

}
else{
  lcd.clear();
  digitalWrite(8, LOW);
}

}
