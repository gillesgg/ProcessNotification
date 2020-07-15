// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include <windows.h>
#include <atlbase.h>
#include <Shlobj.h>

#include <string>
#include <list>
#include <assert.h> 
#include <iostream>
#include <filesystem>
#include <thread>
#include <memory>
#include <atlconv.h>
#include <tchar.h>
#include <psapi.h>
// Boost
// Boost log

#include <boost/log/trivial.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/expressions/keyword.hpp>

#include <boost/program_options.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace		fs = std::filesystem;
namespace		logging = boost::log;
namespace		src = boost::log::sources;
namespace		attrs = boost::log::attributes;
namespace		sinks = boost::log::sinks;
namespace		expr = boost::log::expressions;
namespace		keywords = boost::log::keywords;
#endif //PCH_H
