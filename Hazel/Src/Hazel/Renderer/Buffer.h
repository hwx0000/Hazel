#pragma once
#include "hzpch.h"

namespace Hazel
{
	enum class ShaderDataType
	{
		FLOAT, FLOAT2, FLOAT3, FLOAT4
	};

	// 正常的函数在多个cpp里会出现重定义，但是这里有static就不一样了，每一个函数都是该cpp的namespace范围里适用的
	static uint32_t GetShaderDataTypeSize(const ShaderDataType &type)
	{
		switch (type)
		{
		case ShaderDataType::FLOAT:  return 4;
		case ShaderDataType::FLOAT2: return 4 * 2;
		case ShaderDataType::FLOAT3: return 4 * 3;
		case ShaderDataType::FLOAT4: return 4 * 4;
		}

		HAZEL_ASSERT(false, "Unknown ShaderDataType")
			return -1;
	}

	static uint32_t GetShaderTypeDataCount(const ShaderDataType& type)
	{
		switch (type)
		{
		case ShaderDataType::FLOAT: return 1;
		case ShaderDataType::FLOAT2: return 2;
		case ShaderDataType::FLOAT3: return 3;
		case ShaderDataType::FLOAT4: return 4;
		}
		HAZEL_ASSERT(false, "Unknown Shader Data Type");
		return -1;
	}

	class BufferElement
	{
	public:
		BufferElement(const ShaderDataType& type, const std::string& name, bool isNormalized = false) :
			m_Type(type),
			m_Name(name),
			m_Size(GetShaderDataTypeSize(type)),
			m_Offset(0),
			m_IsNormalized(isNormalized)
		{}

		void SetOffset(uint32_t offset)
		{
			m_Offset = offset;
		}

		uint32_t GetSize() const { return m_Size; }
		uint32_t GetOffset() const { return m_Offset; }
		ShaderDataType GetType() const { return m_Type; }
		bool IsNormalized() const { return m_IsNormalized; }
	private:
		std::string m_Name;
		ShaderDataType m_Type;
		uint32_t m_Size;
		uint32_t m_Offset;
		bool m_IsNormalized;
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& list) :
			m_Elements(list)
		{
			CalculateElementsOffsets();
		}

		uint32_t GetStride() const { return m_Stride; }
		size_t GetCount() const { return m_Elements.size(); }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;

	private:
		void CalculateElementsOffsets();
	};

	/*static*/ uint32_t GetShaderTypeDataCount(const ShaderDataType& type);

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};
		virtual void Bind() const = 0;// 别忘了加const
		virtual void Unbind() const = 0;
		virtual BufferLayout& GetBufferLayout() = 0;
		virtual void SetBufferLayout(const BufferLayout&) = 0;

		// 注意这个static函数是在基类声明的, 但是会根据Platform在派生类里被定义
		static VertexBuffer* Create(float* vertices, uint32_t size);
	protected:
		uint32_t m_VertexBuffer;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};
		virtual void Bind() const = 0;// 别忘了加const
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;
		static IndexBuffer* Create(int* indices, uint32_t size);
	protected:
		uint32_t m_IndexBuffer;
	};
}