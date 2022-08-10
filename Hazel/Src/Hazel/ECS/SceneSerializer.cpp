#include "hzpch.h"
#include "SceneSerializer.h"
#include "Scene.h"
#include "Components/Transform.h"

namespace Hazel 
{

	void SceneSerializer::Serialize(std::shared_ptr<Scene> scene, const char* savePath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "GameObjects" << YAML::Value << YAML::BeginSeq;

		auto& gos = scene->GetGameObjects();
		for (size_t i = 0; i < gos.size(); i++)
			SerializeGameObject(out, gos[i]);

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(savePath);
		fout << out.c_str();
	}

	void SceneSerializer::Deserialize(const char* path)
	{
	}

	void SceneSerializer::SerializeGameObject(YAML::Emitter& out, const GameObject& go)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "GameObject" << YAML::Value << go.ToString(); // TODO: Entity ID goes here
		out << YAML::Key << "InstanceID" << YAML::Value << "12837192831273"; // TODO: Entity ID goes here

		if (go.HasComponent<Transform>())
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; // TransformComponent

			auto& tc = go.GetComponent<Transform>();
			out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
			out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

			out << YAML::EndMap; // TransformComponent
		}

		if (go.HasComponent<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; // CameraComponent

			auto& camera = go.GetComponent<CameraComponent>();

			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap; // Camera
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();
			out << YAML::EndMap; // Camera

			//out << YAML::Key << "Primary" << YAML::Value << cameraComponent.Primary;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << camera.GetFixedAspectRatio();

			out << YAML::EndMap; // CameraComponent
		}

		if (go.HasComponent<SpriteRenderer>())
		{
			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap; // SpriteRendererComponent

			auto& spriteRendererComponent = go.GetComponent<SpriteRenderer>();
			out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent.GetColor();

			out << YAML::EndMap; // SpriteRendererComponent
		}

		out << YAML::EndMap; // Entity
	}
}
