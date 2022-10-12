#include "ContentBrowserPanel.h"
#include "imgui.h"
#include <filesystem>
#include <typeinfo>

namespace Hazel
{
	void ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("ContentBrowser");
		{
			// TODO: 暂时只展示HazelEditor文件夹下的直接子文件
			std::filesystem::path p = std::filesystem::current_path();

			// 打印所有p路径下的子文件
			for (const std::filesystem::directory_entry& pp : std::filesystem::directory_iterator(p))
			{
				ImGui::Text(pp.path().string().c_str());
			}
		}
		ImGui::End();
	}
}
