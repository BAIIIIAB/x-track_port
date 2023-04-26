#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"

#include "driver_debug.h"
#include "led.h"
#include "key.h"
#include "exmc_sdram.h"
#include "lcd.h"
#include "touch.h"
#include "driver_dma.h"
#include "driver_timer.h"

#include "sd_test.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
//#include "lv_demo_music.h"

extern sd_card_info_struct sd_cardinfo;                            /* information of SD card */
extern uint32_t buf_write[512];                                    /* store the data written to the card */
extern uint32_t buf_read[512];

uint16_t POINT[5]={WHITE,BLUE,RED,YELLOW,GREEN};
uint16_t BACK[5]={LIGHTGREEN,LIGHTGRAY,LGRAY,LGRAYBLUE,LBBLUE};

/*!
	\brief    main function
	\param[in]  none
	\param[out] none
	\retval     none
*/
int main(void)
{
    uint16_t i,j;
    uint8_t t = 0;
    uint16_t lastpos[5][2]; 
    
    systick_config();
    nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
    TIMER6_Init();
    Debug_Init(115200U);
    LED_Init();
    KEY_Init();
    
    //printf("start!\r\n");
    
    sd_test();
    //RGB屏需要Gram
    exmc_synchronous_dynamic_ram_init(EXMC_SDRAM_DEVICE0);
    /* RGB屏 */
    //LCD_Init(); //显示屏初始化代码
//    POINT_COLOR=POINT[4];
//    BACK_COLOR=BACK[4];
//    LCD_Clear(1,BACK[4]);
//    LCD_ShowString(1,30,50,480,200,24,1,"https://lckfb.com");
//    LCD_ShowString(1,30,80,480,110,24,1,"touch test....");
    //触摸屏
    //GT1151_Init();
    DMA_Init();
    //lv_gpu_nxp_pxp_init();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    //lv_demo_music();
    
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello World!");
    lv_obj_center(label);
    while(1)
    {
        lv_timer_handler();
        delay_1ms(5);
//        GT1151_Scan(0);
//        for (t = 0; t < CT_MAX_TOUCH; t++) 
//        {
//            if ((tp_dev.sta) & (1 << t))
//            {
//                if (lastpos[t][0] == 0XFFFF)
//                {
//                    lastpos[t][0] = tp_dev.x[t];
//                    lastpos[t][1] = tp_dev.y[t];
//                }
//                lastpos[t][0] = tp_dev.x[t];
//                lastpos[t][1] = tp_dev.y[t];
//                printf("tp_dev.x[t]:%d tp_dev.y[t]:%d\r\n", tp_dev.x[t], tp_dev.y[t]);
//                
//                LTDC_Draw_Point(1,tp_dev.x[t], tp_dev.y[t],POINT_COLOR);
//                LTDC_Draw_Point(1,tp_dev.x[t]-1, tp_dev.y[t],POINT_COLOR);
//                LTDC_Draw_Point(1,tp_dev.x[t], tp_dev.y[t]-1,POINT_COLOR);
//                LTDC_Draw_Point(1,tp_dev.x[t]+1, tp_dev.y[t],POINT_COLOR);
//                LTDC_Draw_Point(1,tp_dev.x[t], tp_dev.y[t]+1,POINT_COLOR);
//                
//                i=0; //重新计时
//            }
//            else  lastpos[t][0] = 0XFFFF;
//        }
//        delay_1ms(1);
        
        
//        //清屏换色
//        if(++i > 800)
//        {
//            i=0;
//            if(++j > 4) j=0;
//            POINT_COLOR=POINT[j];
//            BACK_COLOR=BACK[j];
//            
//            LCD_Clear(1,BACK[j]);
//            LCD_ShowString(1,30,50,480,80,24,1,"https://lckfb.com");
//            LCD_ShowString(1,30,80,480,110,24,1,"touch test....");
//        }

        
   }

}
