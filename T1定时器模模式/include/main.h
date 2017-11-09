#include <iocc2531.h>
#include "types.h"

/*------------------------------------------------------------------------------
                                    ����IO��
------------------------------------------------------------------------------*/

#define LED_1 P1_1

#define TIMER_1                 0x00                //1��Ƶ
#define TIMER_8                 0x04                //8��Ƶ
#define TIMER_32                0x08                //32��Ƶ
#define TIMER_128               0x0C                //128��Ƶ

#define TIMER1_FREEDOM          0x01                //timer1����ģʽ
#define TIMER1_MODULO           0x02                //timer1ģģʽ
#define TIMER1_UPorDOWN         0x03                //timer1��������ģʽ

/*------------------------------------------------------------------------------
                                    ö������
------------------------------------------------------------------------------*/
//                     16M         32M
enum SYSCLK_SRC     {RC_16MHz, XOSC_32MHz};     //ѡ����Դ

//                   ��   ��    ��ת
enum LED_STATE      {ON, OFF, REVERSE};         //led״̬



/*------------------------------------------------------------------------------
                                    ��������
------------------------------------------------------------------------------*/

// ��ʼ��IO��
extern void initIo();

// ��ʼ��timer1
void initTimer1(uint8 mode, uint16 overflow, uint8 fractional);

// ��ʼ�������豸
extern void init();

// ѡ��ϵͳʱ��Դ(��ʱ��Դ)
extern void systemClockSourceSelect(enum SYSCLK_SRC source);

// ����led
extern void setLed(enum LED_STATE state);

