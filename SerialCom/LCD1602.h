#ifndef _LCD1602_
#define	_LCD1602_


extern void delay(unsigned int time);
//��LCD1602����һ������
extern void LCD1602_COMMAND(unsigned char command);
//��LCD1602����һ���ַ�
extern void LCD1602_DATA(unsigned char d);
//��ʼ��LCD1602
extern void LCD_1602_INIT();
//��Ļ�͵�ַָ������
extern void LCD1602_CLEAR();
//����
extern void LCD1602_NEWLINE();
//�ӵ�ǰ��Ļ���һ���ִ���ʼ��ʾ�����ַ���
extern void LCD1602_cat_str(unsigned char *str, unsigned char len);
//��������ͷ��ʾһ���ַ������Զ�����
extern void LCD1602_new_str(unsigned char *str, unsigned char len);
#endif
