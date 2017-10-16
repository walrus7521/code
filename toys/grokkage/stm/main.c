#include <stdint.h>
#include "stm32f4xx.h"

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


#define LED_4 GPIO_PIN_12
#define LED_3 GPIO_PIN_13
#define LED_5 GPIO_PIN_14
#define LED_6 GPIO_PIN_15

void led_init() 
{
    
    RCC->AHB1ENR |= (0x08 );
    
    //configure LED_4 . YELLOW 
    GPIOD->MODER  |= (0x01 << (LED_4 * 2));
    GPIOD->OTYPER |= ( 0 << LED_4);
    GPIOD->PUPDR   |= (0x00 << (LED_4 * 2));
    GPIOD->OSPEEDR |= (0X00 << (LED_4 * 2));
    
        
    //configure LED_3 . SAFFRON  
    GPIOD->MODER  |= (0x01 << (LED_3 * 2));
    GPIOD->OTYPER |= ( 0 << LED_3);
    GPIOD->PUPDR   |= (0x00 << (LED_3 * 2));
    GPIOD->OSPEEDR |= (0X00 << (LED_3 * 2));
    
        
    //configure LED_5 . RED 
    GPIOD->MODER  |= (0x01 << (LED_5 * 2));
    GPIOD->OTYPER |= ( 0 << LED_5);
    GPIOD->PUPDR   |= (0x00 << (LED_5 * 2));
    GPIOD->OSPEEDR |= (0X00 << (LED_5 * 2));
    
        
    //configure LED_6 . BLUE 
    GPIOD->MODER  |= (0x01 << (LED_6 * 2));
    GPIOD->OTYPER |= ( 0 << LED_6);
    GPIOD->PUPDR   |= (0x00 << (LED_6 * 2));
    GPIOD->OSPEEDR |= (0X00 << (LED_6 * 2));
    
}

void led_on(uint8_t led_no)
{
    GPIOD->BSRR = ( 1 << led_no );
}

void led_off(uint8_t led_no)
{
    GPIOD->BSRR = ( 1 << (led_no+16) );
}


void led_toggle(uint8_t led_no)
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

void EXTI0_IRQHandler(void)
{
    // 1. clear the interrupt in EXTI0 in interrupt pending register
    if ( (EXTI->PR & 0x01) ) {
        EXTI->PR &= 0x01;
    }
    led_toggle(LED_4);
    led_toggle(LED_3);
    led_toggle(LED_5);
    led_toggle(LED_6);
}

void led_test()
{
    
    led_init();
    
    button_init();
    
    led_on(LED_4);
    led_on(LED_3);
    led_on(LED_5);
    led_on(LED_6);
    
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
    uint32_t val;
    
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

    uint32_t val;
    BIT_BAND_REGION_MEM_ADDR_1 = 0xA0;
    BIT_BAND_ALIAS_ADDRESS_1 = 0x01;
    BIT_BAND_ALIAS_ADDRESS_2 = 0x01;
    BIT_BAND_ALIAS_ADDRESS_3 = 0x01;

    val = BIT_BAND_REGION_MEM_ADDR_1;

}

extern void do_stack_operations();
void lab4()
{
    do_stack_operations(); // in assembly
}

void lab5()
{
    // masking exceptions
 
}

int main()
{
    //lab2();
    //lab3();
    //lab4();
    //lab5();
    led_test();
    return 0;
}
