#include "timer.h"
#include "IO.h"

uint8 state = 0;

/*------------------------------------------------------------------------------
* 函数胕nitLednitIo
* 功    能：初始化定时器
* 入口参数： uint8 mode               模式选择
                TIMER1_FREEDOM          0x01                //timer1自由模式
                TIMER1_MODULO           0x02                //timer1模模式
                TIMER1_UPorDOWN         0x03                //timer1正反计数模式

            uint16 overflow         溢出

            uint8 fractional        分频
                TIMER_1                 0x00                //1分频
                TIMER_8                 0x04                //8分频
                TIMER_32                0x08                //32分频
                TIMER_128               0x0C                //128分频
* 出口参数：无
* 返 回 值：无
*-----------------------------------------------------------------------------*/
//               定时器模式        溢出              分频     
void initTimer1(uint8 mode, uint16 overflow, uint8 fractional){
    
    T1CC0L = overflow & 0xFF;                       //低八位
    T1CC0H = (uint8)((overflow & 0xFF00) >> 8);     //高八位
    
    
    if(mode == TIMER1_MODULO){
        T1CCTL0 |= 0x44;                            //timer1   比较模式
    }
    
    T1CTL |= (uint8)(mode | fractional);            //设置分频和模式
    T1IE = 0x01;                                    //timer1中断使能
}

/*------------------------------------------------------------------------------
* 功    能：定时器T1服务子程序
*-----------------------------------------------------------------------------*/
#pragma vector = T1_VECTOR //中断服务子程序
__interrupt void T1_ISR(void) {
    T1STAT &= ~0x20;           //timer1计数器溢出标志位     清中断标志
    T1IF = 0;                  //timer1中断标志            清中断标志

    
}


