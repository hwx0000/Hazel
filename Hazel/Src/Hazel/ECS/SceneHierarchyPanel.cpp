#include "hzpch.h"
#include "SceneHierarchyPanel.h"
#include "imgui.h"
#include "ECS/GameObject.h"

namespace Hazel
{
	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("SceneHierarchyPanel");

		const std::vector<GameObject>& gos = m_Scene->GetGameObjects();
		for (size_t i = 0; i < gos.size(); i++)
		{
			uint32_t id = gos[i].GetInstanceId();
			// 每个node都自带OpenOnArrow的flag, 如果当前go正好是被选择的go, 那么还会多一个selected flag
			ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnArrow |
				((m_SelectedGOId == id) ? ImGuiTreeNodeFlags_Selected : 0);

			// 这里的TreeNodeEx会让ImGui基于输入的HashCode(GUID), 绘制一个TreeNode, 由于这里需要一个
			// void*指针, 这里直接把GameObject的id转成void*给它即可
			// ex应该是expanded的意思, 用于判断go对应的Node是否处于展开状态
			bool expanded = ImGui::TreeNodeEx((void*)(id), flag, gos[i].ToString().c_str());
			
			// 如果鼠标悬浮在item上, 且点击了鼠标左键, 则返回true
			if (ImGui::IsItemClicked())
				m_SelectedGOId = id;

			// 如果此节点是expanded状态, 那么需要继续loop到里面去
			// 由于目前没有链式GameObjects, 所以这里把展开的对象再绘制一个相同的子节点
			if (expanded)
			{
				ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnArrow;
				// ID 随便取一个就行, 只要不跟已有的一样就行
				bool opened = ImGui::TreeNodeEx((void*)9817239, flag, gos[i].ToString().c_str());
				
				// TreePop貌似是个结束的操作, 好像每个节点绘制结束时要调用此函数
				if (opened)
					ImGui::TreePop();

				ImGui::TreePop();
			}
		}
		//	ImGui::Text(gos[i].ToString().c_str());

		if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
			m_SelectedGOId = 999999;// 只要这个值跟出现在Hierarchy里Node的Instance Id不同即可

		ImGui::End();
	}
}