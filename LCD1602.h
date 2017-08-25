#ifndef __LCD1602_H__
#define __LCD1602_H__

#define uchar unsigned char
#define uint unsigned int

//LCD1602数据端口
#define DataPort P2
#define LCM_RS P0_7 //LCD1602命令端口
#define LCM_RW P0_6 //LCD1602命令端口
#define LCM_EN P0_5 //LCD1602命令端口

extern void init_LCD1602();
extern void DisplayReset();
extern void DisplayNewline();
extern void DisplayOneChar(uchar X, uchar Y, uchar DData);
//extern void DisplayChar(char);
extern void DisplayString(const char*);
#endif
