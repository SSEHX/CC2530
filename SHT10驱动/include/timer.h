#include <iocc2531.h>
#include "types.h"

/*------------------------------------------------------------------------------
                                    ����IO��
------------------------------------------------------------------------------*/

#define TIMER_1                 0x00                //1��Ƶ
#define TIMER_8                 0x04                //8��Ƶ
#define TIMER_32                0x08                //32��Ƶ
#define TIMER_128               0x0C                //128��Ƶ

#define TIMER1_FREEDOM          0x01                //timer1����ģʽ
#define TIMER1_MODULO           0x02                //timer1ģģʽ
#define TIMER1_UPorDOWN         0x03                //timer1��������ģʽ


/*------------------------------------------------------------------------------
                                    ��������
------------------------------------------------------------------------------*/


// ��ʼ��timer1
void initTimer1(uint8 mode, uint16 overflow, uint8 fractional);



