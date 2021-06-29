#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <iostream>
using namespace std;

HANDLE hSerial;

void ReadCOM()
{
	DWORD size;
	char ch;
	while (true)
	{
		ReadFile(hSerial, &ch, 1, &size, 0);
		if (size > 0)
		{
			cout << ch;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	LPCTSTR sPortName = L"COM1";
	hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		cout << "Error!" << endl;
	}
	DCB params = { 0 };
	params.DCBlength = sizeof(params);
	if (!GetCommState(hSerial, &params))
	{
		cout << "Error!" << endl;
	}
	params.BaudRate = CBR_9600;
	params.ByteSize = 8;
	params.StopBits = ONESTOPBIT;
	params.Parity = NOPARITY;
	if (!SetCommState(hSerial, &params))
	{
		cout << "Error!" << endl;
	}
	char data[] = "Good morning!";
	DWORD size = sizeof(data);
	DWORD bytes;
	LPOVERLAPPED ov;
	BOOL iRet = WriteFile(hSerial, data, size, &bytes, NULL);
	cout << "Bytes in string: " << size << endl << "Bytes sended:  " << bytes << endl;
	while (1)
	{
		ReadCOM();
	}
	return 0;
}

