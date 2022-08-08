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
			if (ImGui::TreeNodeEx((void*)typeid(T).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, name))
			{
				T& tc = go.GetComponent<T>();
				uiFunction(tc);
				ImGui::TreePop();
			}
		}

		std::shared_ptr<Scene> m_Scene;
		uint32_t m_SelectedGOId = INVALID_INSTANCE_ID;
	};
}