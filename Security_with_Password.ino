#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 10, 11, 12, 13, A0);
#define pintu A1

const byte ROWS = 4; //4 baris
const byte COLS = 3; //3 kolom
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //koneksi baris ke pin Arduino
byte colPins[COLS] = {6, 7, 8}; //koneksi kolom ke pin Arduino
char pw[3]={'1','2','3'};
char kp[3];
byte u;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600); //baud rate 9600 bps
  lcd.begin(16, 2);
  lcd.print("Masukkan Password");
  lcd.setCursor(0,1);
}
  
void loop(){
  char key = keypad.getKey();//baca keypad
  
  if (key != NO_KEY){ //jika ada tombol ditekan
    Serial.println(key);//kirim tombol ke serial
    lcd.print('*');
    if(u==3){
      u=0;
      if((kp[0]=='1')&&(kp[1]=='2')&&(kp[2]=='3')){
        digitalWrite(pintu,HIGH);
        lcd.setCursor(0,1);
        lcd.print("Password Benar");
        }
      else {
        digitalWrite(pintu,LOW);
        lcd.setCursor(0,1);
        lcd.print("Password Salah");
        }
      }
    else{
      kp[u]=key;
      u++;
    }
  }
}

