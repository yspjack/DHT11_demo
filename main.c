//STC12C5A60S2
//11.0592MHz
#include <reg51.h>
#include <intrins.h>
#include <LCD1602.h>
#include <stdio.h>
sbit DHT = P1 ^ 1;
void delay(unsigned int k)
{
    unsigned char i, j;
    while(k--)
        for(i = 0; i < 11; ++i)
            for(j = 0; j < 190; ++j);
}
//From stc-isp
void Delay10us()
{
    unsigned char i;

    _nop_();
    _nop_();
    _nop_();
    i = 24;
    while (--i);
}
//位数据“0” 的格式为： 50 微秒的低电平和 26-28 微秒的高电平
//位数据“1”的格式为： 50 微秒的低电平加 70 微秒的高电平
unsigned char getByte()
{
    unsigned char i, timer, ret;
    ret = 0;
    for(i = 0; i < 8; ++i)
    {
        timer = 1;
        while(!DHT && (++timer));//50 微秒的低电平
        Delay10us();
        Delay10us();
        Delay10us();
        //此时若IO口为高电平，则为1
        ret <<= 1;
        ret |= DHT;

        timer = 1;
        while(DHT && (++timer));//等待高电平结束

    }
    return ret;
}
int temp, RH;
//数据格式: 8bit 湿度整数数据 + 8bit 湿度小数数据+8bit 温度整数数据 + 8bit温度小数数据+8bit校验位。
//注：其中温湿度小数部分为 0。
unsigned char temp_H, temp_L, RH_H, RH_L, cksum, tmp;
void communicate()
{
    unsigned char timer;

    temp = 0xff;
    RH = 0xff;
    DHT = 0;//微处理器的 I/O 设置为输出同时输出低电平
    delay(18);//低电平保持时间不能小于 18ms
    DHT = 1;//DHT11 的 DATA 数据线也随之变高
    Delay10us();
    Delay10us();
    Delay10us();
    Delay10us();//DHT11 的 DATA 引脚处于输出状态，输出 80 微秒的低电平作为应答信号
    DHT = 1;
    if(DHT == 0)
    {
        timer = 1;
        while(!DHT && (++timer));
        timer = 1;
        while(DHT && (++timer));
        RH_H = getByte();
        RH_L = getByte();
        temp_H = getByte();
        temp_L = getByte();
        cksum = getByte();
        //“8bit 湿度整数数据 + 8bit湿度小数数据+8bit温度整数数据 + 8bit 温度小数数据”8bit 校验位等于所得结果的末 8 位。
        tmp = temp_H + temp_L + RH_H + RH_L;
        DHT = 1;
        if(tmp == cksum)
        {
            temp = temp_H;
            RH = RH_H;
        }
    }
}
char buf[17];
void main()
{
    init_LCD1602();
    DHT = 1;
    DisplayReset();
    DisplayString("Waiting...");
    delay(1000); //DHT11 上电后要等待1s
    while(1)
    {
        communicate();
        DisplayReset();
        delay(1);
        if(temp == 0xff && RH == 0xff)
        {
            DisplayString("Error");
        }
        else
        {
            sprintf(buf, "Temp: %d%cC ", temp, 0xDF);
            DisplayString(buf);
            DisplayNewline();
            delay(1);
            sprintf(buf, "RH: %d%c", RH, '%');
            DisplayString(buf);
        }
        delay(5000);
    }
}