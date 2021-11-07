// WindowsTasks.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Chapter 2
//Реализовать функции:
//	* std::wstring string2wstring(const std::string& str);
//	* std::string wstring2string(const std::wstring& str);

#include <iostream>
#include <string>
#include <Windows.h>

const std::string HelloWorldStr = "Hellow, world";

std::wstring string2wstring(const std::string& str)
{
	std::wstring wstr;

	int recommendedSize = MultiByteToWideChar(
		CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0);

	if (!recommendedSize)
	{
		return std::wstring();
	}

	wstr.resize(recommendedSize, '\0');
	MultiByteToWideChar(
		CP_UTF8,
		0,
		str.c_str(),
		-1,
		&wstr[0],
		static_cast<int>(wstr.size())
	);

	return wstr;
}

std::string wstring2string(const std::wstring& wstr)
{
	std::string str;

	int recommendedSize = WideCharToMultiByte(
		CP_ACP,
		0,
		wstr.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL
	);

	if (!recommendedSize)
	{
		return std::string();
	}

	str.resize(recommendedSize, '\0');
	WideCharToMultiByte(
		CP_ACP,
		0,
		wstr.c_str(),
		-1,
		&str[0],
		static_cast<int>(str.size()),
		NULL,
		NULL
	);

	return str;
}

int main()
{
	auto wstr = string2wstring(HelloWorldStr);
	auto str = wstring2string(wstr);
	return 0;
}
