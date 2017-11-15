/*
 ******************************************************************************

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation, either
 version 3 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, see <http://www.gnu.org/licenses/>.

 This library is the LCD screen

 Adapted for IntoRobot by Robin, Sept 19, 2015
 ******************************************************************************
 */

#include "LCD12864R.h"

LCD12864R::LCD12864R(int RS_pin, int RW_pin, int EN_pin, int D0_pin, int D1_pin, int D2_pin, int D3_pin, int D4_pin, int D5_pin, int D6_pin, int D7_pin)
{
    this->DEFAULTTIME = 300; // 80 ms default time
    this->delaytime = DEFAULTTIME;

    RS=RS_pin;
    RW=RW_pin;
    EN=EN_pin;
    D0_p=D0_pin;
    D1_p=D1_pin;
    D2_p=D2_pin;
    D3_p=D3_pin;
    D4_p=D4_pin;
    D5_p=D5_pin;
    D6_p=D6_pin;
    D7_p=D7_pin;
}

void LCD12864R::setPins(uint8_t tRS, uint8_t tRW, uint8_t tD7, uint8_t tD6, uint8_t tD5, uint8_t tD4, uint8_t tD3, uint8_t tD2, uint8_t tD1, uint8_t tD0)
{
    digitalWrite(EN,1);
    delayns();
    digitalWrite(RS, tRS);
    digitalWrite(RW, tRW);
    digitalWrite(D7_p, tD7);
    digitalWrite(D6_p, tD6);
    digitalWrite(D5_p, tD5);
    digitalWrite(D4_p, tD4);
    digitalWrite(D3_p, tD3);
    digitalWrite(D2_p, tD2);
    digitalWrite(D1_p, tD1);
    digitalWrite(D0_p, tD0);
    delayns();
    digitalWrite(EN, 0);
    delayns();
}


void LCD12864R::delayns(void)
{
    delayMicroseconds(delaytime);
}

void LCD12864R::VectorConverter(int vector)
{
    int result = vector;
    for (int i = 7; i >= 0; i--)
    {
        this->temp[i] = result % 2;
        result = result/2;
    }
}


void LCD12864R::WriteCommand(int CMD)
{
    delayns();
    delayns();
    VectorConverter(CMD); // lets get the binary from the dec
    setPins(0,0,this->temp[0],this->temp[1],this->temp[2],this->temp[3],this->temp[4],this->temp[5],this->temp[6],this->temp[7]); //WriteCommand
}



void LCD12864R::WriteData(int CMD)
{
    delayns();
    delayns();
    VectorConverter(CMD); // lets get the binary from the dec
    setPins(1,0,this->temp[0],this->temp[1],this->temp[2],this->temp[3],this->temp[4],this->temp[5],this->temp[6],this->temp[7]); //WriteData
}


void LCD12864R::Initialise(void)
{
    pinMode(RS, OUTPUT);
    pinMode(RW, OUTPUT);
    pinMode(EN, OUTPUT);
    pinMode(D0_p, OUTPUT);
    pinMode(D1_p, OUTPUT);
    pinMode(D2_p, OUTPUT);
    pinMode(D3_p, OUTPUT);
    pinMode(D4_p, OUTPUT);
    pinMode(D5_p, OUTPUT);
    pinMode(D6_p, OUTPUT);
    pinMode(D7_p, OUTPUT);
    delayns();

    WriteCommand(0x30);        //function set command
    WriteCommand(0x0c);        //display switch command
    WriteCommand(0x01);        //clear screen command
    WriteCommand(0x06);        //enter set point command
}



void LCD12864R::Clear(void)
{
    WriteCommand(0x30);
    WriteCommand(0x01);//clear screen
}

void LCD12864R::DisplayString(int X,int Y,uchar *ptr,int dat)
{
    int i;

    switch(X)
    {
        case 0:  Y|=0x80;break;

        case 1:  Y|=0x90;break;

        case 2:  Y|=0x88;break;

        case 3:  Y|=0x98;break;

        default: break;
    }
    WriteCommand(Y); //the start address

    for(i=0;i<dat;i++)
    {
        WriteData(ptr[i]);
    }
}



void LCD12864R::DisplaySig(int M,int N,int sig)
{
    switch(M)
    {
        case 0:  N|=0x80;break;

        case 1:  N|=0x90;break;

        case 2:  N|=0x88;break;

        case 3:  N|=0x98;break;

        default: break;
    }
    WriteCommand(N);
    WriteData(sig);
}

void LCD12864R::DrawFullScreen(uchar *p)
{
    int ygroup,x,y,i;
    int temp;
    int tmp;

    for(ygroup=0;ygroup<64;ygroup++)
    {
        if(ygroup<32)
        {
            x=0x80;
            y=ygroup+0x80;
        }
        else
        {
            x=0x88;
            y=ygroup-32+0x80;
        }
        WriteCommand(0x34);
        WriteCommand(y);
        WriteCommand(x);
        WriteCommand(0x30);
        tmp=ygroup*16;
        for(i=0;i<16;i++)
        {
            temp=p[tmp++];
            WriteData(temp);
        }
    }
    WriteCommand(0x34);
    WriteCommand(0x36);
}
