/*******************************************************************/   
/*                                                                 */   
/* BY-V1单片机学习/开发系统演示程序 - 步进电机驱动                        */   
/*                                                                 */    
/* MCU:STC89C52 ,晶体频率：11.0592MHz                                */   
/*                                                                 */   
/* Email:445027559@QQ.COM                                          */   
/* Website:http://www.mcuby.com                                    */    
/* QQ:445027559                                                    */    
/*                                                                 */   
/*【版权】Copyright(C)博弈电子 www.mcuby.com  All Rights Reserved     */   
/*【声明】此程序仅用于学习与参考，引用请注明版权和作者信息！                  */   
/*                                                                 */   
/*******************************************************************/   
#include <reg52.H>   
   
#define uint unsigned int   
#define uchar unsigned char   
   
sbit ledlk=P1^0;   
sbit smglk=P1^1;   
sbit smgbitlk=P1^2;    
sbit key1=P3^0;   
sbit key2=P3^1;   
sbit key3=P3^2;   
sbit key4=P3^3;   
   
sbit led1=P2^0;   
sbit led2=P2^1;   
sbit led3=P2^2;   
sbit led4=P2^3;   
   
    
//char excite[]={0xf7,0xf3,0xfb,0xf9,0xfd,0xfc,0xfe,0xf6};//正转   
char excite[]={0xf6,0xfe,0xfc,0xfd,0xf9,0xfb,0xf3,0xf7};//反转    
void delay(uint ms)   
{   
    uint i,j;   
    for (j=0;j<ms;j++)   
        for (i=0;i<120;i++);   
}   
   
/*   
void delayus(uint us)  
{  
    uint i,j;  
    for (j=0;j<us;j++)  
        for (i=0;i<12;i++);  
}  
  
void showsmg(uchar smg,uchar value)  
{  
    uchar code tablesmg[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};  
    uchar code table[]={ 0x3f , 0x06 ,0x5b , 0x4f , 0x66 , 0x6d , 0x7d , 0x07 , 0x7f  , 0x6f , 0x77 , 0x7c , 0x39 , 0x5e , 0x79 , 0x71 , 0x00};  
  
        smglk=1;  
        P2=tablesmg[smg];  
        smglk=0;  
  
        smgbitlk=1;  
        P2=table[value];  
        smgbitlk=0;  
        delay(3);     
}*/   
   
void main()   
{   
    uchar i;   
    
    smglk=0;   
    smgbitlk=0;   
    P3=0xff;   
    ledlk=1;   
    P2=0xff;//赋初值    
   
    while(1)   
    {   
        for (i=0;i<8;i++)   
        {   
            P2=excite[i];//赋驱动值    
            delayus(10); //改变转速,不过不要超过步进电机的最快值  延时一下   
        }          
        
    }   
}   
