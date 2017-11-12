#include "IO.h"
#include "types.h"


#define SCK_PORT        0
#define SCK_PIN         7

#define DATA_PORT       0
#define DATA_PIN        6

/*------------------------------------------------------------------------------
                                    ����
------------------------------------------------------------------------------*/

#define GET_T           0x03;               //00000011
#define GET_RH          0x05;               //00000101 

#define READ_STATUS     0x07;               //00000111
#define WRITE_STATUS    0x06;               //00000110

/*------------------------------------------------------------------------------
                                    ��������
------------------------------------------------------------------------------*/


//����sck
extern void sck_set();

//����sck
extern void sck_low();

//����data
extern void data_set();

//����data
extern void data_low();

//��������
extern void send_start_command();

//����ʱ��
extern void send_build_command(uint8 command);

//��λ
extern void reset_sht10();
    
//��������
extern void start_sht10();

//��ȡdata��ƽ
char data_status(uint8 port, uint8 pin);

//ackУ��
bool check_ack();

//�����¶�
char measure_t();