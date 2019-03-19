#include <iostream>
#include <Windows.h>
#include<sstream>  
#include<fstream>
using namespace std;

int main_test_system()
{
	HKEY keyhndl;
	ofstream fout("C:\\OpenKey_output.txt");

	//Test 1:
	//ShellExecute(NULL, "open", "C:\\windows\\system32\\cmd.exe", "/c pnputil -e", NULL, SW_HIDE);
	//system("pnputil -e");
	//Test 2:
	DWORD ntrc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "DRIVERS",
		0,
		KEY_ALL_ACCESS,
		&keyhndl);
	
	if (ntrc != ERROR_SUCCESS)
		fout<< "RegOpenKeyEx Error DRIVERS" << endl;
	return 0;
}