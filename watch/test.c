/*****************************************************
This program was produced by the
CodeWizardAVR V2.04.4a Advanced
Automatic Program Generator
© Copyright 1998-2009 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 02.05.2012
Author  : NeVaDa
Company : 
Comments: 


Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 16,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*****************************************************/

// инверсия бита в порту

#define INVBIT(port, bit) port = port ^ (1<<bit);

// выставить бит в порту

#define UPBIT(port, bit) port = port | (1<<bit);

// сбросить бит в порту

#define DOWNBIT(port, bit) port = port & (~(1<<bit));

//***********************************************************************
#define BAUD 9600
//***********************************************************************
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "BoardPrinter.h"

#include "ht1632_ledboard.h"

#include "ProtDef.h"

#define MESSAGEMAXLEN 256


//***********************************************************************
#ifndef RXB8
#define RXB8 1
#endif

#ifndef TXB8
#define TXB8 0
#endif

#ifndef UPE
#define UPE 2
#endif

#ifndef DOR
#define DOR 3
#endif

#ifndef FE
#define FE 4
#endif

#ifndef UDRE
#define UDRE 5
#endif

#ifndef RXC
#define RXC 7
#endif

#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)


// USART1 Receiver buffer
char bufu1[MESSAGEMAXLEN];
char message[MESSAGEMAXLEN];
unsigned int bufu1_index;

static unsigned char start = 0;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// USART1 Receiver interrupt service routine
ISR(USART1_RX_vect)
{

	char status,data,lcount, wcount, wpos[4], cpos[4], cmddata;
	unsigned int cmd = 0;


	status=UCSR1A;
	data=UDR1;
	if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
	{

   	
		

		if(data == STARTMARKER){
			bufu1_index = 0;
		}else if(data == ENDMARKER){ 


			// пусть любая команда начинается со *
			// если не звездочка первая, то это строка для вывода на экран
			if(bufu1[0] != COMMANDMARKER){

				lcount = 0;
				wcount = 0;

				printf_P(PSTR("UARTINT: get message \n"));

				for (int i = 0; i < bufu1_index; i++){
					switch(bufu1[i]){
					case '|':
						wpos[wcount] = i - lcount; 
						cpos[wcount] = i ;
						message[wpos[wcount]] = lcount - 1; // -1 так как последний символ это цвет строки
						lcount = 0;
						wcount++;
						break;
					default:
						message[i+1] = bufu1[i];
						lcount++;
						break;
					}
				
				}
				if (wcount == 2){											// цифра это код - COLOR_SHIFT
					print2line(	message + wpos[0] + 1, message[wpos[0]], message[cpos[0]] - COLOR_SHIFT, 
								message + wpos[1] + 1, message[wpos[1]], message[cpos[1]] - COLOR_SHIFT);
					PrintMatrix(getMainMatrix(), 8);
				}				
				if (wcount == 4){											// цифра это код - COLOR_SHIFT
					print4line(	message + wpos[0] + 1, message[wpos[0]], message[cpos[0]] - COLOR_SHIFT,
								message + wpos[1] + 1, message[wpos[1]], message[cpos[1]] - COLOR_SHIFT,
								message + wpos[2] + 1, message[wpos[2]], message[cpos[2]] - COLOR_SHIFT, 
								message + wpos[3] + 1, message[wpos[3]], message[cpos[3]] - COLOR_SHIFT);
					PrintMatrix(getMainMatrix(), 8);
				}				

				bufu1_index = 0;

			}else{ // это какая то команда 

				printf_P(PSTR("UARTINT: get command = %c\n"), bufu1[1]);

				switch(bufu1[1]){
				case COMMANDSTART:
					start = 1;
					break;
				case COMMANDSTOP:
					start = 0;
					break;
				case COMMANDGETID:
					break;
				case COMMANDRESTART:
					break;
				case COMMANDSETBRIGHT:
					cmddata = bufu1[2] - COMMBRIGHTBASE;
					cmd = cmddata;
					cmd = cmd << 1;
					cmd = cmd & PWM_MASK_DATA; 
					cmd = cmd | PWM_MASK_CMD; 
					WriteCommand(cmd);
					break;
				default:
					break;
				}
			}





		}else{
	   		if (bufu1_index == MESSAGEMAXLEN) 
	   			bufu1_index=0;
	   		bufu1[bufu1_index++]=data;
		}

   	}



}
//***********************************************************************
//***********************************************************************

void SetupTIMER1 (void)
 {
     //With 16 MHz clock and 65536 times counting T/C1 overflow interrupt
     // will occur every:
     //   1<<CS10                  4096 mkS  (no prescale Fclk)
     //   1<<CS11                  32.768 mS (Fclk/8)
     //  (1<<CS11)|(1<<CS10)       262.144 mS (Fclk/64)
     //   1<<CS12                  1048.576 mS (Fclk/256)
       TCCR1B = (1<<CS12);
     TCNT1 = 65536-62439;        //коррекция счетчика, чтобы время было ровно 1 секунда
     /* Enable timer 1 overflow interrupt. */
     TIMSK = (1<<TOIE1);
 }

static unsigned long tc = 0;


	unsigned char ddata, cddata;
	unsigned int ii;

ISR (TIMER1_OVF_vect)
 {
 	static unsigned char bt = 0;
	static unsigned long c = 0;

     //теперь прерывание будет происходить через 62439 тиков
     // таймера 1, что на частоте 16 МГц составит 1 сек.
     //TCNT1 = 65536-62439;
	 TCNT1 = 65536-90;//15;
     TCCR1B = (1<<CS12);
     TIMSK = (1<<TOIE1);
     //Далее идет код, который будет работать каждую секунду.
     //Желательно, чтобы этот код был короче.
/*	 if ( tc++ == 2000 ) {
		//printf_P(PSTR("TIMER1INT: tc = %d\n"), tc);
		//printf_P(PSTR("TIMER1INT: c = %d\n"), c);
		tc = 0;
		c = 0;
	 }
	      
	if (bt != (PINE & 0x04)){
		c++;
	 	bt = PINE & 0x04;

//		printf_P(PSTR("%d|"), bt);

	}
*/
	cddata = (PINE & 4);
	if (ddata != cddata){

		//printf_P(PSTR("int = %d - "), ddata);
		//printf_P(PSTR("%d\n"), ii);
		if (ii > 6){
			printf_P(PSTR("d = %d - "), ddata);
			printf_P(PSTR("%d\n"), ii);
		}
			
		ii = 1;
		ddata = cddata;


	}else{
		ii++;
	}

 }


ISR (INT4_vect)
 {/*
	static unsigned long cc = 0;
	printf_P(PSTR("INT4: cc = %d\n"), cc++);
 */}


//***********************************************************************
// действия, сброшенные в функции, для читабельности
//***********************************************************************

void SystemInit();

//***********************************************************************
// функции для работы с дисплеем
//***********************************************************************

void CleanDisp();

//***********************************************************************
// функции для работы с компортом
//***********************************************************************

char getchar1(void);
void putchar1(char c);

//***********************************************************************

void UART_Transmit(char c, FILE * stream);
char UART_Receive(FILE * stream);

static FILE UART_console = 
	FDEV_SETUP_STREAM(UART_Transmit, UART_Receive, _FDEV_SETUP_RW);

void UART_Init(void);

//***********************************************************************

// основная функция *****************************************************

//***********************************************************************

int main(void)
{
printf_P(PSTR("SYS: START working \n"));

SystemInit(); // там просто регистры инициализируются... чтобы тут не мешали

SetupTIMER1();


unsigned char mdata[ALLCHIPMEMFULLBITE];
unsigned char mhalfdata[ALLCHIPMEMHALFBITE];

char message[MESSAGEMAXLEN];

unsigned int 	ismatrixfull = 0,
				im = 0,
				cmddata = 0;

				

unsigned char 	data = 0,
				cdata = 0,
				iscmd = 0,
				i = 0,
				j = 0,
				k = 0,
				chip_count_to_disp = 0,
				tmp = 0,
				message_index = 0;




UART_Init();

InitBoard();



// пример логирования для будущей отледки
//printf_P(PSTR("SYS: START write to BOARD %d\n"), im++);


CleanDisp();


while(1){

/*	
	ChipSelect(rand() % 8 + 1);
	WriteAddress(rand() % 64);
	WriteData(rand());
	_delay_ms(50);
*/

//	cli();
	//printf_P(PSTR("%d"), PINE & 4 );
/*	cdata = (PINE & 4);
	if (data != cdata){

		printf_P(PSTR("FROM MAIN data = %d - "), data);
		printf_P(PSTR("%d\n"), i);

		i = 1;
		data = cdata;
	}else{
		i++;
	}
	//_delay_ms(1);
*/
	
//	sei();



//**********************
//**********************
//**********************


}

} // end of main

//***********************************************************************

// вспомогательные функции для работы с экраном	*************************

//***********************************************************************

void CleanDisp()
{
	unsigned char i;
	static unsigned char emptimatrix[32];


	for (i = 1; i <= CHIPMAX; i++) {
		ChipSelect(i);
		WriteAddress(0x00);
		WriteMatrixData(emptimatrix, 32);
	}
}

//***********************************************************************

void PrintMatrix(unsigned char * matrix, int chip_count_to_disp)
{
	unsigned char i;

	for (i = 0; i < chip_count_to_disp; i++) {
		ChipSelect(i + 1);
		WriteAddress(0x00);
		WriteMatrixData(matrix + i * 32, 32);
	}

}

//***********************************************************************

// функции для работы с компортом ***************************************

//***********************************************************************

void UART_Init(void)
{
    stdout = &UART_console;
    stdin = &UART_console;
	// USART1 initialization
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART1 Receiver: On
	// USART1 Transmitter: On
	// USART1 Mode: Asynchronous
	// USART1 Baud Rate: 9600
//	UCSR1A=0x00;
//	UCSR1B=0x18;
//	UCSR1C=0x06;
//	UBRR1H=0x00;
//	UBRR1L=0x67;

/*
//19200
UCSR1A=0x00;
UCSR1B=0x98;
UCSR1C=0x06;
UBRR1H=0x00;
UBRR1L=0x33;
*/

// USART1 initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART1 Receiver: On
// USART1 Transmitter: On
// USART1 Mode: Asynchronous
// USART1 Baud Rate: 115200
UCSR1A=0x00;
UCSR1B=0x98;
UCSR1C=0x06;
UBRR1H=0x00;
UBRR1L=0x08;


sei(); // разрешим прерывания


}

//***********************************************************************

//#pragma used+
char getchar1(void)
{
	char status,data;
	while (1)
	      {
	      while (((status=UCSR1A) & RX_COMPLETE)==0);
	      data=UDR1;
	      if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
	         return data;
	      };
}
//#pragma used-

//***********************************************************************

// Write a character to the USART1 Transmitter
//#pragma used+
void putchar1(char c)
{
	while ((UCSR1A & DATA_REGISTER_EMPTY)==0);
	UDR1=c;
}
//#pragma used-

//***********************************************************************

void UART_Transmit(char c, FILE * stream)
{
    cli();
    if (c == '\n')
        UART_Transmit('\r', stream);
    loop_until_bit_is_set(UCSR1A, UDRE);
    UDR1 = c;
    sei();
}

//***********************************************************************

char UART_Receive(FILE * stream)
{

    loop_until_bit_is_set(UCSR1A, RXC);
    if (UCSR1A & _BV(FE))
        return _FDEV_EOF;
    if (UCSR1A & _BV(DOR))
        return _FDEV_ERR;

    return UDR1;

}

//***********************************************************************

// системные функции ****************************************************

//***********************************************************************

void SystemInit()
{
	// Declare your local variables here

	// Input/Output Ports initialization
	// Port A initialization
	// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
	// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
	PORTA=0x00;
	DDRA=0x00;

	// Port B initialization
	// Func7=In Func6=In Func5=In Func4=Out Func3=Out Func2=Out Func1=In Func0=Out 
	// State7=T State6=T State5=T State4=0 State3=0 State2=0 State1=T State0=0 
	PORTB=0x00;
	DDRB=0x1D;
	//DDRB=0x00;

	// Port C initialization
	// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
	// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
	PORTC=0x00;
	DDRC=0x00;

	// Port D initialization
	// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
	// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
	PORTD=0x00;
	DDRD=0x00;

	// Port E initialization
	// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
	// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 

	// если 0 резисторы подтяжки выключены
	PORTE=0x00;

	// если FF то включены
	//PORTE=0xFF;
	DDRE=0x00;

	// Port F initialization
	// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
	// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
	PORTF=0x00;
	DDRF=0x00;

	// Port G initialization
	// Func4=In Func3=In Func2=In Func1=In Func0=In 
	// State4=T State3=T State2=T State1=T State0=T 
	PORTG=0x00;
	DDRG=0x00;

	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: Timer 0 Stopped
	// Mode: Normal top=FFh
	// OC0 output: Disconnected
	ASSR=0x00;
	TCCR0=0x00;
	TCNT0=0x00;
	OCR0=0x00;

	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: Timer1 Stopped
	// Mode: Normal top=FFFFh
	// OC1A output: Discon.
	// OC1B output: Discon.
	// OC1C output: Discon.
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer1 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	// Compare C Match Interrupt: Off
	TCCR1A=0x00;
	TCCR1B=0x00;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;
	OCR1CH=0x00;
	OCR1CL=0x00;

	// Timer/Counter 2 initialization
	// Clock source: System Clock
	// Clock value: Timer2 Stopped
	// Mode: Normal top=FFh
	// OC2 output: Disconnected
	TCCR2=0x00;
	TCNT2=0x00;
	OCR2=0x00;

	// Timer/Counter 3 initialization
	// Clock source: System Clock
	// Clock value: Timer3 Stopped
	// Mode: Normal top=FFFFh
	// OC3A output: Discon.
	// OC3B output: Discon.
	// OC3C output: Discon.
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer3 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	// Compare C Match Interrupt: Off
	TCCR3A=0x00;
	TCCR3B=0x00;
	TCNT3H=0x00;
	TCNT3L=0x00;
	ICR3H=0x00;
	ICR3L=0x00;
	OCR3AH=0x00;
	OCR3AL=0x00;
	OCR3BH=0x00;
	OCR3BL=0x00;
	OCR3CH=0x00;
	OCR3CL=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
// INT3: Off
// INT4: On
// INT4 Mode: Rising Edge
// INT5: Off
// INT6: Off
// INT7: Off
EICRA=0x00;
EICRB=0x03;
EIMSK=0x10;
EIFR=0x10;

	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK=0x00;
	ETIMSK=0x00;

	// Analog Comparator initialization
	// Analog Comparator: Off
	// Analog Comparator Input Capture by Timer/Counter 1: Off
	ACSR=0x80;
	SFIOR=0x00;
}

//***********************************************************************
