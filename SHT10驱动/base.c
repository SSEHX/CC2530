#include "base.h"
#include "timer.h"
#include <iocc2530.h>

//��ʼ��ʱ��
/*------------------------------------------------------------------------------
* �������ƣ�systemClockSourceSelect
* ��    �ܣ�ѡ��ϵͳʱ��Դ(��ʱ��Դ)
* ��ڲ�����source
*             XOSC_32MHz  32MHz��������
*             RC_16MHz    16MHz RC����
* ���ڲ�������
* �� �� ֵ����
*-----------------------------------------------------------------------------*/
void systemClockSourceSelect(enum SYSCLK_SRC source)
{
    unsigned char clkconcmd,clkconsta;
    
    /*
    ϵͳʱ��Դ(��ʱ��Դ)ѡ��16MHz RC��������ʱ��tick����Ϊ16MHz��ʱ���ٶ�����Ϊ16MHz
    CLKCONCMD.OSC32K[b7]���ı�      32KHzʱ��Դѡ�񱣳���ǰ����
    CLKCONCMD.OSC[b6] = 1           ϵͳʱ��Դ(��ʱ��Դ)ѡ��16MHz RC����
    CLKCONCMD.TICKSPD[b5..b3] = 001 ��ʱ��tick����Ϊ16MHz
    CLKCONCMD.CLKSPD[b2..b0] = 001  ʱ���ٶ�����Ϊ16MHz
    */
    if(source == RC_16MHz)
    {             
        CLKCONCMD &= 0x80;
        CLKCONCMD |= 0x49;    //01001001   
    }
    
    
    /*
    ϵͳʱ��Դ(��ʱ��Դ)ѡ��32MHz������������ʱ��tick����Ϊ32MHz��ʱ���ٶ�����Ϊ32MHz
    CLKCONCMD.OSC32K[b7]���ı�      32KHzʱ��Դѡ�񱣳���ǰ����
    CLKCONCMD.OSC[b6] = 0           ϵͳʱ��Դ(��ʱ��Դ)ѡ��32MHz��������
    CLKCONCMD.TICKSPD[b5..b3] = 000 ��ʱ��tick����Ϊ32MHz
    CLKCONCMD.CLKSPD[b2..b0] = 000  ʱ���ٶ�����Ϊ32MHz
    */  
    else if(source == XOSC_32MHz)
    {
        CLKCONCMD &= 0x80;
    }
    
    
    /* �ȴ���ѡ���ϵͳʱ��Դ(��ʱ��Դ)�ȶ� */
    clkconcmd = CLKCONCMD;             // ��ȡʱ�ӿ��ƼĴ���CLKCONCMD
    do
    {
        clkconsta = CLKCONSTA;         // ��ȡʱ��״̬�Ĵ���CLKCONSTA
    }while(clkconsta != clkconcmd);    // ֱ��CLKCONSTA�Ĵ�����ֵ��CLKCONCMD�Ĵ�
                                       // ����ֵһ�£�˵����ѡ���ϵͳʱ��Դ(��
                                       // ʱ��Դ)�Ѿ��ȶ�  
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
* �������ƣ�setLed
* ��    �ܣ�����led��״̬
* ��ڲ�����state
*             ON            ����led
*             OFF           Ϩ��led
*             REVERSE       ��תled
* ���ڲ�������
* �� �� ֵ����
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
* �������ƣ�initLed
* ��    �ܣ���ʼ��LED
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
*-----------------------------------------------------------------------------*/
void initLed(){
    P1SEL &= ~0x02;                //�˿�1����ѡ��1Ϊ���裬0Ϊͨ��IO
    P1DIR |= 0x02;                 //�˿�1�������ã�1Ϊ�����0Ϊ����
}

/*------------------------------------------------------------------------------
* �������ƣ�init
* ��    �ܣ���ʼ��Ӳ��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
*-----------------------------------------------------------------------------*/
void init(){
    systemClockSourceSelect(XOSC_32MHz);            //ѡ��32M����
    initLed();                                       //��ʼ��LED
    initTimer1(TIMER1_UPorDOWN, 30000, TIMER_128);  //��ʼ����ʱ��
    setLed(OFF);                                    //��ʼ���رյ�

    
    EA = 1;                                         //���ж�
}
