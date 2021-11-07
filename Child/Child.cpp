// Child.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <Windows.h>
namespace mpi = boost::mpi;

int main()
{
	mpi::environment env;
	mpi::communicator world;

	std::cout << "The child process executes" << std::endl;

	if (!world.rank())
	{
		std::cout << "The parent process does not exist with mpi type communication" << std::endl;
		return 0;
	}

	HANDLE hFileShared;
	world.recv(0, 1, hFileShared);

	std::cout << "The value of handler:" << hFileShared << std::endl;

	return 0;
}
