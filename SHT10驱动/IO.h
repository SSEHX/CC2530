#include "types.h"
#include <iocc2531.h>

#define st(x)      do { x } while (__LINE__ == -1)
#define BM(n)      (1 << (n))
#define hal_io_get(port, pin)          st((P##port## & BM(pin)))

/*------------------------------------------------------------------------------
                                   函数声明
------------------------------------------------------------------------------*/

//将io口转变为高电平
extern char io_set(uint8 port, uint8 pin);

//将io口转变为低电平
extern char io_low(uint8 port, uint8 pin);

