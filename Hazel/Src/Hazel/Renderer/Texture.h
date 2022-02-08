#pragma once
#include <memory>
#include <string>

namespace Hazel
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;

		virtual void Bind(uint32_t slot) = 0;
	};


	class Texture2D : public Texture 
	{
	public:
		static std::shared_ptr<Texture2D> Create(const std::string& path);
	};
}