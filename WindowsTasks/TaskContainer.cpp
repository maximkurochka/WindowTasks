#include "TaskContainer.h"

static void CreateSuspendedProcess(
	LPCWSTR appName,				//[in]
	LPWSTR commandLine,				//[in]
	STARTUPINFO& startUpInfo,		//[out]
	PROCESS_INFORMATION& processInfo//[out]
)
{
	CreateProcessW(
		appName,
		commandLine,
		NULL,
		NULL,
		FALSE,
		CREATE_SUSPENDED,
		NULL,
		NULL,
		&startUpInfo,
		&processInfo
	);
}

TaskContainer::TaskContainer()
{
	mTask = CreateJobObject(NULL, NULL);
	CreateBasicRestrictionsForTask();
	CreateBasicUiRestrictionsForTask();
}

TaskContainer::~TaskContainer()
{
	EndWork();
}

void TaskContainer::AddProcess()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	TCHAR commandLine[] = L"cmd.exe";

	ZeroMemory(&si, sizeof(STARTUPINFO));
	CreateSuspendedProcess(NULL, commandLine, si, pi);

	AssignProcessToJobObject(mTask, pi.hProcess);
	mListOfProcesses.emplace_back(pi.hProcess);

	ResumeThread(pi.hThread);
	CloseHandle(pi.hThread);
}

void TaskContainer::CreateBasicRestrictionsForTask()
{
	JOBOBJECT_BASIC_LIMIT_INFORMATION jobli = { 0 };
	jobli.PriorityClass = IDLE_PRIORITY_CLASS;
	jobli.PerJobUserTimeLimit.QuadPart = 10000000;
	jobli.LimitFlags = JOB_OBJECT_LIMIT_PRIORITY_CLASS | JOB_OBJECT_LIMIT_JOB_TIME;
	SetInformationJobObject(mTask, JobObjectBasicLimitInformation, &jobli, sizeof(jobli));
}

void TaskContainer::CreateBasicUiRestrictionsForTask()
{
	JOBOBJECT_BASIC_UI_RESTRICTIONS jobuir;
	jobuir.UIRestrictionsClass = JOB_OBJECT_UILIMIT_NONE;
	jobuir.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_EXITWINDOWS;
	jobuir.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_HANDLES;
	SetInformationJobObject(mTask, JobObjectBasicUIRestrictions, &jobuir, sizeof(jobuir));
}

void TaskContainer::EndWork()
{
	mListOfProcesses.emplace_back(mTask);

	WaitForMultipleObjects(
		static_cast<DWORD>(mListOfProcesses.size()),
		&mListOfProcesses[0],
		FALSE,
		INFINITE);

	mListOfProcesses.pop_back();
	for (auto proces : mListOfProcesses)
	{
		CloseHandle(proces);
	}
	CloseHandle(mTask);
}
