#pragma once

#include <string>

struct file_settings
{
	inline static constexpr std::wstring_view RootAppFolder = L"ProcessNotificationClient";
};



class Settings
{
public:
	virtual ~Settings() = default;
	static Settings& GetInstance();

public:
	__declspec(property(get = get_LogLevel, put = set_LogLevel)) std::wstring	LogLevel;
	

public:
	std::wstring get_LogLevel() { return str_loglevel_; }
	void set_LogLevel(std::wstring str_loglevel) { str_loglevel_ = str_loglevel; }


private:
	static std::unique_ptr<Settings> instance_;
	static std::once_flag m_onceFlag;
	std::wstring str_loglevel_;
private:
	Settings() = default;
	Settings(const Settings& src) = delete;
	Settings& operator=(const Settings& rhs) = delete;
	HRESULT CreateFolderSettings(fs::path& root) noexcept;
	HRESULT CreateSubFolderSettings(fs::path root, fs::path subfolder, std::wstring& subfoldersetting) noexcept;
	std::wstring GetExecutableFolder() noexcept;
};