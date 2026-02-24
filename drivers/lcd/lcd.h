
#ifndef __LCD_H
#define __LCD_H

#include "platform.h"
#include "../common/font/fonts.h"

#define  PIXEL_R_PTR(x, y) ((uint8_t *)(lcd_fb_addr + (y * LCD_PIXEL_WIDTH + x) * 3))
#define  PIXEL_G_PTR(x, y) ((uint8_t *)(lcd_fb_addr + (y * LCD_PIXEL_WIDTH + x) * 3 + 1))
#define  PIXEL_B_PTR(x, y) ((uint8_t *)(lcd_fb_addr + (y * LCD_PIXEL_WIDTH + x) * 3 + 2))

#define DRAW_PIXEL(x, y, r, g, b) \
          do { \
            *PIXEL_R_PTR(x, y) = b; \
            *PIXEL_G_PTR(x, y) = g; \
            *PIXEL_B_PTR(x, y) = r; \
          } while (0)

#define LCD_DIR_HORIZONTAL 0
#define LCD_DIR_VERTICAL   1

#define LCD_COLOR_BLACK   0x0
#define LCD_COLOR_WHITE   0xffffff
#define LCD_COLOR_RED     0x0000ff
#define LCD_COLOR_GREEN   0x00ff00
#define LCD_COLOR_BLUE    0xff0000

typedef enum pixel_format {
    PIXEL_FORMAT_RGB565 = 0,
    PIXEL_FORMAT_RGB888,
} pixel_fmt_t;

typedef struct {
    uint16_t width;         // 屏幕宽 horizontal
    uint16_t height;        // 屏幕高 vertical
    uint16_t hsw;           // hsync 脉宽 clk个数
    uint16_t hbp;           // hsync信号开始到一行的有效数据开始之间的CLK个数
    uint16_t hfp;           // 一行的有效数据结束到下一个hsync信号开始之间的CLK个数
    uint16_t vsw;           // vsync 脉宽 clk周期数
    uint16_t vbp;           // vsync信号开始到有效数据开始之间的CLK个数
    uint16_t vfp;           // 有效数据结束到下一个vsync信号开始之间的CLK个数

    pixel_fmt_t pfmt;       // 像素点格式
    uint8_t alpha;          // 透明度

    uint32_t fb_base_addr;  // framebuffer首地址
} lcd_info_t;



void lcd_init(lcd_info_t *info);
void lcd_set_fb(uint32_t addr);
void lcd_set_thickness(uint8_t val); 
void lcd_clear_win(uint32_t clr);
void lcd_draw_line(uint16_t x, uint16_t y, uint16_t len, uint8_t dir, uint32_t clr);
void lcd_draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t clr);
void lcd_set_font(font_t *font);
void lcd_putstr(uint16_t x, uint16_t y, const char *s);


// unit test
void lcd_test(void);

#endif

