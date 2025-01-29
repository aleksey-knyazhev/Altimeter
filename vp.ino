/*   
 *   Высотомер парашютный цифровой, DIY
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
 *   
 */

#include <Arduino.h>
#include <U8x8lib.h>                 // Библиотека для работы с монохромным дисплеем. В целях повышения скорости работы, используется версия U8x8 библиотеки U8g2
#include <Wire.h>                    // Библиотека для работы с интерфейсом I2C
#include <Adafruit_BMP085_U.h>       // Библиотека для работы с датчиком давления BMP085

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_SSD1306_128X64_NONAME_4W_HW_SPI u8x8(/* cs=*/ 8, /* dc=*/ 7, /* reset=*/ U8X8_PIN_NONE);    // Объект для работы с экраном
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);                                    // Объект для работы с датчиком давления

int altitude = 0;
int previousAltitude = -9999;
float seaLevelPressure = 0;

void setup(void)
{
  /* Инициализация модуля дисплея */
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_inb46_4x8_n);

  Serial.begin(9600);
  /* Проверка связи с датчиком давления */
  if(!bmp.begin())
  {
    Serial.print("Датчик давления не обнаружен. Проверьте подключение датчика или его I2C-адрес");
    /* Сигнализируем об этом пользователю потухшим экраном */
    while(1);
  }
  
  /* Задаем стартовую точку отсчета атмосферного давления */
  getCurrentSeaLevelPressureAsAZerroPoint();
}
           
void loop() {
  previousAltitude = altitude;
  getAltitude();
  /* Задаем контрастность дисплея */
  u8x8.setContrast(getContrast());
  /* Задаем стартовую позицию разрядов на экране */
  u8x8.setCursor(getCursorPosition(), 0);
  /* Очищаем экран, при необходимости */ 
  clearDisplayIfNecessity();
  u8x8.print(altitude);
}

void clearDisplayIfNecessity(void) {
  if (getCountsOfDigits(previousAltitude) != getCountsOfDigits(altitude))
  {
    u8x8.clearDisplay();
  }
}

int getCountsOfDigits(int n) {
  if (n >= 0) {
    if (n < 100) {
        if (n < 10) {
            return 1;
        } else {
            return 2;
        }
    } else {
        if (n < 1000) {
            return 3;
        } else {
            return 4;
        }
    } 
  } else {
    if (n > -10) {
          return 2;
    } else if (n > -100) {
          return 3;
    } else {
          return 4;
    } 
  }    
}

void getCurrentSeaLevelPressureAsAZerroPoint(void) {
  sensors_event_t event;
  bmp.getEvent(&event);
 
  if (event.pressure)
  {
    seaLevelPressure = event.pressure;
  }
  else
  {
    Serial.println("Ошибка сенсора");
    /* Сигнализируем об этом пользователю потухшим экраном */
    while(1);
  }
}

void getAltitude(void) 
{
  sensors_event_t event;
  bmp.getEvent(&event);
 
  if (event.pressure)
  {
    float temperature;
    bmp.getTemperature(&temperature);
    /* Получение значения высоты */ 
    altitude = bmp.pressureToAltitude(seaLevelPressure, event.pressure, temperature);

    /*Serial.print("Давление: ");
    Serial.print(event.pressure);
    Serial.println(" гПа");
    Serial.print("Температура: ");
    Serial.print(temperature);
    Serial.println(" С");
    Serial.print("Высота: ");
    Serial.print(altitude); 
    Serial.println(" м");
    Serial.println("");*/
  }
  else
  {
    Serial.println("Ошибка сенсора");
    /* Сигнализируем об этом пользователю потухшим экраном */
    while(1);
  }
}

int getContrast(void) {
    if (altitude >= 5){
      return 255;
    }
    else{
      return 0;
    }
}

int getCursorPosition(void) {
    if (altitude >= 1000){
      return 0;
    }
    else if (altitude >= 100){
      return 4;
    }
    else if (altitude >= 10){
      return 8;
    }
    else if (altitude >= 0){
      return 12;
    }
    else if (altitude < -100){
      return 0;
    }
    else if (altitude < -10){
      return 4;
    }
    else if (altitude < 0){
      return 8;
    }
    return 0;
}
