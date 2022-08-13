#pragma once
#include <string>
#include <optional>

namespace Hazel
{
	class FileDialogWindowUtils
	{
	public:
		// Popup the dialog window for selecting files
		static std::optional<std::string> OpenFile(const char* filter);
		static std::optional<std::string> SaveFile(const char* filter);
	};
}