#pragma once
#include <memory>

namespace Hazel
{
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() {}
		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;

		static std::shared_ptr<UniformBuffer> Create(uint32_t size, uint32_t binding);

	private:
	};
}