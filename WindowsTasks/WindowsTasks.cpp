// WindowsTasks.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Chapter 3 & 4
//Реализовать передачу дескриптора неименованного объекта ядра другому процессу (DuplicateHandle) с ограниченными 
//правами на чтение или запись.
//Для предыдущей программы реализуйте проверку родительским процессом возвращаемого значения второго процесса. Если 
//процесс не имеет прав на доступ к разделяемому объекту - возвращает код ошибки.

#include <iostream>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <Windows.h>
namespace mpi = boost::mpi;


BOOL ShareHandlerWithLimitationedRights(
	HANDLE processSource,	//[in]
	HANDLE handlerSource,	//[in]
	HANDLE processTarget,	//[in]
	HANDLE* handlerTarget,	//[out]
	BOOL isRead = TRUE		//[in]
)
{
	return DuplicateHandle(
		processSource,
		handlerSource,
		processTarget,
		handlerTarget,
		(isRead ? GENERIC_READ : GENERIC_WRITE),
		FALSE,
		0
	);
}

int main()
{
	TCHAR commandLine[] = L"F:\\vs_proj\\Test\\Debug\\Child.exe";
	PROCESS_INFORMATION pi;
	STARTUPINFO sui;

	std::cout << "The parent process excetutes" << std::endl;

	ZeroMemory(&sui, sizeof(STARTUPINFO));
	if (!CreateProcess(
		NULL,
		commandLine,
		NULL,
		NULL,
		FALSE,
		DEBUG_PROCESS | CREATE_SUSPENDED | CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&sui,
		&pi
	)
		)
	{
		std::cout << "The process is not constructed" << std::endl;
		return 0;
	}

	std::cout << "The child process is created" << std::endl;

	DWORD res;
	GetExitCodeProcess(
		pi.hProcess,
		&res
	);

	HANDLE hFile = CreateFile(
		L"file.txt",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CREATE_NEW | OPEN_EXISTING,
		0,
		NULL
	);
	HANDLE hFileShare;

	//duplicate handler
	ShareHandlerWithLimitationedRights(
		GetCurrentProcess(),
		hFile,
		pi.hProcess,
		&hFileShare
	);

	//using the ipc mechanism for transfering the duplicated handler
	mpi::environment env;
	mpi::communicator world;

	if (world.rank())
	{
		std::cout << "The child process exists or exist some process with mpi type communication" << std::endl;
		return 0;
	}

	//resuming the thread of child process
	ResumeThread(pi.hThread);
	CloseHandle(pi.hThread);

	std::cout << "The value of sharing handler: " << hFileShare << std::endl;
	world.send(1, 0, hFileShare);

	WaitForSingleObject(pi.hProcess, INFINITE);
	GetExitCodeProcess(
		pi.hProcess,
		&res
	);

	CloseHandle(pi.hProcess);
	CloseHandle(hFile);

	return 0;
}
