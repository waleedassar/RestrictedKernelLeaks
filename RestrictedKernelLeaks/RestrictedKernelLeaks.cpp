// RestrictedKernelLeaks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

#include "Header.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Leak0();
	Leak1();
	Leak2();
	Leak3();
	Leak4();
	Leak5();
	Leak6();
	Leak7();
	Leak8();
	Leak9();
	LeakA();
	LeakB();
	LeakC();
	LeakD();
	
	printf("Done.\r\n");
	return 0;
}

