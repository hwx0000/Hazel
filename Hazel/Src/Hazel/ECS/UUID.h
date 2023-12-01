#pragma once

namespace Hazel
{
	class UUID
	{
		friend class GameObject;
	public:
		UUID();
		UUID(uint64_t id);

		operator uint64_t() { return m_ID; }

	private:
		UUID(UUID&&) = default;
		UUID(const UUID&) = default;
		UUID& operator=(UUID&&) = default;
		UUID& operator=(const UUID&) = default;

		void SetId(uint64_t t) { m_ID = t; }

	private:
		uint64_t m_ID;
	};
}