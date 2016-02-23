#ifndef _COMMON_FUNC_
#define _COMMON_FUNC_

typedef unsigned char uchar;
typedef unsigned int uint;
//LCD����
extern unsigned char code num2char[10];

extern void delay_ms(unsigned int);
extern void delay_10us();
//Ϊ����ͨ�����õĴ�����ʽͨ�Ž�����־����
extern bit get_response_flag();
extern void set_response_flag(bit);
//��ʱ��غ�����30s
extern void set_timeup_30s(bit);
extern bit is_timeup_30s();
//����״̬
extern void set_connected(bit);
extern bit is_connected();
//�Զ�����״̬
extern void set_auto_renew(bit);
extern bit get_auto_renew();
#endif