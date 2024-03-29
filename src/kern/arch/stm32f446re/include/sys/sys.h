#ifndef __SYS_H__
#define __SYS_H__
#include <stdint.h>

typedef struct
{
  volatile uint32_t CTRL; // Enable SysTick
  volatile uint32_t LOAD; // 24
  volatile uint32_t VAL;
  volatile uint32_t CALIB;
} SysTick_Typedef;
// Address for SysTick 0xE000E010
#define SYSTICK ((SysTick_Typedef *)0xE000E010)
#define SYSTICK_CTRL_CLKSOURCE_AHB (1 << 2)
#define SYSTICK_CTRL_TICKINT (1 << 1)
#define SYSTICK_CTRL_ENABLE (1 << 0)
#define SYSTICK_CTRL_DISABLE ~(1 << 0)
#define PER_TICK_TIME_DELAY_MS 10U
/*
    SysTick Test Code
    180*10^6*10^(-2)-1 = 1799999 = Reload value for 10ms, for AHBCLK = 180Mhz
    SysTick Interrup Time Period = (SysTick_LOAD + 1) * Clock_Period
*/
#define SYSTICK_LOAD_VAL_10MS (((180 * 10 * 10 * 10 * 10 * 10 * 10) * (PER_TICK_TIME_DELAY_MS) / 1000) - 1)

typedef struct
{
  volatile uint32_t CPUID; // CPUID Base Register 0x0
  volatile uint32_t ICSR;  // Interrupt Control and State Register 0x4
  volatile uint32_t VTOR;  // Vector Table Offset Register 0x8
  volatile uint32_t AIRCR; // Application Interrupt and Reset Control Register 0xC
  volatile uint32_t SCR;   // System Control Register 0x10
  volatile uint32_t CCR;   // Configuration and Control Register 0x14
  volatile uint32_t SHPR1; // System Handler Priority Register 1 0x18
  volatile uint32_t SHPR2; // System Handler Priority Register 2 0x1C
  volatile uint32_t SHPR3; // System Handler Priority Register 3 0x20
  volatile uint32_t SHCSR; // System Handler Control and State Register 0x24
  volatile uint32_t CFSR;  // Configurable Fault Status Register combined of MemManage
  // Fault Status Register, BusFault Status Register, UsageFault Status Register 0x28
  volatile uint32_t HFSR;  // HardFault Status Register 0x2C
  uint32_t RESERVED;       // 0x30
  volatile uint32_t MMAR;  // MemManage Fault Address Register 0x34
  volatile uint32_t BFAR;  // BusFault Address Register 0x38
  volatile uint32_t AFSR;  // Auxiliary Fault Status Register 0x3C
  uint32_t RESERVED1[18];  // 0x40
  volatile uint32_t CPACR; // Coprocessor access control register 0x88
} SCB_TypeDef;
// SCB data structure: The starting address for SCB is ‘0xE000E010’
#define SCB ((SCB_TypeDef *)0xE000ED00)

typedef struct
{
  // define NVIC register compenenets -- use volatile data type
  volatile uint32_t ISER[8]; /*!< Offset: 0x000 Interrupt Set Enable Register*/
  uint32_t RESERVED0[24];
  volatile uint32_t ICER[8]; /*!< Offset: 0x180 Interrupt Clear Enable Register*/
  uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8]; /*!< Offset: 0x200 Interrupt Set Pending Register*/
  uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8]; /*!< Offset: 0x280 Interrupt Clear Pending Register*/
  uint32_t RESERVED3[24];
  volatile uint32_t IABR[8]; /*!< Offset: 0x300 Interrupt Active bit Register*/
  uint32_t RESERVED4[56];
  volatile uint8_t IP[240]; /*!< Offset: 0x400 Interrupt Priority Register (8Bit wide) */
  uint32_t RESERVED5[644];
  volatile uint32_t STIR; /*!< Offset: 0xF00 Software Trigger Interrupt Register*/
} NVIC_TypeDef;
// NVIC Data Structure: Starting address: ‘0xE000E100’
#define NVIC ((NVIC_TypeDef *)0xE000E100)

typedef enum
{
  // Needed Exceptions
  NonMaskableInt_IRQn = -14, /*!< 2 Non Maskable Interrupt                                          */
  HardFault_IRQn = -13,
  MemoryManagement_IRQn = -12, /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  BusFault_IRQn = -11,         /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  UsageFault_IRQn = -10,       /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  SecureFault_IRQn = -9,
  SVCall_IRQn = -5,                 /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  DebugMonitor_IRQn = -4,           /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  PendSV_IRQn = -2,                 /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  SysTick_IRQn = -1,                /*!< 15 Cortex-M4 System Tick Interrupt                                */
                                    // STM32 specific Interrupt Numbers
  WWDG_STM_IRQn = 0,                /*!< Window WatchDog Interrupt                                         */
  PVD_STM_IRQn = 1,                 /*!< PVD through EXTI Line detection Interrupt                         */
  TAMP_STAMP_STM_IRQn = 2,          /*!< Tamper and TimeStamp interrupts through the EXTI line             */
  RTC_WKUP_STM_IRQn = 3,            /*!< RTC Wakeup interrupt through the EXTI line                        */
  FLASH_STM_IRQn = 4,               /*!< FLASH global Interrupt                                            */
  RCC_STM_IRQn = 5,                 /*!< RCC global Interrupt                                              */
  EXTI0_STM_IRQn = 6,               /*!< EXTI Line0 Interrupt                                              */
  EXTI1_STM_IRQn = 7,               /*!< EXTI Line1 Interrupt                                              */
  EXTI2_STM_IRQn = 8,               /*!< EXTI Line2 Interrupt                                              */
  EXTI3_STM_IRQn = 9,               /*!< EXTI Line3 Interrupt                                              */
  EXTI4_STM_IRQn = 10,              /*!< EXTI Line4 Interrupt                                              */
  DMA1_Stream0_STM_IRQn = 11,       /*!< DMA1 Stream 0 global Interrupt                                    */
  DMA1_Stream1_STM_IRQn = 12,       /*!< DMA1 Stream 1 global Interrupt                                    */
  DMA1_Stream2_STM_IRQn = 13,       /*!< DMA1 Stream 2 global Interrupt                                    */
  DMA1_Stream3_STM_IRQn = 14,       /*!< DMA1 Stream 3 global Interrupt                                    */
  DMA1_Stream4_STM_IRQn = 15,       /*!< DMA1 Stream 4 global Interrupt                                    */
  DMA1_Stream5_STM_IRQn = 16,       /*!< DMA1 Stream 5 global Interrupt                                    */
  DMA1_Stream6_STM_IRQn = 17,       /*!< DMA1 Stream 6 global Interrupt                                    */
  ADC_STM_IRQn = 18,                /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
  CAN1_TX_STM_IRQn = 19,            /*!< CAN1 TX Interrupt                                                 */
  CAN1_RX0_STM_IRQn = 20,           /*!< CAN1 RX0 Interrupt                                                */
  CAN1_RX1_STM_IRQn = 21,           /*!< CAN1 RX1 Interrupt                                                */
  CAN1_SCE_STM_IRQn = 22,           /*!< CAN1 SCE Interrupt                                                */
  EXTI9_5_STM_IRQn = 23,            /*!< External Line[9:5] Interrupts                                     */
  TIM1_BRK_TIM9_STM_IRQn = 24,      /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
  TIM1_UP_TIM10_STM_IRQn = 25,      /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
  TIM1_TRG_COM_TIM11_STM_IRQn = 26, /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
  TIM1_CC_STM_IRQn = 27,            /*!< TIM1 Capture Compare Interrupt                                    */
  TIM2_STM_IRQn = 28,               /*!< TIM2 global Interrupt                                             */
  TIM3_STM_IRQn = 29,               /*!< TIM3 global Interrupt                                             */
  TIM4_STM_IRQn = 30,               /*!< TIM4 global Interrupt                                             */
  I2C1_EV_STM_IRQn = 31,            /*!< I2C1 Event Interrupt                                              */
  I2C1_ER_STM_IRQn = 32,            /*!< I2C1 Error Interrupt                                              */
  I2C2_EV_STM_IRQn = 33,            /*!< I2C2 Event Interrupt                                              */
  I2C2_ER_STM_IRQn = 34,            /*!< I2C2 Error Interrupt                                              */
  SPI1_STM_IRQn = 35,               /*!< SPI1 global Interrupt                                             */
  SPI2_STM_IRQn = 36,               /*!< SPI2 global Interrupt                                             */
  USART1_STM_IRQn = 37,             /*!< USART1 global Interrupt                                           */
  USART2_STM_IRQn = 38,             /*!< USART2 global Interrupt                                           */
  USART3_STM_IRQn = 39,             /*!< USART3 global Interrupt                                           */
  EXTI15_10_STM_IRQn = 40,          /*!< External Line[15:10] Interrupts                                   */
  RTC_Alarm_STM_IRQn = 41,          /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  OTG_FS_WKUP_STM_IRQn = 42,        /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
  TIM8_BRK_TIM12_STM_IRQn = 43,     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
  TIM8_UP_TIM13_STM_IRQn = 44,      /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
  TIM8_TRG_COM_TIM14_STM_IRQn = 45, /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
  TIM8_CC_STM_IRQn = 46,            /*!< TIM8 Capture Compare global interrupt                             */
  DMA1_Stream7_STM_IRQn = 47,       /*!< DMA1 Stream7 Interrupt                                            */
  FMC_STM_IRQn = 48,                /*!< FMC global Interrupt                                              */
  SDIO_STM_IRQn = 49,               /*!< SDIO global Interrupt                                             */
  TIM5_STM_IRQn = 50,               /*!< TIM5 global Interrupt                                             */
  SPI3_STM_IRQn = 51,               /*!< SPI3 global Interrupt                                             */
  UART4_STM_IRQn = 52,              /*!< UART4 global Interrupt                                            */
  UART5_STM_IRQn = 53,              /*!< UART5 global Interrupt                                            */
  TIM6_DAC_STM_IRQn = 54,           /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
  TIM7_STM_IRQn = 55,               /*!< TIM7 global interrupt                                             */
  DMA2_Stream0_STM_IRQn = 56,       /*!< DMA2 Stream 0 global Interrupt                                    */
  DMA2_Stream1_STM_IRQn = 57,       /*!< DMA2 Stream 1 global Interrupt                                    */
  DMA2_Stream2_STM_IRQn = 58,       /*!< DMA2 Stream 2 global Interrupt                                    */
  DMA2_Stream3_STM_IRQn = 59,       /*!< DMA2 Stream 3 global Interrupt                                    */
  DMA2_Stream4_STM_IRQn = 60,       /*!< DMA2 Stream 4 global Interrupt                                    */
  CAN2_TX_STM_IRQn = 63,            /*!< CAN2 TX Interrupt                                                 */
  CAN2_RX0_STM_IRQn = 64,           /*!< CAN2 RX0 Interrupt                                                */
  CAN2_RX1_STM_IRQn = 65,           /*!< CAN2 RX1 Interrupt                                                */
  CAN2_SCE_STM_IRQn = 66,           /*!< CAN2 SCE Interrupt                                                */
  OTG_FS_STM_IRQn = 67,             /*!< USB OTG FS global Interrupt                                       */
  DMA2_Stream5_STM_IRQn = 68,       /*!< DMA2 Stream 5 global interrupt                                    */
  DMA2_Stream6_STM_IRQn = 69,       /*!< DMA2 Stream 6 global interrupt                                    */
  DMA2_Stream7_STM_IRQn = 70,       /*!< DMA2 Stream 7 global interrupt                                    */
  USART6_STM_IRQn = 71,             /*!< USART6 global interrupt                                           */
  I2C3_EV_STM_IRQn = 72,            /*!< I2C3 event interrupt                                              */
  I2C3_ER_STM_IRQn = 73,            /*!< I2C3 error interrupt                                              */
  OTG_HS_EP1_OUT_STM_IRQn = 74,     /*!< USB OTG HS End Point 1 Out global interrupt                       */
  OTG_HS_EP1_IN_STM_IRQn = 75,      /*!< USB OTG HS End Point 1 In global interrupt                        */
  OTG_HS_WKUP_STM_IRQn = 76,        /*!< USB OTG HS Wakeup through EXTI interrupt                          */
  OTG_HS_STM_IRQn = 77,             /*!< USB OTG HS global interrupt                                       */
  DCMI_STM_IRQn = 78,               /*!< DCMI global interrupt                                             */
  FPU_STM_IRQn = 81,                /*!< FPU global interrupt                                              */
  SPI4_STM_IRQn = 84,               /*!< SPI4 global Interrupt                                             */
  SAI1_STM_IRQn = 87,               /*!< SAI1 global Interrupt                                             */
  SAI2_STM_IRQn = 91,               /*!< SAI2 global Interrupt                                             */
  QUADSPI_STM_IRQn = 92,            /*!< QuadSPI global Interrupt                                          */
  CEC_STM_IRQn = 93,                /*!< CEC global Interrupt                                              */
  SPDIF_RX_STM_IRQn = 94,           /*!< SPDIF-RX global Interrupt                                          */
  FMPI2C1_EV_STM_IRQn = 95,         /*!< FMPI2C1 Event Interrupt                                           */
  FMPI2C1_ER_STM_IRQn = 96          /*!< FMPI2C1 Error Interrupt                                           */
} IRQn_TypeDef;

void __NVIC_SetPriority(IRQn_TypeDef IRQn, uint32_t priority);
uint32_t __NVIC_GetPriority(IRQn_TypeDef IRQn);
void __NVIC_EnableIRQn(IRQn_TypeDef IRQn);
void __NVIC_DisableIRQn(IRQn_TypeDef IRQn);
__attribute__((naked)) void __set_BASEPRI(uint32_t value);
__attribute__((naked)) void __unset_BASEPRI(void);
__attribute__((naked)) void __set_PRIMASK(uint32_t priMask);
__attribute__((naked)) uint32_t __get_PRIMASK(void);
uint32_t __get_BASEPRI(void);
__attribute__((naked)) void __set_FAULTMASK(uint32_t faultMask);
__attribute__((naked)) uint32_t __get_FAULTMASK(void);
#define __enable_irq() __set_PRIMASK(0x00U)
#define __disable_irq() __set_PRIMASK(0x01U)
#define __enable_fault_irq() __set_FAULTMASK(0x00U)
#define __disable_fault_irq() __set_FAULTMASK(0x01U)
void __clear_pending_IRQn(IRQn_TypeDef IRQn);
uint32_t __get_pending_IRQn(IRQn_TypeDef IRQn);
uint32_t __NVIC_GetActive(IRQn_TypeDef IRQn);
/*
This function configure the system timer with interrupt. This function must disable the SysTick
timer, set ‘0’ to VAL register content, and load the reload value so the SysTick timer can interrupt every 10ms. Initialize a global variable ‘mscount’ to ‘0’. The ‘mscount’ variable keeps track of the time in milliseconds from the SysTick timer’s beginning. Then enable the SysTick timer.
*/
void sysTick_init(uint32_t load_value);
/*
This function enables the disabled SysTick timer. The function does not modify an active SysTick timer and ‘mscount’ global variable. However, if the timer is currently disabled, the function must initialize the ‘mscount’ to ‘0’ before enabling it.
*/
void sysTick_enable(void);
// The sysTick disable function disables the SysTick timer if it is currently disabled.
void sysTick_disable(void);
// This function returns the current content of the VAL register.
uint32_t getSysTickCount();
/*
he update function disables the timer, initializes the reload value to the LOAD register, and finally initializes the ‘mscount’ variable.
*/
void updateSysTick(uint32_t reload_val);
/*
This function returns milliseconds by combining the ‘mscount’ and VAL-Register values. You can
use this function to get the execution time required for a code block.
*/
uint32_t getTime(void);
void setTime(uint32_t _mscount);
void SysTick_Delay(uint32_t delay_amount_in_ms);
void SysTick_Handler(void);

#endif
