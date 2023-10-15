#include "Lcd16x20Display.hpp"


Lcd16x20Display::Lcd16x20Display(int I2cAddr) :
	lcd(I2cAddr, 20, 4)
{
	lcd.init();
	lcd.backlight();
	lcd.print("init...");
	lcd.home();
}

void Lcd16x20Display::display(Meteo *meteo) {
	lcd.setCursor(0, 0);
	lcd.print("                ");
	lcd.setCursor(0, 0);
	lcd.printf("%.2fC %.2f%%", meteo->temperature, meteo->humidity);
}
void Lcd16x20Display::display(const char *message) {
	lcd.setCursor(0, 1);
	lcd.print("                ");
	lcd.setCursor(0, 1);
	lcd.print(message);
}