#include "IO.h"
#include "types.h"


#define SCK_PORT        0
#define SCK_PIN         7

#define DATA_PORT       0
#define DATA_PIN        6

/*------------------------------------------------------------------------------
                                    命令
------------------------------------------------------------------------------*/

#define GET_T           0x03;               //00000011
#define GET_RH          0x05;               //00000101 

#define READ_STATUS     0x07;               //00000111
#define WRITE_STATUS    0x06;               //00000110

/*------------------------------------------------------------------------------
                                    函数声明
------------------------------------------------------------------------------*/


//拉高sck
extern void sck_set();

//拉低sck
extern void sck_low();

//拉高data
extern void data_set();

//拉低data
extern void data_low();

//发送命令
extern void send_start_command();

//构建时序
extern void send_build_command(uint8 command);

//软复位
extern void reset_sht10();
    
//启动传输
extern void start_sht10();

//获取data电平
char data_status(uint8 port, uint8 pin);

//ack校验
bool check_ack();

//测量温度
char measure_t();