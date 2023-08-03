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
		static void Serialize(std::shared_ptr<Scene>, const char* path);
		static bool Deserialize(std::shared_ptr<Scene> scene, const char* path);
		static void SerializeGameObject(YAML::Emitter& out, const GameObject&);
		static GameObject& DeserializeGameObject(YAML::Emitter& out);
	};
}

namespace YAML
{
	// 为了让Yaml能写入自定义类, 需要重载oprator <<
	
	// operator <<
	inline Emitter& operator<<(Emitter& emitter, const glm::vec2& v2)
	{
		return emitter << YAML::Flow << std::vector<float>{v2.x, v2.y};
	}


	// operator <<
	inline Emitter& operator<<(Emitter& emitter, const glm::vec3& v3)
	{
		return emitter << YAML::Flow << std::vector<float>{v3.x, v3.y, v3.z};
	}

	// operator <<
	inline Emitter& operator<<(Emitter& emitter, const glm::vec4& v4)
	{
		return emitter << YAML::Flow << std::vector<float>{v4.x, v4.y, v4.z, v4.w};
	}

	
	// 为了让Yaml能解析出glm::vec3这个class, 需要定义convert模板特化
	
	template <>
	struct convert<glm::vec2>
	{
	private:
		static bool isNodeValid(const Node& node)
		{
			return node.IsSequence() && node.size() == 2;
		}

	public:
		static Node encode(const glm::vec2& rhs)
		{
			Node node(NodeType::Sequence);
			node.push_back(rhs.x);
			node.push_back(rhs.y);

			return node;
		}

		static bool decode(const Node& node, glm::vec2& res)
		{
			if (!isNodeValid(node))
				return false;

			res.x = node[0].as<float>();
			res.y = node[1].as<float>();

			return true;
		}
	};


	template <>
	struct convert<glm::vec3> 
	{
	private:
		static bool isNodeValid(const Node& node) 
		{
			return node.IsSequence() && node.size() == 3;
		}

	public:
		static Node encode(const glm::vec3& rhs)
		{
			Node node(NodeType::Sequence);
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);

			return node;
		}

		static bool decode(const Node& node, glm::vec3& res)
		{
			if (!isNodeValid(node))
				return false;

			res.x = node[0].as<float>();
			res.y = node[1].as<float>();
			res.z = node[2].as<float>();

			return true;
		}
	};

	template <>
	struct convert<glm::vec4>
	{
	private:
		static bool isNodeValid(const Node& node)
		{
			return node.IsSequence() && node.size() == 4;
		}

	public:
		static Node encode(const glm::vec4& rhs)
		{
			Node node(NodeType::Sequence);
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);

			return node;
		}

		static bool decode(const Node& node, glm::vec4& res)
		{
			if (!isNodeValid(node))
				return false;

			res.x = node[0].as<float>();
			res.y = node[1].as<float>();
			res.z = node[2].as<float>();
			res.w = node[3].as<float>();

			return true;
		}
	};
}