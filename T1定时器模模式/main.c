#include "main.h"


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
* 函数名称：initIo
* 功    能：初始化硬件
* 入口参数：无
* 出口参数：无
* 返 回 值：无
*-----------------------------------------------------------------------------*/
void initIo(){
    P1SEL &= ~0x02;                //端口1功能选择：1为外设，0为通用IO
    P1DIR |= 0x02;                 //端口1方向设置：1为输出，0为输入
}

/*------------------------------------------------------------------------------
* 函数名称：initIo
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

    setLed(REVERSE);        //反转led
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
    initIo();                                       //初始化IO
    initTimer1(TIMER1_UPorDOWN, 30000, TIMER_128);  //初始化定时器
    setLed(OFF);                                    //初始化关闭灯

    
    EA = 1;                                         //开中断
}


void main( void )
{
    
    init();                                         //初始化硬件及软件设置
    while(1){
    
    }
}


