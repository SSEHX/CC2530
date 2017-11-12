#include "types.h"
#include "IO.h"
#include "base.h"


/*------------------------------------------------------------------------------
* �������ƣ�io_set
* ��    �ܣ���ָ��IO�ڱ�Ϊ�ߵ�ƽ
* ��ڲ�����port
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
* ���ڲ�������
* �� �� ֵ����
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
* �������ƣ�io_set
* ��    �ܣ���ָ��IO�ڱ�Ϊ�͵�ƽ
* ��ڲ�����port
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
* ���ڲ�������
* �� �� ֵ����
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
* �������ƣ�io_get
* ��    �ܣ���ȡָ��io��ƽ
* ��ڲ�����port
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
* ���ڲ�������
* �� �� ֵ����
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

