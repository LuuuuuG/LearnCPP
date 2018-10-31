#define _CRT_SECURE_NO_WARNINGS 
#include <windows.h>
#include "cstdio"
#include "iostream"

#define ulong_sy unsigned int
#define CURRENT_VERSION         "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"

void get_windows_last_error_msg(char *s)
{
	if (s != NULL) {
		DWORD dwLastError = GetLastError();
		LPVOID lpMsgBuf;
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS
			| FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK,
			NULL,
			dwLastError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0,
			NULL)) {
			sprintf(s, "%s", lpMsgBuf);
		}
		else
			sprintf(s, "Last Error code: %d", dwLastError);
	}

}


DWORD ms_get_registry_key_dword(char *key, char *value_name)
{
	HKEY key_handle;
	DWORD value, value_size = sizeof(DWORD);

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, key, 0, KEY_QUERY_VALUE, &key_handle) != ERROR_SUCCESS) {
		//MS_ERROR_MSG("get_registry_key: RegOpenKeyEx HKEY_LOCAL_MACHINE\\%s failed", key);
		char msg[255] = { 0 };
		get_windows_last_error_msg(msg);
		//MS_ERROR_MSG("get_registry_key: RegOpenKeyEx HKEY_LOCAL_MACHINE\\%s failed, reason: %s", key, msg);
		printf("get_registry_key: RegOpenKeyEx HKEY_LOCAL_MACHINE\\%s failed, reason: %s", key, msg);
		return(NULL);
	}

	if (RegQueryValueEx(key_handle, value_name, NULL, NULL, (LPBYTE)&value, &value_size) != ERROR_SUCCESS) {
		//MS_ERROR_MSG("get_registry_key: RegQueryValueEx HKEY_LOCAL_MACHINE\\%s\\%s failed", key, value_name);
		char msg[255] = { 0 };
		get_windows_last_error_msg(msg);
		//MS_ERROR_MSG("get_registry_key: RegQueryValueEx HKEY_LOCAL_MACHINE\\%s\\%s failed, reason: %s", key, value_name, msg);
		printf("get_registry_key: RegQueryValueEx HKEY_LOCAL_MACHINE\\%s\\%s failed, reason: %s", key, value_name, msg);

		RegCloseKey(key_handle);
		return(NULL);
	}

	RegCloseKey(key_handle);
	return(value);
}

void createFile()
{

}

int main_get_last_error()
{
	//int major_version = ms_get_registry_key_dword(CURRENT_VERSION, "CurrentMajorVersionNumber");
	//int minor_version = ms_get_registry_key_dword(CURRENT_VERSION, "CurrentMinorVersionNumber");
	createFile();
	getchar();
	return 0;
}
