#include "DHT11_FUNCTIONS.h"
#include <reg52.h>
#include "COMMON_FUNC.h"
//��������
#define NUMBER 20
//�˿�����
sbit DHT11_DATA = P3^2;

#define SIZE 5
static uchar status;
static uchar data_array[SIZE];

//��ȡһ���ֽ�
static uchar DHT11_READ_VALUE()
{
	uchar count, value = 0, i;
	status = OK;
	for(i = 8;i > 0;i--)
	{
		value <<= 1;
		count = 0;
		//��ȡһλ����ǰ�ȴ�50us�͵�ƽ
		while((DHT11_DATA) != 1 && (count++ < NUMBER));
		if(count > NUMBER)
		{
			status = ERROR;
			return ERROR;
		}
		
		count = 0;
		
		delay_10us();
		delay_10us();
		delay_10us();
		
		//26-28us�ߵ�ƽ��ʾ��λΪ0��70usΪ1
		if(DHT11_DATA != 0)//����1
		{
			value++;
			//�ȴ�ʣ��ߵ�ƽʱ�����
			while((DHT11_DATA) != 0 && (count++ < NUMBER))
				DHT11_DATA = 1;
			
			if(count > NUMBER)
			{
				status = ERROR;
				return 0;
			}
		}
	}
	return value;
}

//��ȡ�¶Ⱥ�ʪ��
extern uchar READ_DHT11(int* t_h, int* h_h, int* t_l, int* h_l)
{
	uchar check = 0, i = 0, count = 0;
	//ȫ���жϹر�
	EA = 0;
	//����������18ms����
	DHT11_DATA = 0;
	delay_ms(20);
	DHT11_DATA = 1;
	//��ʱ20-40us�ȴ�80usӦ���ź�
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	delay_10us();
	
	if(DHT11_DATA != 0)
	{
		EA = 1;
		return ERROR;
	}
	else
	{
		//�ȴ�ʣ��͵�ƽʱ�����
		while((DHT11_DATA) == 0 && (count++ < NUMBER));
		if(count > NUMBER)
		{
			EA = 1;
			DHT11_DATA = 1;
			return ERROR;
		}
		count = 0;
		DHT11_DATA = 1;//�ͷ�������
		//Ӧ���źź��80us�ߵ�ƽ
		while((DHT11_DATA) != 0 && (count++ < NUMBER));
		if(count >= NUMBER)
		{
			EA = 1;
			DHT11_DATA = 1;
			return ERROR;
		}
		//����ʪ�¶�
		for(i = 0;i < SIZE;i++)
		{
			data_array[i] = DHT11_READ_VALUE();
			if(status == ERROR)
			{
				EA = 1;
				DHT11_DATA = 1;
				return ERROR;
			}
			if(i != SIZE - 1)
			{
				check += data_array[i];
			}
		}
		//û������ȡ����У������
		if(check == data_array[SIZE - 1])
		{
			*h_h = data_array[0];
			*h_l = data_array[1];
			*t_h = data_array[2];
			*t_l = data_array[3];
			
			
			EA = 1;
			DHT11_DATA = 1;
			return OK;
		}
		else
		{
			EA = 1;
			return ERROR;
		}
	}
}

extern unsigned char READ_DHT11_toStr(unsigned char* t_str, unsigned char* h_str)
{
	int th, tl, hh, hl;
	if(READ_DHT11(&th, &hh, &tl, &hl) == OK)
	{
		t_str[0] = 'T';
		t_str[1] = num2char[th / 10];
		t_str[2] = num2char[th % 10];
		h_str[0] = 'H';
		h_str[1] = num2char[hh / 10];
		h_str[2] = num2char[hh % 10];
		return OK;
	}
	else
	{
		return ERROR;
	}
}