#pragma once
#include <vector>
#include <Windows.h>

class TaskContainer
{
public:
	TaskContainer();

	~TaskContainer();

	void AddProcess();

private:
	void CreateBasicRestrictionsForTask();

	void CreateBasicUiRestrictionsForTask();

	void EndWork();

private:
	HANDLE mTask;
	std::vector<HANDLE> mListOfProcesses;
};
