#include "hzpch.h"
#include "ShaderLibrary.h"

namespace Hazel 
{
	void ShaderLibrary::Load(const std::string& path)
	{
		std::shared_ptr<Shader> sp = Shader::Create(path);

		// get shader last name with out suffix as the shader name
		size_t end = path.find_last_of('.');
		size_t begin = path.find_last_of("\\/") + 1;

		std::string name = path.substr(begin, end - begin);

		m_Map[name] = sp;
		//m_Map.insert(name, sp);
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& shaderName)
	{
		HAZEL_CORE_ASSERT(Contains(shaderName), "Can't find shader:{0}", shaderName);

		return m_Map[shaderName];
	}

	bool ShaderLibrary::Contains(const std::string & shaderName)
	{
		return m_Map.find(shaderName) != m_Map.end();
	}
}