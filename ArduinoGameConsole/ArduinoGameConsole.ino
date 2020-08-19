/*
  Исходный код к проекту компактной игровой консоли на Atmega328p
  v1.0
*/

/* Дефайны для библиотек обьявляем ПЕРЕД их одключением */
#define OLED_SOFT_BUFFER_64

/* Дефайны для пинов */
#define BTN_OK    2
#define BTN_UP    3
#define BTN_DOWN  4
#define BTN_LEFT  8
#define BTN_RIGHT 9
#define OLED_PWR1 5
#define OLED_PWR2 6
#define OLED_PWR3 7

/* Библиотеки */
#include <directADC.h>
#include <EEPROM.h>
#include <GyverPower.h>
#include <GyverTimer.h>
#include <GyverButton.h>
#include <GyverOLED.h>

/* системные дефайны */
#define SYSTEM_DATA_ADDR 0  // По этому адресу храним системные настройки в EEPROM
#define APPS_NUM 1          // Количество приложений, ограничивает указатель
#define CONTR_INC 5         // Шаг регулировки яркости 
#define VCC_INC 5           // Шаг регулировки напряжения питания 
#define VCC_INT 300         // Период опроса напряжения питания в мс
#define BAT_EMPTY 2000      // Напряжение полностью севшей батарейки в мв
#define BAT_FULL 3100       // напряжение свежей батарейки в мв

/* обьекты библиотек */
GyverOLED oled;
GButton ok(BTN_OK, HIGH_PULL);
GButton up(BTN_UP, HIGH_PULL);
GButton down(BTN_DOWN, HIGH_PULL);
GButton left(BTN_LEFT, HIGH_PULL);
GButton right(BTN_RIGHT, HIGH_PULL);
GTimer vccTimer(MS);

/* структура для системных данных */
struct {
  uint8_t contrast;
  uint16_t internal_ref;
} systemData;


uint8_t charge = 0; // переменная для заряда 0-10

void setup() {
  adcInit();                                  // Настройка АЦП
  EEPROM.get(SYSTEM_DATA_ADDR, systemData);   // Читаем системные настройки из EEPROM
  oledEnable();                               // Включаем и инициализируем дисплей
  if (!digitalRead(BTN_OK)) {                 // Если при старте кнопка ОК нажата
    serviceMode();                            // Вызываем сервис мод
  }
  vccTimer.setInterval(VCC_INT);              // Установка периода опроса напряжения питания
}

void loop() {
  static uint8_t pointer = 1;                 // Переменная указатель в меню

  buttonsTick();     // Опрос кнопок
  batteryTick();     // Опрос батарейки

  if (up.isClick() or up.isStep()) {                // Клик или удержание кнопки
    pointer = constrain(pointer - 1, 1, APPS_NUM);  // Двигаем указатель
  }
  if (down.isClick() or down.isStep()) {
    pointer = constrain(pointer + 1, 1, APPS_NUM);
  }
  if (left.isClick() or left.isHold()) {
    systemData.contrast = constrain(systemData.contrast - CONTR_INC, 5, 255); // меняем яркость
    oled.setContrast(systemData.contrast);                                    // Отправляем яркость дисплею
    EEPROM.put(SYSTEM_DATA_ADDR, systemData);                                 // Сохраняем яркость в память
  }
  if (right.isClick() or right.isHold()) {
    systemData.contrast = constrain(systemData.contrast + CONTR_INC, 5, 255);
    oled.setContrast(systemData.contrast);
    EEPROM.put(SYSTEM_DATA_ADDR, systemData);
  }
  if (ok.isClick()) {     // Нажатие на ОК
    switch (pointer) {    // По указателю
      case 1:             // Вызываем нужное приложение
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        break;
    }
  }

  oled.clear();             // Очистить буфер дисплея
  oled.home();              // Установить курсор в (0,0)
  oled.print                // Вывод всех строк меню
  (F(
     "\n"
     " Flappy bird\n"
     // " Google dino\n"
     // " Simple pong\n"
     "\n"
     "\n"
     "\n"
     "\n"
   ));
  oled.setCursor(0, pointer); // Установить указатель на нужную строку
  oled.print(F(">"));         // напечатать указатель
  batteryPrint();             // Выводим индикатор на дисплей
  oled.update();              // Выводим буфер на дисплей
}


void oledEnable() {                        // включение оледа
  pinMode(OLED_PWR1, OUTPUT);              // пины как выход
  pinMode(OLED_PWR2, OUTPUT);
  pinMode(OLED_PWR3, OUTPUT);
  digitalWrite(OLED_PWR1, HIGH);           // подать на них +
  digitalWrite(OLED_PWR2, HIGH);
  digitalWrite(OLED_PWR3, HIGH);
  delay(50);                               // дать время дисплею прийти в себя
  oled.init(OLED128x64, 500);              // инициализировать дисплей
  oled.setContrast(systemData.contrast);   // отправить ему актуальную яркость
}

void oledDisable() {                      // выкл оледа
  digitalWrite(OLED_PWR1, LOW);
  digitalWrite(OLED_PWR2, LOW);
  digitalWrite(OLED_PWR3, LOW);
}

void buttonsTick() {  // опрос всех кнопок
  ok.tick();
  up.tick();
  down.tick();
  left.tick();
  right.tick();
}


void serviceMode() {    // сервис режим (калибровка опорного)
  uint16_t vcc = 5000;  // переменная для хранения реального напряжения питания
  while (1) {           // бесконечный цикл
    buttonsTick();      // опросить кнопки
    if (up.isClick() or up.isHold()) {  // нажатием или удержанием устанавливаем vcc
      vcc = constrain(vcc + VCC_INC, 2000, 5500);
    } if (down.isClick() or down.isHold()) {
      vcc = constrain(vcc - VCC_INC, 2000, 5500);
    } if (ok.isClick()) {                         // нажатие на ок
      EEPROM.put(SYSTEM_DATA_ADDR, systemData);   // сохраняет настройки
    }

    systemData.internal_ref = getVref(vcc);       // рассчитать значение опорного из напряжения питания

    oled.clear();                                 // вывод значений
    oled.home();
    oled.scale2X();
    oled.print(F("Vcc: "));
    oled.println(vcc);
    oled.print(F("Ref: "));
    oled.println(systemData.internal_ref);
    oled.scale1X();
    oled.print
    (F(
       "\n"
       "Press OK to save\n"
       "Press UP/DOWN to adj\n"
     ));
    oled.update();
  }
}

uint16_t getVref(uint16_t vcc) {    // чтение внуреннего опорного
  uint16_t buf = 0;                 // буфер для усредняющего фильтра
  for (uint8_t i = 0; i < 8; i++) { // цикл усредняющего фильтра
    _ADC.convert();                 // запустить преобразование ацп
    while (_ADC.isBusy());          // дождаться окончания
    buf += _ADC.read();             // прочитать ацп
  }
  buf >>= 3;                        // поделить на кол во итераций
  return ((uint32_t) vcc * buf) >> 10;  // рассчитать опорное
}

void adcInit() {                  // инициализация ацп
  _ADC.setReference(DEFAULT);     // опорное для ацп - vcc
  _ADC.setInput(ADC_BANDGAP);     // вход для ацп - внутреннее опорное
  _ADC.setPrescaler(ADC_PRESCALER_128); // самый медленный режим ацп
  _ADC.enable(true);              // включаем ацп
  delayMicroseconds(100);         // даем паузу
}

uint16_t getVcc() {               // чтение напряжения питания
  uint16_t buf = 0;
  for (uint8_t i = 0; i < 8; i++) { // читаем буфера
    _ADC.convert();
    while (_ADC.isBusy());
    buf += _ADC.read();
  }
  buf >>= 3;                      // аналогично сдвигаем буфер
  return (uint32_t)((systemData.internal_ref * 1024UL) / buf); // считаем напряжение питания
}

void batteryPrint() {         // вывод индикатора заряда
  oled.rect(117, 0, 127, 6);  // тело индикатора
  oled.line(116, 1, 116, 6);  // полосочка для красоты
  for (uint8_t i = 0; i < charge; i++) { // заполнение индикатора
    oled.line(127 - i, 0, 127 - i, 6);   // полосками
  }
}

void batteryTick() {          // опрос батарейки
  if (vccTimer.isReady()) {   // по таймеру
    charge = constrain(map(getVcc(), BAT_EMPTY, BAT_FULL, 0, 10), 0, 10); // преобразуем мин-макс напряжение батарейки в диапазон 0-10 и ограничиваем в этом диапазоне
  }
}
