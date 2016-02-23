#include <reg52.h>
#include "LCD1602.h"
#include "COMMON_FUNC.h"

sbit LCD1602_RS = P2^0;
sbit LCD1602_E = P2^1;

extern void LCD1602_COMMAND(unsigned char command)
{
	LCD1602_RS =0;
	P0 = command;
	delay_ms(5);
	LCD1602_E = 1;
	delay_ms(5);
	LCD1602_E = 0;
}


extern void LCD1602_DATA(unsigned char d)
{
	LCD1602_RS =1;
	P0 = d;
	delay_ms(5);
	LCD1602_E = 1;
	delay_ms(5);
	LCD1602_E = 0;
}

 
extern void LCD_1602_INIT()
{
	LCD1602_E = 0;

	LCD1602_COMMAND(0x38);//16*2��ʾ��5*7����8λ���ݽӿ�
	LCD1602_COMMAND(0x0C);//��ʼ��ʾ���޹��
	LCD1602_COMMAND(0x06);//��ַ�Զ���һ
	LCD1602_COMMAND(0x01);//��ʾ���㣬��ַָ������
}

//��Ļ�͵�ַָ������
extern void LCD1602_CLEAR()
{
	LCD1602_COMMAND(0x01);//��ʾ���㣬��ַָ������
}

//����
extern void LCD1602_NEWLINE()
{
	LCD1602_COMMAND(0x80 + 0x40);
}

//�ӵ�ǰ��Ļ���һ���ִ���ʼ��ʾ�����ַ���
extern void LCD1602_cat_str(unsigned char *str, unsigned char len)
{
	uchar i;
	
	for(i = 0;i < len && i < 32;i++)
	{
		LCD1602_DATA(str[i]);
		if(i == 15)//����
		{
			LCD1602_NEWLINE();
		}
	}
}

//��������ͷ��ʾһ���ַ������Զ�����
extern void LCD1602_new_str(unsigned char *str, unsigned char len)
{
	LCD1602_CLEAR();
	LCD1602_COMMAND(0x80);
	LCD1602_cat_str(str, len);
}
