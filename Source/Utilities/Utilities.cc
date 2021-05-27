#include "Utilities.hh"

bool CUtilities::IsProcessActive(std::wstring sProcess) {

	HANDLE hSnapshot = LI_FN(CreateToolhelp32Snapshot)(TH32CS_SNAPPROCESS, 0UL);

	LI_FN(memset)(&g_ProcessEntry, NULL, sizeof(g_ProcessEntry));
	g_ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	LI_FN(Process32First)(hSnapshot, &g_ProcessEntry);

	if (!LI_FN(_wcsicmp)((wchar_t*)&g_ProcessEntry.szExeFile, sProcess.c_str())) {

		return true;
	}

	while (LI_FN(Process32Next)(hSnapshot, &g_ProcessEntry)) {

		if (!LI_FN(_wcsicmp)((wchar_t*)&g_ProcessEntry.szExeFile, sProcess.c_str())) {

			return true;
		}
	}

	return false;
}

void CUtilities::CreateConsole() {

	_Old_Output = LI_FN(GetStdHandle)(STD_OUTPUT_HANDLE);
	_Old_Error = LI_FN(GetStdHandle)(STD_ERROR_HANDLE);
	_Old_Input = LI_FN(GetStdHandle)(STD_INPUT_HANDLE);

	LI_FN(AllocConsole)() && LI_FN(AttachConsole)(GetCurrentProcessId());

	_Output = LI_FN(GetStdHandle)(STD_OUTPUT_HANDLE);
	_Error = LI_FN(GetStdHandle)(STD_ERROR_HANDLE);
	_Input = LI_FN(GetStdHandle)(STD_INPUT_HANDLE);

	LI_FN(SetConsoleMode)(_Output, ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
	LI_FN(SetConsoleMode)(_Input, ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);

	LI_FN(SetConsoleTitle)(RandomString(25).c_str());
}

void CUtilities::DetachConsole() {

	if (_Output && _Error && _Input) {

		LI_FN(FreeConsole)();

		if (_Old_Output) {

			LI_FN(SetStdHandle)(STD_OUTPUT_HANDLE, _Old_Output);
		}

		if (_Old_Error) {

			LI_FN(SetStdHandle)(STD_ERROR_HANDLE, _Old_Error);
		}

		if (_Old_Input) {

			LI_FN(SetStdHandle)(STD_INPUT_HANDLE, _Old_Input);
		}
	}
}

bool CUtilities::ConsolePrint(const char* LogText, ...)
{
	if (!_Output) {

		return false;
	}

	char Buffer[BufferSize];
	va_list VaList;

	va_start(VaList, LogText);
	_vsnprintf_s(Buffer, BufferSize, LogText, VaList);
	va_end(VaList);

	return !!LI_FN(WriteConsole)(_Output, Buffer, static_cast<DWORD>(strlen(Buffer)), nullptr, nullptr);
}

std::string CUtilities::RandomString(int iLengthString) {

	const std::string sSymbols("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");
	std::string String(iLengthString, NULL);

	std::default_random_engine Generator{ std::random_device{}() };
	const std::uniform_int_distribution<std::string::size_type>Distribution{ 0ULL, sSymbols.size() - 1ULL };

	for (auto& i : String) {

		i = sSymbols[Distribution(Generator)];
	}

	return String;
}