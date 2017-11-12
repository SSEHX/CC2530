#include "base.h"
#include "timer.h"
#include <iocc2530.h>

//初始化时钟
/*------------------------------------------------------------------------------
* 函数名称：systemClockSourceSelect
* 功    能：选择系统时钟源(主时钟源)
* 入口参数：source
*             XOSC_32MHz  32MHz晶体振荡器
*             RC_16MHz    16MHz RC振荡器
* 出口参数：无
* 返 回 值：无
*-----------------------------------------------------------------------------*/
void systemClockSourceSelect(enum SYSCLK_SRC source)
{
    unsigned char clkconcmd,clkconsta;
    
    /*
    系统时钟源(主时钟源)选择16MHz RC振荡器，定时器tick设置为16MHz，时钟速度设置为16MHz
    CLKCONCMD.OSC32K[b7]不改变      32KHz时钟源选择保持先前设置
    CLKCONCMD.OSC[b6] = 1           系统时钟源(主时钟源)选择16MHz RC振荡器
    CLKCONCMD.TICKSPD[b5..b3] = 001 定时器tick设置为16MHz
    CLKCONCMD.CLKSPD[b2..b0] = 001  时钟速度设置为16MHz
    */
    if(source == RC_16MHz)
    {             
        CLKCONCMD &= 0x80;
        CLKCONCMD |= 0x49;    //01001001   
    }
    
    
    /*
    系统时钟源(主时钟源)选择32MHz晶体振荡器，定时器tick设置为32MHz，时钟速度设置为32MHz
    CLKCONCMD.OSC32K[b7]不改变      32KHz时钟源选择保持先前设置
    CLKCONCMD.OSC[b6] = 0           系统时钟源(主时钟源)选择32MHz晶体振荡器
    CLKCONCMD.TICKSPD[b5..b3] = 000 定时器tick设置为32MHz
    CLKCONCMD.CLKSPD[b2..b0] = 000  时钟速度设置为32MHz
    */  
    else if(source == XOSC_32MHz)
    {
        CLKCONCMD &= 0x80;
    }
    
    
    /* 等待所选择的系统时钟源(主时钟源)稳定 */
    clkconcmd = CLKCONCMD;             // 读取时钟控制寄存器CLKCONCMD
    do
    {
        clkconsta = CLKCONSTA;         // 读取时钟状态寄存器CLKCONSTA
    }while(clkconsta != clkconcmd);    // 直到CLKCONSTA寄存器的值与CLKCONCMD寄存
                                       // 器的值一致，说明所选择的系统时钟源(主
                                       // 时钟源)已经稳定  
}

/***********************************************************************************
* @fn          halMcuWaitUs
*
* @brief       Busy wait function. Waits the specified number of microseconds. Use
*              assumptions about number of clock cycles needed for the various
*              instructions. This function assumes a 32 MHz clock.
*
*              NB! This function is highly dependent on architecture and compiler!
*
* @param       uint16 usec - number of microseconds delays
*
* @return      none
*/
#pragma optimize=none
void wait_us(uint16 usec)
{
    usec>>= 1;
    while(usec--)
    {
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
    }
}
/***********************************************************************************
* @fn          halMcuWaitMs
*
* @brief       Busy wait function. Waits the specified number of milliseconds. Use
*              assumptions about number of clock cycles needed for the various
*              instructions.
*
*              NB! This function is highly dependent on architecture and compiler!
*
* @param       uint16 millisec - number of milliseconds delay
*
* @return      none
*/
#pragma optimize=none
void wait_ms(uint16 msec)
{
    while(msec--)
        wait_us(1000);
}

/*------------------------------------------------------------------------------
* 函数名称：setLed
* 功    能：更改led灯状态
* 入口参数：state
*             ON            点亮led
*             OFF           熄灭led
*             REVERSE       反转led
* 出口参数：无
* 返 回 值：无
*-----------------------------------------------------------------------------*/
void setLed(enum LED_STATE state){
    if (state == ON){
        LED_1 = 0;
    } 
    if (state == OFF){
        LED_1 = 1;

    } 
    if (state == REVERSE){
        LED_1 = !LED_1;
    } 
}

/*------------------------------------------------------------------------------
* 函数名称：initLed
* 功    能：初始化LED
* 入口参数：无
* 出口参数：无
* 返 回 值：无
*-----------------------------------------------------------------------------*/
void initLed(){
    P1SEL &= ~0x02;                //端口1功能选择：1为外设，0为通用IO
    P1DIR |= 0x02;                 //端口1方向设置：1为输出，0为输入
}

/*------------------------------------------------------------------------------
* 函数名称：init
* 功    能：初始化硬件
* 入口参数：无
* 出口参数：无
* 返 回 值：无
*-----------------------------------------------------------------------------*/
void init(){
    systemClockSourceSelect(XOSC_32MHz);            //选择32M晶振
    initLed();                                       //初始化LED
    initTimer1(TIMER1_UPorDOWN, 30000, TIMER_128);  //初始化定时器
    setLed(OFF);                                    //初始化关闭灯

    
    EA = 1;                                         //开中断
}
