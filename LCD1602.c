#include <reg52.h>
#include "LCD1602.h"
#include <intrins.h>

//16x2
static unsigned char cur_x = 0, cur_y = 0;


void WaitForEnable(void)
{
    DataPort = 0xff;
    LCM_RS = 0;
    LCM_RW = 1;
    _nop_();
    LCM_EN = 1;
    _nop_();
    _nop_();
    while(DataPort & 0x80);
    LCM_EN = 0;
}
/*******************************/
void WriteCommandLCM(uchar CMD, uchar Attribc)
{
    if(Attribc)
        WaitForEnable();
    LCM_RS = 0;
    LCM_RW = 0;
    _nop_();
    DataPort = CMD;
    _nop_();
    LCM_EN = 1;
    _nop_();
    _nop_();
    LCM_EN = 0;
}
/*******************************/
void WriteDataLCM(uchar dataW)
{
    WaitForEnable();
    LCM_RS = 1;
    LCM_RW = 0;
    _nop_();
    DataPort = dataW;
    _nop_();
    LCM_EN = 1;
    _nop_();
    _nop_();
    LCM_EN = 0;
}
/***********************************/
void init_LCD1602()
{
    WriteCommandLCM(0x38, 1);
    WriteCommandLCM(0x08, 1); // Display off
    WriteCommandLCM(0x01, 1); // Display clear
    WriteCommandLCM(0x0c, 1); // Display on
}
/***********************************/
void DisplayOneChar(uchar X, uchar Y, uchar DData)
{
    Y &= 1;
    X &= 15;
    if(Y)X |= 0x40;
    X |= 0x80;
    WriteCommandLCM(X, 0);
    WriteDataLCM(DData);
}

void DisplayReset()
{
    WriteCommandLCM(0x01, 1); // Display clear
    cur_x = cur_y = 0;
}
void DisplayNewline()
{
    cur_x = 0;
    cur_y++;
}

//void DisplayChar(char ch)
//{
//    DisplayOneChar(cur_x, cur_y, ch);
//    cur_x++;
//}

void DisplayString(const char *s)
{
    while(*s)
    {
        DisplayOneChar(cur_x, cur_y, *s);
        s++;
        cur_x++;
    }
}

