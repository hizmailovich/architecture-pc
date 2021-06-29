#include "stdio.h"
#include "windows.h"
#define N 40

int main()
{
	int a_array[N][N];
	int Time1, Time2, Delay1;
	int res = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			a_array[i][j] = i * N + j;
		}
	printf("Before: ");
	printf("\nResult = %d", res);
	Time1 = GetTickCount();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			res += a_array[i][j];
		}
	}
	Time2 = GetTickCount();
	Delay1 = Time2 - Time1;
	printf("\nAfter: ");
	printf("\nResult = %d\n", res);
	printf("\nTime = %d\n", Delay1);
	return 0;
}