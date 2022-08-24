#pragma once

#include "Hazel/Core/Core.h"

#include "Hazel/Core/Application.h"

#include "Hazel/Core/Log.h"

#include "Hazel/ImGui/ImGuiLayer.h"

#include "Hazel/Core/KeyCode.h"
#include "Hazel/Core/MouseButtonCode.h"
#include "Hazel/Event/Event.h"
#include "Hazel/Core/Input.h"

#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/EditorCamera.h"
#include "Hazel/Renderer/VertexArray.h"

#include "Hazel/Core/Timestep.h"
#include "Hazel/EditorCameraController.h"

#include "Hazel/Renderer/ShaderLibrary.h"
#include "Hazel/Renderer/Texture.h"
#include "Hazel/Renderer/SubTexture2D.h"
#include "Hazel/Renderer/RenderCommandRegister.h"

#ifdef HAZEL_PROFILING
#include "Hazel/Debug/Timer.h"
#include "Hazel/Debug/Instrumentor.h"
#endif

#include "Hazel/ECS/Scene.h"
#include "Hazel/ECS/Components/Component.h"
#include "Hazel/ECS/Components/ScriptComponent.h"
#include "Hazel/ECS/SceneHierarchyPanel.h"