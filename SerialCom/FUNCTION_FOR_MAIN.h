#include <reg52.h>
#include "DHT11_FUNCTIONS.h"
#include "LCD1602.h"
#include "COMMON_FUNC.h"
#include "ULTRASOUND.h"
#include "SERIALCOM.h"
#include "SERVOS_MOTORS.h"

//��ʼ���豸
extern void init();

//��Ϣ�������
extern void TranslateMsg(uchar msg);

//�����յ���Ϣ��־��λ
extern void set_data_come(bit);

extern bit get_data_come();

//��ȡ���յ�������
extern uchar get_data();