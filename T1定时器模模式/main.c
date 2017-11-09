#include "main.h"


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
* �������ƣ�initIo
* ��    �ܣ���ʼ��Ӳ��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
*-----------------------------------------------------------------------------*/
void initIo(){
    P1SEL &= ~0x02;                //�˿�1����ѡ��1Ϊ���裬0Ϊͨ��IO
    P1DIR |= 0x02;                 //�˿�1�������ã�1Ϊ�����0Ϊ����
}

/*------------------------------------------------------------------------------
* �������ƣ�initIo
* ��    �ܣ���ʼ����ʱ��
* ��ڲ����� uint8 mode               ģʽѡ��
                TIMER1_FREEDOM          0x01                //timer1����ģʽ
                TIMER1_MODULO           0x02                //timer1ģģʽ
                TIMER1_UPorDOWN         0x03                //timer1��������ģʽ

            uint16 overflow         ���

            uint8 fractional        ��Ƶ
                TIMER_1                 0x00                //1��Ƶ
                TIMER_8                 0x04                //8��Ƶ
                TIMER_32                0x08                //32��Ƶ
                TIMER_128               0x0C                //128��Ƶ
* ���ڲ�������
* �� �� ֵ����
*-----------------------------------------------------------------------------*/
//               ��ʱ��ģʽ        ���              ��Ƶ     
void initTimer1(uint8 mode, uint16 overflow, uint8 fractional){
    
    T1CC0L = overflow & 0xFF;                       //�Ͱ�λ
    T1CC0H = (uint8)((overflow & 0xFF00) >> 8);     //�߰�λ
    
    
    if(mode == TIMER1_MODULO){
        T1CCTL0 |= 0x44;                            //timer1   �Ƚ�ģʽ
    }
    
    T1CTL |= (uint8)(mode | fractional);            //���÷�Ƶ��ģʽ
    T1IE = 0x01;                                    //timer1�ж�ʹ��
}

/*------------------------------------------------------------------------------
* ��    �ܣ���ʱ��T1�����ӳ���
*-----------------------------------------------------------------------------*/
#pragma vector = T1_VECTOR //�жϷ����ӳ���
__interrupt void T1_ISR(void) {
    T1STAT &= ~0x20;           //timer1�����������־λ     ���жϱ�־
    T1IF = 0;                  //timer1�жϱ�־            ���жϱ�־

    setLed(REVERSE);        //��תled
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
    initIo();                                       //��ʼ��IO
    initTimer1(TIMER1_UPorDOWN, 30000, TIMER_128);  //��ʼ����ʱ��
    setLed(OFF);                                    //��ʼ���رյ�

    
    EA = 1;                                         //���ж�
}


void main( void )
{
    
    init();                                         //��ʼ��Ӳ�����������
    while(1){
    
    }
}


