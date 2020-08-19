#include <directADC.h>

/*------------------------------------------------------------------------------------- АЦП -------------------------------------------------------------------------------------------------*/
void DirectADC::enable(bool state) {
  ADCSRA = ADCSRA & 0b01111111 | state << 7; 			// Установить или сбросить бит ADEN, установка включает АЦП (true / false)
}

void DirectADC::setPrescaler(uint8_t prescaler) {
  ADCSRA = ADCSRA & 0b11111000 | prescaler;				// Загрузить делитель в биты ADPS0-ADPS2 (ADC_PRESCALER_2 /.../ ADC_PRESCALER_128)
}

void DirectADC::setResolution(bool resolution) {
  ADMUX = ADMUX & 0b11011111 | resolution << 5;			// Установить или сбросить бит ADLAR (ADC_RESOLUTION_8 / ADC_RESOLUTION_10)
}

void DirectADC::setReference(uint8_t reference) {
  ADMUX = ADMUX & 0b00111111 | reference << 6;			// Загрузить опорное в биты REFS0-REFS1 (EXTERNAL / DEFAULT / INTERNAL)
}

void DirectADC::setInput(uint8_t input) {
  ADMUX = ADMUX & 0b11100000 | input & 0b00011111;		// Загрузить младшие 5 бит конфигурации в биты MUX0-MUX4
#if defined(ADCSRB) && defined(MUX5)
  ADCSRB = ADCSRB & 0b11011111 | input & 0b00100000;	// При наличии загрузить 6й бит в MUX5
#endif
}

void DirectADC::interruptEnable(bool state) {
  ADCSRA = ADCSRA & 0b11110111 | state << 3;			// Установить или сбросить бит ADIE, установка включает прерывание готовности (true / false)
}

void DirectADC::clearFlag(void) {
  ADCSRA |= 1 << ADIF;									// Сбросить бит ADIF записью в него '1', если прерывание еще не было обработано, оно будет 'забыто'
}

void DirectADC::autoTrigger(bool state, uint8_t source) {
  ADCSRA = ADCSRA & 0b11011111 | state << 5;			// Установить или сбросить бит ADATE, установка включает триггер по событию (true / false)  
  ADCSRB = ADCSRB & 0b11111000 | source;				// Загрузить источник триггера в биты ADTS0 - ADTS1, эти биты выбирают триггер 
}

void DirectADC::convert(void) {	
  ADCSRA |= 1 << ADSC;									// Начать преобразование записью '1' в бит ADSC
}

void DirectADC::highSpeedMode(bool state) {
#if defined(__AVR_ATmega32U4__)
  ADCSRB = ADCSRB & 0b01111111 | state << 7;			// Установить или сбросить бит ADHSM, установка позвоялет работать на повышенной скорости (true / false) 
#endif
}

bool DirectADC::isBusy(void) {
  return (bool)(ADCSRA & (1 << ADSC));					// Вернуть значение бита ADSC, преобразование в процессе если бит установлен
}

bool DirectADC::readFlag(void) {
  return (bool)(ADCSRA & (1 << ADIF));					// Вернуть значение бита ADIF, прерывание произошло, но еще не было обработано если бит установлен
}

uint16_t DirectADC::read(void) {
  if (ADMUX & (1 << ADLAR)) {							// Если  требуются только младшие 8 бит
    return (uint8_t) ADCH;								// Читаем эти младшие 8 бит, выровненные по правому краю
  } return (uint16_t) ADC;								// Иначе читаем весь результат (10 бит) целиком
}		
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------------- Аналоговый компаратор ------------------------------------------------------------------------------*/
void DirectACOMP::enable(bool state) {
  ACSR = ACSR & 0b01111111 | state << 7;				// Установить или сбросить бит ACD, установка выключает компаратор (true / false)
}

void DirectACOMP::setNegInput(bool input) {
#if defined (__AVR_ATmega32U4__)
  ADCSRB = ADCSRB & 0b10111111 | ~input << 6;			// Для 32u4 логика обратная	
#else
  ADCSRB = ADCSRB & 0b10111111 | input << 6;			// Установить или сбросить бит ACME, установка подключает '-' вход к мультиплексору АЦП (ACOMP_AIN1 / ACOMP_MUX)	
#endif 
}

void DirectACOMP::setPosInput(bool input) {
  ACSR = ACSR & 0b10111111 | input << 6;				// Установить или сбросить бит ACBG, установка подключает '+' вход к внутреннему опорному 1.1В (ACOMP_AIN0 / INTERNAL)
}

void DirectACOMP::clearFlag(void) {
  ACSR |= 1 << ACI;										// Сбросить бит ACI записью в него '1', если прерывание еще не было обработано, оно будет 'забыто'
}

void DirectACOMP::interruptEnable(bool state, uint8_t mode) {
  ACSR = ACSR & 0b11110100 | (state << 3 | mode);		// Установить или сбросить бит ACIE, установка включает прерывание по событию mode (true / false, CHANGE / FALLING / RISING)
}

void DirectACOMP::connectToCaprute(bool state) {
  ACSR = ACSR & 0b11111011 | state << 2;				// Установить или сбросить бит ACIC, установка подключает выход компаратора к схеме захвата 
}

bool DirectACOMP::read(void) {
  return (bool) ACSR & (1 << ACO);						// Вернуть значение на выходе компаратора (бит ACO), если напряжение на '+' > '-' вернет true
}

bool DirectACOMP::readFlag(void) {
  return (bool) ACSR & (1 << ACI);						// Вернуть значение бита ACI, прерывание произошло, но еще не было обработано если бит установлен
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


DirectADC _ADC = DirectADC();
DirectACOMP _ACOMP = DirectACOMP();