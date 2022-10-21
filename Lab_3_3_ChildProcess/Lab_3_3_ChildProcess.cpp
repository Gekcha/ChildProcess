#include <stdio.h>
#include <windows.h> 
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma argsused

HINSTANCE hLibrary;
int(*contentLibrary)(int argc, LPTSTR argv[]);

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	hLibrary = LoadLibrary("Lab_3_3DLL.dll");
	if (hLibrary == NULL) {
		printf("библиотека Lab_3_3DLL не найдена");
		exit(-1);
	}
	contentLibrary = (int(*)(int argc, LPTSTR argv[]))GetProcAddress(hLibrary, "Lab_3_3DLL");
	if (contentLibrary == NULL) {
		printf("Функции в библиотеке Lab_3_3DLL не найдены\n");
		exit(-2);
	}
	short a = (*contentLibrary)(argc, argv);
	FreeLibrary(hLibrary);
	return a;
	return 0;

}
