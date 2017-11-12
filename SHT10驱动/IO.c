#include "types.h"
#include "IO.h"
#include "base.h"


/*------------------------------------------------------------------------------
* 函数名称：io_set
* 功    能：将指定IO口变为高电平
* 入口参数：port
                0
                1
                2
            pin
                0
                1
                2
                3
                4
                5
                6
                7
* 出口参数：无
* 返 回 值：无
*-----------------------------------------------------------------------------*/
char io_set(uint8 port, uint8 pin){
    if (port == 0){
        P0SEL &= ~(1 << (pin));
        P0DIR |= (1 << (pin));
        P0 |= (1 << (pin));
        return TRUE;
    }else if (port == 1){
        P1SEL &= ~(1 << (pin));
        P1DIR |= (1 << (pin));
        P1 |= (1 << (pin));
        return TRUE;
    }else if (port == 2){
        if (pin >= 3){
            return FALSE;
        }
        P2SEL &= ~(1 << (pin));
        P2DIR |= (1 << (pin));
        P2 |= (1 << (pin));
        return TRUE;
    }else{
        return FALSE;
    }
}


/*------------------------------------------------------------------------------
* 函数名称：io_set
* 功    能：将指定IO口变为低电平
* 入口参数：port
                0
                1
                2
            pin
                0
                1
                2
                3
                4
                5
                6
                7
* 出口参数：无
* 返 回 值：无
*-----------------------------------------------------------------------------*/
char io_low(uint8 port, uint8 pin){
    if (port == 0){
        if (pin >= 8){
            return FALSE;
        }
        P0SEL &= ~(1 << (pin));
        P0DIR |= (1 << (pin));
        P0 &= ~(1 << (pin));
        return TRUE;
    }else if(port == 1){
        if (pin >= 8){
            return FALSE;
        }
        P1SEL &= ~(1 << (pin));
        P1DIR |= (1 << (pin));
        P1 &= ~(1 << (pin));
        return TRUE;
    }else if (port == 2){
        if (pin >= 3){
            return FALSE;
        }
        P2SEL &= ~(1 << (pin));
        P2DIR |= (1 << (pin));
        P2 &= ~(1 << (pin));
        return TRUE;
    }else{
        return FALSE;
    }
}
/*------------------------------------------------------------------------------
* 函数名称：io_get
* 功    能：读取指定io电平
* 入口参数：port
                0
                1
                2
            pin
                0
                1
                2
                3
                4
                5
                6
                7
* 出口参数：无
* 返 回 值：无
*-----------------------------------------------------------------------------*/
char io_get(uint8 port, uint8 pin){
    if (port == 0){
        if (pin >= 8){
            return FALSE;
        }
        P0SEL &= ~(1 << (pin));
        P0DIR &= ~(1 << (pin));
        
        return hal_io_get(port, pin); 
            
    }else if(port == 1){
        if (pin >= 8){
            return FALSE;
        }
        P1SEL &= ~(1 << (pin));
        P1DIR &= ~(1 << (pin));
        
        return hal_io_get(port, pin); 
        
    }else if (port == 2){
        if (pin >= 3){
            return FALSE;
        }
        P2SEL &= ~(1 << (pin));
        P2DIR &= ~(1 << (pin));
        
        return hal_io_get(port, pin); 
        
    }else{
        return FALSE;
    }
}

