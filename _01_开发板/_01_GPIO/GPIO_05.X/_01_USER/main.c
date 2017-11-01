#include "main.h"



void delay_ms(unsigned int _ms)
{   
    unsigned int i=999999;
    
    while(_ms--)
    while(i--);   
}   

void LED_Switch(unsigned char _list)
{
    switch(_list)
    {
    case 0 : PORTEbits.RE2=0;PORTEbits.RE3=1;PORTEbits.RE4=1;PORTEbits.RE5=1;break; 
    case 1 : PORTEbits.RE2=0;PORTEbits.RE3=0;PORTEbits.RE4=1;PORTEbits.RE5=1;break; 
    case 2 : PORTEbits.RE2=0;PORTEbits.RE3=0;PORTEbits.RE4=0;PORTEbits.RE5=1;break;   
    case 3 : PORTEbits.RE2=0;PORTEbits.RE3=0;PORTEbits.RE4=0;PORTEbits.RE5=0;break;    
    }  
    
}

int main(void)
{
    unsigned char i=0;
    TRISE=0x00;
    while (1)
    {
 
//    TRISE = 0X02<<i;
    i=(i+1)%4;
    
    delay_ms(1);
    LED_Switch(i);
   
    }

    return 0;
}









