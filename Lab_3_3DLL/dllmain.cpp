#include "pch.h"
#include <windows.h> 
#include <stdio.h> 
#include <stdlib.h>

#define BUF_SIZE 1
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		MessageBox(NULL, "Библиотека Lab_3_3DLL загружена", "DLL Message", MB_OK);
		break;
	case DLL_THREAD_ATTACH:
		MessageBox(NULL, "Текущий процесс создал новый поток", "DLL Message", MB_OK);
		break;
	case DLL_THREAD_DETACH:
		MessageBox(NULL, "Поток завершил свою работу", "DLL Message", MB_OK);
		break;
	case DLL_PROCESS_DETACH:
		MessageBox(NULL, "Библиотека Lab_3_3DLL выгружена", "DLL Message", MB_OK);
		break;
	}
	return TRUE;
}

extern "C" __declspec(dllexport) int Lab_3_3DLL(int argc, LPTSTR argv[])
{
	HANDLE hIn, hOut;
	DWORD nIn, nOut;
	CHAR Buffer[BUF_SIZE], Bu[BUF_SIZE], B[BUF_SIZE] = { '\n' };
	CHAR outname[255];

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	printf("\nОбработка файла: %s\n", argv[1]);

	if (argc == 3) {
		printf("\nВходные параметры считаны\n");
	}
	else {
		printf("Ошибка. Допустимое количество параметров: %d\n", argc);
		return 0;
	}

	int k = 0, i = 0;
	for (int i = 0; i < BUF_SIZE; i++)
		Buffer[i] = 0;
	while (*(argv[1] + i) != '.' && *(argv[1] + i) != '\0') {
		outname[i] = *(argv[1] + i);
		i++;
	}
	outname[i] = '\0';
	strcat(outname, ".docx");
	hIn = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hIn == INVALID_HANDLE_VALUE) {
		printf("Невозможно открыть входной файл. Ошибка: %x\n", GetLastError());
		return  2;
	}
	hOut = CreateFile(outname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hOut == INVALID_HANDLE_VALUE) {
		printf("Невозможно открыть выходной файл. Ошибка: %x\n", GetLastError());
		return 3;
	}

	int n = 0, j = 0, b = 0;
	while (ReadFile(hIn, Buffer, BUF_SIZE, &nIn, NULL)
		&& nIn > 0) {
		for (int b = 0; b < BUF_SIZE; b++) {
			if (Buffer[b] == argv[2][0]) {
				Buffer[b] = '\0';
				k++;
				n++;
			}
		}
		WriteFile(hOut, Buffer, nIn, &nOut, NULL);
	}

	//int b = FILE_END;
	printf("Количество действий : %d", n);
	CloseHandle(hIn);
	CloseHandle(hOut);
	return 0;

}

