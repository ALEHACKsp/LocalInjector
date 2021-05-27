#include "DllMain.hh"

BOOL APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int iShowCmd) {

	CUtilities::Get().CreateConsole();

	CUtilities::Get().ConsolePrint(XorStr("Local Injector by Dylane (Warface DX11) \n"));
	std::this_thread::sleep_for(600ms);

	if (!CUtilities::Get().IsProcessActive(L"GameDX11.exe")) {

		CUtilities::Get().ConsolePrint(XorStr("[Failed] Game isn't running, start game first \n"));
		std::this_thread::sleep_for(600ms);

		CUtilities::Get().ConsolePrint(XorStr("[Waiting] This window closed after 3 seconds \n"));
		std::this_thread::sleep_for(3s);

		return EXIT_FAILURE;
	}

	/* Find window */
	HWND hGameHWND = LI_FN(FindWindow)(XorStr("CryENGINE"), XorStr("Warface"));

	if (hGameHWND) {

		CUtilities::Get().ConsolePrint(XorStr("[Success] GameHWND: %p \n"), hGameHWND);
		std::this_thread::sleep_for(600ms);

	}
	else if (hGameHWND == NULL) {

		CUtilities::Get().ConsolePrint(XorStr("[Failed] Couldn't find target window \n"));
		std::this_thread::sleep_for(600ms);

		CUtilities::Get().ConsolePrint(XorStr("[Waiting] This window closed after 3 seconds \n"));
		std::this_thread::sleep_for(3s);

		return EXIT_FAILURE;
	}

	/* Getting the thread of the window and the PID */
	DWORD dwProcessId = NULL;
	DWORD dwThreadProcessId = LI_FN(GetWindowThreadProcessId)(hGameHWND, &dwProcessId);

	if (dwThreadProcessId) {

		CUtilities::Get().ConsolePrint(XorStr("[Success] ThreadProcessId: %p \n"), dwThreadProcessId);
		std::this_thread::sleep_for(600ms);

	} else if (dwThreadProcessId == NULL) {

		CUtilities::Get().ConsolePrint(XorStr("[Failed] Couldn't get thread id of window \n"));
		std::this_thread::sleep_for(600ms);

		CUtilities::Get().ConsolePrint(XorStr("[Waiting] This window closed after 3 seconds \n"));
		std::this_thread::sleep_for(3s);

		return EXIT_FAILURE;
	}

	/* Loading DLL */
	HMODULE hDllFile = LI_FN(LoadLibraryEx)(XorStr("C:\\Cheat\\YourDll.dll"), NULL, DONT_RESOLVE_DLL_REFERENCES);

	if (hDllFile) {

		CUtilities::Get().ConsolePrint(XorStr("[Success] Dll: %p \n"), dwThreadProcessId);
		std::this_thread::sleep_for(600ms);

	} else if (hDllFile == NULL) {

		CUtilities::Get().ConsolePrint(XorStr("[Failed] The DLL couldn't be found \n"));
		std::this_thread::sleep_for(600ms);

		CUtilities::Get().ConsolePrint(XorStr("[Waiting] This window closed after 3 seconds \n"));
		std::this_thread::sleep_for(3s);

		return EXIT_FAILURE;
	}

	/* Getting function address */
	HOOKPROC hpFunctionAddress = (HOOKPROC)GetProcAddress;

	if (hpFunctionAddress) {

		CUtilities::Get().ConsolePrint(XorStr("[Success] FunctionAddress: %p \n"), hpFunctionAddress);
		std::this_thread::sleep_for(600ms);

	} else if(hpFunctionAddress == NULL) {

		CUtilities::Get().ConsolePrint(XorStr("[Failed] The function wasn't found \n"));
		std::this_thread::sleep_for(600ms);

		CUtilities::Get().ConsolePrint(XorStr("[Waiting] This window closed after 3 seconds \n"));
		std::this_thread::sleep_for(3s);

		return EXIT_FAILURE;
	}

	/* Setting the hook in the hook chain. Or you can use WH_KEYBOARD(instead WH_GETMESSAGE) if you prefer to trigger the hook manually */
	HHOOK hHandle = LI_FN(SetWindowsHookEx)(WH_GETMESSAGE, hpFunctionAddress, hDllFile, dwThreadProcessId);

	if (hHandle == NULL) {

		CUtilities::Get().ConsolePrint(XorStr("[Failed] Couldn't set the hook \n"));
		std::this_thread::sleep_for(600ms);

		CUtilities::Get().ConsolePrint(XorStr("[Waiting] This window closed after 3 seconds \n"));
		std::this_thread::sleep_for(3s);

		return EXIT_FAILURE;
	}

	/* Triggering the hook */
	LI_FN(PostThreadMessage)(dwThreadProcessId, WM_NULL, NULL, NULL);

	CUtilities::Get().ConsolePrint(XorStr("[Success] Dll was injected, have fun \n"));
	std::this_thread::sleep_for(600ms);

	CUtilities::Get().ConsolePrint(XorStr("[Success] Dont close this window, need for working game \n"));
	LI_FN(system)(XorStr("pause > nul"));

	//CUtilities::Get().DetachConsole();

	return EXIT_SUCCESS;
}