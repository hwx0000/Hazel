#pragma once
#include <memory>

namespace Hazel
{
	class Scene;
	class SceneHierarchyPanel
	{
	public:
		void SetContext(const std::shared_ptr<Scene>& scene) { m_Scene = scene; }

		void OnImGuiRender();

	private:
		std::shared_ptr<Scene> m_Scene;
	};
}