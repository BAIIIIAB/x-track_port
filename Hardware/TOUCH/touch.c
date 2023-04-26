#include "touch.h"
#include "stdio.h"
#include "string.h" 
#include "math.h"
#include <stdlib.h>

_m_tp_dev tp_dev;


void delay_1us(uint16_t us)
{
    while(us--)
    {
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }
}

//����I2C�ٶȵ���ʱ
void CT_Delay(void)
{
	delay_1us(2);
} 

//���ݴ���оƬIIC�ӿڳ�ʼ��
void CT_IIC_Init(void)
{			
 		/* enable the led clock */
    rcu_periph_clock_enable(SCL_RCU);
    /* configure led GPIO port */ 
    gpio_mode_set(SCL_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,SCL_PIN);
    gpio_output_options_set(SCL_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,SCL_PIN);

	rcu_periph_clock_enable(SDA_RCU);
	gpio_mode_set(SDA_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,SDA_PIN);
	gpio_output_options_set(SDA_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,SDA_PIN);

}
//����IIC��ʼ�ź�
void CT_IIC_Start(void)
{
	CT_SDA_OUT();     //sda�����
	SDA_ON;	  	  
	SCL_ON;//SCL=1ʱ��SDA��1��0����
	delay_1us(30);
 	SDA_OFF;//START:when CLK is high,DATA change form high to low 
	CT_Delay();
	SCL_OFF;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void CT_IIC_Stop(void)
{
	CT_SDA_OUT();//sda�����
	SCL_ON;//SCL=1ʱ��SDA��0��1����
	delay_1us(30);
	SDA_OFF;//STOP:when CLK is high DATA change form low to high
	CT_Delay();
	SDA_ON;//����I2C���߽����ź�  
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t CT_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	CT_SDA_IN();      //SDA����Ϊ����  
	SDA_ON;	   
	SCL_ON;
	CT_Delay();
	while(CT_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;
		} 
		CT_Delay();
	}
	SCL_OFF;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void CT_IIC_Ack(void)
{
	SCL_OFF;
	CT_SDA_OUT();
	CT_Delay();
	SDA_OFF;
	CT_Delay();
	SCL_ON;
	CT_Delay();
	SCL_OFF;
}
//������ACKӦ��		    
void CT_IIC_NAck(void)
{
	SCL_OFF;
	CT_SDA_OUT();
	CT_Delay();
	SDA_ON;
	CT_Delay();
	SCL_ON;
	CT_Delay();
	SCL_OFF;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void CT_IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	CT_SDA_OUT(); 	    
  	SCL_OFF;//����ʱ�ӿ�ʼ���ݴ���
	CT_Delay();
	for(t=0;t<8;t++)
    {              
        // CT_IIC_SDA=(txd&0x80)>>7;
		// CT_IIC_SDA((txd&0x80)>>7);
		if((txd&0x80)>>7)
		{
			gpio_bit_set(SDA_PORT,SDA_PIN);
		}
		else
		{
			gpio_bit_reset(SDA_PORT,SDA_PIN);
		}

        txd<<=1; 	      
		SCL_ON; 
		CT_Delay();
		SCL_OFF;	
		CT_Delay();
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t CT_IIC_Read_Byte(unsigned char ack)
{
	uint8_t i,receive=0;
 	CT_SDA_IN();//SDA����Ϊ����
	delay_1us(30);
	for(i=0;i<8;i++ )
	{ 
		SCL_OFF; 	    	   
		CT_Delay();
		SCL_ON;	 
		receive<<=1;

		//printf("%d ",CT_READ_SDA);
		if(CT_READ_SDA)receive++;   
	}
	//printf("\r\n receive:%0x \r\n",receive);	  				 

	if (!ack)CT_IIC_NAck();//����nACK
	else CT_IIC_Ack(); //����ACK   
 	return receive;
}









const uint8_t GT1151_CFG_TBL[]=
{ 
	0x63,0xE0,0x01,0x20,0x03,0x05,0x3D,0x04,0x00,0x08,
	0x09,0x0F,0x55,0x37,0x33,0x11,0x00,0x03,0x08,0x56,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x48,0x00,0x00,
	0x3C,0x08,0x0A,0x28,0x1E,0x50,0x00,0x00,0x82,0xB4,
	0xD2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x85,0x25,0x10,0x41,0x43,0x31,
	0x0D,0x00,0xAD,0x22,0x24,0x7D,0x1D,0x1D,0x32,0xDF,
	0x4F,0x44,0x0F,0x80,0x2C,0x50,0x50,0x00,0x00,0x00,
	0x00,0xD3,0x00,0x00,0x00,0x00,0x0F,0x28,0x1E,0xFF,
	0xF0,0x37,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x50,0xB4,0xC0,0x94,0x53,0x2D,
	0x0A,0x02,0xBE,0x60,0xA2,0x71,0x8F,0x82,0x80,0x92,
	0x74,0xA3,0x6B,0x01,0x0F,0x14,0x03,0x1E,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x0D,0x0E,0x0F,0x10,0x12,
	0x13,0x14,0x15,0x1F,0x1D,0x1B,0x1A,0x19,0x18,0x17,
	0x16,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x06,0x08,0x0C,
	0x12,0x13,0x14,0x15,0x17,0x18,0x19,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
	0xC4,0x09,0x23,0x23,0x50,0x5D,0x54,0x4B,0x3C,0x0F,
	0x32,0xFF,0xE4,0x04,0x40,0x00,0x8A,0x05,0x40,0x00,
	0xAA,0x00,0x22,0x22,0x00,0x00,0x73,0x22,0x01
}; 



uint16_t CRC16(uint8_t *srcdata,uint16_t length)
{
	uint16_t crc=0xffff;
	uint16_t i,j;
	uint8_t value;
	for(i=0;i<length;i++)
	{
		for(j=0;j<8;j++)
		{
			value=((srcdata[i]<<j)&0x80)^((crc&0x8000)>>8);	
			crc<<=1;
			if(value!=0)
			{
				crc^=0x8005;
			}
		}
	}
	return crc;
}


void check_sum(void)
	
{
	
	uint16_t checksum=0;
	uint8_t checksumH,checksumL;
	uint8_t i=0;	
	for(i=0;i<(sizeof(GT1151_CFG_TBL)-3);i+=2)
	checksum +=((GT1151_CFG_TBL[i]<<8)|GT1151_CFG_TBL[i+1]);//����У���
	//checksum +=(GT1151_CFG_TBL[i]<<8)+GT1151_CFG_TBL[i+1];
	//checksum =0-checksum;
	checksum =(~checksum)+1;
	checksumH=checksum>>8;
	checksumL=checksum;
	printf("chksum:0x%X,\r\n",checksum);
	printf("chksumH:0x%X,\r\n",checksumH);
	printf("chksumL:0x%X,\r\n",checksumL);
	
		
}







//����GT5668���ò���
//mode:0,���������浽flash
//     1,�������浽flash
uint8_t GT1151_Send_Cfg(uint8_t mode)
{
	uint16_t checksum=0;
	uint8_t buf[3];
	uint8_t i=0;	
	for(i=0;i<(sizeof(GT1151_CFG_TBL)-3);i+=2)
	checksum +=((GT1151_CFG_TBL[i]<<8)|GT1151_CFG_TBL[i+1]);//����У���
	//checksum +=(GT1151_CFG_TBL[i]<<8)+GT1151_CFG_TBL[i+1];
	//checksum =0-checksum;
	checksum =(~checksum)+1;
	printf("chksum:0x%x,\r\n",checksum);
	buf[0]= checksum>>8;
	buf[1]= checksum;
	buf[2]= mode;	//�Ƿ�д�뵽GT1151 FLASH?  ���Ƿ���籣��
	GT1151_WR_Reg(GT_CFGS_REG,(uint8_t*)GT1151_CFG_TBL,sizeof(GT1151_CFG_TBL));//���ͼĴ�������
	return 0;
	

} 



//��GT1151д��һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:д���ݳ���
//����ֵ:0,�ɹ�;1,ʧ��.
uint8_t GT1151_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t i;
	uint8_t ret=0;
	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT_CMD_WR);   	//����д���� 	  0x28
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg>>8);   	//���͸�8λ��ַ
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
    CT_IIC_Send_Byte(buf[i]);  	//������
		ret=CT_IIC_Wait_Ack();
		if(ret)break;  
	}
    CT_IIC_Stop();					//����һ��ֹͣ����	    
	return ret; 
}
//��GT1151����һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:�����ݳ���			  
void GT1151_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t i; 
 	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT_CMD_WR);   //����д���� 	0x28 
	CT_IIC_Wait_Ack();
 	CT_IIC_Send_Byte(reg>>8);   	  //���͸�8λ��ַ
	CT_IIC_Wait_Ack(); 	 										  		   
 	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
 	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(GT_CMD_RD);   //���Ͷ�����		    0x29
	CT_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //������	 
		//printf("buf:%0x %c \r\n",buf[i],buf[i]);   
	} 
    CT_IIC_Stop();//����һ��ֹͣ����  
} 
//��ʼ��GT1151������
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ�� 
uint8_t Cfg_Info1[239] = {0};
uint8_t GT1151_Init(void)
{
	uint8_t temp[6]={0}; 
	uint8_t i=0;
	uint8_t buf[2]={0};
	buf[0]=0;
	

//	//PD12����Ϊ�������(RST)
//	/* enable the led clock */
//    rcu_periph_clock_enable(RST_RCU);
//    /* configure led GPIO port */ 
//    gpio_mode_set(RST_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RST_PIN);
//    gpio_output_options_set(RST_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RST_PIN);
	
	//PD11����Ϊ��������(INT)
	/* enable the led clock */
    rcu_periph_clock_enable(INT_RCU);
    /* configure led GPIO port */ 
    gpio_mode_set(INT_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,INT_PIN);
    gpio_output_options_set(INT_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,INT_PIN);


	CT_IIC_Init();  //��ʼ����������I2C����  
//	RST_OFF;	    //��λ  
//	delay_1ms(10);
// 	RST_ON;	   //�ͷŸ�λ		    
//	delay_1ms(10); 
	
	gpio_mode_set(INT_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,INT_PIN);
	
	delay_1ms(100);  

	GT1151_RD_Reg(GT_PID_REG,temp,4);//��ȡ��ƷID
	
	
	
	printf("CTP ID:GT%s\r\n",temp);	 //��ӡID
	 
	check_sum();
	
	if(strcmp((char*)temp,"1158")==0)//ID==1158
	{
		GT1151_RD_Reg(GT_CFGS_REG,temp,1);//��ȡGT_CFGS_REG�Ĵ���		
		printf("Default Ver:0x%x\r\n",temp[0]);				
		//if(temp[0]<0x60)//Ĭ�ϰ汾�Ƚϵ�,��Ҫ����flash����		
		//{
			//GT1151_Send_Cfg(1);//���²���������
		//}
		
		#if 1
		GT1151_RD_Reg(0x8050,Cfg_Info1,239);	
		printf("Config Info:\r\n");
		for( i = 0; i < 239; i++ )
		{
			printf("0x%02X,",Cfg_Info1[i]);
			if((i+1)%10==0)
			printf("\r\n");
		}
		printf("\r\n");
		#endif	  
		return 0;	
	} 
	return 1;
}

const uint16_t GT1151_TPX_TBL[5]={GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG};
//ɨ�败����(���ò�ѯ��ʽ)
//mode:0,����ɨ��.
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
uint8_t GT1151_Scan(uint8_t mode)
{
	uint8_t buf[4];
	uint8_t i=0;
	uint8_t res=0;
	uint8_t temp;
	uint8_t tempsta;
 	static uint8_t t=0;//���Ʋ�ѯ���,�Ӷ�����CPUռ����   
	t++;
	if((t%10)==0||t<10)//����ʱ,ÿ����10��CTP_Scan�����ż��1��,�Ӷ���ʡCPUʹ����
	{
		GT1151_RD_Reg(GT_GSTID_REG,&mode,1);	//��ȡ�������״̬  
 		if(mode&0X80&&((mode&0XF)<6))
		{
			temp=0;
			GT1151_WR_Reg(GT_GSTID_REG,&temp,1);//���־ 		
		}		
		if((mode&0XF)&&((mode&0XF)<6))
		{
			temp=0XFF<<(mode&0XF);	//����ĸ���ת��Ϊ1��λ��,ƥ��tp_dev.sta���� 
			tempsta=tp_dev.sta;			//���浱ǰ��tp_dev.staֵ
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
			tp_dev.x[4]=tp_dev.x[0];	//���津��0������
			tp_dev.y[4]=tp_dev.y[0];
			for(i=0;i<5;i++)
			{
				if(tp_dev.sta&(1<<i))	//������Ч?
				{
					GT1151_RD_Reg(GT1151_TPX_TBL[i],buf,4);	//��ȡXY����ֵ
					if(tp_dev.touchtype&0X01)//����
					{
						tp_dev.x[i]=((uint16_t)buf[1]<<8)+buf[0];
						tp_dev.y[i]=((uint16_t)buf[3]<<8)+buf[2];
					}else
					{
						tp_dev.x[i]=((uint16_t)buf[1]<<8)+buf[0];
						tp_dev.y[i]=((uint16_t)buf[3]<<8)+buf[2];
					}  
					if(tp_dev.x[i]>0&&tp_dev.x[i]<480&&tp_dev.y[i]>0&&tp_dev.y[i]<800)
					printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);
				}			
			} 
			res=1;
			if(tp_dev.x[0]>1024||tp_dev.y[0]>1024)//�Ƿ�����(���곬����)
			{ 
				if((mode&0XF)>1)		//��������������,�򸴵ڶ�����������ݵ���һ������.
				{
					tp_dev.x[0]=tp_dev.x[1];
					tp_dev.y[0]=tp_dev.y[1];
					t=0;				//����һ��,��������������10��,�Ӷ����������
				}else					//�Ƿ�����,����Դ˴�����(��ԭԭ����)  
				{
					tp_dev.x[0]=tp_dev.x[4];
					tp_dev.y[0]=tp_dev.y[4];
					mode=0X80;		
					tp_dev.sta=tempsta;	//�ָ�tp_dev.sta
				}
			}else t=0;							//����һ��,��������������10��,�Ӷ����������
		}
	}
	if((mode&0X8F)==0X80)//�޴����㰴��
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)	//֮ǰ�Ǳ����µ�
		{
			tp_dev.sta&=~(1<<7);	//��ǰ����ɿ�
		}else						//֮ǰ��û�б�����
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE0;	//�������Ч���	
		}	 
	} 	
	if(t>240)t=10;//���´�10��ʼ����
	return res;
}
 



























