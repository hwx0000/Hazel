#include "ContentBrowserPanel.h"
#include "imgui.h"
#include <typeinfo>

namespace Hazel
{
	void ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("ContentBrowser");
		{
			std::filesystem::path p;
			if (m_CurSelectedPath.empty())
			{
				p = std::filesystem::current_path();
				m_CurSelectedPath = p;
			}
			else
				p = std::filesystem::current_path() / (m_CurSelectedPath);// Combine Path

			if (ImGui::Button("<-"))
			{
				if (!m_LastSelectedPath.empty())
					m_CurSelectedPath = m_LastSelectedPath;
			}

			// 打印所有p路径下的子文件
			for (const std::filesystem::directory_entry& pp : std::filesystem::directory_iterator(p))
			{
				if (ImGui::Button(pp.path().string().c_str()))
				{
					if (std::filesystem::is_directory(pp))
					{
						m_LastSelectedPath = m_CurSelectedPath;
						m_CurSelectedPath = pp;
						//LOG(m_CurSelectedPath);
					}
				}
			}
		}
		ImGui::End();
	}
}
