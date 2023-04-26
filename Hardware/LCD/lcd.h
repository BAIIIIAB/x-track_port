#ifndef __LCD_H
#define __LCD_H
#include "gd32f4xx.h"
#include "systick.h"

#define LCD_SDA_RCU  			RCU_GPIOE   // SDA
#define LCD_SDA_PORT  		    GPIOE
#define LCD_SDA_PIN    		    GPIO_PIN_6//GPIO_PIN_5  //v0.0.1����Ļ6������Ļ5
#define LCD_SDA_WRITE(x)	    gpio_bit_write(LCD_SDA_PORT,LCD_SDA_PIN,x)
#define LCD_SCL_RCU  			RCU_GPIOE   // SCL
#define LCD_SCL_PORT  		    GPIOE
#define LCD_SCL_PIN    		    GPIO_PIN_2
#define LCD_SCL_WRITE(x)	    gpio_bit_write(LCD_SCL_PORT,LCD_SCL_PIN,x)
#define LCD_CS_RCU  			RCU_GPIOE   // CS
#define LCD_CS_PORT  		    GPIOE
#define LCD_CS_PIN    		    GPIO_PIN_4
#define LCD_CS_WRITE(x)	        gpio_bit_write(LCD_CS_PORT,LCD_CS_PIN,x)
#define LCD_RST_RCU  			RCU_GPIOD   // RST
#define LCD_RST_PORT  		    GPIOD
#define LCD_RST_PIN    		    GPIO_PIN_12
#define LCD_RST_WRITE(x)	    gpio_bit_write(LCD_RST_PORT,LCD_RST_PIN,x)
#define LCD_BLK_ON              gpio_bit_set(GPIOD,GPIO_PIN_13)	// PD13
#define LCD_BLK_OFF             gpio_bit_reset(GPIOD,GPIO_PIN_13)	// PD13
#define LCD_CS_Clr()            gpio_bit_reset(GPIOE,GPIO_PIN_4)	// PD13
#define LCD_CS_Set()            gpio_bit_set(GPIOE,GPIO_PIN_4)	// PD13
#define LCD_SDI_RCU  			RCU_GPIOC   // SDI
#define LCD_SDI_PORT  		    GPIOC
#define LCD_SDI_PIN    		    GPIO_PIN_1
#define LCD_SDI_WRITE(x)	    gpio_bit_write(LCD_SDI_PORT,LCD_SDI_PIN,x)


#define HORIZONTAL_SYNCHRONOUS_PULSE  10
#define HORIZONTAL_BACK_PORCH         150
#define ACTIVE_WIDTH                  480
#define HORIZONTAL_FRONT_PORCH        40

#define VERTICAL_SYNCHRONOUS_PULSE    10
#define VERTICAL_BACK_PORCH           140
#define ACTIVE_HEIGHT                 800
#define VERTICAL_FRONT_PORCH          15


//extern uint16_t *ltdc_framebuf[2];              
//extern uint16_t ltdc_lcd_framebuf0[800][480];              
//extern uint16_t ltdc_lcd_framebuf1[800][480]; 


//������ɫ
#define WHITE        0xFFFF
#define BLACK        0x0000	  
#define BLUE         0x001F  
#define BRED         0XF81F
#define GRED         0XFFE0
#define GBLUE        0X07FF
#define RED          0xF800
#define MAGENTA      0xF81F
#define GREEN        0x07E0
#define CYAN         0x7FFF
#define YELLOW       0xFFE0
#define BROWN        0XBC40 //��ɫ
#define BRRED        0XFC07 //�غ�ɫ
#define GRAY         0X8430 //��ɫ
//GUI��ɫ
#define DARKBLUE         0X01CF	//����ɫ
#define LIGHTBLUE        0X7D7C	//ǳ��ɫ  
#define GRAYBLUE         0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
#define LIGHTGREEN       0X841F //ǳ��ɫ
#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY            0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


////ɨ�跽����
//#define L2R_U2D  0 //������,���ϵ���
//#define L2R_D2U  1 //������,���µ���
//#define R2L_U2D  2 //���ҵ���,���ϵ���
//#define R2L_D2U  3 //���ҵ���,���µ���
//#define U2D_L2R  4 //���ϵ���,������
//#define U2D_R2L  5 //���ϵ���,���ҵ���
//#define D2U_L2R  6 //���µ���,������
//#define D2U_R2L  7 //���µ���,���ҵ���	 
//#define DFT_SCAN_DIR  L2R_U2D  //Ĭ�ϵ�ɨ�跽��


//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern uint16_t  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern uint16_t  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ



//////////
void NT35510_Init(void);
void TLI_ConfigParam( 
int b_HORIZONTAL_SYNCHRONOUS_PULSE,
int b_HORIZONTAL_BACK_PORCH       ,
int b_HORIZONTAL_FRONT_PORCH      ,
int b_VERTICAL_SYNCHRONOUS_PULSE  ,
int b_VERTICAL_BACK_PORCH         ,
int b_VERTICAL_FRONT_PORCH        );
////////////////
void LCD_Init(void);//��Ļ��ʼ��
////////////////
//void LTDC_Draw_Point(uint8_t layer, uint16_t x, uint16_t y, uint32_t color);/////����
//void LCD_Clear(uint8_t layer,uint16_t  color);//��������   
//void LCD_ShowChar(uint8_t layer,uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode);////��ָ��λ����ʾһ���ַ�
//void LCD_ShowString(uint8_t layer,uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t mode,uint8_t *p);//��ʾ�ַ���

#endif  




