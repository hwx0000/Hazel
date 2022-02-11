#pragma once
#include "Shader.h"
#include <unordered_map>

namespace Hazel
{
	class ShaderLibrary
	{
	public:
		void Load(const std::string& path);
		std::shared_ptr<Shader> Get(const std::string& shaderName);
		bool Contains(const std::string& shaderName);

	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Map;
	};
}