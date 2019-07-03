#include "client\windows\common\ipc_protocol.h"
#include "client\windows\handler\exception_handler.h"

#pragma comment(lib, "exception_handler.lib")
#pragma comment(lib, "common.lib")
#pragma comment(lib, "crash_generation_client.lib")

google_breakpad::ExceptionHandler* handler;
static size_t kCustomInfoCount = 2;
static google_breakpad::CustomInfoEntry kCustomInfoEntries[] = {
	google_breakpad::CustomInfoEntry(L"prod", L"wincrash"),
	google_breakpad::CustomInfoEntry(L"ver", L"1.0"),
};

std::wstring dump_path = L"C:\\Dumps\\";
const wchar_t kPipeName[] = L"\\\\.\\pipe\\BreakpadCrashServices\\TestServer";

bool ShowDumpResults(const wchar_t* dump_path,
	const wchar_t* minidump_id,
	void* context,
	EXCEPTION_POINTERS* exinfo,
	MDRawAssertionInfo* assertion,
	bool succeeded) {
	if (succeeded) {
		// 如果指定OOP Minidump Generation（管道），dump_path和minidump_id将为NULL
		printf("dump path is %ws\n", dump_path);
		printf("dump guid is %ws\n", minidump_id);
	}
	else {
		printf("dump failed\n");
	}
	system("pause");
	return succeeded;
}

void DerefZeroCrash() {
	int* x = 0;
	*x = 1;
}

void InvalidParamCrash() {
	printf(NULL);
}

void RequestDump() {
	if (!handler->WriteMinidump()) {
		MessageBoxW(NULL, L"Dump request failed", L"Dumper", MB_OK);
	}
	kCustomInfoEntries[1].set_value(L"1.1");
}


int main()
{
	if (_wmkdir(dump_path.c_str()) && (errno != EEXIST)) {
		MessageBoxW(NULL, L"Unable to create dump directory", L"Dumper", MB_OK);
		return 1;
	}
	google_breakpad::CustomClientInfo custom_info = { kCustomInfoEntries, kCustomInfoCount };
	handler = new google_breakpad::ExceptionHandler(
		dump_path,// 如果指定OOP Minidump Generation（管道）将忽略该参数
		NULL, 
		ShowDumpResults,
		NULL, 
		google_breakpad::ExceptionHandler::HANDLER_ALL, 
		MiniDumpNormal,
		kPipeName, 
		&custom_info);

	DerefZeroCrash();
	//InvalidParamCrash();
	//RequestDump();

	system("pause");
	return 0;
}
