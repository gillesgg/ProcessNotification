#pragma once

namespace Notification
{
	class IProcessNotification
	{
	public:
		virtual ~IProcessNotification() = default;
		//virtual IProcessNotification();
		virtual void StartETW() = 0;
		virtual void Stop() = 0;
	};
}

