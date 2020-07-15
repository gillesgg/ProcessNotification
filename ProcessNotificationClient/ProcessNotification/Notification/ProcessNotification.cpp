#include <pch.h>

#include "ProcessNotification.h"
#include "../../../EventTracing/event_tracing/event_provider_list.h"
#include "../../../EventTracing/event_tracing/event_info.h"
#include "../../../EventTracing/event_tracing/event_trace.h"
#include "../../../EventTracing/event_tracing/event_trace_session.h"
#include "process_list.h"
#include "../../logger/Logger.h"

namespace Notification
{
	event_tracing::event_trace* global_trace = nullptr;
	event_tracing::event_trace_session* global_session = nullptr;

	ProcessNotification::ProcessNotification()
		: tracker_(std::make_unique<process_list>())
	{
		 
	}

	void ProcessNotification::StartETW()	
	{
		LOG_TRACE << __FUNCTION__;
		try
		{
			connections_.emplace_back(tracker_->on_new_process(std::bind(&ProcessNotification::on_new_process, this, std::placeholders::_1)));
			connections_.emplace_back(tracker_->on_stopped_process(std::bind(&ProcessNotification::on_stopped_process, this, std::placeholders::_1, std::placeholders::_2)));
			tracker_->start_tracking();
		}
		catch (const std::exception& e)
		{
			LOG_ERROR << "Unable to initialize ETW trace error=" << e.what();
			throw std::exception("Unable to initialize ETW trace error");			
		}
	}

	std::wstring GetProcessName(std::uint32_t pid)
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			FALSE,
			pid);

		if (hProcess != nullptr)
		{
			TCHAR szModName[MAX_PATH];
			if (::GetModuleFileNameEx(hProcess, 0, szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				return std::wstring(szModName);
			}
		}
		return std::wstring();
	}

	void ProcessNotification::on_stopped_process(const process& stopped_process,std::uint32_t exit_code) const noexcept
	{
		fs::path pathObj(stopped_process.get_path());
		if (boost::iequals(pathObj.filename().wstring(), L"shutdown.exe"))
		{
			LOG_INFO << __FUNCTION__;
			LOG_INFO << "process ID=" << stopped_process.get_pid() << " process path=" << stopped_process.get_path() << " process name=" << pathObj.filename().string() << " parent PID=" << stopped_process.get_parent_pid() << " parent Process Name=" << GetProcessName(stopped_process.get_parent_pid());
		}
	}
	void ProcessNotification::on_new_process(const process& new_process) const noexcept
	{
		fs::path pathObj(new_process.get_path());
		if (boost::iequals(pathObj.filename().wstring(), L"shutdown.exe"))
		{
			LOG_INFO << __FUNCTION__;
			LOG_INFO << "process ID=" << new_process.get_pid() << " process path=" << new_process.get_path() << " process name=" << pathObj.filename().string() << " parent PID=" << new_process.get_parent_pid() << " parent Process Name=" << GetProcessName(new_process.get_parent_pid());
		}
	}
	void ProcessNotification::Stop(){}
}

