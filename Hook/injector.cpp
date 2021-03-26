#include <Windows.h>
#include <string>
#include <tchar.h>
#include <iostream>
typedef void(__cdecl* PopCalc_t)(void);
BOOL IsProcessRunning(DWORD pid)
{
	HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
	DWORD ret = WaitForSingleObject(process, 0);
	CloseHandle(process);
	return ret == WAIT_TIMEOUT;
}
int _tmain(int argc, char* argv[])
{
	DWORD processid;
	HINSTANCE hPopCalc;
	PopCalc_t PopCalc;
	std::wcout << "Enter process id : \t";
	std::cin >> processid;
	if (!IsProcessRunning(processid))
	{
		std::wcout << "False";
	}
	hPopCalc = LoadLibrary(TEXT("Hook_Calc.dll"));
	if (hPopCalc == NULL)
	{
		return EXIT_FAILURE;
	}
	std::wcout << "[+] SUCCESS: Loaded PopCalc.dll" << std::endl;
	PopCalc = (PopCalc_t)GetProcAddress(hPopCalc, "PopCalc");
	if (PopCalc == NULL)
	{
		return EXIT_FAILURE;
	}
	std::cout << "SUCCESS: Found PopCalc function pointer" << std::endl;
	PopCalc();
	return 0;
}