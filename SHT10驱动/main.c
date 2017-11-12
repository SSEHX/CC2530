#include "timer.h"
#include "IO.h"
#include "base.h"
#include "SHT10.h"

void main(){
    init();
    
    setLed(OFF);
    
    while(1){
        if(measure_t()){
            setLed(ON);
        }
        
        wait_ms(3000);
    }

}