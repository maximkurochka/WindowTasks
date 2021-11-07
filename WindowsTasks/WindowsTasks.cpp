// WindowsTasks.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Chapter 5
//Процесс порождает два дочерних процесса, объединённых в одну задачу.

#include <iostream>
#include "TaskContainer.h"

void CreateTwoChildProcessInOneTask()
{
	TaskContainer task;
	task.AddProcess();
	task.AddProcess();
}

int main()
{
	std::cout << "Association of two processes in one task" << std::endl;
	CreateTwoChildProcessInOneTask();
	return 0;
}
