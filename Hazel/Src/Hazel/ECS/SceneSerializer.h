#pragma once
#include "yaml-cpp/yaml.h"
#include "glm/glm.hpp"

namespace Hazel
{
	class Scene;
	class GameObject;
	class SceneSerializer
	{
	public:	
		static void Serialize(std::shared_ptr<Scene>, const char*);
		static void Deserialize(const char* path);
		static void SerializeGameObject(YAML::Emitter& out, const GameObject&);
	};
}

namespace YAML
{
	// operator <<
	inline Emitter& operator<<(Emitter& emitter, const glm::vec3& v3)
	{
		emitter.WriteStreamable(v3.x);
		emitter.Write(" ");
		emitter.WriteStreamable(v3.y);
		emitter.Write(" ");
		emitter.WriteStreamable(v3.z);
		return emitter.Write(" ");
	}

	// operator <<
	inline Emitter& operator<<(Emitter& emitter, const glm::vec4& v4)
	{
		emitter.WriteStreamable(v4.x);
		emitter.Write(" ");
		emitter.WriteStreamable(v4.y);
		emitter.Write(" ");
		emitter.WriteStreamable(v4.z);
		emitter.Write(" ");
		emitter.WriteStreamable(v4.w);
		return emitter.Write(" ");
	}
}