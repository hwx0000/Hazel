#pragma once
#include "Component.h"

namespace Hazel
{
	class ScriptComponent : public Component
	{
	public:
		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
	};
}