#pragma once

/*
  Все варианты входов ацп в двух вариантах:
  "Ардуиновский" - (привязан к пинам платы)
  "Авровский" - (Привязан к выводам мк, см. datasheet на мк)
*/ 


#define ADC_RESOLUTION_8	1
#define ADC_RESOLUTION_10	0

#define ADC_PRESCALER_2		1
#define ADC_PRESCALER_4		2
#define ADC_PRESCALER_8		3
#define ADC_PRESCALER_16	4
#define ADC_PRESCALER_32	5
#define ADC_PRESCALER_64	6
#define ADC_PRESCALER_128	7

#if defined (__AVR_ATmega1280__) || defined (__AVR_ATmega2560__)

/* "Ардуиновский" вариант */
#define ADC_A0				0
#define ADC_A1				1
#define ADC_A2				2
#define ADC_A3				3
#define ADC_A4				4
#define ADC_A5				5
#define ADC_A6				6
#define ADC_A7				7
#define ADC_A0_A0_10X		8
#define ADC_A1_A0_10X		9
#define ADC_A0_A0_200X		10
#define ADC_A1_A0_200X		11
#define ADC_A2_A2_10X		12
#define ADC_A3_A2_10X		13
#define ADC_A2_A2_200X		14
#define ADC_A3_A2_200X		15
#define ADC_A0_A1_1X		16
#define ADC_A1_A1_1X		17
#define ADC_A2_A1_1X		18
#define ADC_A3_A1_1X		19
#define ADC_A4_A1_1X		20
#define ADC_A5_A1_1X		21
#define ADC_A6_A1_1X		22
#define ADC_A7_A1_1X		23
#define ADC_A0_A2_1X		24
#define ADC_A1_A2_1X		25
#define ADC_A2_A2_1X		26
#define ADC_A3_A2_1X		27
#define ADC_A4_A2_1X		28
#define ADC_A5_A2_1X		29
#define ADC_BANDGAP			30
#define ADC_GND				31
#define ADC_A8				32
#define ADC_A9				33
#define ADC_A10				34
#define ADC_A11				35
#define ADC_A12				36
#define ADC_A13				37
#define ADC_A14				38
#define ADC_A15				39
#define ADC_A8_A8_10X		40
#define ADC_A9_A8_10X		41
#define ADC_A8_A8_200X		42
#define ADC_A9_A8_200X		43
#define ADC_A10_A10_10X		44
#define ADC_A11_A10_10X		45
#define ADC_A10_A10_200X	46
#define ADC_A11_A10_200X	47
#define ADC_A8_A9_1X		48
#define ADC_A9_A9_1X		49
#define ADC_A10_A9_1X		50
#define ADC_A11_A9_1X		51
#define ADC_A12_A9_1X		52
#define ADC_A13_A9_1X		53
#define ADC_A14_A9_1X		54
#define ADC_A15_A9_1X		55
#define ADC_A8_A10_1X		56
#define ADC_A9_A10_1X		57
#define ADC_A10_A10_1X		58
#define ADC_A11_A10_1X		59
#define ADC_A12_A10_1X		60
#define ADC_A13_A10_1X		61
#define ACOMP_D5			0

/* "Авровский" вариант */
#define ADC0				0
#define ADC1				1
#define ADC2				2
#define ADC3				3
#define ADC4				4
#define ADC5				5
#define ADC6				6
#define ADC7				7
#define ADC0_ADC0_10X		8
#define ADC1_ADC0_10X		9
#define ADC0_ADC0_200X		10
#define ADC1_ADC0_200X		11
#define ADC2_ADC2_10X		12
#define ADC3_ADC2_10X		13
#define ADC2_ADC2_200X		14
#define ADC3_ADC2_200X		15
#define ADC0_ADC1_1X		16
#define ADC1_ADC1_1X		17
#define ADC2_ADC1_1X		18
#define ADC3_ADC1_1X		19
#define ADC4_ADC1_1X		20
#define ADC5_ADC1_1X		21
#define ADC6_ADC1_1X		22
#define ADC7_ADC1_1X		23
#define ADC0_ADC2_1X		24
#define ADC1_ADC2_1X		25
#define ADC2_ADC2_1X		26
#define ADC3_ADC2_1X		27
#define ADC4_ADC2_1X		28
#define ADC5_ADC2_1X		29
#define ADC_BANDGAP			30
#define ADC_GND				31
#define ADC8				32
#define ADC9				33
#define ADC10				34
#define ADC11				35
#define ADC12				36
#define ADC13				37
#define ADC14				38
#define ADC15				39
#define ADC8_ADC8_10X		40
#define ADC9_ADC8_10X		41
#define ADC8_ADC8_200X		42
#define ADC9_ADC8_200X		43
#define ADC10_ADC10_10X		44
#define ADC11_ADC10_10X		45
#define ADC10_ADC10_200X	46
#define ADC11_ADC10_200X	47
#define ADC8_ADC9_1X		48
#define ADC9_ADC9_1X		49
#define ADC10_ADC9_1X		50
#define ADC11_ADC9_1X		51
#define ADC12_ADC9_1X		52
#define ADC13_ADC9_1X		53
#define ADC14_ADC9_1X		54
#define ADC15_ADC9_1X		55
#define ADC8_ADC10_1X		56
#define ADC9_ADC10_1X		57
#define ADC10_ADC10_1X		58
#define ADC11_ADC10_1X		59
#define ADC12_ADC10_1X		60
#define ADC13_ADC10_1X		61
#define ACOMP_MUX			1
#define ACOMP_AIN1			0
#define ACOMP_AIN0			0

#elif defined (__AVR_ATmega32U4__)

/* "Ардуиновский" вариант */
#define ADC_A5				0
#define ADC_A4				1
#define ADC_A3				4
#define ADC_A2				5
#define ADC_A1				6
#define ADC_A0				7
#define ADC_A4_A5_10X 		9
#define ADC_A4_A5_200X 		11
#define ADC_A5_A4_1X 		16
#define ADC_A3_A4_1X 		20
#define ADC_A2_A4_1X 		21
#define ADC_A1_A4_1X 		22
#define ADC_A0_A4_1X 		23
#define ADC_BANDGAP			30
#define ADC_GND				31
#define ADC_ADC8			32
#define ADC_ADC9			33
#define ADC_A40				34
#define ADC_A41				35
#define ADC_A42				36
#define ADC_A43				37
#define ADC_A4_A5_40X 		38
#define ADC_A3_A5_10X		40
#define ADC_A2_A5_10X		41
#define ADC_A1_A5_10X		42
#define ADC_A0_A5_10X		43
#define ADC_A3_A4_10X		44
#define ADC_A2_A4_10X		45
#define ADC_A1_A4_10X		46
#define ADC_A0_A4_10X		47
#define ADC_A3_A5_40X		48
#define ADC_A2_A5_40X		49
#define ADC_A1_A5_40X		50
#define ADC_A0_A5_40X		51
#define ADC_A3_A4_40X		52
#define ADC_A2_A4_40X		53
#define ADC_A1_A4_40X		54
#define ADC_A0_A4_40X		55
#define ADC_A3_A5_200X		56
#define ADC_A2_A5_200X		57
#define ADC_A1_A5_200X		58
#define ADC_A0_A5_200X		59
#define ADC_A3_A4_200X		60
#define ADC_A2_A4_200X		61
#define ADC_A1_A4_200X		62
#define ADC_A0_A4_200X		63
#define ACOMP_D7			0
#define ACOMP_MUX 			1

/* "Авровский" вариант */
#define ADC0				0
#define ADC1				1
#define ADC4				4
#define ADC5				5
#define ADC6				6
#define ADC7				7
#define ADC1_ADC0_10X 		9
#define ADC1_ADC0_200X 		11
#define ADC0_ADC1_1X 		16
#define ADC4_ADC1_1X 		20
#define ADC5_ADC1_1X 		21
#define ADC6_ADC1_1X 		22
#define ADC7_ADC1_1X 		23
#define ADC_BANDGAP			30
#define ADC_GND				31
#define ADC8				32
#define ADC9				33
#define ADC10				34
#define ADC11				35
#define ADC12				36
#define ADC13				37
#define ADC1_ADC0_40X 		38
#define ADC_THERMOMETER		39
#define ADC4_ADC0_10X		40
#define ADC5_ADC0_10X		41
#define ADC6_ADC0_10X		42
#define ADC7_ADC0_10X		43
#define ADC4_ADC1_10X		44
#define ADC5_ADC1_10X		45
#define ADC6_ADC1_10X		46
#define ADC7_ADC1_10X		47
#define ADC4_ADC0_40X		48
#define ADC5_ADC0_40X		49
#define ADC6_ADC0_40X		50
#define ADC7_ADC0_40X		51
#define ADC4_ADC1_40X		52
#define ADC5_ADC1_40X		53
#define ADC6_ADC1_40X		54
#define ADC7_ADC1_40X		55
#define ADC4_ADC0_200X		56
#define ADC5_ADC0_200X		57
#define ADC6_ADC0_200X		58
#define ADC7_ADC0_200X		59
#define ADC4_ADC1_200X		60
#define ADC5_ADC1_200X		61
#define ADC6_ADC1_200X		62
#define ADC7_ADC1_200X		63
#define ACOMP_MUX			0
#define ACOMP_AIN0			0

#else

/* "Ардуиновский" вариант */
#define ADC_A0				0
#define ADC_A1				1
#define ADC_A2				2
#define ADC_A3				3
#define ADC_A4				4
#define ADC_A5				5
#define ADC_A6				6
#define ADC_A7				7
#define ADC_THERMOMETER		8
#define ADC_BANDGAP			14
#define ADC_GND				15
#define ACOMP_D7			0
#define ACOMP_D6			0

/* "Авровский" вариант */
#define ADC0				0
#define ADC1				1
#define ADC2				2
#define ADC3				3
#define ADC4				4
#define ADC5				5
#define ADC6				6
#define ADC7				7
#define ACOMP_MUX			1
#define ACOMP_AIN1			0
#define ACOMP_AIN0			0

#endif

