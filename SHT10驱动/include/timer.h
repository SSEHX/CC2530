#include <iocc2531.h>
#include "types.h"

/*------------------------------------------------------------------------------
                                    定义IO口
------------------------------------------------------------------------------*/

#define TIMER_1                 0x00                //1分频
#define TIMER_8                 0x04                //8分频
#define TIMER_32                0x08                //32分频
#define TIMER_128               0x0C                //128分频

#define TIMER1_FREEDOM          0x01                //timer1自由模式
#define TIMER1_MODULO           0x02                //timer1模模式
#define TIMER1_UPorDOWN         0x03                //timer1正反计数模式


/*------------------------------------------------------------------------------
                                    函数声明
------------------------------------------------------------------------------*/


// 初始化timer1
void initTimer1(uint8 mode, uint16 overflow, uint8 fractional);



