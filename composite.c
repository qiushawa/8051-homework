#include <REGX51.h>
void Delay(unsigned int count){
    unsigned int i, j;
    for(i = 0; i < count; i++)
        for(j = 0; j < 123; j++);
}
void main(void){
	int DelayCount;
	unsigned char a=0, LED=0x00;
	P1 = 0x00;
	while(1){
		P2 = LED;
		a=(P1)&0x0f;
		DelayCount=50+a*60;
		Delay(DelayCount);
		LED=LED<<1;
		if(LED==0x80)
			LED=0x01;
	}
}
