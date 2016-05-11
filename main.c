
#include <stm32f10x.h>

#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>

#include "xuart.h"
#include "xprintf.h"
#include "encoder_dc.h"  //New encoder reader code.
#include "board_Naze.h"

#define TRUE 1
#define FALSE 0

#define LED_SIGNAL_DURATION 750

void init_USART1 (void);

// AO! void Delay( uint32_t nTime );

static __IO uint8_t TimerEventFlag;
//AO! remove for cleaning. static __IO uint16_t GPIO_Delay;
//Declared as __IO to ensure that the compiler doesn't perform 
//undesired optimization.

int main(void)
{
  int i;
  int LED_ON_counter;

  // Turn off JTAG module to be able to use the GPIO for leds
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  //Both below seem to work OK:
  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//Disable only JTAG, keep SWJ on.
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //Disable both JTAG&SWJ

  
  init_ENC();  //Initialize ports connected to encoder.
  init_LED_GPIO();  //Initialize ports connected to LED.

  /* Init Chan's Embedded String Functions (xprintf etc) */
  xdev_out(uart_putc);
  xdev_in(uart_getc);

  // Initialize USART1:
  init_USART1();   //Initialize USART1 clock.
  uart_open (USART1, 115200, 0); //USART2 is not supported.
  
  //AO! remove for cleaning.  int GPIO_Delay_Max =250; // Check GPIO so often.
  
  if (SysTick_Config(SystemCoreClock/1000))
    while (1);
  // Every 1 msec, the timer triggers a call to the SysTick_Handler.   

  //AO! remove for cleaning.   GPIO_Delay = 0;      //Counts the number of timer ticks so far.

  xprintf ("STM32F103 RTB6 Mini STM Test Board.\n\r");
  xprintf("System core clock rate is %d Hz\n\r",SystemCoreClock);




  //Turn off LED
  LED_OFF();
  LED_ON_counter=0;

  while (1) {

    if (TimerEventFlag==TRUE){
      i=EncRead_Guarded();
	if (i==UP || i==DOWN){
	  xprintf("%d ",i);
	  LED_ON();
	  LED_ON_counter= LED_SIGNAL_DURATION;
	}else if (i==CLICK){
	  LED_ON();
	  LED_ON_counter= LED_SIGNAL_DURATION; 
	}else if (i== DOUBLECLICK_EVENT){
	  LED_ON();
	  LED_ON_counter= LED_SIGNAL_DURATION;
	}else if (i== LONGPRESS_EVENT){
	  LED_ON();
	  LED_ON_counter= LED_SIGNAL_DURATION;
	}
	if (LED_ON_counter){
	  --LED_ON_counter;
	  if (LED_ON_counter==0){
	    LED_OFF();
	  }
	}

	//if (i==UP) LED_ON();
	//if (i==DOWN) LED_OFF();
      TimerEventFlag=FALSE;
    }
  } //END: while(1)
} //END: main



void init_USART1 (void){
  // Start UART clock:
  RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1, ENABLE ); 
}

/*
//This function does timing for the MS5611 baro sensor,
// based on the ststem clock tick.
static __IO uint32_t TimingDelay;

void Delay( uint32_t nTime ){  //To handle a blocking delay timer. Not precise.
  TimingDelay = nTime ;
  while ( TimingDelay != 0);   //Burn off time while the timer ISR occurs.
}
*/

void SysTick_Handler (void){            // Timer ISR
  // TimerEventFlag should not be set when we come here. 
  // That would mean, we could not handle the previous flag.
  if(TimerEventFlag == TRUE){
    //LED_ON();
  }  
  TimerEventFlag = TRUE;
  //AO! remove for cleaning.   ++GPIO_Delay;

  /* AO! Code Cleanup
  if ( TimingDelay != 0x00)  //Added for MS5611 timing.
    TimingDelay --;
  */
}

#ifdef USE_FULL_ASSERT
  void assert_failed ( uint8_t* file, uint32_t line)
  {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
  }
#endif

