#pragma once
#include "IProcessNotification.h"
#include <memory>
#include <boost/signals2.hpp>
#include "process_list.h"

namespace Notification
{
	class ProcessNotification final : public IProcessNotification
	{
	public:
		ProcessNotification();
		virtual void StartETW();		
		virtual void Stop();
	private:


		std::vector<boost::signals2::connection> connections_;
		std::unique_ptr<process_list> tracker_;
	public:
		void on_new_process(const process& new_process) const noexcept;
		void on_stopped_process(const process& stopped_process, std::uint32_t exit_code) const noexcept;
	};
}
