#include "reg52.h"

typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;

#define EEPROM_ADDRESS	0	//定义数据存入EEPROM的起始地址

//定义EEPROM控制脚
sbit IIC_SCL=P2^1;//SCL时钟线
sbit IIC_SDA=P2^0;//SDA数据线

void delay_10us(u16 ten_us)
{
	while(ten_us--);
}

void delay_ms(u16 ms)
{
	u16 i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}

/*******************************************************************************
* 函 数 名       : iic_start
* 函数功能		 : 产生IIC起始信号
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void iic_start(void)
{
	IIC_SDA=1;//如果把该条语句放在SCL后面，第二次读写会出现问题
	delay_10us(1);
	IIC_SCL=1;
	delay_10us(1);
	IIC_SDA=0;	//当SCL为高电平时，SDA由高变为低
	delay_10us(1);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据
	delay_10us(1);
}

/*******************************************************************************
* 函 数 名         : iic_stop
* 函数功能		   : 产生IIC停止信号
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void iic_stop(void)
{
	IIC_SDA=0;//如果把该条语句放在SCL后面，第二次读写会出现问题
	delay_10us(1);
	IIC_SCL=1;
	delay_10us(1);
	IIC_SDA=1;	//当SCL为高电平时，SDA由低变为高
	delay_10us(1);
}

/*******************************************************************************
* 函 数 名         : iic_ack
* 函数功能		   : 产生ACK应答
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void iic_ack(void)
{
	IIC_SCL=0;
	IIC_SDA=0;	//SDA为低电平
	delay_10us(1);
   	IIC_SCL=1;
	delay_10us(1);
	IIC_SCL=0;
}

/*******************************************************************************
* 函 数 名         : iic_nack
* 函数功能		   : 产生NACK非应答
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void iic_nack(void)
{
	IIC_SCL=0;
	IIC_SDA=1;	//SDA为高电平
	delay_10us(1);
   	IIC_SCL=1;
	delay_10us(1);
	IIC_SCL=0;
}

/*******************************************************************************
* 函 数 名         : iic_wait_ack
* 函数功能		   : 等待应答信号到来
* 输    入         : 无
* 输    出         : 1，接收应答失败
        			 0，接收应答成功
*******************************************************************************/
u8 iic_wait_ack(void)
{
	u8 time_temp=0;

	IIC_SCL=1;
	delay_10us(1);
	while(IIC_SDA)	//等待SDA为低电平
	{
		time_temp++;
		if(time_temp>100)//超时则强制结束IIC通信
		{
			iic_stop();
			return 1;
		}
	}
	IIC_SCL=0;
	return 0;
}

/*******************************************************************************
* 函 数 名         : iic_write_byte
* 函数功能		   : IIC发送一个字节
* 输    入         : dat：发送一个字节
* 输    出         : 无
*******************************************************************************/
void iic_write_byte(u8 dat)
{
    u8 i=0;

    IIC_SCL=0;
    for(i=0;i<8;i++)	//循环8次将一个字节传出，先传高再传低位
    {
        if((dat&0x80)>0)
			IIC_SDA=1;
		else
			IIC_SDA=0;
        dat<<=1;
		delay_10us(1);
		IIC_SCL=1;
		delay_10us(1);
		IIC_SCL=0;
		delay_10us(1);
    }
}

/*******************************************************************************
* 函 数 名         : iic_read_byte
* 函数功能		   : IIC读一个字节
* 输    入         : ack=1时，发送ACK，ack=0，发送nACK
* 输    出         : 应答或非应答
*******************************************************************************/
u8 iic_read_byte(u8 ack)
{
	u8 i=0,receive=0;

    for(i=0;i<8;i++ )	//循环8次将一个字节读出，先读高再传低位
	{
        IIC_SCL=0;
        delay_10us(1);
		IIC_SCL=1;
        receive<<=1;
        if(IIC_SDA)receive++;
		delay_10us(1);
    }
    if (!ack)
        iic_nack();
    else
        iic_ack();

    return receive;
}

/*******************************************************************************
* 函 数 名         : at24c02_write_one_byte
* 函数功能		   : 在AT24CXX指定地址写入一个数据
* 输    入         : addr:写入数据的目的地址
					 dat:要写入的数据
* 输    出         : 无
*******************************************************************************/
void at24c02_write_one_byte(u8 addr,u8 dat)
{
    iic_start();
	iic_write_byte(0XA0);	//发送写命令
	iic_wait_ack();
    iic_write_byte(addr);	//发送写地址
	iic_wait_ack();
	iic_write_byte(dat);	//发送字节
	iic_wait_ack();
    iic_stop();				//产生一个停止条件
	delay_ms(10);
}

/*******************************************************************************
* 函 数 名         : at24c02_read_one_byte
* 函数功能		   : 在AT24CXX指定地址读出一个数据
* 输    入         : addr:开始读数的地址
* 输    出         : 读到的数据
*******************************************************************************/
u8 at24c02_read_one_byte(u8 addr)
{
	u8 temp=0;
    iic_start();
	iic_write_byte(0XA0);	//发送写命令
	iic_wait_ack();
    iic_write_byte(addr); 	//发送写地址
	iic_wait_ack();
	iic_start();
	iic_write_byte(0XA1); 	//进入接收模式
	iic_wait_ack();
    temp=iic_read_byte(0);	//读取字节
    iic_stop();				//产生一个停止条件
	return temp;			//返回读取的数据
}

//定义独立按键控制脚
sbit KEY1=P3^1;
sbit KEY2=P3^0;
sbit KEY3=P3^2;
sbit KEY4=P3^3;

//使用宏定义独立按键按下的键值
#define KEY1_PRESS	1
#define KEY2_PRESS	2
#define KEY3_PRESS	3
#define KEY4_PRESS	4
#define KEY_UNPRESS	0

u8 key_scan(u8 mode)
{
	static u8 key=1;

	if(mode)key=1;//连续扫描按键
	if(key==1&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))//任意按键按下
	{
		delay_10us(1000);//消抖
		key=0;
		if(KEY1==0)
			return KEY1_PRESS;
		else if(KEY2==0)
			return KEY2_PRESS;
		else if(KEY3==0)
			return KEY3_PRESS;
		else if(KEY4==0)
			return KEY4_PRESS;
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)	//无按键按下
	{
		key=1;
	}
	return KEY_UNPRESS;
}

#define SMG_A_DP_PORT	P0	//使用宏定义数码管段码口

//定义数码管位选信号控制脚
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//共阴极数码管显示0~F的段码数据
u8 gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
				0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

/*******************************************************************************
* 函 数 名       : smg_display
* 函数功能		 : 动态数码管显示
* 输    入       : dat：要显示的数据
				   pos：从左开始第几个位置开始显示，范围1-8
* 输    出    	 : 无
*******************************************************************************/
void smg_display(u8 dat[],u8 pos)
{
	u8 i=0;
	u8 pos_temp=pos-1;

	for(i=pos_temp;i<8;i++)
	{
	   	switch(i)//位选
		{
			case 0: LSC=1;LSB=1;LSA=1;break;
			case 1: LSC=1;LSB=1;LSA=0;break;
			case 2: LSC=1;LSB=0;LSA=1;break;
			case 3: LSC=1;LSB=0;LSA=0;break;
			case 4: LSC=0;LSB=1;LSA=1;break;
			case 5: LSC=0;LSB=1;LSA=0;break;
			case 6: LSC=0;LSB=0;LSA=1;break;
			case 7: LSC=0;LSB=0;LSA=0;break;
		}
		SMG_A_DP_PORT=gsmg_code[dat[i-pos_temp]];//传送段选数据
		delay_10us(100);//延时一段时间，等待显示稳定
		SMG_A_DP_PORT=0x00;//消音
	}
}

void main()
{
	u8 key_temp=0;
	u8 save_value=0;
	u8 save_buf[3];

	while(1)
	{
		key_temp=key_scan(0);
		if(key_temp==KEY1_PRESS)
		{
			at24c02_write_one_byte(EEPROM_ADDRESS,save_value);
		}
		else if(key_temp==KEY2_PRESS)
		{
			save_value=at24c02_read_one_byte(EEPROM_ADDRESS);
		}
		else if(key_temp==KEY3_PRESS)
		{
			save_value++;
			if(save_value==255)save_value=255;
		}
		else if(key_temp==KEY4_PRESS)
		{
			save_value=0;
		}
		save_buf[0]=save_value/100;
		save_buf[1]=save_value%100/10;
		save_buf[2]=save_value%100%10;
		smg_display(save_buf,6);
	}
}