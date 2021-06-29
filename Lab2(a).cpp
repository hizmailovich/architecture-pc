#include "stdio.h"
#include "windows.h"

int main()
{
	short a_array[4][4];
	long cnt = 16;
	int res = 0, res1 = 0;
	int Time1, Time2, Delay1; 
	double Speedup;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			a_array[i][j] = i * 4 + j;
		}
	printf("Before: ");
	printf("\nResult 1 = %d", res);
	printf("\nResult 2 = %d", res1);
	Time1 = GetTickCount();
	for (int i = 0; i < 10000000; i++)
	{
		cnt = 16;
		__asm
		{
			push esi
			mov ecx, [cnt]
			lea esi, [a_array + ecx * 2]
			neg ecx
			pcmpeqd mm2, mm2
			psrlw mm2, 15; mm2 = (1, 1, 1, 1)
			pxor mm0, mm0
			b :
			movq mm1, [esi + ecx * 2]
			pmaddwd mm1, mm2
			paddd mm0, mm1
			add ecx, 4
			jnz b
			movq mm1, mm0
			psrlq mm1, 32
			paddd mm0, mm1
			movd[res], mm0
			emms
			pop esi
		}
	}
	Time2 = GetTickCount();
	printf("\n\nUsing MMX: ");
	printf("\nResult 1 = %d", res);
	Delay1 = Time2 - Time1;
	printf("\nTime = %d ms\n", Delay1);
	Time1 = GetTickCount();
	for (int i = 0; i < 10000000; i++)
	{
		cnt = 16;
		__asm
		{
			push eax
			push ecx
			push esi
			xor esi, esi
			xor ecx, ecx
			loop1 :
			movsx eax, a_array[esi]
			add cx, ax
			add esi, 2
			sub cnt, 1
			jnz loop1
			mov res1, ecx
			pop esi
			pop ecx
			pop eax
		}
	}
	Time2 = GetTickCount();
	printf("\nWithout MMX: ");
	printf("\nResult 2 = %d\n", res1);
	printf("Time = %d ms\n", Time2 - Time1);
	Speedup = float((Time2 - Time1)) / float(Delay1);
	printf("\nMMX SpeedUp = %2.4f times\n\n", Speedup);
	return 0;
}