#include "SHT10.h"
//#include

//����sck
void sck_set(){
    io_set(SCK_PORT, SCK_PIN);
}

//����sck
void sck_low(){
    io_low(SCK_PORT, SCK_PIN);
}

//����data
void data_set(){
    io_set(DATA_PORT, DATA_PIN);
}

//����data
void data_low(){
    io_low(DATA_PORT, DATA_PIN);
}

char data_status(){
    return io_get(DATA_PORT, DATA_PIN);
}
/*------------------------------------------------------------------------------
* �������ƣ�reset_sht10
* ��    �ܣ���λSHT10
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
*-----------------------------------------------------------------------------*/
void reset_sht10(){
    uint8 i;
    data_set();
    for (i = 0; i <=9; i++){
        sck_low();
        wait_ms(1);
        sck_set();
        wait_ms(1);
    }
}
/*------------------------------------------------------------------------------
* �������ƣ�start_sht10
* ��    �ܣ���������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
*-----------------------------------------------------------------------------*/
void start_sht10(){
    wait_ms(20);                //�ȴ�20msʹ�豸����׼��״̬
    
    reset_sht10();              //��λ
            
    send_start_command();             //��������
    
}
/*------------------------------------------------------------------------------
* �������ƣ�build_command
* ��    �ܣ���������ʱ��
* ��ڲ�����uint8 command
                GET_T           0x03;               //00000011
                GET_RH          0x05;               //00000101 

                READ_STATUS     0x07;               //00000111
                WRITE_STATUS    0x06;               //00000110
* ���ڲ�������
* �� �� ֵ����
*-----------------------------------------------------------------------------*/
void send_build_command(uint8 command){
    uint8 i;
    
    //��ʼ��sck��������
    sck_low();
    
    //��������
    for(i = 7 ; i >= 0; i--){
        if((1 << (i)) & command){
            data_set();
            wait_ms(1);
            sck_set();
            wait_ms(1);
            sck_low();
            wait_ms(1);
        }else{
            data_low();
            wait_ms(1);
            sck_set();
            wait_ms(1);
            sck_low();
            wait_ms(1);
        }
    }
    
}
/*------------------------------------------------------------------------------
* �������ƣ�check_ack
* ��    �ܣ�ackУ��
                Ӧ�ڹ�������� build_command() ֮�����
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ��bool
                TRUE        �ɹ�
                FALSE       ʧ��
*-----------------------------------------------------------------------------*/
bool check_ack(){
    
    uint8 j;
    //ackУ��
    //ѭ����ȡ���data��ƽ
    for(j = 0 ; j < 5 ; j++){
        if(!data_status()){
            sck_set();
            wait_ms(1);
            sck_low();
            wait_ms(1);
            
            //ѭ����ȡ��Σ�
            for(j = 0; j < 5; j++){
                if(data_status()){
                    return TRUE;
                }else{
                    
                    //���5ms֮��û��ȡ���򷵻�FALSE
                    if(j == 4){
                        return FALSE;
                    }
                }
                //�ȴ�1ms������ȡ
                wait_ms(1);
            }
            
        }else{
            
            //���5ms֮��û��ȡ���򷵻�FALSE
            if(j==4){
                return FALSE;
            }
        }
        wait_ms(1);
    }
}

//��������ʱ��
void send_start_command(){
    
    data_set();
    wait_ms(1);
    sck_set();
    wait_ms(1);
    
    data_low();
    wait_ms(1);
    sck_low();
    wait_ms(1);
    
    sck_set();
    wait_ms(1);
    data_set();

}

//�����¶�
char measure_t(){
    start_sht10();
    send_build_command(GET_T);
    return check_ack();
}