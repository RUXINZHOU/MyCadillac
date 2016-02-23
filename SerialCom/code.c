/**************************************
	���ߣ�������
	Email:792570367@qq.com
	����ʱ�䣺2016/02/04,11:45
**************************************/

#include "FUNCTION_FOR_MAIN.h"
int main()
{
	init();
	delay_ms(100);
	LCD1602_new_str("Initializing...", sizeof("Initializing...")  - 1);
	delay_ms(100);
	LCD1602_new_str("Cadillac Ready!", sizeof("Cadillac Ready!")  - 1);
	
	while(1)
	{
		if(get_data_come() == 1)
		{	
			set_data_come(0);
			TranslateMsg(get_data());
		}
		else if(is_auto())
		{
			manage_auto();
		}
		else if(is_timeup_30s() && get_auto_renew() && get_direction() == 0x00)//�����Զ�������û�յ�ָ��ʱ��ÿ30s�ش�һ������
		{
			uchar buf[5], b_h[3], b_t[3];
			uchar count = 0;
			set_timeup_30s(0);
			//���������;���
			measure_distanceF2str(buf);
			send_string(buf, 5);
			measure_distanceB2str(buf);
			send_string(buf, 5);
			//������������ʪ��
			while(READ_DHT11_toStr(b_t, b_h) == ERROR && (++count) <= 3);
			if(count <= 3)
			{
				send_string(b_t, 3);
				send_string(b_h, 3);
			}
			else
			{
				send_string("TRetry", sizeof("TRetry") - 1);
				send_string("HRetry", sizeof("HRetry") - 1);
			}
		}
		else
		{
			accelerator();//ִ�м�����������ģ�⻺�����������٣�
		}
	}
}
