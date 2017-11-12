#include "timer.h"
#include "IO.h"

uint8 state = 0;

/*------------------------------------------------------------------------------
* �����initLednitIo
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

    
}


