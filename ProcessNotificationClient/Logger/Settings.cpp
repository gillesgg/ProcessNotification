#include <pch.h>
#include "Settings.h"
#include "Logger.h"

std::unique_ptr<Settings> Settings::instance_;
std::once_flag Settings::m_onceFlag;

Settings& Settings::GetInstance()
{
	std::call_once(m_onceFlag,
		[] {
			instance_.reset(new Settings);
		});
	return *instance_.get();
}

std::wstring Settings::GetExecutableFolder() noexcept
{
	TCHAR szbuffer[MAX_PATH * sizeof(TCHAR)];

	if (GetModuleFileName(nullptr, szbuffer, MAX_PATH))
	{
		return(fs::path(szbuffer).parent_path().native());
	}
	return std::wstring();
}

HRESULT Settings::CreateFolderSettings(fs::path& root) noexcept
{
	LPWSTR				wszPath = nullptr;
	HRESULT				hr = S_OK;

	if (SUCCEEDED(hr = SHGetKnownFolderPath(FOLDERID_ProgramData, KF_FLAG_CREATE, nullptr, &wszPath)))
	{
		root = fs::path(wszPath).append(file_settings::RootAppFolder);
		if (!is_directory(root))
		{
			if (!create_directory(root))
			{
				return (HRESULT_FROM_WIN32(GetLastError()));
			}
		}		
	}
	else
	{
		return (HRESULT_FROM_WIN32(GetLastError()));
	}
	return (hr);
}

HRESULT Settings::CreateSubFolderSettings(fs::path root, fs::path subfolder, std::wstring& subfoldersetting) noexcept
{
	HRESULT				hr = S_OK;

	const auto path_folder = fs::path(root).append(subfolder.generic_wstring());
	if (!is_directory(path_folder))
	{
		if (!create_directory(path_folder))
		{
			return (HRESULT_FROM_WIN32(GetLastError()));
		}
	}
	subfoldersetting = path_folder.native();
	return (hr);
}



//
//HRESULT Settings::InitFile() noexcept
//{
//	HRESULT				hr = S_OK;
//	std::wstring		str_config_name = L"DSMemTrackSRV";
//	fs::path			str_config_full_name;
//	fs::path			root;
//
//	if (SUCCEEDED(hr = CreateFolderSettings(root)))
//	{
//		if (FAILED(hr = CreateSubFolderSettings(root, file_settings::appFolderDump, path_folder_dump_)))
//		{
//			LOG_FATAL << "unable to create the folder=" << root << std::wstring(file_settings::appFolderDump) << " hr=" << hr;
//			return hr;
//		}
//		if (FAILED(hr = CreateSubFolderSettings(root, file_settings::appFolderXML, path_folder_xml_)))
//		{
//			LOG_FATAL << "unable to create the folder=" << root << std::wstring(file_settings::appFolderXML) << " hr=" << hr;
//			return hr;
//		}
//		if (FAILED(hr = CreateSubFolderSettings(root, file_settings::appFolderData, path_folder_data_)))
//		{
//			LOG_FATAL << "unable to create the folder=" << root << std::wstring(file_settings::appFolderData) << " hr=" << hr;
//			return hr;
//		}
//
//		file_data_ = fs::path(path_folder_data_).append(file_settings::DataFile).native();
//
//		if (FAILED(hr = CreateSubFolderSettings(root, file_settings::appFolderSymbols, path_folder_symbols_)))
//		{
//			LOG_FATAL << "unable to create the folder=" << root << std::wstring(file_settings::appFolderSymbols) << " hr=" << hr;
//			return hr;
//		}
//		filename_setting_ = fs::path(root).append(file_settings::AppConfig).native();
//		if (FAILED(hr = WriteDefault()))
//		{
//			LOG_FATAL << "unable to create the file setting hr=" << hr;
//			return hr;
//		}
//
//		str_symbolsfileredist_ = GetExecutableFolder();
//		if (FAILED(hr = WriteDefault()))
//		{
//			LOG_FATAL << "Unable to find symbols file redist hr=" << hr;
//			return hr;
//		}
//		hr = LoadFile();
//	}
//	return hr;
//}
//HRESULT Settings::LoadFile() noexcept
//{
//
//	USES_CONVERSION;
//	namespace pt = boost::property_tree;
//
//	pt::ptree root;
//
//	if (fs::exists(filename_setting_))
//	{
//		read_json(W2A(filename_setting_.c_str()), root);
//
//		std::string str_adressA = root.get<std::string>("Address", "");
//		std::string str_port = root.get<std::string>("Port", "");
//		std::string str_symbols = root.get<std::string>("Symbols", "");
//		std::string str_symbolsfile = root.get<std::string>("SymbolsFiles", "");
//		std::string strLogLevel = root.get<std::string>("LogLevel", "");
//
//		if (str_adressA.empty() || str_port.empty() || str_symbols.empty())
//		{
//			LOG_FATAL << "invalid file setting";
//			return (HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));
//		}
//
//		str_address_ = A2W(str_adressA.c_str());
//		str_port_ = A2W(str_port.c_str());
//		str_symbols_ = A2W(str_symbols.c_str());
//		str_symbolsfile_ = A2W(str_symbolsfile.c_str());
//		str_loglevel_ = A2W(strLogLevel.c_str());
//	}
//	else
//	{
//		LOG_FATAL << "file setting not found=" << filename_setting_;
//		return (HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));		
//	}
//	return (S_OK);
//}
