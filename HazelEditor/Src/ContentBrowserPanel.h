#pragma once
#include "Hazel.h"
#include <filesystem>

namespace Hazel
{
	class ContentBrowserPanel
	{
	public:
		void OnImGuiRender();

	private:
		std::filesystem::path m_SelectedPath;
	};
};