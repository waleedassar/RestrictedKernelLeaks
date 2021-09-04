#include "stdafx.h"

#define ulong unsigned long
#define ulonglong unsigned long long
#define longlong long long
#define ULONG unsigned long
#define ULONGLONG unsigned long long
#define ushort unsigned short
#define USHORT unsigned short

void DumpHex(const void* data, size_t size) {
	char ascii[17];
	size_t i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}





void DumpHex_8(const void* data, size_t size)
{
	ulong Q_per_Line = 4;
	wchar_t Buffer[0x100]={0};



	ulong nQs = size / 8;
	ulong Rem = size % 8;


	ulong c = 0;
	ulong l = 0;
	if(nQs)
	{
		for(unsigned long i = 0; i < nQs; i++,c+= 8)
		{
			ulonglong* p = (ulonglong*)(((unsigned char*)data) + c);
			ulonglong ValX = *p;
			_ui64tow(ValX,&Buffer[0],0x10);
			printf("%016llX",ValX);
			//wprintf(L"%s",Buffer);
			l++;
			if(l < Q_per_Line)
			{
				printf(" ");
			}
			else
			{
				printf("\r\n");
				l = 0;
			}

		}
	}

	if(Rem)
	{
		for(ulong ii=0;ii<Rem;ii++,c++)
		{
			unsigned char* pX = (unsigned char*)(((unsigned char*)data) + c);
			unsigned char ValXX = *pX;
			printf("%02X\r\n",ValXX);
		}
	}
	
	return;
}