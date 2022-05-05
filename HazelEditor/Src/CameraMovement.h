#pragma once
#include "Hazel.h"

class CameraMovement : public Hazel::ScriptComponent
{
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;

	void SetCameraComponent(const std::shared_ptr <Hazel::CameraComponent>& c) { m_CameraComponent = c; }

private:
	std::shared_ptr <Hazel::CameraComponent> m_CameraComponent;
};