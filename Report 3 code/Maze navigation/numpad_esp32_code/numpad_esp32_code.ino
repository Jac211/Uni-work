#include <Wire.h>
#include <Keypad.h>

// include the library code:
#include <LiquidCrystal.h>
#define I2C_SDA 21
#define I2C_SCL 22
#define I2C_SLAVE_ADDR 0x04

 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(32, 33, 25, 26, 27, 14);

#define ROW_NUM     4 // four rows
#define COLUMN_NUM  3 // three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pin_rows[ROW_NUM] = {15,2, 0, 4}; // GIOP18, GIOP5, GIOP17, GIOP16 connect to the row pins
byte pin_column[COLUMN_NUM] = {16, 17, 5};  // GIOP4, GIOP0, GIOP2 connect to the column pins

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup() {
  Serial.begin(10);
  lcd.begin(16,2);
  //lcd starting message
  lcd.setCursor(0,0);
  lcd.print("2=Fwd  8=Bwd");
  lcd.setCursor(0,1);
  lcd.print("4=Left  6=Right");
}

void loop() {
  Wire.beginTransmission(I2C_SLAVE_ADDR);  
  char key = keypad.getKey();
  
  if (key) {
    Serial.println(key);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print(key);
    delay(9);
    Wire.write(key);
    Wire.endTransmission();
  }
}