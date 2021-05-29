#pragma once

#ifndef Utilities_hh
#define Utilities_hh

#include "../Includes.hh"

class CUtilities : public CSingleton<CUtilities> {
public:
	bool IsProcessActive(std::string sProcess = XorStr("Process.exe"));

	void CreateConsole();
	void DetachConsole();
	bool ConsolePrint(const char* LogText, ...);
	std::string RandomString(int iLengthString);

private:
	#define BufferSize 2048

	PROCESSENTRY32 g_ProcessEntry = {};

	HANDLE _Output, _Old_Output = NULL;
	HANDLE _Error, _Old_Error = NULL;
	HANDLE _Input, _Old_Input = NULL;
};

#endif // !Utilities_hh