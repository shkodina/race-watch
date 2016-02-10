//***********************************************************************

#ifndef _HT1632_LEDBOARD_H_
#define _HT1632_LEDBOARD_H_

//***********************************************************************

// здесь заложено, что игры будут с портом B (т.е. он рабочий)
// используются пины 0 2 3 4

#define WPORT PORTB  	// порт, к которому подключен борд
#define CS_P 0 			// PB0 
#define CLK_P 2			// PB2
#define WR_P 3			// PB3
#define DATA_P 4		// PB4

#define SELECTALL -1	// выбрать все чипы
#define SELECTNONE 0	// отключить все чипы

#define CHIPMAX 8 		// количество чипов на борде
#define ALLCHIPMEMFULLBITE 512 // размер матрицы в двое больше нужного
#define ALLCHIPMEMHALFBITE 1024 // размер матрицы в двое больше нужного

//***********************************************************************

#define SLAVE_MODE 				0b100000100000
#define RC_MASTER_MODE 			0b100000110000
#define EXT_CLOCK_MASTER_MODE 	0b100000111000

#define SYS_EN					0b100000000010

#define LED_ON					0b100000000110
#define LED_OFF					0b100000000100

#define BLINK_ON				0b100000010010
#define BLINK_OFF				0b100000010000

#define N_MOS_COM8				0b100001000000

#define PWM_01					0b100101000000
#define PWM_02					0b100101000010
#define PWM_03					0b100101000100
#define PWM_04					0b100101000110
#define PWM_05					0b100101001000
#define PWM_06					0b100101001010
#define PWM_07					0b100101001100
#define PWM_08					0b100101001110
#define PWM_09					0b100101010000
#define PWM_10					0b100101010010
#define PWM_11					0b100101010100
#define PWM_12					0b100101010110
#define PWM_13					0b100101011000
#define PWM_14					0b100101011010
#define PWM_15					0b100101011100
#define PWM_16					0b100101011110
#define PWM_MASK_CMD			0b100101000000
#define PWM_MASK_DATA			0b000000011110

//***********************************************************************

void InitBoard();
void ChipSelect(int chipn);
void WriteCommand( unsigned int command);
void WriteAddress( unsigned char addr);
void WriteData (unsigned char data);
void WriteFirst4BitOfData (unsigned char data);
void WriteMatrixData (unsigned char * data, int len);
void WriteMatrixFirst4BitOfData (unsigned char * data, int len);



//***********************************************************************

void testport();

//***********************************************************************

#endif //_HT1632_LEDBOARD_H_

//***********************************************************************
