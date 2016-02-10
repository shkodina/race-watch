
#include <avr/io.h>
#include <util/delay.h>
#include "ht1632_ledboard.h"



//***********************************************************************
// сделаем быстрые макросы для работы с битами
//***********************************************************************

// инверсия бита в порту

#define INVBIT(port, bit) port = port ^ (1<<bit);
#define INVBITW(bit) WPORT = WPORT ^ (1<<bit);

// выставить бит в порту

#define UPBIT(port, bit) port = port | (1<<bit);
#define UPBITW(bit) WPORT = WPORT | (1<<bit);

// сбросить бит в порту

#define DOWNBIT(port, bit) port = port & (~(1<<bit));
#define DOWNBITW(bit) WPORT = WPORT & (~(1<<bit));

//***********************************************************************

// задержка для реализации протокола
#define CLKDEL _delay_us(0.1);
#define WRDEL _delay_us(0.1);

//***********************************************************************

// выдать пульс на clock
#define PULSCLK { UPBITW(CLK_P) CLKDEL DOWNBITW(CLK_P) CLKDEL};

//***********************************************************************

// пульс на WR
#define PULSWR { UPBITW(WR_P) WRDEL DOWNBITW(WR_P) WRDEL};

//***********************************************************************

// выбор чипа на плате
// если меньше ноля, то все выбрать
void ChipSelect(int chipn)
{

	static int last_chipn = SELECTNONE;

	unsigned char i = 0;
	if (chipn <= SELECTALL){			// выбрать все
		DOWNBITW(CS_P)
		CLKDEL
		for (i = 0; i < CHIPMAX; i++){
			PULSCLK	
		}
		last_chipn = SELECTALL;
	}else if (chipn == SELECTNONE){ 	// отключить все
		UPBITW(CS_P)
		CLKDEL
		for (i = 0; i < CHIPMAX; i++){
			PULSCLK	
		}
		last_chipn = SELECTNONE;
	}else{								// выбрать конкретный
		
		if (last_chipn < chipn && 		// следующий чип старше предыдущего
			last_chipn != SELECTNONE && // в прошлый раз ничего не затиралось
			last_chipn != SELECTALL)	// в прошлый раз ничего не выбиралось
		{
			// вот тут выбор 2-го и далее чипов
			for (i = last_chipn; i < chipn; i++){
				PULSCLK	
			}
			last_chipn = chipn;
			return;
		}	

		UPBITW(CS_P)
		CLKDEL	
		for (i = 0; i < CHIPMAX; i++){
			PULSCLK	
		}
		DOWNBITW(CS_P)
		CLKDEL
		PULSCLK	
		CLKDEL
		UPBITW(CS_P)
		CLKDEL	

		// вот тут выбор 2-го и далее чипов
		for (i = 1; i < chipn; i++){
			PULSCLK	
		}
	}
}

//***********************************************************************

// запись всеми любимых команд
void WriteCommand( unsigned int command)
{
	unsigned char i;
	unsigned int j;
	command = command & 0x0fff; // команда состоит из 12 бит
	ChipSelect(SELECTNONE);
	CLKDEL
	ChipSelect(SELECTALL);
	CLKDEL
	for (i = 0; i < 12; i++){
		DOWNBITW(WR_P)
		WRDEL
		j = command & 0x0800; // первый бит команды
		command = command << 1; // сдвинули всю команду
		j = j >> 11; // сдвинули на начальную позицию
		if (j){
			UPBITW(DATA_P)
		}else{
			DOWNBITW(DATA_P)
		}
		WRDEL
		UPBITW(WR_P) // в этот момент данные считываются с ножки
		WRDEL
	}
//	UPBITW(WR_P) // в этот момент данные считываются с ножки
//	WRDEL
	ChipSelect(SELECTNONE);
	CLKDEL
}

//***********************************************************************

// запись адреса в выбранный заранее чип
void WriteAddress( unsigned char addr)
{
	unsigned char i, j;
	
	addr = addr & 0x7f; // адрес в 7 бит, остальное лишнее
	
	// дальше идентификационный код 101 только потом адрес
	DOWNBITW(WR_P)
	WRDEL
	UPBITW(DATA_P)	// код 1 в порт
	WRDEL
	UPBITW(WR_P)	// запись идет при смене WR с 0 на 1
	WRDEL
	DOWNBITW(WR_P)	// сбросим WR в ноль
	WRDEL
	DOWNBITW(DATA_P)	// код 0 в порт
	WRDEL
	UPBITW(WR_P)	// запись идет при смене WR с 0 на 1
	WRDEL
	DOWNBITW(WR_P)	// сбросим WR в ноль
	WRDEL
	UPBITW(DATA_P)	// код 1 в порт
	WRDEL
	UPBITW(WR_P)	// запись идет при смене WR с 0 на 1
	WRDEL
	DOWNBITW(WR_P)	// сбросим WR в ноль
	WRDEL
	for (i = 0; i < 7; i++){
		DOWNBITW(WR_P)
		WRDEL
		j = addr & 0x40; // первый бит адреса
		addr = addr << 1; // сдвинули весь адрес
		j = j >> 6; // сдвинули на начальную позицию
		if (j){
			UPBITW(DATA_P)
		}else{
			DOWNBITW(DATA_P)
		}
		WRDEL
		UPBITW(WR_P) // в этот момент данные считываются с ножки
		WRDEL
	}
//	UPBITW(WR_P) // в этот момент данные считываются с ножки
//	WRDEL
}

//***********************************************************************

// инициализация боарда в рабочий режим
void InitBoard()
{
	WriteCommand(SYS_EN);
	WriteCommand(LED_ON);
	WriteCommand(BLINK_OFF);
	WriteCommand(RC_MASTER_MODE);
	WriteCommand(N_MOS_COM8);
	WriteCommand(PWM_04);
}

//***********************************************************************

// самодельная реализация протокола SPI
void WriteData (unsigned char data)
{
	unsigned char i, j;
	for (i = 0; i < 8; i++){
		DOWNBITW(WR_P)
		WRDEL
		j = data & 0x80; // первый бит данных
		data = data << 1; // сдвинули весь байт
		if (j > 0){
			UPBITW(DATA_P)
		}else{
			DOWNBITW(DATA_P)
		}
		WRDEL
		UPBITW(WR_P) // в этот момент данные считываются с ножки
		WRDEL
	}
	//UPBITW(WR_P) // в этот момент данные считываются с ножки
	//WRDEL
}

//***********************************************************************

// самодельная реализация протокола SPI на одну ячейку памяти
void WriteFirst4BitOfData (unsigned char data)
{
	unsigned char i, j;
	for (i = 0; i < 4; i++){
		DOWNBITW(WR_P)
		WRDEL
		j = data & 0x01; // первый бит данных
		data = data >> 1; // сдвинули весь байт
		if (j > 0){
			UPBITW(DATA_P)
		}else{
			DOWNBITW(DATA_P)
		}
		WRDEL
		UPBITW(WR_P) // в этот момент данные считываются с ножки
		WRDEL
	}
	//UPBITW(WR_P) // в этот момент данные считываются с ножки
	//WRDEL
}
//***********************************************************************

void WriteMatrixData (unsigned char * matrixdata, int len)
{
	unsigned char i, j, k, data;

	for (k = 0; k < len; k++){
		data = matrixdata[k];
		for (i = 0; i < 8; i++){
			DOWNBITW(WR_P)
			WRDEL
			j = data & 0x01; // первый бит данных
			data = data >> 1; // сдвинули весь байт
			if (j > 0){
				UPBITW(DATA_P)
			}else{
				DOWNBITW(DATA_P)
			}
			WRDEL
			UPBITW(WR_P) // в этот момент данные считываются с ножки
			WRDEL
		}
	}

}

//***********************************************************************

void WriteMatrixFirst4BitOfData (unsigned char * matrixdata, int len)
{

	unsigned char i, j, k, data;

	for (k = 0; k < len; k++){
		data = matrixdata[k];
		for (i = 0; i < 4; i++){
			DOWNBITW(WR_P)
			WRDEL
			j = data & 0x01; // первый бит данных
			data = data >> 1; // сдвинули весь байт
			if (j > 0){
				UPBITW(DATA_P)
			}else{
				DOWNBITW(DATA_P)
			}
			WRDEL
			UPBITW(WR_P) // в этот момент данные считываются с ножки
			WRDEL
		}
	}
	//UPBITW(WR_P) // в этот момент данные считываются с ножки
	//WRDEL
};

//***********************************************************************

void testport(){
	while(1){
		DOWNBITW(WR_P)
		WRDEL
		UPBITW(WR_P)
		WRDEL
	}
}

//***********************************************************************




























