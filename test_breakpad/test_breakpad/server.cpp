#include "tchar.h"
#include <string>
#include "client/windows/crash_generation/crash_generation_server.h"
#include "client\windows\common\ipc_protocol.h"
#include "client\windows\crash_generation\client_info.h"

#pragma comment(lib, "common.lib")
#pragma comment(lib, "crash_generation_server.lib")

// Maximum length of a line in the edit box.
const size_t kMaximumLineLength = 256;
std::wstring dump_path2 = L"C:\\Dumps\\";
// 这个管道名要和上面客户端所指定的管道名相同
const wchar_t kPipeName[] = L"\\\\.\\pipe\\BreakpadCrashServices\\TestServer";

static google_breakpad::CrashGenerationServer* crash_server = NULL;

static void ShowClientConnected(void* context,
	const google_breakpad::ClientInfo* client_info) {
	TCHAR* line = new TCHAR[kMaximumLineLength];
	line[0] = _T('\0');
	int result = swprintf_s(line,
		kMaximumLineLength,
		L"Client connected:\t\t%d\r\n",
		client_info->pid());

	if (result == -1) {
		delete[] line;
		return;
	}
}

static void ShowClientCrashed(void* context,
	const google_breakpad::ClientInfo* client_info,
	const std::wstring* dump_path2) {
	TCHAR* line = new TCHAR[kMaximumLineLength];
	line[0] = _T('\0');
	int result = swprintf_s(line,
		kMaximumLineLength,
		TEXT("Client requested dump:\t%d\r\n"),
		client_info->pid());

	if (result == -1) {
		delete[] line;
		return;
	}

	google_breakpad::CustomClientInfo custom_info = client_info->GetCustomInfo();
	if (custom_info.count <= 0) {
		return;
	}

	std::wstring str_line;
	for (size_t i = 0; i < custom_info.count; ++i) {
		if (i > 0) {
			str_line += L", ";
		}
		str_line += custom_info.entries[i].name;
		str_line += L": ";
		str_line += custom_info.entries[i].value;
	}

	line = new TCHAR[kMaximumLineLength];
	line[0] = _T('\0');
	result = swprintf_s(line,
		kMaximumLineLength,
		L"%s\n",
		str_line.c_str());
	if (result == -1) {
		delete[] line;
		return;
	}
}

static void ShowClientExited(void* context,
	const google_breakpad::ClientInfo* client_info) {
	TCHAR* line = new TCHAR[kMaximumLineLength];
	line[0] = _T('\0');
	int result = swprintf_s(line,
		kMaximumLineLength,
		TEXT("Client exited:\t\t%d\r\n"),
		client_info->pid());

	if (result == -1) {
		delete[] line;
		return;
	}
}

void CrashServerStart() {
	// Do not create another instance of the server.
	if (crash_server) {
		return;
	}

	if (_wmkdir(dump_path2.c_str()) && (errno != EEXIST)) {
		MessageBoxW(NULL, L"Unable to create dump directory", L"Dumper", MB_OK);
		return;
	}

	crash_server = new google_breakpad::CrashGenerationServer(kPipeName,
		NULL,
		ShowClientConnected,
		NULL,
		ShowClientCrashed,
		NULL,
		ShowClientExited,
		NULL,
		NULL,
		NULL,
		true,
		&dump_path2);

	if (!crash_server->Start()) {
		MessageBoxW(NULL, L"Unable to start server", L"Dumper", MB_OK);
		delete crash_server;
		crash_server = NULL;
	}
}

void CrashServerStop() {
	delete crash_server;
	crash_server = NULL;
}

int main()
{
	CrashServerStart();
	system("pause");
	CrashServerStop();
	return 0;
}