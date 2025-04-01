#include <REGX51.h>

unsigned short a = 0x0001;
short mode = 0;
bit status = 0;
unsigned short LEDs = 0x0000;

void Delay(unsigned int count){
    unsigned int i, j;
    for(i = 0; i < count; i++)
        for(j = 0; j < 123; j++);
}

void all_off(void){
    LEDs = 0xFFFF;
}

void all_on(void){
    LEDs = 0x0000;
}

void all_flash(void){
    LEDs = ~LEDs;
    Delay(100);
}

void left(void){
    LEDs = a;
    Delay(100);
    a = a << 1;
    if (a == 0) {
        if (mode != 5) 
            a = 0x0001;
        else {
            a = 0x8000;
            status = 1;
        }
    }
}

void right(void){
    LEDs = a;
    Delay(100);
    a = a >> 1;
    if (a == 0) {
        if (mode != 5) 
            a = 0x8000;
        else {
            a = 0x0001;
            status = 0;
        }
    }
}

void LR(void){
    if (status == 0)
        left();
    else
        right();
}

bit Button(int d){
    bit BtnStatus = 0;
    if (P3_0 == 1) {
        Delay(d);
        if (P3_0 == 1)
            BtnStatus = 1;
    }
    return BtnStatus;
}

void main(void){
    while(1){
        if (Button(100) == 1) {
            mode++;
            if (mode > 5) 
                mode = 0;
        }
        switch(mode){
            case 0:
                all_off();
                break;
            case 1:
                all_on();
                break;
            case 2:
                all_flash();
                break;
            case 3:
                left();
                break;
            case 4:
                right();
                break;
            case 5:
                LR();
                break;
        }
        P2 = (LEDs >> 8) & 0xFF;
        P1 = LEDs & 0xFF;
    }
}
