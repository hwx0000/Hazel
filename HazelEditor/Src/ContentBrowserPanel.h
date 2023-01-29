#pragma once
#include "Hazel.h"
#include <filesystem>

namespace Hazel
{
	class ContentBrowserPanel
	{
	public:
		const float HEIGHT = 24.0f;

		void Init();
		void OnImGuiRender();

	private:
		std::filesystem::path m_CurSelectedPath;
		std::filesystem::path m_LastSelectedPath;

		std::shared_ptr<Texture2D> m_DirTex;
		std::shared_ptr<Texture2D> m_FileTex;
	};
};