#include "public.h"
#include "24c02.h"
#include "key.h"
#include "smg.h"


#define EEPROM_ADDRESS	0	//定义数据存入EEPROM的起始地址

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
