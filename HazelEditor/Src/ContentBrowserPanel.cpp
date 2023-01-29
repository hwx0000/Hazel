#include "ContentBrowserPanel.h"
#include "imgui.h"
#include <typeinfo>

namespace Hazel
{
	void ContentBrowserPanel::Init()
	{
		m_DirTex = Texture2D::Create("Resources/Icons/DirectoryIcon.png");
		m_FileTex = Texture2D::Create("Resources/Icons/FileIcon.png");
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		//ImGui::ShowDemoWindow();

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
				bool isDir = pp.is_directory();

				int frame_padding = -1;										// -1 == uses default padding (style.FramePadding)
				ImVec2 size = ImVec2(HEIGHT, HEIGHT);						// Size of the image we want to make visible

				if (isDir)
					ImGui::Image((ImTextureID)m_DirTex->GetTextureId(), size, { 0, 0 }, { 1, 1 });
				else
					ImGui::Image((ImTextureID)m_FileTex->GetTextureId(), size, { 0, 0 }, { 1, 1 });
				ImGui::SameLine();
				if (ImGui::Button(pp.path().string().c_str()))
				{
					if (isDir)
					{
						m_LastSelectedPath = m_CurSelectedPath;
						m_CurSelectedPath = pp;
					}
					LOG(m_CurSelectedPath);
				}
			}
		}
		ImGui::End();
	}
}
