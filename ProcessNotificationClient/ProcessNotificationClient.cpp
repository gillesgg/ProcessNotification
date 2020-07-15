// ProcessNotificationClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Logger/Logger.h"
#include "ProcessNotification/Notification/IProcessNotification.h"
#include "ProcessNotification/Notification/ProcessNotification.h"


int main()
{
	std::unique_ptr <Notification::IProcessNotification> process_notification;

	LOG_INFO << "Start ETW listener...";
	process_notification = std::unique_ptr<Notification::IProcessNotification>(std::make_unique<Notification::ProcessNotification>());
	process_notification->StartETW();

	printf("Press a key to exit...");
	getchar();
}