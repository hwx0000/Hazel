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
			ImGui::Text(gos[i].ToString().c_str());

		ImGui::End();
	}
}