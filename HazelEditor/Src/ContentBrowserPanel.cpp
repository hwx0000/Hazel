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

			// 绘制项目根目录下的所有内容
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

				const auto& path = pp.path();
				// 不再直接判断Button是否点击了, 而是通过ImGui的MouseDoubleClick状态和是否hover来判断双击的
				// 其实这里的ImGui::Button改成ImGui::Text也可以双击, 无非是没有hover时的高亮button效果了
				ImGui::Button(path.string().c_str());
			
				if (path.extension() == ".scene")
				{
					// 拖拽时传入拖拽的item的path
					if (ImGui::BeginDragDropSource())
					{
						const wchar_t* itemPath = path.c_str();
						int len = wcslen(itemPath) + 1;
						// Convert w_char array to char arr(deep copy)
						char* itemPathArr = new char[len];
						std::wcsrtombs(itemPathArr, &itemPath, len, nullptr);

						ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPathArr, (len) * sizeof(char));
						ImGui::EndDragDropSource();
					}
				}

				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					if (isDir)
					{
						m_LastSelectedPath = m_CurSelectedPath;
						m_CurSelectedPath = pp;
					}
				}
			}
		}
		ImGui::End();
	}
}
