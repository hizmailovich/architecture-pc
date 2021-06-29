#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>


unsigned int lab_notes[] = 
{
	392, 392, 392, 329, 349, 349, 349, 293, 293, 1
};

unsigned int ndelay[] = 
{
	400, 400, 400, 1000, 400, 400, 400, 800, 1000,
};

void MenuChoice(int* number) 
{
	while (1) 
	{
		while (scanf("%d", number) != 1) 
		{
			printf("\nIncorrect input. Try again: ");
			while (getchar() != '\n');
			continue;
		}
		if (*number != 1 && *number != 2 && *number != 3
			&& *number != 4 && *number != 5 && *number != 6) 
		{
			printf("\nIncorrect input. Try again: ");
			continue;
		}
		if (getchar() != '\n')
		{
			printf("\nIncorrect input. Try again: ");
			while (getchar() != '\n');
			continue;
		}
		else 
		{
			break;
		}
	}
	return;
}


void TurnSpeaker(int isActive)
{
	if (isActive)
	{
		outp(0x61, inp(0x61) | 3); 
		return;
	}
	else
	{
		outp(0x61, inp(0x61) & 0xFC);
		return;
	}
}

void SetSoundFreq(unsigned int freq)
{
	long base = 1193180; 
	long kd;
	outp(0x43, 0xB6);
	kd = base / freq;
	outp(0x42, kd % 256);
	kd /= 256;
	outp(0x42, kd);
	return;
}

void PlaySound()
{
	for (int i = 0; lab_notes[i] != 1; i++)
	{
		SetSoundFreq(lab_notes[i]);
		TurnSpeaker(1);
		delay(ndelay[i]);
		TurnSpeaker(0);
	}
}

void CharToBin(unsigned char state, char* str)
{
	int i, j;
	char temp;
	for (i = 7; i >= 0; i--) 
	{
		temp = state % 2;
		state /= 2;
		str[i] = temp + '0';
	}
	str[8] = '\0';
}

void PrintKd()
{
	int iChannel;
	long j;
	long kd_low, kd_high, kd, kd_max;

	for (iChannel = 0; iChannel < 3; iChannel++) 
	{
		kd_max = 0;
		for (j = 0; j < 65535; j++) 
		{
			switch (iChannel) 
			{
			case 0: 
			{
				outp(0x43, 0x0);
				kd_low = inp(0x40);
				kd_high = inp(0x40);
				kd = kd_high * 256 + kd_low;
				break;
			}
			case 1: 
			{
				outp(0x43, 0x40);
				kd_low = inp(0x41);
				kd_high = inp(0x41);
				kd = kd_high * 256 + kd_low;
				break;
			}
			case 2: 
			{
				outp(0x43, 0x80);
				kd_low = inp(0x42);
				kd_high = inp(0x42);
				kd = kd_high * 256 + kd_low;
				break;
			}
			}
			if (kd_max < kd) 
			{
				kd_max = kd;
			}
		}
		switch (iChannel) 
		{
		case 0: 
		{
			printf("Channel 0x40 kd: %ld\n", kd_max);
			break;
		}
		case 1: 
		{
			printf("Channel 0x41 kd: %ld\n", kd_max);
			break;
		}
		case 2: 
		{
			printf("Channel 0x42 kd: %ld\n", kd_max);
			break;
		}
		}
	}
	return;
}

void StateWords()
{
	char* bin_state;
	int iChannel;
	unsigned char state;
	bin_state = (char*)calloc(9, sizeof(char));
	if (bin_state == NULL)
	{
		printf("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	for (iChannel = 0; iChannel < 3; iChannel++)
	{
		switch (iChannel)
		{
		case 0: 
		{
			outp(0x43, 0xE2); 
			state = inp(0x40);
			CharToBin(state, bin_state);
			printf("Channel 0x40 word: %s\n", bin_state);
			break;
		}
		case 1:
		{
			bin_state[0] = '\0';
			outp(0x43, 0xE4); 	
			state = inp(0x41);
			CharToBin(state, bin_state);
			printf("Channel 0x41 word: %s\n", bin_state);
			break;
		}
		case 2:
		{
			bin_state[0] = '\0';
			outp(0x43, 0xE8); 	
			state = inp(0x42);
			CharToBin(state, bin_state);
			printf("Channel 0x42 word: %s\n", bin_state);
			break;
		}
		}
	}
	free(bin_state);
	return;
}

int main() 
{
	int number=0;
	system("cls");
	printf("1. Play sound");
	printf("\n2. Print channels kd");
	printf("\n3. Print state words");
	printf("\n4. Exit");
	printf("\n\nEnter choice: ");
	MenuChoice(&number);
	while (number != 4)
	{
		switch (number)
		{
		case 1:
		{
			PlaySound();
			break;
		}
		case 2: 
		{
			PrintKd();
			break;
		}
		case 3:
		{
			StateWords();
			break;
		}
		}
		number = 0;
		system("pause");
		system("cls");
		printf("1. Play sound");
		printf("\n2. Print channels kd");
		printf("\n3. Print state words");
		printf("\n4. Exit");
		printf("\n\nEnter choice: ");
		MenuChoice(&number);
	}
	return 0;
}