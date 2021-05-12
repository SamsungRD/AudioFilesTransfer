#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include <MMSystem.h>

using namespace System;
using namespace std;

int main()
{
    bool played = PlaySound(TEXT("ALAN-WALKER-Faded-Different-World-feat-Julia.wav"), NULL, SND_SYNC);
    printf(" Sucess or not ");
    system("pause");
    return 0;
}