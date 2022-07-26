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
		std::shared_ptr<Scene> m_Scene;
		uint32_t m_SelectedGOId;
	};
}