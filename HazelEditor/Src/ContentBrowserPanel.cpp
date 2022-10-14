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
			if (m_SelectedPath.empty())
				p = std::filesystem::current_path();
			else
				p = std::filesystem::current_path() / (m_SelectedPath);// Combine Path


			// 打印所有p路径下的子文件
			for (const std::filesystem::directory_entry& pp : std::filesystem::directory_iterator(p))
			{
				if (ImGui::Button(pp.path().string().c_str()))
				{
					if (std::filesystem::is_directory(pp))
					{
						m_SelectedPath = pp;
						LOG(m_SelectedPath);
					}
				}
			}
		}
		ImGui::End();
	}
}
