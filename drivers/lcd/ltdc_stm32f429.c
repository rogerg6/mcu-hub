#include "lcd.h"

#define CurrentBackColor 0x00ff00
#define CurrentTextColor 0x0

static lcd_info_t *lcd_info = NULL;
static uint32_t lcd_fb_addr;
static uint16_t LCD_PIXEL_WIDTH = 0;
static uint16_t LCD_PIXEL_HEIGHT = 0;

LTDC_HandleTypeDef hltdc;

font_t *cur_font = &Font12x12;
uint8_t thickess = 1;


void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(ltdcHandle->Instance==LTDC)
  {
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLLSAI.PLLSAIN = 50;
    PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
    PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PE4     ------> LTDC_B0
    PE5     ------> LTDC_G0
    PE6     ------> LTDC_G1
    PI9     ------> LTDC_VSYNC
    PI10     ------> LTDC_HSYNC
    PF10     ------> LTDC_DE
    PH2     ------> LTDC_R0
    PH3     ------> LTDC_R1
    PA3     ------> LTDC_B5
    PB0     ------> LTDC_R3
    PB1     ------> LTDC_R6
    PH8     ------> LTDC_R2
    PG6     ------> LTDC_R7
    PG7     ------> LTDC_CLK
    PC7     ------> LTDC_G6
    PA11     ------> LTDC_R4
    PA12     ------> LTDC_R5
    PH13     ------> LTDC_G2
    PH15     ------> LTDC_G4
    PI0     ------> LTDC_G5
    PI2     ------> LTDC_G7
    PD6     ------> LTDC_B2
    PG10     ------> LTDC_G3
    PG11     ------> LTDC_B3
    PG12     ------> LTDC_B1
    PB8     ------> LTDC_B6
    PB9     ------> LTDC_B7
    PI4     ------> LTDC_B4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_2
                          |GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_8|GPIO_PIN_13
                          |GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* LTDC interrupt Init */
    HAL_NVIC_SetPriority(LTDC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);

	// bl, disp
    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
    __HAL_RCC_LTDC_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_2
                          |GPIO_PIN_4);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_8|GPIO_PIN_13
                          |GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3|GPIO_PIN_11|GPIO_PIN_12);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_8|GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_6);

    HAL_NVIC_DisableIRQ(LTDC_IRQn);
  }
}


void lcd_init(lcd_info_t *info)
{
	assert_param(info != NULL);
	if (lcd_info)
		return;

	lcd_info = info;
	lcd_fb_addr = info->fb_base_addr;
	LCD_PIXEL_WIDTH = info->width;
	LCD_PIXEL_HEIGHT = info->height;

	// ldtc init
	LTDC_LayerCfgTypeDef pLayerCfg = {0};
	hltdc.Instance = LTDC;
	hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
	hltdc.Init.HorizontalSync = info->hsw - 1;
	hltdc.Init.VerticalSync = info->vsw -1;
	hltdc.Init.AccumulatedHBP = info->hbp;
	hltdc.Init.AccumulatedVBP = info->vbp;
	hltdc.Init.AccumulatedActiveW = info->hbp + info->width;
	hltdc.Init.AccumulatedActiveH = info->vbp + info->height;
	hltdc.Init.TotalWidth = info->hbp + info->width + info->hfp;
	hltdc.Init.TotalHeigh = info->vbp + info->height + info->vfp;
	hltdc.Init.Backcolor.Blue = 0;
	hltdc.Init.Backcolor.Green = 0;
	hltdc.Init.Backcolor.Red = 0;
	if (HAL_LTDC_Init(&hltdc) != HAL_OK)
		Error_Handler();

	// ldtc layer init
	pLayerCfg.WindowX0 = 0;
	pLayerCfg.WindowX1 = info->width - 1;
	pLayerCfg.WindowY0 = 0;
	pLayerCfg.WindowY1 = info->height - 1;

	if (info->pfmt == PIXEL_FORMAT_RGB888)
		pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
	else if (info->pfmt == PIXEL_FORMAT_RGB565)
		pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
	pLayerCfg.Alpha = info->alpha;
	pLayerCfg.Alpha0 = 0;
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
	pLayerCfg.FBStartAdress = (uint32_t)lcd_fb_addr;
	pLayerCfg.ImageWidth = info->width;
	pLayerCfg.ImageHeight = info->height;
	pLayerCfg.Backcolor.Blue = 0;
	pLayerCfg.Backcolor.Green = 0;
	pLayerCfg.Backcolor.Red = 0;
	if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
		Error_Handler();

}

void lcd_set_fb(uint32_t addr)
{
    assert_param(addr != 0);
	lcd_fb_addr = addr;
}

void lcd_set_thickness(uint8_t val) 
{
  thickess = val;
}

void lcd_set_font(font_t *font) 
{
  cur_font = font;
}

void lcd_clear_win(uint32_t clr)
{
  int x, y;
  uint8_t b = (clr >> 16) & 0xFF;
  uint8_t g = (clr >> 8) & 0xFF;
  uint8_t r = (clr) & 0xFF;

  for (y = 0; y < LCD_PIXEL_HEIGHT; y++) {
    for (x = 0; x < LCD_PIXEL_WIDTH; x++) {
      DRAW_PIXEL(x, y, r, g, b);
    }
  }
}

void lcd_draw_line(uint16_t x, uint16_t y, uint16_t len, uint8_t dir, uint32_t clr)
{
  assert_param(x < LCD_PIXEL_WIDTH);
  assert_param(y < LCD_PIXEL_HEIGHT);
 
  uint16_t row, col;
  uint8_t b = (clr >> 16) & 0xFF;
  uint8_t g = (clr >> 8) & 0xFF;
  uint8_t r = (clr) & 0xFF;

  if (dir == LCD_DIR_HORIZONTAL)
    for (row = y; row < y + thickess; row++)
      for (col = x; col < x + len; col++)
        DRAW_PIXEL(col, row, r, g, b);
  else if (dir == LCD_DIR_VERTICAL)
    for (col = x; col < x + thickess; col++)
      for (row = y; row < y + len; row++)
        DRAW_PIXEL(col, row, r, g, b);
}

void lcd_draw_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t clr)
{
  assert_param(x < LCD_PIXEL_WIDTH);
  assert_param(y < LCD_PIXEL_HEIGHT);
  assert_param(w < LCD_PIXEL_WIDTH);
  assert_param(h < LCD_PIXEL_HEIGHT);
 
  lcd_draw_line(x, y, w, LCD_DIR_HORIZONTAL, clr);
  lcd_draw_line(x, y, h, LCD_DIR_VERTICAL, clr);
  lcd_draw_line(x, y + h, w + thickess, LCD_DIR_HORIZONTAL, clr);
  lcd_draw_line(x + w, y, h, LCD_DIR_VERTICAL, clr);
}

void lcd_draw_char(uint16_t x, uint16_t y, int ascii)
{
  uint16_t row;
  uint8_t r, g, b;
  uint32_t clr;
  int i;
  uint16_t line;

  ascii -= 32;
  const uint16_t *c = &cur_font->table[ascii * cur_font->height];

  for (row = y; row < y + cur_font->height; row++) {
      line = *c;
      for (i = 0; i < cur_font->width; i++) {
        if (line & 1)
          clr = CurrentTextColor;
        else
          clr = CurrentBackColor;
        b = (clr >> 16) & 0xFF;
        g = (clr >> 8) & 0xFF;
        r = (clr) & 0xFF;

        DRAW_PIXEL(x + i, row, r, g, b);
        line >>= 1;
    }
    c++;
  }
  
}

void lcd_putstr(uint16_t x, uint16_t y, const char *s)
{
  int c;

  while ((c = *s++)) {
    lcd_draw_char(x, y, c);
    x += cur_font->width;
  }
}


void lcd_test(void) {
  lcd_clear_win(LCD_COLOR_WHITE);

//   for (int y = 0; y < LCD_PIXEL_HEIGHT; y++)
//     for (int x = 0; x < LCD_PIXEL_WIDTH; x++) {
// 		printf("pixel=%d ", *(uint8_t*)(lcd_fb_addr+3*(y*LCD_PIXEL_WIDTH+x)));
// 		printf("pixel=%d ", *(uint8_t*)(lcd_fb_addr+3*(y*LCD_PIXEL_WIDTH+x) + 1));
// 		printf("pixel=%d\n", *(uint8_t*)(lcd_fb_addr+3*(y*LCD_PIXEL_WIDTH+x + 2)));
// 	}

  lcd_set_thickness(5);
  lcd_draw_line(0, 240, 400, LCD_DIR_HORIZONTAL, LCD_COLOR_BLACK);
  lcd_draw_rect(400, 240, 100, 200, LCD_COLOR_RED);

  lcd_set_font(&Font16x24);
  lcd_putstr(0, 120, "Fello world !");
  lcd_draw_line(0, 120 + 24, 13*16, LCD_DIR_HORIZONTAL, LCD_COLOR_BLACK);
}
