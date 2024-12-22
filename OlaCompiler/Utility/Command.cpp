#include <cstdlib>
#if _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <chrono>
#include <thread>
#endif
#include "Command.h"
#include "Core/Log.h"
#include "Compiler/CompilerMacros.h"

namespace ola
{
	namespace
	{
#if _WIN32
		void KillProcessAndChildren(DWORD pid)
		{
			HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hSnapShot == INVALID_HANDLE_VALUE) return;

			PROCESSENTRY32 pe32;
			pe32.dwSize = sizeof(PROCESSENTRY32);

			if (Process32First(hSnapShot, &pe32)) {
				do {
					if (pe32.th32ParentProcessID == pid) {
						HANDLE hChildProc = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);
						if (hChildProc) {
							KillProcessAndChildren(pe32.th32ProcessID); // Recursively kill child processes
							TerminateProcess(hChildProc, 1);
							CloseHandle(hChildProc);
						}
					}
				} while (Process32Next(hSnapShot, &pe32));
			}
			CloseHandle(hSnapShot);

			// Now kill the main process
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION, FALSE, pid);
			if (hProcess) {
				TerminateProcess(hProcess, 1);
				CloseHandle(hProcess);
			}
		}
#endif
	}


	Int ExecuteCommand(Char const* cmd)
	{
		return std::system(cmd);
	}

	Int ExecuteCommand_NonBlocking(Char const* cmd, Float timeout)
	{
#if _WIN32
		STARTUPINFO si{};
		si.cb = sizeof(si);
		PROCESS_INFORMATION pi{};
		std::string full_cmd = "cmd.exe /c " + std::string(cmd);

		if (!CreateProcess(nullptr,
			const_cast<Char*>(full_cmd.c_str()),
			nullptr,
			nullptr,
			false,
			CREATE_NO_WINDOW,
			nullptr,
			nullptr,
			&si,
			&pi)
			)
		{
			OLA_ASSERT_MSG(false, "CreateProcess failed");
		}

		auto start = std::chrono::steady_clock::now();
		while (true)
		{
			DWORD exit_code;
			if (GetExitCodeProcess(pi.hProcess, &exit_code))
			{
				if (exit_code != STILL_ACTIVE)
				{
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
					return exit_code;
				}
			}

			auto now = std::chrono::steady_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
			if (elapsed >= timeout)
			{
				KillProcessAndChildren(pi.dwProcessId);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				OLA_ERROR("Timed out after {} seconds.", timeout);
				return OLA_TIMEOUT_ERROR_CODE;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
#else
		return ExecuteCommand(cmd);
#endif
	}
}

