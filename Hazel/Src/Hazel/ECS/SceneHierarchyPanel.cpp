#include "hzpch.h"
#include "SceneHierarchyPanel.h"
#include "imgui.h"
#include "ECS/GameObject.h"
#include "ECS/Components/Transform.h"

namespace Hazel
{
	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("SceneHierarchyPanel");

		std::vector<GameObject>& gos = m_Scene->GetGameObjects();
		for (size_t i = 0; i < gos.size(); i++)
			DrawGameObject(gos[i]);

		//	ImGui::Text(gos[i].ToString().c_str());

		if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
			m_SelectedGOId = INVALID_INSTANCE_ID;// 只要这个值跟出现在Hierarchy里Node的Instance Id不同即可

		ImGui::End();

		ImGui::Begin("Inspector");
		if(m_SelectedGOId != INVALID_INSTANCE_ID)
			DrawComponentsForSelectedGameObject();
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawGameObject(const GameObject& go)
	{
		uint32_t id = go.GetInstanceId();
		// 每个node都自带OpenOnArrow的flag, 如果当前go正好是被选择的go, 那么还会多一个selected flag
		ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnArrow | ((m_SelectedGOId == id) ? ImGuiTreeNodeFlags_Selected : 0);

		// 这里的TreeNodeEx会让ImGui基于输入的HashCode(GUID), 绘制一个TreeNode, 由于这里需要一个
		// void*指针, 这里直接把GameObject的id转成void*给它即可
		// ex应该是expanded的意思, 用于判断go对应的Node是否处于展开状态
		bool expanded = ImGui::TreeNodeEx((void*)(id), flag, go.ToString().c_str());

		// 如果鼠标悬浮在item上, 且点击了鼠标左键, 则返回true
		if (ImGui::IsItemClicked())
			m_SelectedGOId = id;

		// 如果此节点是expanded状态, 那么需要继续loop到里面去
		// 由于目前没有链式GameObjects, 所以这里把展开的对象再绘制一个相同的子节点
		if (expanded)
		{
			ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnArrow;
			// ID 随便取一个就行, 只要不跟已有的一样就行
			bool opened = ImGui::TreeNodeEx((void*)9817239, flag, go.ToString().c_str());

			// TreePop貌似是个结束的操作, 好像每个节点绘制结束时要调用此函数
			if (opened)
				ImGui::TreePop();

			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawComponentsForSelectedGameObject()
	{
		// Draw name for GameObject
		bool suc;
		GameObject& go = m_Scene->GetGameObjectById(m_SelectedGOId, suc);
		if (!suc) return;

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), go.ToString().c_str());

		//// 老式的写法会让Text在右边显示
		//if (ImGui::InputText("Name", buffer, sizeof(buffer)))
		//	go.SetName(std::string(buffer));

		// 新的写法用" "占了个位, 也不是特别科学
		ImGui::Text("Name");
		ImGui::SameLine();
		if (ImGui::InputText(" ", buffer, sizeof(buffer)))
			go.SetName(std::string(buffer));


		// Draw Transform Component
		HAZEL_ASSERT(go.HasComponent<Transform>(), "Invalid GameObject Without Transform Component!");
		if (go.HasComponent<Transform>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				glm::mat4& transform = go.GetComponent<Transform>();
				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);

				ImGui::TreePop();
			}
		}
	}
}