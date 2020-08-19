#pragma once
#include <Arduino.h>
#include "defs.h"

/*
   Библиотека для прямого использования аналоговой части МК ATmega 
   Ручная инициализация и полный контроль за АЦП и встроенным аналоговым компаратором
   Возможно использование и на других МК (требуется корректировка констант)
   Доступен весь перечисленный в datasheet функционал
   
   v2.0  - Полный рерайт, обернута в класс, расширен функционал и список поддерживаемых МК (НЕ СОВМЕСТИМА С ПРЕДЫДУЩЕЙ ВЕРСИЕЙ)
   Для МК | ATmega48/88/168/328p | ATmega32u4 | ATmega1280/2560 |  
   by Egor 'Nich1con' Zakharov
*/ 





class DirectADC {
  public:
    void enable(bool state);						// Включение / выключение АЦП (default: выключен)	 	
    void setPrescaler(uint8_t prescaler);			// Установка делителя частоты АЦП (default: ADC_PRESCALER_2)	
    void setResolution(bool resolution);			// Установка разрешения АЦП (default: ADC_RESOLUTION_10)
    void setReference(uint8_t reference);			// Установка опорного напряжения АЦП (default: EXTERNAL)
    void setInput(uint8_t input);					// Установка мультиплексора АЦП (default: ADC0)
    void interruptEnable(bool state);				// Включение / выключение прерывания готовности АЦП (default: выключен)
    void clearFlag(void);							// Очистка флага прерывания АЦП (default: очищен)
    void autoTrigger(bool state, uint8_t source);	// Включения триггера АЦП (default: выключен, FREE_RUN)
    void convert(void);						// Старт преобразования АЦП (default: АЦП остановлен)
    void highSpeedMode(bool state);					// Высокоскоростной режим АЦП - только для ATmega32u4(default: выключен)
    bool isBusy(void);								// Вернуть текущее состояние АЦП (true - преобразование в процессе)
    bool readFlag(void);							// Вернуть состояние флага прерывания АЦП (default: очищен)
    uint16_t read(void);							// Прочитать результат преобразования АЦП (10 или 8 бит)
  private:
};


class DirectACOMP {
  public:
    void enable(bool state);						// Включение / выключение компаратора (default: включен)
    void setNegInput(bool input);					// Подключить '-' компаратора к AIN1 или ACOMP_MUX (любому аналог. входу)
    void setPosInput(bool input);					// Подключить '+' компаратора к AIN0 или INTERNAL (внутреннему опорному)
    void clearFlag(void);							// Очистка флага прерывания компаратора (default: очищен)
    void interruptEnable(bool state, uint8_t mode);	// Включение / выключение прерывания компаратора (default: выключен , CHANGE)
    void connectToCaprute(bool state);				// Подключить выход компаратора к схеме захвата (default: выключен)	
    bool read(void);								// Прочитать состояние выхода компаратора (default: неизвестно)
    bool readFlag(void);							// Вернуть состояние флага прерывания компаратора (default: очищен)
  private:
};

extern DirectADC _ADC;
extern DirectACOMP _ACOMP;