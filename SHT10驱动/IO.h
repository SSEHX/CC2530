#include "types.h"
#include <iocc2531.h>

#define st(x)      do { x } while (__LINE__ == -1)
#define BM(n)      (1 << (n))
#define hal_io_get(port, pin)          st((P##port## & BM(pin)))

/*------------------------------------------------------------------------------
                                   ��������
------------------------------------------------------------------------------*/

//��io��ת��Ϊ�ߵ�ƽ
extern char io_set(uint8 port, uint8 pin);

//��io��ת��Ϊ�͵�ƽ
extern char io_low(uint8 port, uint8 pin);

