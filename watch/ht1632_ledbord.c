
#include <avr/io.h>
#include <util/delay.h>
#include "ht1632_ledboard.h"



//***********************************************************************
// ������� ������� ������� ��� ������ � ������
//***********************************************************************

// �������� ���� � �����

#define INVBIT(port, bit) port = port ^ (1<<bit);
#define INVBITW(bit) WPORT = WPORT ^ (1<<bit);

// ��������� ��� � �����

#define UPBIT(port, bit) port = port | (1<<bit);
#define UPBITW(bit) WPORT = WPORT | (1<<bit);

// �������� ��� � �����

#define DOWNBIT(port, bit) port = port & (~(1<<bit));
#define DOWNBITW(bit) WPORT = WPORT & (~(1<<bit));

//***********************************************************************

// �������� ��� ���������� ���������
#define CLKDEL _delay_us(0.1);
#define WRDEL _delay_us(0.1);

//***********************************************************************

// ������ ����� �� clock
#define PULSCLK { UPBITW(CLK_P) CLKDEL DOWNBITW(CLK_P) CLKDEL};

//***********************************************************************

// ����� �� WR
#define PULSWR { UPBITW(WR_P) WRDEL DOWNBITW(WR_P) WRDEL};

//***********************************************************************

// ����� ���� �� �����
// ���� ������ ����, �� ��� �������
void ChipSelect(int chipn)
{

	static int last_chipn = SELECTNONE;

	unsigned char i = 0;
	if (chipn <= SELECTALL){			// ������� ���
		DOWNBITW(CS_P)
		CLKDEL
		for (i = 0; i < CHIPMAX; i++){
			PULSCLK	
		}
		last_chipn = SELECTALL;
	}else if (chipn == SELECTNONE){ 	// ��������� ���
		UPBITW(CS_P)
		CLKDEL
		for (i = 0; i < CHIPMAX; i++){
			PULSCLK	
		}
		last_chipn = SELECTNONE;
	}else{								// ������� ����������
		
		if (last_chipn < chipn && 		// ��������� ��� ������ �����������
			last_chipn != SELECTNONE && // � ������� ��� ������ �� ����������
			last_chipn != SELECTALL)	// � ������� ��� ������ �� ����������
		{
			// ��� ��� ����� 2-�� � ����� �����
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

		// ��� ��� ����� 2-�� � ����� �����
		for (i = 1; i < chipn; i++){
			PULSCLK	
		}
	}
}

//***********************************************************************

// ������ ����� ������� ������
void WriteCommand( unsigned int command)
{
	unsigned char i;
	unsigned int j;
	command = command & 0x0fff; // ������� ������� �� 12 ���
	ChipSelect(SELECTNONE);
	CLKDEL
	ChipSelect(SELECTALL);
	CLKDEL
	for (i = 0; i < 12; i++){
		DOWNBITW(WR_P)
		WRDEL
		j = command & 0x0800; // ������ ��� �������
		command = command << 1; // �������� ��� �������
		j = j >> 11; // �������� �� ��������� �������
		if (j){
			UPBITW(DATA_P)
		}else{
			DOWNBITW(DATA_P)
		}
		WRDEL
		UPBITW(WR_P) // � ���� ������ ������ ����������� � �����
		WRDEL
	}
//	UPBITW(WR_P) // � ���� ������ ������ ����������� � �����
//	WRDEL
	ChipSelect(SELECTNONE);
	CLKDEL
}

//***********************************************************************

// ������ ������ � ��������� ������� ���
void WriteAddress( unsigned char addr)
{
	unsigned char i, j;
	
	addr = addr & 0x7f; // ����� � 7 ���, ��������� ������
	
	// ������ ����������������� ��� 101 ������ ����� �����
	DOWNBITW(WR_P)
	WRDEL
	UPBITW(DATA_P)	// ��� 1 � ����
	WRDEL
	UPBITW(WR_P)	// ������ ���� ��� ����� WR � 0 �� 1
	WRDEL
	DOWNBITW(WR_P)	// ������� WR � ����
	WRDEL
	DOWNBITW(DATA_P)	// ��� 0 � ����
	WRDEL
	UPBITW(WR_P)	// ������ ���� ��� ����� WR � 0 �� 1
	WRDEL
	DOWNBITW(WR_P)	// ������� WR � ����
	WRDEL
	UPBITW(DATA_P)	// ��� 1 � ����
	WRDEL
	UPBITW(WR_P)	// ������ ���� ��� ����� WR � 0 �� 1
	WRDEL
	DOWNBITW(WR_P)	// ������� WR � ����
	WRDEL
	for (i = 0; i < 7; i++){
		DOWNBITW(WR_P)
		WRDEL
		j = addr & 0x40; // ������ ��� ������
		addr = addr << 1; // �������� ���� �����
		j = j >> 6; // �������� �� ��������� �������
		if (j){
			UPBITW(DATA_P)
		}else{
			DOWNBITW(DATA_P)
		}
		WRDEL
		UPBITW(WR_P) // � ���� ������ ������ ����������� � �����
		WRDEL
	}
//	UPBITW(WR_P) // � ���� ������ ������ ����������� � �����
//	WRDEL
}

//***********************************************************************

// ������������� ������ � ������� �����
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

// ����������� ���������� ��������� SPI
void WriteData (unsigned char data)
{
	unsigned char i, j;
	for (i = 0; i < 8; i++){
		DOWNBITW(WR_P)
		WRDEL
		j = data & 0x80; // ������ ��� ������
		data = data << 1; // �������� ���� ����
		if (j > 0){
			UPBITW(DATA_P)
		}else{
			DOWNBITW(DATA_P)
		}
		WRDEL
		UPBITW(WR_P) // � ���� ������ ������ ����������� � �����
		WRDEL
	}
	//UPBITW(WR_P) // � ���� ������ ������ ����������� � �����
	//WRDEL
}

//***********************************************************************

// ����������� ���������� ��������� SPI �� ���� ������ ������
void WriteFirst4BitOfData (unsigned char data)
{
	unsigned char i, j;
	for (i = 0; i < 4; i++){
		DOWNBITW(WR_P)
		WRDEL
		j = data & 0x01; // ������ ��� ������
		data = data >> 1; // �������� ���� ����
		if (j > 0){
			UPBITW(DATA_P)
		}else{
			DOWNBITW(DATA_P)
		}
		WRDEL
		UPBITW(WR_P) // � ���� ������ ������ ����������� � �����
		WRDEL
	}
	//UPBITW(WR_P) // � ���� ������ ������ ����������� � �����
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
			j = data & 0x01; // ������ ��� ������
			data = data >> 1; // �������� ���� ����
			if (j > 0){
				UPBITW(DATA_P)
			}else{
				DOWNBITW(DATA_P)
			}
			WRDEL
			UPBITW(WR_P) // � ���� ������ ������ ����������� � �����
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
			j = data & 0x01; // ������ ��� ������
			data = data >> 1; // �������� ���� ����
			if (j > 0){
				UPBITW(DATA_P)
			}else{
				DOWNBITW(DATA_P)
			}
			WRDEL
			UPBITW(WR_P) // � ���� ������ ������ ����������� � �����
			WRDEL
		}
	}
	//UPBITW(WR_P) // � ���� ������ ������ ����������� � �����
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




























