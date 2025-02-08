#include <Adafruit_LiquidCrystal.h>

int buttonPin = 2;
int buttonState = 0;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 5;

int count = 0;

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
  lcd_1.begin(16, 2);
  lcd_1.print("Count: ");
  pinMode(buttonPin, INPUT);
}

void loop()
{
  int reading = digitalRead(buttonPin);

  // Check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Debounce the button
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // If the button is pressed, increment the count
      if (buttonState == HIGH) {
        count++;
        lcd_1.setCursor(7, 0); // Set cursor to the position after "Count: "
        lcd_1.print(count);    // Update the count on the LCD
      }
    }
  }

  lastButtonState = reading;

  // Control the backlight based on button state
  if (buttonState == HIGH) {
    lcd_1.setBacklight(1); // Turn on backlight
  } else {
    lcd_1.setBacklight(0); // Turn off backlight
  }
}
