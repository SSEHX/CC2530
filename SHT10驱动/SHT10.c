#include "SHT10.h"
//#include

//拉高sck
void sck_set(){
    io_set(SCK_PORT, SCK_PIN);
}

//拉低sck
void sck_low(){
    io_low(SCK_PORT, SCK_PIN);
}

//拉高data
void data_set(){
    io_set(DATA_PORT, DATA_PIN);
}

//拉低data
void data_low(){
    io_low(DATA_PORT, DATA_PIN);
}

char data_status(){
    return io_get(DATA_PORT, DATA_PIN);
}
/*------------------------------------------------------------------------------
* 函数名称：reset_sht10
* 功    能：软复位SHT10
* 入口参数：无
* 出口参数：无
* 返 回 值：无
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
* 函数名称：start_sht10
* 功    能：启动传输
* 入口参数：无
* 出口参数：无
* 返 回 值：无
*-----------------------------------------------------------------------------*/
void start_sht10(){
    wait_ms(20);                //等待20ms使设备进入准备状态
    
    reset_sht10();              //软复位
            
    send_start_command();             //发送命令
    
}
/*------------------------------------------------------------------------------
* 函数名称：build_command
* 功    能：构建命令时序
* 入口参数：uint8 command
                GET_T           0x03;               //00000011
                GET_RH          0x05;               //00000101 

                READ_STATUS     0x07;               //00000111
                WRITE_STATUS    0x06;               //00000110
* 出口参数：无
* 返 回 值：无
*-----------------------------------------------------------------------------*/
void send_build_command(uint8 command){
    uint8 i;
    
    //初始化sck，先拉低
    sck_low();
    
    //发送命令
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
* 函数名称：check_ack
* 功    能：ack校验
                应在构建命令函数 build_command() 之后调用
* 入口参数：无
* 出口参数：无
* 返 回 值：bool
                TRUE        成功
                FALSE       失败
*-----------------------------------------------------------------------------*/
bool check_ack(){
    
    uint8 j;
    //ack校验
    //循环读取五次data电平
    for(j = 0 ; j < 5 ; j++){
        if(!data_status()){
            sck_set();
            wait_ms(1);
            sck_low();
            wait_ms(1);
            
            //循环读取五次，
            for(j = 0; j < 5; j++){
                if(data_status()){
                    return TRUE;
                }else{
                    
                    //如果5ms之后还没读取到则返回FALSE
                    if(j == 4){
                        return FALSE;
                    }
                }
                //等待1ms继续读取
                wait_ms(1);
            }
            
        }else{
            
            //如果5ms之后还没读取到则返回FALSE
            if(j==4){
                return FALSE;
            }
        }
        wait_ms(1);
    }
}

//启动传输时序
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

//测量温度
char measure_t(){
    start_sht10();
    send_build_command(GET_T);
    return check_ack();
}