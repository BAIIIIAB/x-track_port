#ifndef __TOUCH_H__
#define __TOUCH_H__
#include "gd32f4xx.h"
#include "systick.h"

//???
#define AD_Left 300
#define AD_Right 3850
#define AD_Top 220
#define AD_Bottom 3850

#define LCD_X 480
#define LCD_Y 800
#define CH_X 0XD2
#define CH_Y 0X92


#define SCL_RCU  		RCU_GPIOB
#define SCL_PORT 	 	GPIOB
#define SCL_PIN    		GPIO_PIN_6
#define SCL_ON			gpio_bit_set(SCL_PORT,SCL_PIN)
#define SCL_OFF			gpio_bit_reset(SCL_PORT,SCL_PIN)
#define SCL_TOGGLE		gpio_bit_toggle(SCL_PORT,SCL_PIN)

#define SDA_RCU  		RCU_GPIOB
#define SDA_PORT  		GPIOB
#define SDA_PIN    		GPIO_PIN_7
#define SDA_ON			gpio_bit_set(SDA_PORT,SDA_PIN)
#define SDA_OFF			gpio_bit_reset(SDA_PORT,SDA_PIN)
#define SDA_TOGGLE		gpio_bit_toggle(SDA_PORT,SDA_PIN)

//IO��������
#define CT_SDA_IN()  gpio_mode_set(SCL_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,SDA_PIN);//{GPIOF->MODER&=~(3<<(2*11));GPIOF->MODER|=0<<2*11;}	//PF11����ģʽ
#define CT_SDA_OUT() gpio_mode_set(SCL_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,SDA_PIN);//{GPIOF->MODER&=~(3<<(2*11));GPIOF->MODER|=1<<2*11;} 	//PF11���ģʽ
//IO��������	 
#define CT_IIC_SCL    //PBout(0) 	//SCL
#define CT_IIC_SDA(val)    ((val)==1?SDA_ON:SDA_OFF)//PFout(11) //SDA	 
#define CT_READ_SDA   gpio_input_bit_get(SDA_PORT,SDA_PIN) //PFin(11)  //����SDA 
 
#define RST_RCU             RCU_GPIOD
#define RST_PORT            GPIOD
#define RST_PIN             GPIO_PIN_12
#define RST_ON			    gpio_bit_set(RST_PORT,RST_PIN);
#define RST_OFF			    gpio_bit_reset(RST_PORT,RST_PIN);
#define RST_TOGGLE	        gpio_bit_toggle(RST_PORT,RST_PIN);

#define INT_RCU             RCU_GPIOD
#define INT_PORT            GPIOD
#define INT_PIN             GPIO_PIN_11
#define INT_ON			    gpio_bit_set(INT_PORT,INT_PIN);
#define INT_OFF			    gpio_bit_reset(INT_PORT,INT_PIN);
#define INT_TOGGLE	        gpio_bit_toggle(INT_PORT,INT_PIN);
   
//I2C��д����	
#define GT_CMD_WR 		0X28    	//д����
#define GT_CMD_RD 		0X29		//������
  
//GT1151 ���ּĴ������� 
#define GT_CTRL_REG 	0X8040   	//GT1151���ƼĴ���
#define GT_CFGS_REG 	0X8050   	//GT1151��ַ�Ĵ���
#define GT_CHECK_REG 	0X813C   	//GT1151��ͼĴ���
#define GT_PID_REG 		0X8140   	//GT1151��ƷID�Ĵ���

#define GT_GSTID_REG 	0X814E   	//GT1151ǰ��⵽�Ĵ������
#define GT_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT_TP5_REG 		0X8170		//��������������ݵ�ַ  
 
#define TP_PRES_DOWN 0x80  //����������	  
#define TP_CATH_PRES 0x40  //�а��������� 
#define CT_MAX_TOUCH  5    //������֧�ֵĵ���,�̶�Ϊ5��
//������������
typedef struct
{
//    uint8_t (*init)(void);			//��ʼ��������������
//    uint8_t (*scan)(uint8_t);				//ɨ�败����.0,��Ļɨ��;1,��������;	 
//    void (*adjust)(void);		//������У׼ 
    uint16_t x[CT_MAX_TOUCH]; 		//��ǰ����
    uint16_t y[CT_MAX_TOUCH];		//�����������5������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
    uint8_t  sta;			//�ʵ�״̬    
    float xfac;					
    float yfac;
    short xoff;
    short yoff;	   
    uint8_t touchtype;
}_m_tp_dev;
extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��


//IIC���в�������
void CT_IIC_Init(void);                	//��ʼ��IIC��IO��				 
void CT_IIC_Start(void);				//����IIC��ʼ�ź�
void CT_IIC_Stop(void);	  				//����IICֹͣ�ź�
void CT_IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t CT_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
uint8_t CT_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void CT_IIC_Ack(void);					//IIC����ACK�ź�
void CT_IIC_NAck(void);					//IIC������ACK�ź�
 
 
 
uint8_t GT1151_Send_Cfg(uint8_t mode);
uint8_t GT1151_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
void GT1151_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len); 
uint8_t GT1151_Init(void);
uint8_t GT1151_Scan(uint8_t mode); 






#endif

















