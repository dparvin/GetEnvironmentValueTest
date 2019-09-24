// GetEnvironmentValueTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "GetEnvironmentValueTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: code your application's behavior here.
			wprintf(L"Fatal Error: MFC initialization failed\n");
			nRetCode = 1;
		}
		else
		{
			CString szEnvironmentStrings = GetEnvironmentStringsList();
			CString szValue;
			BOOL found = szValue.GetEnvironmentVariable(L"SESSIONNAME");
			wprintf(L"All Environment Variables:\n %s\n\n", szEnvironmentStrings.GetString());
			wprintf(found ? L"Environment Variable was found\n" : L"Environment Variable not was found\n");
			wprintf(L"Environment Variable 'SESSIONNAME' = '%s'\n", szValue.GetString());

		}
	}
	else
	{
		// TODO: change error code to suit your needs
		wprintf(L"Fatal Error: GetModuleHandle failed\n");
		nRetCode = 1;
	}

	std::cin.get();

	return nRetCode;
}

CString GetEnvironmentStringsList()
{
	CString szReturn;
	LPTSTR lpszVariable;
	LPTCH lpvEnv;

	// Get a pointer to the environment block.

	lpvEnv = GetEnvironmentStrings();

	// If the returned pointer is NULL, exit.
	if (lpvEnv == NULL)
	{
		printf("GetEnvironmentStrings failed (%d)\n", GetLastError());
		return 0;
	}

	// Variable strings are separated by NULL byte, and the block is
	// terminated by a NULL byte.

	lpszVariable = (LPTSTR)lpvEnv;

	while (*lpszVariable)
	{
		CString szValue = lpszVariable;
		szReturn += szValue + L"\n";
		lpszVariable += lstrlen(lpszVariable) + 1;
	}
	FreeEnvironmentStrings(lpvEnv);

	return szReturn;
}