#ifndef _SERVO_MOTOR_
#define _SERVO_MOTOR_
#define DANGEROUS_DIATANCE 32
#define DELAY_TIME 120
#define STEER_F 0
#define STEER_L 1
#define STEER_R 2
/***********************
******���Ƶ��**********
**********************/

//���Ƶ��ת��
extern void motor_ctrl(const unsigned char);
extern unsigned char get_direction();
//���õ��ת��
extern void set_speed(unsigned char s);//�����ٶ�����
extern unsigned char get_speed();//��ȡ�ٶ�����
extern void set_speed_direct();//ֱ�������ٶ�Ϊ���赵λ
//����ٶȲ���
extern void accelerator();

/***********************
******���ƶ��**********
	ǰ�����F
	������B
**********************/

//��ʼ�����
extern void init_servos_motors();
//���ýǶȵĺ���
extern void set_angleF(unsigned char);
extern void set_angleB(unsigned char);
//����ǶȼӼ�
extern void angleFDec();
extern void angleFInc();
extern void angleBDec();
extern void angleBInc();
//�Զ�����
extern void manage_auto();
extern void turn_Left();
extern void turn_Right();
extern void steer_turn_Left();
extern void steer_turn_Right();
extern void steer_turn_F();
extern void backward();
extern void forward();
extern void measure_f(unsigned int*);
extern void set_auto(bit);
extern bit is_auto();
extern void set_orientation(bit);
extern bit get_orientation();
extern void inform_danger();
extern void inform_safe();
extern bit is_dangerous();
extern void set_steer_state(unsigned char);
extern unsigned char get_steer_state();
#endif