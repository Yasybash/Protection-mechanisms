#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <winreg.h>
#include <Tlhelp32.h> 
#include <libloaderapi.h>
#pragma comment(lib, "IPHLPAPI.lib") 
#pragma comment(lib, "ntdll.lib") 


#define N 1000
#define key 9

int WriteMe(void* addr, int wb)
{
	HANDLE h = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE, true, GetCurrentProcessId());
	return WriteProcessMemory(h, addr, &wb, 1, NULL);
}


int notVM()
{
	HKEY rKey;
	char RegKey[10000];
	char chk[] = "VMware";
	DWORD bufsz = 10000;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services\\disk\\Enum", 0, KEY_QUERY_VALUE, &rKey);
	RegQueryValueEx(rKey, L"0", NULL, NULL, (LPBYTE)&RegKey, &bufsz);
	char* istr;
	istr = strstr(RegKey, chk);
	RegCloseKey(rKey);
	if (istr == NULL)
		return 0;

	return 1;
}

int notVM2()
{
	HKEY rKey;
	char RegKey[10000];
	char chk[] = "VMware";
	DWORD bufsz = 10000;
	RegOpenKeyEx(HKEY_CLASSES_ROOT, L"Applications\\VMwareHostOpen.exe", 0, KEY_QUERY_VALUE, &rKey);
	if (rKey != NULL)
		return 1;

	return 0;

}


bool IsDebugOllyDBG()
{
	if (FindWindow(TEXT("OLLYDBG"), NULL) || FindWindow(TEXT("OllyDbg"), NULL) || FindWindow(TEXT("OllyDBG"), NULL))
		return false;
	else return true;
}

bool IsDebugFlag()
{
	unsigned long NtGlobalFlags = 0;
	__asm {
		mov eax, fs: [30h]
		mov eax, [eax + 68h]
		mov NtGlobalFlags, eax
	}

	if (NtGlobalFlags & 0x70)
		return false;

	return true;
}

bool IsDebugWinApi()
{
	if (IsDebuggerPresent() == 0)
		return false;
	return true;
}

bool IsDebugWinApiRemote()
{
	BOOL result;
	if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &result))
	{
		if (result == 1)
			return true;
		else
			return false;
	}
	else return false;
}

int proverka(char* pass, char* TRUEpass);
void mes1();

unsigned char CRC_8(unsigned char* data, int len)
{
	unsigned char crc = 0x00;
	char sum;
	char extr;
	for (int i = 0; i < len; i++)
	{
		extr = *data;
		for (char temp = 8; temp; temp--)
		{
			sum = (crc ^ extr) & 0x01;
			crc >>= 1;
			if (sum)
				crc ^= 0x80;
			extr >>= 1;
		}
		data++;
	}
	return crc;
}

int musthave(char* password)
{
	int i = 1;
	int buf = 15;
	if (password[i] == password[++i])
	{
		while (buf != 0)
		{
			int u = 2 * 2;
			u += i;
			buf--;
		}
	}
	return buf;
}

int crc__8()
{
	int len = 10;
	char sum;
	unsigned char crc8 = 0x01;
	for (int i = 0; i < len; i++)
	{
		for (char temp = 8; temp; temp--)
		{
			sum = crc8 & 0x01;
			crc8 >>= 1;
			if (sum)
				crc8 ^= 0x80;
		}
	}
	return crc8;
}

int tooMUCHimportant(char* pass, char* TRUEpass)
{
	if (IsDebugWinApi() == false || IsDebugWinApiRemote() == false || IsDebugFlag() == false || IsDebugOllyDBG() == false)
	{
		mes1();
		return 0;
	}


	if (proverka(pass, TRUEpass) == 0)
	{
		int crc = crc__8();
		return crc__8();
	}
	else
	{
		__asm
		{
			jz false_place
			jnz false_place
			__emit(0xB8)
			false_place:
			call mes1
		}
		return 0;
	}
}

void code(char* s)
{
	char cpy1[1000] = { 0 };
	for (int i = 0; s[i] != '\0'; i++)
	{
		cpy1[i] = s[i] ^ key;
	}
	puts(cpy1);

}

int wait2(char* pass, char* TRUEpass)
{
	if (IsDebugWinApi() == false || IsDebugWinApiRemote() == false || IsDebugFlag() == false || IsDebugOllyDBG() == false)
	{
		mes1();
		return 0;
	}
	int buf = sizeof(pass) ^ (*TRUEpass >> (2 % sizeof(__int64)));
	(buf == INT_MAX) ? (true) : (buf = INT_MAX);
	if (buf & INT_MAX)
		goto important_code;
check_password:
	if (buf != 0)
		return 1;
	else return 0;
important_code:
	buf = strcmp(TRUEpass, pass);
	goto check_password;
}

int wait(char* pass, char* TRUEpass)
{
	if (IsDebugWinApi() == false || IsDebugWinApiRemote() == false || IsDebugFlag() == false || IsDebugOllyDBG() == false)
	{
		mes1();
		return 0;
	}
	char str[] = "ERROR";

	__asm
	{
		push str
		call printf
		call exit
	};

	if (wait2(pass, TRUEpass) == 1)
		return 1;
	else return 0;
}

int proverka(char* pass, char* TRUEpass)
{
	if (IsDebugWinApi() == false || IsDebugWinApiRemote() == false || IsDebugFlag() == false || IsDebugOllyDBG() == false)
	{
		mes1();
		return 0;
	}
	int buf = strcmp(TRUEpass, pass);

	if (buf != 0)
	{
		return 1;
	}
	else return 0;
}

void mes4()
{
	char mes2[] = "D|e}`ye`jh}`fg)fo)}alzl)g|dkl{z)`z)lx|he)}f3)";
	for (int i = 0; mes2[i] != '\0'; i++)
		printf("%c", mes2[i] ^ key);
}

void mes3()
{
	char mes[] = "Lg}l{)}~f)g|dkl{z3)";
	for (int i = 0; mes[i] != '\0'; i++)
		printf("%c", mes[i] ^ key);
}

void mes2()
{
	char success[] = "Z\\JJLZZ()";
	for (int i = 0; success[i] != '\0'; i++)
		printf("%c", success[i] ^ key);
}

void mes1()
{
	char E[] = "L[[F[(";
	for (int i = 0; E[i] != '\0'; i++)
		printf("%c", E[i] ^ key);
}


void main(void)
{
	__asm
	{
		push 0x74; JMP-- >> JZ
		push offset Here
		call WriteMe
		add esp, 8
		Here:  JMP short here
	}


	__asm
	{

		__emit(0xEB)
		__emit(0xFF)
		__emit(0xC0)
		__emit(0x48)
	}

	try
	{
		notVM();
		notVM2();
	}

	catch (int x)
	{
		return;
	}

	if (notVM())
	{
		printf("WMvare wound");
		return;
	}

	if (notVM2())
	{
		printf("VM detected\n");
		return;
	}

	if (IsDebugWinApi() == false || IsDebugWinApiRemote() == false || IsDebugFlag() == false || IsDebugOllyDBG() == false)
	{
		printf("Debugging!");
		return;
	}
	unsigned char* p = (unsigned char*)&proverka;
	int crc = CRC_8(p, 345);
	std::string s_1;
	//printf("%d", crc);
	if (crc != 231)
	{
		printf("CRC ERROR");
		return;
	}

	char password[N] = { 0 };
	char TRUEpassword[] = "8;:="; //1234
	goto open;
	s_1 = static_cast<std::string>(password);
	for (char c : s_1)
	{
		size_t i = 0;
		if (static_cast<int>(c) < sizeof(int) * static_cast<short>(c))
			password[0] += (++i - c) % crc;
	}
	s_1.clear();
open:
	FILE* pass = fopen("password.txt", "r+");
	for (int i = 0; password[i] != '\0'; i++)
		password[i] = password[i] ^ key;

	musthave(password);

open2:
	FILE* serial = fopen("serial.txt", "w+");
	int i = 0;
	char KEY[50] = "-BLP"; //$KEY

	char c;
	while ((c = fgetc(pass)) != EOF)
	{
		password[i] = c;
		i++;
	}
	for (int i = 0; password[i] != '\0'; i++)
		password[i] = password[i] ^ key;


	tooMUCHimportant(password, TRUEpassword);


	__asm
	{
		xor eax, eax
		jz label
		__emit 0xe9

		label:
		mov ebx, eax
	}

	proverka(password, TRUEpassword);


	if (proverka(TRUEpassword, password) != 0)
	{
		mes1();
		proverka(password, TRUEpassword);
		return;
	}
	else
	{
		mes2();
		char s[12] = { 0 };
		for (int i = 0; i < 9; ++i) s[i] = rand() % 26 + 'a';
		char ch[] = "-";
		proverka(password, TRUEpassword);
		strcat(s, ch);
		strcat(KEY, s);
		for (int i = 0; KEY[i] != '\0'; i++)
			KEY[i] = KEY[i] ^ key;
		fprintf(serial, KEY);
		proverka(password, TRUEpassword);
		int a, b;
		mes3();

		scanf("%d", &a);
		scanf("%d", &b);
		int result = a * b;
		proverka(password, TRUEpassword);
		//mes3();
		printf("%d\n", result);
	}
	int a, b;
	scanf("%d", &a);
	scanf("%d", &b);


	/*//start modif code
	const int ms = 256;

	LPBYTE pCode = (LPBYTE)GetFunctionAddress(&BuggyFunction);
	for (int g = 0; g < ms; g++, pCode++)
	{
		if (*(BYTE*)pCode == 0x45) {
			pCode++;
			if (*(BYTE*)pCode == 0x0C)
				break;
		}

	}
	pCode--;

	BYTE  bSub = 0x03;
	WriteProcessMemoryEx(pCode - 1, &bSub, sizeof(bSub));

	printf("%i\n", BuggyFunction(a, b));*/

}
