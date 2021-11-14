﻿// WindowsTasks.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Chapter 1
//Реализовать функцию, которая вернёт текст ошибки по коду, не используя флаг FORMAT_MESSAGE_ALLOCATE_BUFFER

#include <iostream>
#include <string>
#include <Windows.h>

std::wstring GetDescripriongOfErrorByNumber(DWORD errorNumber)
{
	std::wstring description(1000, '\0');

	bool res = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		errorNumber,
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
		&description[0],
		static_cast<DWORD>(description.size()),
		NULL
	);

	if (!res)
	{
		return std::wstring();
	}

	return description;
}

int main()
{
	std::wcout << L"ERROR_SUCCESS: " << GetDescripriongOfErrorByNumber(ERROR_SUCCESS) << std::endl;									// 0 (0x0)

	std::wcout << L"ERROR_SHARING_BUFFER_EXCEEDED: " << GetDescripriongOfErrorByNumber(ERROR_SHARING_BUFFER_EXCEEDED) << std::endl;	// 36 (0x24)

	std::wcout << L"DNS_ERROR_BAD_KEYMASTER: " << GetDescripriongOfErrorByNumber(DNS_ERROR_BAD_KEYMASTER) << std::endl;				// 9122 (0x23A2)
}
