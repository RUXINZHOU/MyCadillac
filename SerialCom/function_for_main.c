#include "FUNCTION_FOR_MAIN.h"


//�յ����ݵı�־λ
static bit DATA_COME;

//���Դ��ڵ�����
static uchar DATA_BUF_R;

//��ʼ���豸
extern void init()
{
	DATA_COME = 0;
	init_serial_com();
	init_servos_motors();
	LCD_1602_INIT();
}

//��Ϣ�������
extern void TranslateMsg(uchar msg)
{
	uchar buf[5], b_h[3], b_t[3];
	uchar count;
	switch(msg)
	{
		//�Ե���Ĳ���
		case 'U':
		case 'L':
		case 'R':
		case 'D':
			motor_ctrl(msg);
			break;
		case 's':
			set_auto(0);
			motor_ctrl('s');
			break;
		case 'l':
			set_angleF(17);
			break;
		case 'f':
			set_angleF(11);
			break;
		case 'r':
			set_angleF(5);
			break;
		case '1':
			set_angleB(5);
			break;
		case '2':
			set_angleB(11);
			break;
		case '3':
			set_angleB(22);
			break;
		case '-':
			angleFDec();
			break;
		case '+':
			angleFInc();
			break;
		case 'J':
			angleBDec();
			break;
		case 'j':
			angleBInc();
			break;
		case 'A'://һ��
			set_speed(40);
			LCD1602_new_str("Level 1", sizeof("Level 1")  - 1);
			break;
		case 'B':
			set_speed(80);
			LCD1602_new_str("Level 2", sizeof("Level 2")  - 1);
			break;
		case 'C':
			set_speed(120);
			LCD1602_new_str("Level 3", sizeof("Level 3")  - 1);
			break;
		case 'E':
			set_speed(160);
			LCD1602_new_str("Level 4", sizeof("Level 4")  - 1);
			break;
		case 'F':
			set_speed(200);
			LCD1602_new_str("Level 5", sizeof("Level 5")  - 1);
			break;
		case 'T':
			send_string("MOK",sizeof("MOK") - 1);
			break;
		case 'N':
			measure_distanceF2str(buf);
			send_string(buf, 5);
			measure_distanceB2str(buf);
			send_string(buf, 5);
			break;
		case 'n':
			count = 0;
			while(READ_DHT11_toStr(b_t, b_h) == ERROR && (++count) <= 3);//DHT11��̫�ȶ�����������
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
			break;
		case 'S':
			set_connected(1);
			break;
		case 'O':
			set_connected(0);
			break;
		case '#':
			set_auto_renew(1);
			break;
		case '$':
			set_auto_renew(0);
			break;
		case 'P':
			set_auto(1);
			set_speed(120);
			break;
	}
}

//�����յ���Ϣ��־��λ
extern void set_data_come(bit value)
{
	DATA_COME = value;
}

extern bit get_data_come()
{
	return DATA_COME;
}

//��ȡ���յ�������
extern uchar get_data()
{
	return DATA_BUF_R;
}

//�����жϺ���
void serial_com() interrupt 4
{
	RI = 0;	
	DATA_BUF_R = SBUF;
	if(DATA_BUF_R == '&')//�յ���Ϣ������־���������ͣ�
	{
		set_response_flag(1);
	}
	else
	{
		DATA_COME = 1;//�յ�����������Ϣ
	}
}