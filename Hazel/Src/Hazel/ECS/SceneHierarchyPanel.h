#pragma once
#include <memory>

namespace Hazel
{
	class Scene;
	class GameObject;
	class SceneHierarchyPanel
	{
		const uint32_t INVALID_INSTANCE_ID = 999999;

	public:
		void SetContext(const std::shared_ptr<Scene>& scene) { m_Scene = scene; }

		void OnImGuiRender();
		void DrawGameObject(const GameObject&);
		void DrawComponentsForSelectedGameObject();

	private:
		template<class T>
		void DrawComponent(const char* name, GameObject& go, std::function<void(T&)> uiFunction)
		{
			// 1. 绘制通用的右上角的按钮
			// 在每一个Component的绘制函数里添加此函数
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, name);

			// SameLine的意思是继续与上面的内容在同一行
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			// 绘制20x20大小的+号按钮
			if (ImGui::Button("...", ImVec2{ 20, 20 }))
			{
				// 这里的Popup通过OpenPopup、BeginPopup和EndPopup一起生效, 输入的string为id
				ImGui::OpenPopup("ComponentSettings");
			}

			ImGui::PopStyleVar();

			bool openComponentDetails = true;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				// Transform cannot be removed
				if (!std::is_same<T, Transform>::value)
				{
					if (ImGui::MenuItem("Remove component"))
					{
						m_Scene->RemoveComponentForGameObject<T>(go);
						openComponentDetails = false;
					}
				}

				ImGui::EndPopup();
			}

			if (openComponentDetails && open)
			{
				T& tc = go.GetComponent<T>();
				uiFunction(tc);
			}

			if(open)
				ImGui::TreePop();
		}

		std::shared_ptr<Scene> m_Scene;
		uint32_t m_SelectedGOId = INVALID_INSTANCE_ID;
	};
}