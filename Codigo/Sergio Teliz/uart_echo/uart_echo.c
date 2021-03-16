//*****************************************************************************
//
// uart_echo.c - Example for reading data from and writing data to the UART in
//               an interrupt driven fashion.
//
// Copyright (c) 2013-2016 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.3.156 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_timer.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>UART Echo (uart_echo)</h1>
//!
//! This example application utilizes the UART to echo text.  The first UART
//! (connected to the USB debug virtual serial port on the evaluation board)
//! will be configured in 115,200 baud, 8-n-1 mode.  All characters received on
//! the UART are transmitted back to the UART.
//
//*****************************************************************************

//****************************************************************************
//
// Define parameters
//
//****************************************************************************
#define CPUCLKMHz 120

//****************************************************************************
//
// Variables
//
//****************************************************************************
uint32_t g_ui32SysClock;
uint32_t counter;

volatile uint32_t pulse0;	//Stores the pulse length
volatile uint32_t pulse1;
volatile uint32_t pulse2;
volatile uint32_t pulse3;
volatile uint8_t echowait0 = 0;//Flag to tell if the a pulse is being read at the moment
volatile uint8_t echowait1 = 0;
volatile uint8_t echowait2 = 0;
volatile uint8_t echowait3 = 0;
volatile uint32_t Dist0; //Distance store value
volatile uint32_t Dist1;
volatile uint32_t Dist2;
volatile uint32_t Dist3;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// Timer 0 Interrupt
//
//*****************************************************************************
void
Timer0IntHandler(void)
{
    //
    // Clear the timer interrupt.
    //
    ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
        //
	//Send new pulse if no pulse is being measured at the time
	//Do other things instead
    //
	//Does the required pulse of 10uS
	ROM_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, GPIO_PIN_0);
	ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2);
	ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
	//ROM_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_6, GPIO_PIN_6);
	SysCtlDelay(10*(SysCtlClockGet()/3/1000000));
	ROM_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, ~GPIO_PIN_0);
	ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, ~GPIO_PIN_2);
	ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, ~GPIO_PIN_1);
	//ROM_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_6, ~GPIO_PIN_6);
}

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void
UART7IntHandler(void)
{
    uint32_t ui32Status;
    uint32_t val;
    uint32_t valuart0;
    uint32_t valuart1;
    uint32_t valuart2;
    uint32_t valuart3;

    //
    // Get the interrupt status.
    //
    ui32Status = ROM_UARTIntStatus(UART7_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    ROM_UARTIntClear(UART7_BASE, ui32Status);

    //
    // Turn on the LED to show a character transfer is occurring.
    //
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(ROM_UARTCharsAvail(UART7_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //


        //ROM_UARTCharPutNonBlocking(UART7_BASE,ROM_UARTCharGetNonBlocking(UART7_BASE));
    	val=ROM_UARTCharGetNonBlocking(UART7_BASE);
    	switch (val){
    		case 'F':
    			valuart0 = pulse0;
    			valuart1 = pulse1;
    			valuart2 = pulse2;
    			valuart3 = pulse3;
    			break;
    		case 'L':
    			valuart0 = Dist0;
    			valuart1 = Dist1;
    			valuart2 = Dist2;
    			valuart3 = Dist3;
    			break;
    		case 'S':{
    			valuart0 = 0;
    			valuart1 = 0;
    			valuart2 = 0;
    			valuart3 = 0;
    			counter = 0;
    			}
    			break;
    		default:{
    			valuart0 = 255;
    			valuart1 = 255;
    			valuart2 = 255;
    			valuart3 = 255;
    			counter = 255;
    		}
    		break;
    	}

    	//
    	//Send sequence of numbers and parameters
    	//
    	ROM_UARTCharPut(UART7_BASE,counter);
    	//Envio variable varuart0 32 bits
    	ROM_UARTCharPut(UART7_BASE,valuart0);
    	ROM_UARTCharPut(UART7_BASE,valuart0>>8);
    	ROM_UARTCharPut(UART7_BASE,valuart0>>16);
    	ROM_UARTCharPut(UART7_BASE,valuart0>>24);
    	//Envio variable varuart1 32 bits
    	ROM_UARTCharPut(UART7_BASE,valuart1);
    	ROM_UARTCharPut(UART7_BASE,valuart1>>8);
    	ROM_UARTCharPut(UART7_BASE,valuart1>>16);
    	ROM_UARTCharPut(UART7_BASE,valuart1>>24);
    	//Envio variable varuart2 32 bits
    	ROM_UARTCharPut(UART7_BASE,valuart2);
    	ROM_UARTCharPut(UART7_BASE,valuart2>>8);
    	ROM_UARTCharPut(UART7_BASE,valuart2>>16);
    	ROM_UARTCharPut(UART7_BASE,valuart2>>24);
    	//Envio variable varuart3 32 bits
    	ROM_UARTCharPut(UART7_BASE,valuart3);
    	ROM_UARTCharPut(UART7_BASE,valuart3>>8);
    	ROM_UARTCharPut(UART7_BASE,valuart3>>16);
    	ROM_UARTCharPut(UART7_BASE,valuart3>>24);
    	//Envio valores boolenaos
    	ROM_UARTCharPut(UART7_BASE,1);
    	ROM_UARTCharPut(UART7_BASE,valuart0>=255);
    	ROM_UARTCharPut(UART7_BASE,valuart0>=65536);
    	ROM_UARTCharPut(UART7_BASE,valuart0>=16777216);
    	ROM_UARTCharPut(UART7_BASE,val);

        //
        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
        //
        SysCtlDelay(g_ui32SysClock / (1000 * 3));

        //
        // Turn off the LED
        //
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
    	counter++;
    }
}


//*****************************************************************************
//
// The SR04_0 interrupt handler.
//
//*****************************************************************************
void
SR04Int0(void){

	ROM_GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_1); //clear interrupt flag
	//
	// Ask the state of PL0, if HIGH, rising edge happened, timer cleared
	// If it's LOW, falling edge happened, save timer value
	//
	if (ROM_GPIOPinRead(GPIO_PORTL_BASE, GPIO_PIN_1) == GPIO_PIN_1){
		HWREG(TIMER1_BASE+TIMER_O_TAV) = 0; // Timer cleared
		ROM_TimerEnable(TIMER1_BASE,TIMER_A); //start timer to record
		echowait0=1;
	}

	else{
		ROM_TimerDisable(TIMER1_BASE,TIMER_A); //stop timer
		pulse0 = ROM_TimerValueGet(TIMER1_BASE,TIMER_A); //record value
		Dist0 = pulse0/120/58;
		echowait0=0;
  }
}

//*****************************************************************************
//
// The SR04_1 interrupt handler.
//
//*****************************************************************************
void
SR04Int1(void){

	ROM_GPIOIntClear(GPIO_PORTE_BASE, GPIO_PIN_3); //clear interrupt flag
	//
	// Ask the state of PL3, if HIGH, rising edge happened, timer cleared
	// If it's LOW, falling edge happened, save timer value
	//
	if (ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3) == GPIO_PIN_3){
		HWREG(TIMER2_BASE+TIMER_O_TAV) = 0; // Timer cleared
		ROM_TimerEnable(TIMER2_BASE,TIMER_A); //start timer to record
		echowait1=1;
	}

	else{
		ROM_TimerDisable(TIMER2_BASE,TIMER_A); //stop timer
		pulse1 = ROM_TimerValueGet(TIMER2_BASE,TIMER_A); //record value
		Dist1 = pulse1/120/58;
		echowait1=0;
  }
}

//*****************************************************************************
//
// The SR04_2 interrupt handler.
//
//*****************************************************************************
void
SR04Int2(void){

	ROM_GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_1); //clear interrupt flag
	//
	// Ask the state of PL0, if HIGH, rising edge happened, timer cleared
	// If it's LOW, falling edge happened, save timer value
	//
	if (ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1) == GPIO_PIN_1){
		HWREG(TIMER3_BASE+TIMER_O_TAV) = 0; // Timer cleared
		ROM_TimerEnable(TIMER3_BASE,TIMER_A); //start timer to record
		echowait2=1;
	}

	else{
		ROM_TimerDisable(TIMER3_BASE,TIMER_A); //stop timer
		pulse2 = ROM_TimerValueGet(TIMER3_BASE,TIMER_A); //record value
		Dist2 = pulse2/120/58;
		echowait2=0;
  }
}

/*
*****************************************************************************

 The SR04_3 interrupt handler.

*****************************************************************************
void
SR04Int3(void){

	ROM_GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_7); //clear interrupt flag
	//
	// Ask the state of PL0, if HIGH, rising edge happened, timer cleared
	// If it's LOW, falling edge happened, save timer value
	//
	if (ROM_GPIOPinRead(GPIO_PORTL_BASE, GPIO_PIN_7) == GPIO_PIN_7){
		HWREG(TIMER2_BASE+TIMER_O_TAV) = 0; // Timer cleared
		ROM_TimerEnable(TIMER4_BASE,TIMER_A); //start timer to record
		echowait3=1;
	}

	else{
		ROM_TimerDisable(TIMER4_BASE,TIMER_A); //stop timer
		pulse3 = ROM_TimerValueGet(TIMER4_BASE,TIMER_A); //record value
		Dist3 = pulse3/120/58;
		echowait3=0;
  }
}

*/

//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void
UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        ROM_UARTCharPutNonBlocking(UART7_BASE, *pui8Buffer++);
    }
}

//*****************************************************************************
//
// The Timer0 initialization routine
//
//*****************************************************************************
void Timer0_init(){
    //
    // Enable timer0
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    //
    // Configure 32-bit periodic timer. Set a 100ms period
    //
    ROM_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, 100*(SysCtlClockGet()/1000));
    //
    // Setup the interrupts for the timer timeouts.
    //
    ROM_IntEnable(INT_TIMER0A);
    ROM_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    //
    // Enable the timer.
    //
    ROM_TimerEnable(TIMER0_BASE, TIMER_A);
}

//*****************************************************************************
//
// The SR04_0 initialization routine
//
//*****************************************************************************
void SR04_init0(){

    //
    // Configure the trigger pin, use PL0
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_0);

    //
	// Configure Echo pin, use PL1
    // Set the interrupt to enable at both edges
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, GPIO_PIN_1);
	ROM_GPIOIntEnable(GPIO_PORTL_BASE, GPIO_PIN_1);
	ROM_GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_1,GPIO_BOTH_EDGES);
	GPIOIntRegister(GPIO_PORTL_BASE,SR04Int0);

    //
    // Set the timer 2 to periodic up and in full mode
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	ROM_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC_UP);
	ROM_TimerEnable(TIMER1_BASE,TIMER_A);
}

//*****************************************************************************
//
// The SR04_1 initialization routine
//
//*****************************************************************************
void SR04_init1(){

    //
    // Configure the trigger pin, use PL2
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_2);

    //
	// Configure Echo pin, use PL3
    // Set the interrupt to enable at both edges
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_3);
	ROM_GPIOIntEnable(GPIO_PORTE_BASE, GPIO_PIN_3);
	ROM_GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_3,GPIO_BOTH_EDGES);
	GPIOIntRegister(GPIO_PORTE_BASE,SR04Int1);

    //
    // Set the timer 2 to periodic up and in full mode
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
	ROM_TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC_UP);
	ROM_TimerEnable(TIMER2_BASE,TIMER_A);
}



//*****************************************************************************
//
// The SR04_2 initialization routine
//
//*****************************************************************************
void SR04_init2(){

    //
    // Configure the trigger pin, use PL4
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);

    //
	// Configure Echo pin, use PL5
    // Set the interrupt to enable at both edges
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_1);
	ROM_GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_1);
	ROM_GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_1,GPIO_BOTH_EDGES);
	GPIOIntRegister(GPIO_PORTD_BASE,SR04Int2);

    //
    // Set the timer 2 to periodic up and in full mode
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
	ROM_TimerConfigure(TIMER3_BASE, TIMER_CFG_PERIODIC_UP);
	ROM_TimerEnable(TIMER3_BASE,TIMER_A);
}

/*

*****************************************************************************
//
// The SR04_3 initialization routine
//
*****************************************************************************
void SR04_init3(){

    //
    // Configure the trigger pin, use PL6
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_6);

    //
	// Configure Echo pin, use PL7
    // Set the interrupt to enable at both edges
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, GPIO_PIN_7);
	ROM_GPIOIntEnable(GPIO_PORTL_BASE, GPIO_PIN_7);
	ROM_GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_7,GPIO_BOTH_EDGES);
	GPIOIntRegister(GPIO_PORTL_BASE,SR04Int3);

    //
    // Set the timer 2 to periodic up and in full mode
    //
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER4);
	ROM_TimerConfigure(TIMER4_BASE, TIMER_CFG_PERIODIC_UP);
	ROM_TimerEnable(TIMER4_BASE,TIMER_A);
}

*/

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, g_ui32SysClock);
}

//*****************************************************************************
//
// The UART initialization routine
//
//*****************************************************************************
void UART7_init(){

    //
    // Enable the peripherals used by this example.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    //
    // Set GPIO PC4 and PC5 as UART pins.
    //
    GPIOPinConfigure(GPIO_PC4_U7RX);
    GPIOPinConfigure(GPIO_PC5_U7TX);
    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    //
    // Configure the UART for 9,600, 8-N-1 operation.
    //
    ROM_UARTConfigSetExpClk(UART7_BASE, g_ui32SysClock, 9600,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    //
    // Enable the UART interrupt.
    //
    ROM_IntEnable(INT_UART7);
    ROM_UARTIntEnable(UART7_BASE, UART_INT_RX | UART_INT_RT);

}

//*****************************************************************************
//
// This example demonstrates how to send data to the UART.
//
//*****************************************************************************
int
main(void)
{
    //
    // Set the clocking to run directly from the crystal at 120MHz.
    //
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480), 120000000);

    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    //
    // Enable the GPIO pins for the LED (PN0).
    //
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);

    //
    // Initialize UART7 9600 baud
    //
    UART7_init();

    //
    // Initialize the UART.
    //
    ConfigureUART();

    //
    // Hello!
    //
    UARTprintf("Hello, world!\n");

    //
    // Initialize SR04
    //
    SR04_init0();
    SR04_init1();
    SR04_init2();
    //SR04_init3();

    ROM_IntPrioritySet(INT_GPIOL, 0x00);
    ROM_IntPrioritySet(INT_GPIOE, 0x00);
    ROM_IntPrioritySet(INT_GPIOD, 0x00);

    //
    // Initialize Timer0
    //
    Timer0_init();

    //
    // Enable processor interrupts.
    //
    ROM_IntMasterEnable();

    //
    // Loop forever sending data through the UART.
    //
    while(1){
    	 UARTprintf("Dist0:%d\tDist1:%d\tDist2:%d\n",Dist0,Dist1,Dist2);
    	 SysCtlDelay(1000*(SysCtlClockGet()/1000));

    }
}
