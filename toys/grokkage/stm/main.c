#include <stdint.h>
//#include "stm32f4xx.h"
#include "hal_gpio_driver.h"

// LED code
// need base address of RCC to use with offsets
#define RCC_BASE_ADDR      (0x40023800)
#define RCC_AHB1ENR_OFFSET (0x50) // offset of RCC AHB1 with GPIO clock enable bits
#define RCC_AHB1ENR_ADDR *((volatile unsigned long *) (RCC_BASE_ADDR + RCC_AHB1ENR_OFFSET))


#define GPIOD_BASE_ADDR     (0x40020C00)
#define GPIOD_MODER_OFFSET  (0x00)
#define GPOIOD_MODER_ADDR *((volatile unsigned long *) (GPIOD_BASE_ADDR + GPIOD_MODER_OFFSET))

#define GPIOD_OUTPUT_DATA_OFFSET    (0x14)
#define GPIOD_INPUT_DATA_OFFSET     (0x10)

#define GPOIOD_OUTPUT_DATA_ADDR  *((volatile unsigned long *) (GPIOD_BASE_ADDR + GPIOD_OUTPUT_DATA_OFFSET))
#define GPOIOD_INPUT_DATA_ADDR   *((volatile unsigned long *) (GPIOD_BASE_ADDR + GPIOD_INPUT_DATA_OFFSET))

#define GPIO_PIN_12   12
#define GPIO_PIN_13   13
#define GPIO_PIN_14   14
#define GPIO_PIN_15   15


//#define LED_4 GPIO_PIN_12
//#define LED_3 GPIO_PIN_13
//#define LED_5 GPIO_PIN_14
//#define LED_6 GPIO_PIN_15

#define GPIO_BUTTON_PIN		0
#define GPIO_BUTTON_PORT  GPIOA

#define LED_GREEN					GPIO_PIN_12
#define LED_ORANGE        GPIO_PIN_13
#define LED_RED           GPIO_PIN_14
#define LED_BLUE					GPIO_PIN_15

void led_init() 
{
	gpio_pin_conf_t led_pin_conf;
	// enable clock for GPIOD port
	_HAL_RCC_GPIOD_CLK_ENABLE();

	GPIOA->MODER &= ~0x03;
	GPIOA->PUPDR &= ~0x03;
	
	// enable RCC clock
	RCC->APB2ENR |= 0x00004000;
	
	// config button interrupt as falling edge
	hal_gpio_configure_interrupt(GPIO_BUTTON_PIN, INT_RISING_FALLING_EDGE);
	// enable interrupt on EXTI0 line
	hal_gpio_enable_interrupt(GPIO_BUTTON_PIN, EXTI0_IRQn);
	
	led_pin_conf.pin = LED_ORANGE;
	led_pin_conf.mode = GPIO_PIN_OUTPUT_MODE;
	led_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL;
	led_pin_conf.speed = GPIO_PIN_SPEED_MEDIUM;
	led_pin_conf.pull = GPIO_PIN_NO_PULL_PUSH;
	hal_gpio_init(GPIOD, &led_pin_conf);
	
	led_pin_conf.pin = LED_BLUE;
	hal_gpio_init(GPIOD, &led_pin_conf);
	
	led_pin_conf.pin = LED_GREEN;
	hal_gpio_init(GPIOD, &led_pin_conf);

	led_pin_conf.pin = LED_RED;
	hal_gpio_init(GPIOD, &led_pin_conf);
}

void led_turn_on(GPIO_TypeDef *GPIOx, uint16_t pin)
{
	hal_gpio_write_to_pin(GPIOx, pin, 1);
}

void led_turn_off(GPIO_TypeDef *GPIOx, uint16_t pin)
{
	hal_gpio_write_to_pin(GPIOx, pin, 0);
}

void led_toggle(GPIO_TypeDef *GPIOx, uint16_t pin)
{
	if (hal_gpio_read_from_pin(GPIOx, pin)) {
		hal_gpio_write_to_pin(GPIOx, pin, 0);
	} else {
		hal_gpio_write_to_pin(GPIOx, pin, 1);
	}
}

void led_init2() 
{
    
    RCC->AHB1ENR |= (0x08 );
    
    //configure LED_GREEN . YELLOW 
    GPIOD->MODER  |= (0x01 << (LED_GREEN * 2));
    GPIOD->OTYPER |= ( 0 << LED_GREEN);
    GPIOD->PUPDR   |= (0x00 << (LED_GREEN * 2));
    GPIOD->OSPEEDR |= (0X00 << (LED_GREEN * 2));
    
        
    //configure LED_3 . SAFFRON  
    GPIOD->MODER  |= (0x01 << (LED_ORANGE * 2));
    GPIOD->OTYPER |= ( 0 << LED_ORANGE);
    GPIOD->PUPDR   |= (0x00 << (LED_ORANGE * 2));
    GPIOD->OSPEEDR |= (0X00 << (LED_ORANGE * 2));
    
        
    //configure LED_5 . RED 
    GPIOD->MODER  |= (0x01 << (LED_RED * 2));
    GPIOD->OTYPER |= ( 0 << LED_RED);
    GPIOD->PUPDR   |= (0x00 << (LED_RED * 2));
    GPIOD->OSPEEDR |= (0X00 << (LED_RED * 2));
    
        
    //configure LED_6 . BLUE 
    GPIOD->MODER  |= (0x01 << (LED_BLUE * 2));
    GPIOD->OTYPER |= ( 0 << LED_BLUE);
    GPIOD->PUPDR   |= (0x00 << (LED_BLUE * 2));
    GPIOD->OSPEEDR |= (0X00 << (LED_BLUE * 2));
    
}

void led_on(uint8_t led_no)
{
    GPIOD->BSRR = ( 1 << led_no );
}

void led_off(uint8_t led_no)
{
    GPIOD->BSRR = ( 1 << (led_no+16) );
}

void led_toggle2(uint8_t led_no)
{
    if(GPIOD->ODR & (1 << led_no) )
    {
        led_off(led_no);
    }else
    {
        led_on(led_no);
    }
    
}

void button_init()
{
    // 1. enable clock for GPIOA
    RCC->AHB1ENR |= 0x01;
    
    // 2. set mode of GPIOA pin 0 to input
    GPIOA->MODER &= ~0x03;
    
    // 3. set interrupt triggering level falling level
    EXTI->FTSR |= 0x01;
    
    // 4. enable interrupt over EXTI0 (EXTI_IMR)
    EXTI->IMR |= 0x01;
     
    // 5. interrupt on NVIC for IRQ 6 
    NVIC->ISER[0] |= (1 << EXTI0_IRQn);
    
}

void led_test()
{
    
    led_init();
    
    button_init();
    
    led_on(LED_GREEN);
    led_on(LED_ORANGE);
    led_on(LED_RED);
    led_on(LED_BLUE);
    
    /*infinite loop */
    while(1)
    {
    
    }
    
}

void led()
{
    // 1. enable the clock for GPIOD port
    RCC_AHB1ENR_ADDR |= (1 << 3);  // bit 3 is GPIOD EN see 6.3.9
    
    // 2. configure GPIO pins to output mode using MODE register
    GPOIOD_MODER_ADDR |= (1 << (12 * 2)); // set bits 24 & 25 to 0x01 to make GPIO pin 12 an output
    
    // 3. use the DATA register of GPIOD port to read/write LED
    GPOIOD_OUTPUT_DATA_ADDR  |= (1 << 12); // turn on bit 12
    
    while (1)
    {
        int i;
        for (i = 0; i < 500000; i++) ;
        if (GPOIOD_INPUT_DATA_ADDR & (1 << 12)) {
            GPOIOD_OUTPUT_DATA_ADDR  &= ~(1 << 12); // turn on bit 12           
        } else {
            GPOIOD_OUTPUT_DATA_ADDR  |= (1 << 12); // turn on bit 12
        }       
    }
}


int is_privileged_access()
{
    if ( ( __get_CONTROL() & 0X01 )) {
        return 0; // unprivileged
    } else {
        return 1; // we are privileged
    }
}

void go_to_unprivileged_access_level()
{
    __set_CONTROL(0x01);
}

void go_to_privileged_access_level()
{
    __set_CONTROL(0x04);
}

void lab2()
{
    //uint32_t val;    
    //val = __get_PRIMASK();
    //__set_PRIMASK(1);
    if (is_privileged_access()) {
        __set_PRIMASK(1);
        __set_PRIMASK(0);       
    }
    
    // now make processor move to un-priv level
    go_to_unprivileged_access_level();
    
    // and try to change the restricted register
    __set_PRIMASK(1);
    __set_PRIMASK(0);       
}

void lab3()
{
    // demo bit-banding (atomic R-M-W)
#define BIT_BAND_REGION_MEM_ADDR_1 *((volatile unsigned long *)(0x20000000))
#define BIT_BAND_ALIAS_BASE_ADDRESS (0x22000000)

// define bits 0, 1, 2 
#define BIT_BAND_ALIAS_ADDRESS_1 *((volatile unsigned long *) (BIT_BAND_ALIAS_BASE_ADDRESS+0))
#define BIT_BAND_ALIAS_ADDRESS_2 *((volatile unsigned long *) (BIT_BAND_ALIAS_BASE_ADDRESS+4))
#define BIT_BAND_ALIAS_ADDRESS_3 *((volatile unsigned long *) (BIT_BAND_ALIAS_BASE_ADDRESS+8))

    BIT_BAND_REGION_MEM_ADDR_1 = 0xA0;
    BIT_BAND_ALIAS_ADDRESS_1 = 0x01;
    BIT_BAND_ALIAS_ADDRESS_2 = 0x01;
    BIT_BAND_ALIAS_ADDRESS_3 = 0x01;

	  //int val;
    //val = BIT_BAND_REGION_MEM_ADDR_1;

}

extern void do_stack_operations(void);
void lab4()
{
    do_stack_operations(); // in assembly
}

int add(int a, int b)
{
	return (a+b);
}

int mul(int a, int b)
{
	return (a*b);
}

void PendSV_IRQHandler(void)
{
}

void EXTI0_IRQHandler(void)
{
	if ( (EXTI->PR & 0x01) ) {
		EXTI->PR = 0x01;
	}
	led_toggle2(LED_GREEN);
	
	// process the rest in PendSV handler
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void PendSV_Handler(void)
{
	led_toggle2(LED_ORANGE);
}

void trigger_svc()
{
	// service number is not passed to exception handler
	// but rather extracts via PC - decodes LR value, then PC 
	// inc MSP by 6
	// next_instruction_after_svc = MSP[6];
	// SVC_number = *( (next_instruction_after_svc) - 2);
	
	// PendSV exception is like a DPC or bottom half
	// is pended by SysTick to do context switching
	
	
}


void driver_led_test()
{
	uint32_t i;
	led_init();
	
	while (1) {
		led_turn_on(GPIOD, LED_ORANGE);
		led_turn_on(GPIOD, LED_BLUE);
		
		for (i = 0; i < 500000; i++) ;
		
		led_turn_off(GPIOD, LED_ORANGE);
		led_turn_off(GPIOD, LED_BLUE);
		
		for (i = 0; i < 500000; i++) ;
		
	}
	
}

int main()
{
    //lab2();
    //lab3();
    //lab4();
    //lab5();
    //led_test();
	  driver_led_test();
    return 0;
}
