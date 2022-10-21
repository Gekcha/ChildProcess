#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#pragma argsused

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	DWORD finish, result, total = 0;
	LPDWORD res = &result;
	char line[255];
	HANDLE hThread[255];
	STARTUPINFO si[255];
	PROCESS_INFORMATION pi[255];

	if (argc < 4) {
		printf("Необходимо ввести минимум 3 аргумента:\n1 - Программа обработки\n2..n - Текстовые файлы\nn + 1 - Количество замен\n");
		exit(-1);
	}

	for (short i = 2; i < argc - 1; i++) {
		char* ln = line;
		strcpy(ln, argv[1]);
		ln = strcat(ln, " ");
		ln = strcat(ln, argv[i]);
		ln = strcat(ln, " ");
		ln = strcat(ln, argv[argc - 1]);
		ZeroMemory(&si[i - 2], sizeof(si[i - 2]));
		si[i - 2].cb = sizeof(si);
		ZeroMemory(&pi[i - 2], sizeof(pi[i - 2]));
		if (!CreateProcess(NULL, line, NULL, NULL, TRUE, NULL, NULL, NULL, &si[i - 2], &pi[i - 2]))
		{
			printf("Ошибка при создании процесса\n");
			printf("\n%Lu", GetLastError());
			exit(-2);
		}
		else {
			printf("\nПроцесс %lu работает с файлом %s\n", pi[i - 2].dwProcessId, argv[i]);
			hThread[i - 2] = pi[i - 2].hProcess;
			Sleep(1000);
		}
	}

	for (short i = 0; i < (argc - 1); i++)
	{
		finish = WaitForSingleObject(pi[i].hProcess, INFINITE);
		if (finish == WAIT_OBJECT_0) {
			GetExitCodeProcess(pi[i].hProcess, res);
			printf("\nПроцесс %lu завершен\n", pi[i].dwProcessId);
			total += result;
		}
		else {
			CloseHandle(pi[i].hProcess);
			CloseHandle(pi[i].hThread);
			TerminateProcess(pi[i].hProcess, 0);
		}
	}
	//printf("\nКоличество успешно обработанных файлов: %d\n", total);
	return 0;
}