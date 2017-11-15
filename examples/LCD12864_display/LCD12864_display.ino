/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date     :  03-30-15
************************************************************************
    LCD12864  并口通讯方式

    LCD  IntoRobot Atom
    RS  = A0;
    RW = A1;
    EN  = A2;
    D0  = D0;
    D1  = D1;
    D2  = D2;
    D3  = D3;
    D4  = D4;
    D5  = D5;
    D6  = D6;
    D7  = D7;
    PIN15 PSB = 5V;
*/

#include <LCD12864R.h>
#include "IntoRobot_bmp.h"

#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )

unsigned char show1[]="ST7920 LCD12864 ";
unsigned char show2[]="welcome";
unsigned char show3[]="您好！欢迎！！！";
unsigned char show4[]="by IntoRobot";

LCD12864R LCDA(A0,A1,A2,D0,D1,D2,D3,D4,D5,D6,D7);

void setup()
{
    //初始化
    LCDA.Initialise();
    delay(100);
}

void loop()
{
    LCDA.Clear();
    delay(100);
    LCDA.DrawFullScreen(logo);
    delay(5000);

    LCDA.Clear();
    delay(100);
    LCDA.DisplayString(0,0,show1,AR_SIZE(show1));
    delay(10);
    LCDA.DisplayString(1,0,show2,AR_SIZE(show2));
    delay(10);
    LCDA.DisplayString(2,0,show3,AR_SIZE(show3));
    delay(10);
    LCDA.DisplayString(3,0,show4,AR_SIZE(show4));
    delay(5000);
}
