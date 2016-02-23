#include "SERIALCOM.h"
#include <reg52.h>
#include "COMMON_FUNC.h"

//���ڵ�����,��ʽ1��������9600
extern void init_serial_com()
{
	TMOD |= 0x20;
	TH1 = 0xFD;
	TL1 = 0xFD;
	TR1 = 1;
	SCON = 0x50;
	EA = 1;
	ES = 1;
	set_response_flag(0);
	set_connected(0);
}
//�򴮿ڷ��ͳ���Ϊlen���ַ�����û�����ӽ�ֱ�ӷ���
extern void send_string(unsigned char* str,unsigned char len)
{
	uchar i = 0;
	if(is_connected() == 0)
		return;
	//�رմ����ж�,�����ж�����
	set_response_flag(0);
	ES = 0;
	TI = 0;
	//���Ϳ�ʼ��
	SBUF = '$';
	while(!TI);
	TI = 0;
	//�ȴ���Ӧ�ټ�������
	ES = 1;
	while(get_response_flag() == 0);
	//��ʼ����
	while(i < len)
	{
		set_response_flag(0);
		ES = 0;
		SBUF = str[i++];
		while(!TI);
		TI = 0;
		//�ȴ���Ӧ�ټ�������
		ES = 1;
		while(get_response_flag() == 0);
	}
	//������ֹ��
	set_response_flag(0);
	ES = 0;
	SBUF = '#';
	while(!TI);
	TI = 0;
	//�ȴ���Ӧ
	ES = 1;
	while(get_response_flag() == 0);
}
