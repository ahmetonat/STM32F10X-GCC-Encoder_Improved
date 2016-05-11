
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>


#define NumKeys 3  //Keys: Encoder A, B, Click
// ENC A: GPIO PA0: WKUP, UART2_CTS, TIM2_CH1_ETR, ADC12-1
// ENC B: GPIO PA1: UART2_RTS, TIM2_CH2, ADC12-2
// ENC C: GPIO PA3: UART2_RX, TIM2_CH4, ADC12-4 (nearer edge of conn than PA2)

#define ENC_A_GPIO_PIN GPIO_Pin_1
#define ENC_B_GPIO_PIN GPIO_Pin_3
#define ENC_C_GPIO_PIN GPIO_Pin_0
#define ENC_GPIO_PORT GPIOA

//Random definitions of keys to address easily later on.
#define ENC_A 0
#define ENC_B 1
#define ENC_C 2

#define KeyPressed 0
#define KeyAtRest 1

#define UP 1
#define DOWN 0
#define NOCHANGE 2
#define CLICK 3  //encoder top key pressed.

///////////////////////////////////////////////
//Double Click functionality implementation:
// States of the encoder press button.

#define LONGPRESS_EVENT 4
#define DOUBLECLICK_EVENT 5

#define C_IDLE       0
#define C_CLICKED1   1
#define C_UNCLICKED1 2
#define C_CLICKED2   3
#define C_ROTATING   4

#define C_LONGPRESS_DURATION 3000
#define C_DOUBLECLICK_MINLIM 50
#define C_DOUBLECLICK_MAXLIM 900



///////////////////////////////////////////////



void init_ENC (void); //Initialize the functions of the encoder.
void init_ENC_GPIO (void); //Initialize the HW related to encoder.
void check_keypress(uint8_t key); //Encoder debounce pins
int EncRead_Guarded(void);        //Encoder interpret.
