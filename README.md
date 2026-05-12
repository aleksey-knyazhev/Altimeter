 # Высотомер парашютный цифровой, DIY

## Необходимые библиотеки

- U8g2
- Adafruit_BMP085_Unified
- Adafruit_Sensor-master

## Подключение OLED-дисплея

Схема подключения OLED-дисплея к Arduino Pro Mini через аппаратный SPI-интерфейс.

| OLED | Arduino Pro Mini |
| --- | --- |
| VCC | VCC |
| GND | GND |
| SCK (SCL) | Pin 13 |
| MOSI (SDA) | Pin 11 |
| CS | Pin 8 |
| DC | Pin 7 |

## Подключение модуля GY-68 BMP180

Схема подключения модуля GY-68 на микросхеме BMP180 к Arduino Pro Mini через I2C-интерфейс.

| GY-68 | Arduino Pro Mini |
| --- | --- |
| VIN | VCC |
| GND | GND |
| SCL | A5 |
| SDA | A4 |

## Скриншоты

### Общий вид

![Общий вид](Plain%20view.jpg)

### Интегральная схема

![Интегральная схема](Сircuit%20design.jpg)
