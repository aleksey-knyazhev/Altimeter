 *   Высотомер парашютный цифровой, Княжева
 *   https://vk.com/wall5514303_583
 *   
 *   Для работы Вам понадобятся библиотеки:
 *   U8g2
 *   Adafruit_BMP085_Unified
 *   Adafruit_Sensor-master
 *    
 *   Схема подключения OLED-дисплея через аппаратный SPI интерфейс.
 *   OLED        = Arduino Pro Mini
 *   -----------------------------
 *   VCC         = VCC
 *   GND         = GND
 *   SCK (SCL)   = Pin 13
 *   MOSI (SDA)  = Pin 11
 *   CS          = Pin 8
 *   DC          = Pin 7
 *   
 *   
 *   Схема подключения модуля GY-68 на микросхеме BMP180 (датчик атмосферного давления и температуры) через I2C интерфейс
 *   GY-68       = Arduino Pro Mini
 *   -----------------------------
 *   VIN         = VCC
 *   GND         = GND
 *   SCL         = A5
 *   SDA         = A4
