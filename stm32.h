#ifndef STM32_H
#define STM32_H


#define RCC_BASE ((volatile int *) 0x40023800)
#define FSMC_BASE ((volatile int *) 0xA0000000)
#define RNG_BASE ((volatile int *) 0x50060800)
#define HASH_BASE ((volatile int *) 0x50060400)
#define CRYP_BASE ((volatile int *) 0x50060000)
#define DCMI_BASE ((volatile int *) 0x50050000)
#define USB_BASE ((volatile int *) 0x50000000)
#define USB_BASE2 ((volatile int *) 0x40040000)
#define ETHERNET_BASE ((volatile int *) 0x40028800)
#define DMA2_BASE ((volatile int *) 0x40026400)
#define DMA1_BASE ((volatile int *) 0x40026000)
#define BKPSRAM_BASE ((volatile int *) 0x40024000)
#define Flash_BASE ((volatile int *) 0x40023C00)
#define CRC_BASE ((volatile int *) 0x40023000)
#define GPIOI_BASE ((volatile int *) 0x40022000)
#define GPIOH_BASE ((volatile int *) 0x40021C00)
#define GPIOG_BASE ((volatile int *) 0x40021800)
#define GPIOF_BASE ((volatile int *) 0x40021400)
#define GPIOE_BASE ((volatile int *) 0x40021000)
#define GPIOD_BASE ((volatile int *) 0x40020c00)
#define GPIOC_BASE ((volatile int *) 0x40020800)
#define GPIOB_BASE ((volatile int *) 0x40020400)
#define GPIOA_BASE ((volatile int *) 0x40020000)
#define TIM11_BASE ((volatile int *) 0x40014800)
#define TIM10_BASE ((volatile int *) 0x40014400)
#define TIM9_BASE ((volatile int *) 0x40014000)
#define EXTI_BASE ((volatile int *) 0x40013C00)
#define SYSCFG_BASE ((volatile int *) 0x40013800)
#define SPI1_BASE ((volatile int *) 0x40013000)
#define SDIO_BASE ((volatile int *) 0x40012C00)
#define ADC1_BASE ((volatile int *) 0x40012000)
#define USART6_BASE ((volatile int *) 0x40011400)
#define USART1_BASE ((volatile int *) 0x40011000)
#define TIM8_BASE ((volatile int *) 0x40010400)
#define TIM1_BASE ((volatile int *) 0x40010000)
#define DAC_BASE ((volatile int *) 0x40007400)
#define PWR_BASE ((volatile int *) 0x40007000)
#define CAN2_BASE ((volatile int *) 0x40006800)
#define CAN1_BASE ((volatile int *) 0x40006400)
#define I2C3_BASE ((volatile int *) 0x40005C00)
#define I2C2_BASE ((volatile int *) 0x40005800)
#define I2C1_BASE ((volatile int *) 0x40005400)
#define UART5_BASE ((volatile int *) 0x40005000)
#define UART4_BASE ((volatile int *) 0x40004C00)
#define USART3_BASE ((volatile int *) 0x40004800)
#define USART2_BASE ((volatile int *) 0x40004400)
#define I2S3ext_BASE ((volatile int *) 0x40004000)
#define SPI3_BASE ((volatile int *) 0x40003C00)
#define SPI2_BASE ((volatile int *) 0x40003800)
#define I2S2ext_BASE ((volatile int *) 0x40003400)
#define IWDG_BASE ((volatile int *) 0x40003000)
#define WWDG_BASE ((volatile int *) 0x40002C00)
#define RTC_BASE ((volatile int *) 0x40002800)
#define TIM14_BASE ((volatile int *) 0x40002000)
#define TIM13_BASE ((volatile int *) 0x40001C00)
#define TIM12_BASE ((volatile int *) 0x40001800)
#define TIM7_BASE ((volatile int *) 0x40001400)
#define TIM6_BASE ((volatile int *) 0x40001000)
#define TIM5_BASE ((volatile int *) 0x40000C00)
#define TIM4_BASE ((volatile int *) 0x40000800)
#define TIM3_BASE ((volatile int *) 0x40000400)
#define TIM2_BASE ((volatile int *) 0x40000000)

#define rcc_cr        ( RCC_BASE + 0/sizeof(*RCC_BASE))
#define rcc_pllcfgr   ( RCC_BASE + 4/sizeof(*RCC_BASE))
#define rcc_cfgr      ( RCC_BASE + 8/sizeof(*RCC_BASE))
#define rcc_cir       ( RCC_BASE + 12/sizeof(*RCC_BASE))
#define rcc_ahb1rstr  ( RCC_BASE + 0x10/sizeof(*RCC_BASE))
#define rcc_ahb2rstr  ( RCC_BASE + 0x14/sizeof(*RCC_BASE))
#define rcc_ahb3rstr  ( RCC_BASE + 0x18/sizeof(*RCC_BASE))
#define rcc_apb1rstr  ( RCC_BASE + 0x20/sizeof(*RCC_BASE))
#define rcc_apb2rstr  ( RCC_BASE + 0x24/sizeof(*RCC_BASE))
#define rcc_ahb1enr   ( RCC_BASE + 0x30/sizeof(*RCC_BASE))
#define rcc_ahb2enr   ( RCC_BASE + 0x34/sizeof(*RCC_BASE))
#define rcc_ahb3enr   ( RCC_BASE + 0x38/sizeof(*RCC_BASE))
#define rcc_apb1enr   ( RCC_BASE + 0x40/sizeof(*RCC_BASE))
#define rcc_apb1lpenr   ( RCC_BASE + 0x60/sizeof(*RCC_BASE))
#define rcc_apb2enr   ( RCC_BASE + 0x44/sizeof(*RCC_BASE))
#define rcc_ahb1lpenr   ( RCC_BASE + 0x50/sizeof(*RCC_BASE))
#define rcc_bdcr  ( RCC_BASE + 0x70/sizeof(*RCC_BASE))
#define rcc_csr  ( RCC_BASE + 0x74/sizeof(*RCC_BASE))
#define rcc_sscgr  ( RCC_BASE + 0x80/sizeof(*RCC_BASE))
#define rcc_plli2scfgr   ( RCC_BASE + 0x84/sizeof(*RCC_BASE))
#define gpioa_moder    ( GPIOA_BASE + 0/sizeof(*RCC_BASE))
#define gpioa_otyper   ( GPIOA_BASE + 4/sizeof(*RCC_BASE))
#define gpioa_ospeedr  ( GPIOA_BASE + 8/sizeof(*RCC_BASE))
#define gpioa_pupdr    ( GPIOA_BASE + 12/sizeof(*RCC_BASE))
#define gpioa_idr      ( GPIOA_BASE + 0x10/sizeof(*RCC_BASE))
#define gpioa_odr      ( GPIOA_BASE + 0x14/sizeof(*RCC_BASE))
#define gpioa_bsrr     ( GPIOA_BASE + 0x18/sizeof(*RCC_BASE))
#define gpioa_lckr     ( GPIOA_BASE + 0x1c/sizeof(*RCC_BASE))
#define gpioa_afrl     ( GPIOA_BASE + 0x20/sizeof(*RCC_BASE))
#define gpioa_afrh     ( GPIOA_BASE + 0x24/sizeof(*RCC_BASE))
#define gpiob_moder    ( GPIOB_BASE + 0/sizeof(*RCC_BASE))
#define gpiob_otyper   ( GPIOB_BASE + 4/sizeof(*RCC_BASE))
#define gpiob_ospeedr  ( GPIOB_BASE + 8/sizeof(*RCC_BASE))
#define gpiob_pupdr    ( GPIOB_BASE + 12/sizeof(*RCC_BASE))
#define gpiob_idr      ( GPIOB_BASE + 0x10/sizeof(*RCC_BASE))
#define gpiob_odr      ( GPIOB_BASE + 0x14/sizeof(*RCC_BASE))
#define gpiob_bsrr     ( GPIOB_BASE + 0x18/sizeof(*RCC_BASE))
#define gpiob_lckr     ( GPIOB_BASE + 0x1c/sizeof(*RCC_BASE))
#define gpiob_afrl     ( GPIOB_BASE + 0x20/sizeof(*RCC_BASE))
#define gpiob_afrh     ( GPIOB_BASE + 0x24/sizeof(*RCC_BASE))
#define gpioc_moder    ( GPIOC_BASE + 0/sizeof(*RCC_BASE))
#define gpioc_otyper   ( GPIOC_BASE + 4/sizeof(*RCC_BASE))
#define gpioc_ospeedr  ( GPIOC_BASE + 8/sizeof(*RCC_BASE))
#define gpioc_pupdr    ( GPIOC_BASE + 12/sizeof(*RCC_BASE))
#define gpioc_idr      ( GPIOC_BASE + 0x10/sizeof(*RCC_BASE))
#define gpioc_odr      ( GPIOC_BASE + 0x14/sizeof(*RCC_BASE))
#define gpioc_bsrr     ( GPIOC_BASE + 0x18/sizeof(*RCC_BASE))
#define gpioc_lckr     ( GPIOC_BASE + 0x1c/sizeof(*RCC_BASE))
#define gpioc_afrl     ( GPIOC_BASE + 0x20/sizeof(*RCC_BASE))
#define gpioc_afrh     ( GPIOC_BASE + 0x24/sizeof(*RCC_BASE))
#define gpiod_moder    ( GPIOD_BASE + 0/sizeof(*RCC_BASE))
#define gpiod_otyper   ( GPIOD_BASE + 4/sizeof(*RCC_BASE))
#define gpiod_ospeedr  ( GPIOD_BASE + 8/sizeof(*RCC_BASE))
#define gpiod_pupdr    ( GPIOD_BASE + 12/sizeof(*RCC_BASE))
#define gpiod_idr      ( GPIOD_BASE + 0x10/sizeof(*RCC_BASE))
#define gpiod_odr      ( GPIOD_BASE + 0x14/sizeof(*RCC_BASE))
#define gpiod_bsrr     ( GPIOD_BASE + 0x18/sizeof(*RCC_BASE))
#define gpiod_lckr     ( GPIOD_BASE + 0x1c/sizeof(*RCC_BASE))
#define gpiod_afrl     ( GPIOD_BASE + 0x20/sizeof(*RCC_BASE))
#define gpiod_afrh     ( GPIOD_BASE + 0x24/sizeof(*RCC_BASE))
#define gpioe_moder    ( GPIOE_BASE + 0/sizeof(*RCC_BASE))
#define gpioe_otyper   ( GPIOE_BASE + 4/sizeof(*RCC_BASE))
#define gpioe_ospeedr  ( GPIOE_BASE + 8/sizeof(*RCC_BASE))
#define gpioe_pupdr    ( GPIOE_BASE + 12/sizeof(*RCC_BASE))
#define gpioe_idr      ( GPIOE_BASE + 0x10/sizeof(*RCC_BASE))
#define gpioe_odr      ( GPIOE_BASE + 0x14/sizeof(*RCC_BASE))
#define gpioe_bsrr     ( GPIOE_BASE + 0x18/sizeof(*RCC_BASE))
#define gpioe_lckr     ( GPIOE_BASE + 0x1c/sizeof(*RCC_BASE))
#define gpioe_afrl     ( GPIOE_BASE + 0x20/sizeof(*RCC_BASE))
#define gpioe_afrh     ( GPIOE_BASE + 0x24/sizeof(*RCC_BASE))
#define pwr_cr  ( PWR_BASE + 0/sizeof(*PWR_BASE))
#define pwr_csr  ( PWR_BASE + 4/sizeof(*PWR_BASE))
#define exti_imr  ( EXTI_BASE + 0/sizeof(*EXTI_BASE))
#define exti_emr  ( EXTI_BASE + 4/sizeof(*EXTI_BASE))
#define exti_rtsr  ( EXTI_BASE + 8/sizeof(*EXTI_BASE))
#define exti_ftsr  ( EXTI_BASE + 0xc/sizeof(*EXTI_BASE))
#define exti_swier  ( EXTI_BASE + 0x10/sizeof(*EXTI_BASE))
#define exti_pr  ( EXTI_BASE + 0x14/sizeof(*EXTI_BASE))

#define usart2_sr  ( (USART2_BASE + 0))
#define usart2_dr  ( (USART2_BASE + 1))
#define usart2_brr  ( (USART2_BASE + 2))
#define usart2_cr1  ( (USART2_BASE + 3))
#define usart2_cr2  ( (USART2_BASE + 4))
#define usart2_cr3  ( (USART2_BASE + 5))
#define usart2_gtpr  ( (USART2_BASE + 6))

/* System control block (SCB) */
#define ICTR	(volatile int *)0xe000e004
#define ACTLR	(volatile int *)0xe000e008
#define CPUID	(volatile int *)0xe000ed00
#define ICSR	(volatile int *)0xe000ed04
#define VTOR	(volatile int *)0xe000ed08
#define AIRCR	(volatile int *)0xe000ed0c
#define SCR	(volatile int *)0xe000ed10
#define CCR	(volatile int *)0xe000ed14
#define SHPR1	(volatile int *)0xe000ed18
#define SHPR2	(volatile int *)0xe000ed1c
#define SHPR3	(volatile int *)0xe000ed20
#define SHCRS	(volatile int *)0xe000ed24
#define CFSR	(volatile int *)0xe000ed28
#define MMSR	(volatile int *)0xe000ed28
#define BFSR	(volatile int *)0xe000ed29
#define UFSR	(volatile int *)0xe000ed2a
#define HFSR	(volatile int *)0xe000ed2c
#define MMAR	(volatile int *)0xe000ed34
#define BFAR	(volatile int *)0xe000ed38
#define AFSR	(volatile int *)0xe000ed3c

#define NVIC_ISER (volatile int *)0xE000E100
#define NVIC_ICER (volatile int *)0xE000E180

#define NVIC_ISPR (volatile int *)0xE000E200
#define NVIC_ICPR (volatile int *)0xE000E280

#define NVIC_IAPR (volatile int *)0xE000E300

#define NVIC_IPR (volatile int *)0xE000E400

#endif
