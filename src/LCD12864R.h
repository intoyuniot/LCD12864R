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

 HT1632
 ******************************************************************************
 */
#ifndef LCD12864R_H
#define LCD12864R_H

#include "Arduino.h"


class LCD12864R
{
    typedef unsigned char uchar;

    public:
    LCD12864R(int RS_pin, int RW_pin, int EN_pin, int D0_pin, int D1_pin, int D2_pin, int D3_pin, int D4_pin, int D5_pin, int D6_pin, int D7_pin);

    void Initialise(void);
    void Clear(void);
    void DisplayString(int X,int Y,uchar *ptr,int dat);
    void DisplaySig(int M,int N,int sig);
    void DrawFullScreen(uchar *p);

    private:
    int ScreenBuffer[16][32];
    int temp[8];

    int delaytime;
    int DEFAULTTIME;

    int RS;
    int RW;
    int EN;
    int D0_p;
    int D1_p;
    int D2_p;
    int D3_p;
    int D4_p;
    int D5_p;
    int D6_p;
    int D7_p;

    void setPins(uint8_t tRS, uint8_t tRW, uint8_t tD7, uint8_t tD6, uint8_t tD5, uint8_t tD4, uint8_t tD3, uint8_t tD2, uint8_t tD1, uint8_t tD0);
    void delayns(void);
    void VectorConverter(int vector);
    void WriteCommand(int CMD);
    void WriteData(int CMD);
};


#endif
