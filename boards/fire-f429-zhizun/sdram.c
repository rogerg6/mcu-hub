/**
 *  IS42S16400J
 */
#include "platform.h"
#include "modules.h"
#include <stdio.h>
#include "gpio.h"

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)      

SDRAM_HandleTypeDef hsdram2;

static void IS42S16400J_init(void)
{
  FMC_SDRAM_CommandTypeDef FMC_SDRAMCommandStructure;
  uint32_t tmpr = 0;
  
/* Step 3 --------------------------------------------------------------------*/
  /* 配置命令：开启提供给SDRAM的时钟 */
  FMC_SDRAMCommandStructure.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
  FMC_SDRAMCommandStructure.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
  FMC_SDRAMCommandStructure.AutoRefreshNumber = 1;
  FMC_SDRAMCommandStructure.ModeRegisterDefinition = 0;
  FMC_SDRAM_SendCommand(hsdram2.Instance, &FMC_SDRAMCommandStructure, HAL_MAX_DELAY);  
  
/* Step 4 --------------------------------------------------------------------*/
  /* 约100ms的延时 */
  HAL_Delay(100);
    
/* Step 5 --------------------------------------------------------------------*/
  /* 配置命令：对所有的bank预充电 */ 
  FMC_SDRAMCommandStructure.CommandMode = FMC_SDRAM_CMD_PALL;
  FMC_SDRAMCommandStructure.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
  FMC_SDRAMCommandStructure.AutoRefreshNumber = 1;
  FMC_SDRAMCommandStructure.ModeRegisterDefinition = 0;
  FMC_SDRAM_SendCommand(hsdram2.Instance,&FMC_SDRAMCommandStructure, HAL_MAX_DELAY);
  
/* Step 6 --------------------------------------------------------------------*/
  /* 配置命令：自动刷新 */   
  FMC_SDRAMCommandStructure.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  FMC_SDRAMCommandStructure.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
  FMC_SDRAMCommandStructure.AutoRefreshNumber = 4;
  FMC_SDRAMCommandStructure.ModeRegisterDefinition = 0;
  FMC_SDRAM_SendCommand(hsdram2.Instance, &FMC_SDRAMCommandStructure, HAL_MAX_DELAY);
  FMC_SDRAM_SendCommand(hsdram2.Instance, &FMC_SDRAMCommandStructure, HAL_MAX_DELAY);
  
/* Step 7 --------------------------------------------------------------------*/
  /* 设置sdram寄存器配置 */
  tmpr = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
                   SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                   SDRAM_MODEREG_CAS_LATENCY_3           |
                   SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                   SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
  
  /* 配置命令：设置SDRAM寄存器 */
  FMC_SDRAMCommandStructure.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  FMC_SDRAMCommandStructure.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
  FMC_SDRAMCommandStructure.AutoRefreshNumber = 1;
  FMC_SDRAMCommandStructure.ModeRegisterDefinition = tmpr;
  FMC_SDRAM_SendCommand(hsdram2.Instance, &FMC_SDRAMCommandStructure, HAL_MAX_DELAY);
  
/* Step 8 --------------------------------------------------------------------*/

  /* 设置刷新计数器 */
  /* (15.62 us x Freq) - 20 */
  FMC_SDRAM_ProgramRefreshRate(hsdram2.Instance, 1386);
}

// sdram
static pinctrl_t sdram_gpios[] = {
    {GPIOF, {GPIO_PIN_0, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_A0
    {GPIOF, {GPIO_PIN_1, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_A1
    {GPIOF, {GPIO_PIN_2, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_A2
    {GPIOF, {GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_A3
    {GPIOF, {GPIO_PIN_4, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_A4
    {GPIOF, {GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_A5
    {GPIOF, {GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_A6
    {GPIOF, {GPIO_PIN_13, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_A7
    {GPIOF, {GPIO_PIN_14, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_A8
    {GPIOF, {GPIO_PIN_15, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_A9
    {GPIOG, {GPIO_PIN_0, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_A10
    {GPIOG, {GPIO_PIN_1, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_A11

    {GPIOD, {GPIO_PIN_14, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D0
    {GPIOD, {GPIO_PIN_15, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D1
    {GPIOD, {GPIO_PIN_0, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D2
    {GPIOD, {GPIO_PIN_1, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D3
    {GPIOE, {GPIO_PIN_7, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D4
    {GPIOE, {GPIO_PIN_8, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D5
    {GPIOE, {GPIO_PIN_9, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D6
    {GPIOE, {GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D7
    {GPIOE, {GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D8
    {GPIOE, {GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D9
    {GPIOE, {GPIO_PIN_13, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D10
    {GPIOE, {GPIO_PIN_14, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D11
    {GPIOE, {GPIO_PIN_15, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D12
    {GPIOD, {GPIO_PIN_8, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D13
    {GPIOD, {GPIO_PIN_9, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D14
    {GPIOD, {GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_D15

    {GPIOC, {GPIO_PIN_0, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_SDNWE
    {GPIOF, {GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_SDNRAS
    {GPIOH, {GPIO_PIN_6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_SDNE1
    {GPIOH, {GPIO_PIN_7, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_SDCKE1
    {GPIOG, {GPIO_PIN_8, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_SDCLK
    {GPIOG, {GPIO_PIN_15, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_SDNCAS
    {GPIOE, {GPIO_PIN_0, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_NBL0
    {GPIOE, {GPIO_PIN_1, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_NBL1
    {GPIOG, {GPIO_PIN_4, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_BA0
    {GPIOG, {GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_FMC}},// FMC_BA1
};

static void sdram_gpio_init(void) {
    __HAL_RCC_FMC_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    int n = sizeof(sdram_gpios) / sizeof(pinctrl_t);
    for (int i = 0; i < n; i++)
      HAL_GPIO_Init(sdram_gpios[i].port, &sdram_gpios[i].config);
}

static void sdram_gpio_deinit(void) {
    __HAL_RCC_FMC_CLK_DISABLE();
    for (int i = 0; i < sizeof(sdram_gpios); i++)
        HAL_GPIO_DeInit(sdram_gpios[i].port, sdram_gpios[i].config.Pin);
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* sdramHandle){
  sdram_gpio_init();
}

void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* sdramHandle){
  sdram_gpio_deinit();
}

void fmc_sdram_init(void) {
  FMC_SDRAM_TimingTypeDef SdramTiming = {0};
  /** Perform the SDRAM2 memory initialization sequence
  */
  hsdram2.Instance = FMC_SDRAM_DEVICE;
  /* hsdram2.Init */
  hsdram2.Init.SDBank = FMC_SDRAM_BANK2;
  hsdram2.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
  hsdram2.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
  hsdram2.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram2.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram2.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
  hsdram2.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram2.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
  hsdram2.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
  hsdram2.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 2;
  SdramTiming.ExitSelfRefreshDelay = 7;
  SdramTiming.SelfRefreshTime = 4;
  SdramTiming.RowCycleDelay = 7;
  SdramTiming.WriteRecoveryTime = 4;
  SdramTiming.RPDelay = 2;
  SdramTiming.RCDDelay = 2;

  if (HAL_SDRAM_Init(&hsdram2, &SdramTiming) != HAL_OK)
  {
    Error_Handler( );
  }
}

void sdram_init(void)
{
    fmc_sdram_init();
    IS42S16400J_init();
}

void sdram_test(void) {
  uint8_t src1[5] = {0x12, 0x34, 0x56, 0x78, 0x90};
  uint8_t dst1[5] = {0};
  uint16_t src2[5] = {0x1234, 0x5678, 0x90ab, 0xcdef, 0xbadb};
  uint16_t dst2[5] = {0};

  // uint8 test
  uint8_t *p = (uint8_t*)SDRAM_BASE_ADDR;
  for (int i = 0; i < 5; i++)
    *p++ = src1[i];

  p = (uint8_t*)SDRAM_BASE_ADDR;
  for (int i = 0; i < 5; i++)
    dst1[i] = *p++;

  for (int i = 0; i < 5; i++) {
    if (src1[i] != dst1[i]) {
      printf("sdram test1 failed\n");
      return;
    }
  }

  // uint16 test
  uint16_t *p1 = (uint16_t*)(SDRAM_BASE_ADDR + 0x700000);
  for (int i = 0; i < 5; i++)
    *p1++ = src2[i];

  p1 = (uint16_t*)(SDRAM_BASE_ADDR + 0x700000);
  for (int i = 0; i < 5; i++)
    dst2[i] = *p1++;

  for (int i = 0; i < 5; i++) {
    if (src2[i] != dst2[i]) {
      printf("sdram test2 failed\n");
      return;
    }
  }
  printf("sdram test ok\n");
}
