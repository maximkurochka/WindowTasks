// WindowsTasks.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Chapter 6 & 7
//Реализовать поток, вычисляющий простое число (prime number), следующее за переданным ему аргументом и уведомляет 
//главный поток о результате вычислений.
//Пусть поток, вычисляющий следующее простое число, по завершению работы отображает (пишет в файл/выводит на консоль
// /другой способ) результат и время вычислений.

#include <iostream>
#include <string>
#include <process.h>
#include "WinTimer.h"

unsigned int __stdcall CalculateNextIntNumber(void* args)
{
	WinTimer timer;
	int* ptrNumber = reinterpret_cast<int*>(args);
	(*ptrNumber)++;
	timer.End();

	std::wstring result;
	result = L"The value: " + std::to_wstring(*ptrNumber) + L"\nTime of calculating: " + std::to_wstring(timer.CalculateTotalTime()) + L"\n";
	MessageBox(
		0,
		result.c_str(),
		L"Result of calculating",
		MB_OK | MB_ICONINFORMATION
	);

	return 0;
}

int main()
{
	int counter = 0;
	std::cout << "Counter is " << counter << std::endl;

	HANDLE thread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, &CalculateNextIntNumber, &counter, 0, NULL));

	if (thread == NULL)
	{
		std::cout << "Thread does not constructed" << std::endl;
		return 0;
	}
	std::cout << "Thread is constructed" << std::endl;

	WaitForSingleObject(thread, INFINITE);
	std::cout << "Counter is " << counter << std::endl;

	CloseHandle(thread);

	return 0;
}
