#include <reg52.h>
#include "COMMON_FUNC.h"
#include "ULTRASOUND.h"

//�˿�����
sbit trigF = P2^4;
sbit echoF = P2^5;
sbit trigB = P2^6;
sbit echoB = P2^7;

static void init_T2()
{
	T2CON = 0x00;
	TH2 = 0;
	TL2 = 0;
}

//ǰ���
extern void measure_distanceF(unsigned int *distance)
{
	init_T2();
	
	*distance = 0;
	
	send_trigF();
	
	while(!echoF);
	//��ʼ��ʱ
     TR2 = 1;
	while(echoF);
     TR2 = 0;
	//��λcm
	*distance = ((TH2*256 + TL2) * 1.866) / 100;
}

extern void send_trigF()
{
	trigF = 1;
    delay_10us();
    trigF = 0;
}

//����
extern void measure_distanceB(unsigned int *distance)
{
	init_T2();
	
	*distance = 0;
	
	send_trigB();
	
	while(!echoB);
	//��ʼ��ʱ
     TR2 = 1;
	while(echoB);
     TR2 = 0;
	//��λcm
	*distance = ((TH2*256 + TL2) * 1.866) / 100;
}

extern void send_trigB()
{
	trigB = 1;
    delay_10us();
    trigB = 0;
}

//ǰ��ಢת��Ϊ�ַ���
extern void measure_distanceF2str(uchar *str_d)
{
	uint d;
	measure_distanceF(&d);
	str_d[0] = 'D';
	str_d[1] = num2char[d / 1000];
	str_d[2] = num2char[(d % 1000) / 100];
	str_d[3] = num2char[(d % 100) / 10];
	str_d[4] = num2char[d % 10];
}
//���ಢת��Ϊ�ַ���
extern void measure_distanceB2str(uchar *str_d)
{
	uint d;
	measure_distanceB(&d);
	str_d[0] = 'd';
	str_d[1] = num2char[d / 1000];
	str_d[2] = num2char[(d % 1000) / 100];
	str_d[3] = num2char[(d % 100) / 10];
	str_d[4] = num2char[d % 10];
}