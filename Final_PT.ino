#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// define force resistive sensor pins
#define FRS_PIN_1 A0
#define FRS_PIN_2 A1
#define FRS_PIN_3 A2

const int addr = 0x27;
// Initialize the LCD
LiquidCrystal_I2C lcd_1(addr,16, 2);

// Variables to store the maximum values
int max_val_1 = 0;
int max_val_2 = 0;
int max_val_3 = 0;

void setup()
{
  // begin serial port
  Serial.begin(9600);

  // begin LCD
  lcd_1.init();
  lcd_1.setBacklight(HIGH);

  // Print "DDAK BAM START" on the LCD
  lcd_1.setCursor(0, 0);
  lcd_1.print("DDAK BAM START");
  lcd_1.setCursor(0, 1);
  lcd_1.print("READY ACTION");
    
  // set FRS pins as input pins
  pinMode(FRS_PIN_1, INPUT);
  pinMode(FRS_PIN_2, INPUT);
  pinMode(FRS_PIN_3, INPUT);

  // Wait for 2 seconds before clearing the LCD
  delay(2000);
  lcd_1.clear();
}

void loop()
{
  // read the values from the sensors
  int val_1 = analogRead(FRS_PIN_1);
  int val_2 = analogRead(FRS_PIN_2);
  int val_3 = analogRead(FRS_PIN_3);

  // Limit the maximum sensor value to 250
  val_1 = min(val_1, 250);
  val_2 = min(val_2, 250);
  val_3 = min(val_3, 250);

  // Remap the sensor values to the range 0 - 999
  val_1 = map(val_1, 0, 250, 0, 999);
  val_2 = map(val_2, 0, 250, 0, 999);
  val_3 = map(val_3, 0, 250, 0, 999);

  // check if any sensor value is not zero
  if (val_1 != 0 || val_2 != 0 || val_3 != 0) {

    // Update the maximum values
    max_val_1 = max(max_val_1, val_1);
    max_val_2 = max(max_val_2, val_2);
    max_val_3 = max(max_val_3, val_3);

    // Clear the LCD screen
    lcd_1.clear();

    // Print the current values to the LCD
    lcd_1.setCursor(0, 1);
    lcd_1.print("L");
    lcd_1.print(val_1);
    lcd_1.setCursor(5, 1);
    lcd_1.print("C");
    lcd_1.print(val_2);
    lcd_1.setCursor(10, 1);
    lcd_1.print("R");
    lcd_1.print(val_3);
      
    // Print the maximum values to the LCD
    lcd_1.setCursor(0, 0);
    lcd_1.print("L");
    lcd_1.print(max_val_1);
    lcd_1.setCursor(5, 0);
    lcd_1.print("C");
    lcd_1.print(max_val_2);
    lcd_1.setCursor(10, 0);
    lcd_1.print("R");
    lcd_1.print(max_val_3);

    // print the values to the serial port
    Serial.print("L");
    Serial.print(val_1);
    Serial.print("  C");
    Serial.print(val_2);
    Serial.print("  R");
    Serial.println(val_3);
    
    // Add a delay to synchronize LCD and Serial outputs
    delay(10);
  }

  delay(200); // Wait for 200 milliseconds
}
