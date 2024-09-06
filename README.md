# Security System with Password

## Description

This project demonstrates a simple password-protected security system using an Arduino, a 4x3 keypad, and a 16x2 LCD display. The user inputs a password through the keypad, and if the entered password matches the predefined one, the system grants access by unlocking the door. If the password is incorrect, access is denied.

## Components

- Arduino Uno
- 4x3 Keypad
- 16x2 LCD Display
- Relay or door lock system (connected to the Arduino pin for unlocking)
- Jumper wires
- Breadboard

## Libraries Required

- **Keypad.h**: For interfacing with the keypad.
- **LiquidCrystal.h**: For handling the 16x2 LCD display.

## Wiring Diagram

| Component           | Arduino Pin  |
|---------------------|--------------|
| Keypad Row 1        | 2            |
| Keypad Row 2        | 3            |
| Keypad Row 3        | 4            |
| Keypad Row 4        | 5            |
| Keypad Col 1        | 6            |
| Keypad Col 2        | 7            |
| Keypad Col 3        | 8            |
| LCD RS              | 9            |
| LCD Enable          | 10           |
| LCD D4              | 11           |
| LCD D5              | 12           |
| LCD D6              | 13           |
| LCD D7              | A0           |
| Door Control (Relay) | A1           |

## Code

```cpp
#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 10, 11, 12, 13, A0);
#define pintu A1

const byte ROWS = 4;  // 4 baris
const byte COLS = 3;  // 3 kolom
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};  // Koneksi baris ke pin Arduino
byte colPins[COLS] = {6, 7, 8};     // Koneksi kolom ke pin Arduino
char pw[3] = {'1', '2', '3'};       // Predefined password
char kp[3];                         // Array to store entered password
byte u = 0;                         // Password character index

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);  // Baud rate 9600 bps
  lcd.begin(16, 2);
  lcd.print("Masukkan Password");
  lcd.setCursor(0, 1);
  pinMode(pintu, OUTPUT);  // Set the pin controlling the door lock
}

void loop() {
  char key = keypad.getKey();  // Baca keypad
  
  if (key != NO_KEY) {  // Jika ada tombol ditekan
    Serial.println(key);  // Kirim tombol ke serial
    lcd.print('*');       // Tampilkan bintang di LCD (untuk privasi)
    
    // If 3 characters have been entered
    if (u == 3) {
      u = 0;  // Reset the index for next input
      
      // Check if entered password matches predefined password
      if ((kp[0] == '1') && (kp[1] == '2') && (kp[2] == '3')) {
        digitalWrite(pintu, HIGH);  // Unlock the door
        lcd.setCursor(0, 1);
        lcd.print("Password Benar ");
      } else {
        digitalWrite(pintu, LOW);  // Keep the door locked
        lcd.setCursor(0, 1);
        lcd.print("Password Salah ");
      }
    } else {
      kp[u] = key;  // Store entered key in password array
      u++;          // Increment the password index
    }
  }
}
```

## How It Works

1. Keypad Input: The user is prompted to enter a 3-digit password via the 4x3 keypad. Each key press is represented as a * on the LCD for privacy.
2. Password Verification: After 3 digits are entered, the system checks if the input matches the predefined password ('123' in this case).
3. Access Control:
    - If the password is correct, a signal is sent to unlock the door (represented by digitalWrite(pintu, HIGH)).
    - If the password is incorrect, the door remains locked and an error message is displayed on the LCD.
4. LCD Display: The LCD displays "Masukkan Password" initially, then either "Password Benar" (Correct Password) or "Password Salah" (Incorrect Password) after the input is processed.

## Setup Instructions

- Wiring: Connect the keypad, LCD, and relay (door lock) as per the wiring diagram.
- Upload Code: Upload the provided code to your Arduino using the Arduino IDE.
- Testing: When powered on, the LCD will prompt for a password. Enter the password using the keypad to unlock the door.

## Applications

- A simple security system for doors or other access-controlled areas.
- Educational tool to demonstrate password-based systems with microcontrollers.
- Can be expanded to support multiple users or passwords.