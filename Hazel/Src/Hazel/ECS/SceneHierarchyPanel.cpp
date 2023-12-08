#include "hzpch.h"
#include "SceneHierarchyPanel.h"
#include "ECS/GameObject.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/CameraComponent.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace Hazel
{
	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		// Translation、Scale都会有相同的类似DragFloat("##Y"的函数, 而ImGui是根据输入的"##Y"来作为identifier的
		// 为了让不同组件的相同名字的值可以各自通过UI读写, 这里需要在绘制最开始加入ID, 绘制结束后PopId
		ImGui::PushID(label.c_str());

		// 先在最左边绘制vector代表的label
		ImGui::Columns(2);// 大概意思是Label占两列的空间
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		// 这行代码参考自ImGui::DragScalarN函数, 意思是我要在一行绘制3个Item
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		// 基于字体的大小和Padding算出这一行的行高
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		// x值的处理, 三个StyleColor分别对应: 按钮本身颜色、鼠标悬停在按钮上的颜色、点击按钮时的颜色
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		
		ImGuiIO& io = ImGui::GetIO();
		ImFontAtlas& fontAtlas = io.Fonts[0];

		ImGui::PushFont(fontAtlas.Fonts[1]);
		// 按X按钮重置x值
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopStyleColor(3);// 把上面Push的三个StyleColor给拿出来
		ImGui::PopFont();

		// 把x值显示出来, 同时提供拖拽修改功能
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		// y值的处理
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(fontAtlas.Fonts[1]);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		// z值的处理
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(fontAtlas.Fonts[1]);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");// 小数点后2位
		ImGui::PopItemWidth();

		// 与前面的PushStyleVar相对应
		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	// SceneHierarchyPanel分为两个子窗口, Hierarchy窗口和Inspector窗口
	void SceneHierarchyPanel::OnImGuiRender()
	{
		// Draw Hierarchy
		ImGui::Begin("SceneHierarchyPanel");
		{
			std::vector<GameObject>& gos = m_Scene->GetGameObjects();
			for (size_t i = 0; i < gos.size(); i++)
				DrawGameObject(gos[i]);

			//	ImGui::Text(gos[i].ToString().c_str());

			if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
				m_SelectedGOId = INVALID_INSTANCE_ID;// 只要这个值跟出现在Hierarchy里Node的Instance Id不同即可


			// Right-click on blank space
			// 1代表鼠标右键(0代表左键、2代表中键), bool over_item为false, 意味着这个窗口只在空白处点击才会触发 
			// 后续应该允许在item上点击, 无非此时创建的是子GameObject
			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				// 这里的快捷键只是一个说明, 还要手动实现对应的Event Callback
				if (ImGui::MenuItem("Create New GameObject", "Ctrl+Alt+N"))
					m_Scene->CreateGameObjectInScene(m_Scene, "New GameObject");

				ImGui::EndPopup();
			}

			if (m_SelectedGOId != INVALID_INSTANCE_ID)
			{
				if (ImGui::BeginPopupContextWindow("Delete", 1, true))
				{
					if (ImGui::MenuItem("Delete GameObject"))
					{
						m_Scene->DestroyGameObjectById(m_SelectedGOId);
						m_SelectedGOId = INVALID_INSTANCE_ID;
					}

					ImGui::EndPopup();
				}
			}

			ImGui::GetStyle().WindowMinSize.x = 250.0f;

		}
		ImGui::End();

		// Draw Inspector
		ImGui::Begin("Inspector");
		{
			if (m_SelectedGOId != INVALID_INSTANCE_ID)
				DrawComponentsForSelectedGameObject();

			ImGui::GetStyle().WindowMinSize.x = 250.0f;
		}
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawGameObject(const GameObject& go)
	{
		uint64_t id = go.GetInstanceId();
		// 每个node都自带OpenOnArrow的flag, 如果当前go正好是被选择的go, 那么还会多一个selected flag
		ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding
			| ((m_SelectedGOId == id) ? ImGuiTreeNodeFlags_Selected : 0);

		// 这里的TreeNodeEx会让ImGui基于输入的HashCode(GUID), 绘制一个TreeNode, 由于这里需要一个
		// void*指针, 这里直接把GameObject的id转成void*给它即可
		// ex应该是expanded的意思, 用于判断go对应的Node是否处于展开状态, 转成uint64_t是为了干掉Warning
		bool expanded = ImGui::TreeNodeEx((void*)(uint64_t)(id), flag, go.ToString().c_str());

		// 如果鼠标悬浮在item上, 且点击了鼠标左键, 则返回true
		if (ImGui::IsItemClicked())
			m_SelectedGOId = id;

		// 如果此节点是expanded状态, 那么需要继续loop到里面去
		// 由于目前没有链式GameObjects, 所以这里把展开的对象再绘制一个相同的子节点
		if (expanded)
		{
			//ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnArrow;
			//// ID 随便取一个就行, 只要不跟已有的一样就行
			//bool opened = ImGui::TreeNodeEx((void*)9817239, flag, go.ToString().c_str());

			//// TreePop貌似是个结束的操作, 好像每个节点绘制结束时要调用此函数
			//if (opened)
			//	ImGui::TreePop();

			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawComponentsForSelectedGameObject()
	{
		// 1. Draw name for GameObject
		GameObject go;
		bool suc = m_Scene->GetGameObjectById(m_SelectedGOId, go);
		if (!suc) 
			return;

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), go.ToString().c_str());

		//// 老式的写法会让Text在右边显示
		//if (ImGui::InputText("Name", buffer, sizeof(buffer)))
		//	go.SetName(std::string(buffer));

		// 新的写法用" "占了个位, 也不是特别科学
		ImGui::Text("Name");
		ImGui::SameLine();
		ImGui::PushItemWidth(200);
		if (ImGui::InputText(" ", buffer, sizeof(buffer)))
			go.SetName(std::string(buffer));
		ImGui::PopItemWidth();


		//ImGui::SameLine();
		ImGui::SameLine(ImGui::GetWindowWidth() - 110.0f);

		// 2. Draw AddComponent Menu
		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			if (ImGui::MenuItem("Camera"))
			{
				if (!go.HasComponent<CameraComponent>())
					go.AddComponent<CameraComponent>();

				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Sprite Renderer"))
			{
				if (!go.HasComponent<SpriteRenderer>())
					go.AddComponent<SpriteRenderer>();

				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Rigidbody2D"))
			{
				glm::vec3& pos = go.GetPosition();
				glm::vec3& rot = go.GetRotation();
				if (!go.HasComponent<Rigidbody2D>())
					go.AddComponent<Rigidbody2D>(pos.x, pos.y, rot.z);
				
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		

		// 3. Draw Transform Component
		HAZEL_ASSERT(go.HasComponent<Transform>(), "Invalid GameObject Without Transform Component!");
		if (go.HasComponent<Transform>())
		{
			DrawComponent<Transform>("Transform", go, [](Transform& tc)
				{
					DrawVec3Control("Translation", tc.Translation);
					// 面板上展示的是degrees, 但是底层数据存的是radians
					glm::vec3 rotation = glm::degrees(tc.Rotation);
					DrawVec3Control("Rotation", rotation);
					tc.Rotation = glm::radians(rotation);
					DrawVec3Control("Scale", tc.Scale, 1.0f);
				}
			);
		}

		// 4. Draw Camera Component
		if (go.HasComponent<CameraComponent>())
		{
			DrawComponent<CameraComponent>("CameraComponent", go, [](CameraComponent& cam)
				{
					// 绘制俩选项, 这里的选项顺序与ProjectionType的枚举顺序相同
					const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
					// 当前选项从数组中找
					const char* currentProjectionTypeString = projectionTypeStrings[(int)cam.GetProjectionType()];

					bool projectionTypeChanged = false;

					// BeginCombo是ImGui绘制EnumPopup的方法
					if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
					{
						for (int i = 0; i < 2; i++)
						{
							bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
							if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
							{
								if (cam.GetProjectionType() != (CameraComponent::ProjectionType)i)
								{
									currentProjectionTypeString = projectionTypeStrings[i];
									cam.SetProjectionType((CameraComponent::ProjectionType)i);
									projectionTypeChanged = true;
								}
							}

							// 高亮当前已经选择的Item
							if (isSelected)
								ImGui::SetItemDefaultFocus();
						}

						ImGui::EndCombo();
					}

					if (cam.GetProjectionType() == CameraComponent::ProjectionType::Perspective)
					{
						float verticalFov = glm::degrees(cam.GetPerspectiveVerticalFOV());
						if (ImGui::DragFloat("Vertical FOV", &verticalFov))
							cam.SetPerspectiveVerticalFOV(glm::radians(verticalFov));

						float orthoNear = cam.GetPerspectiveNearClip();
						if (ImGui::DragFloat("Near", &orthoNear))
							cam.SetPerspectiveNearClip(orthoNear);

						float orthoFar = cam.GetPerspectiveFarClip();
						if (ImGui::DragFloat("Far", &orthoFar))
							cam.SetPerspectiveFarClip(orthoFar);
					}

					if (cam.GetProjectionType() == CameraComponent::ProjectionType::Orthographic)
					{
						float orthoSize = cam.GetOrthographicSize();
						if (ImGui::DragFloat("Size", &orthoSize))
							cam.SetOrthographicSize(orthoSize);

						float orthoNear = cam.GetOrthographicNearClip();
						if (ImGui::DragFloat("Near", &orthoNear))
							cam.SetOrthographicNearClip(orthoNear);

						float orthoFar = cam.GetOrthographicFarClip();
						if (ImGui::DragFloat("Far", &orthoFar))
							cam.SetOrthographicFarClip(orthoFar);

						ImGui::Checkbox("Fixed Aspect Ratio", &cam.GetFixedAspectRatio());
					}

					ImGui::Checkbox("Main Camera", &cam.GetIsMainCamera());

					if (projectionTypeChanged)
						cam.RecalculateProjectionMat();
				}
			);
		}
	
		// 5. Draw SpriteRendererComponent
		if (go.HasComponent<SpriteRenderer>())
		{
			DrawComponent<SpriteRenderer>("SpriteRenderer", go, [](SpriteRenderer& sr)
			{
				ImGui::ColorEdit4("Color", glm::value_ptr(sr.GetTintColor()));

				// 贴图槽位其实是用Button绘制的, 这里并没有绘制出贴图的略缩图
				ImGui::Button("Texture", ImVec2(100.0f, 0.0f));
				if (ImGui::BeginDragDropTarget())
				{
					// 在Content Panel里做了相关文件拽出的代码, 这里只要做接受的代码即可
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM_IMAGE"))
					{
						const char* path = (const char*)payload->Data;
						std::filesystem::path texturePath = path;
						sr.SetTexture(Texture2D::Create(texturePath.string()));
					}
					ImGui::EndDragDropTarget();
				}

				ImGui::DragFloat("Tiling Factor X", &sr.GetTilingFactor().x, 0.1f, 0.0f, 100.0f);
				ImGui::DragFloat("Tiling Factor Y", &sr.GetTilingFactor().y, 0.1f, 0.0f, 100.0f);
			});
		}

		// 6. Draw Rigidbody2DComponent
		if (go.HasComponent<Rigidbody2D>())
		{
			DrawComponent<Rigidbody2D>("Rigidbody2D", go, [](Rigidbody2D& rb)
				{
					// TODO: 这种绘制Menu的东西应该封装一下

					const int typesCnt = 3;
					const char* typeChoices[typesCnt] = { "Static", "Dynamic", "Kinematic" };
					// 当前选项从数组中找
					const char* curChoice = typeChoices[(int)rb.GetType()];

					//bool bTypeChanged = false;

					if (ImGui::BeginCombo(" ", curChoice))
					{
						for (int i = 0; i < typesCnt; i++)
						{
							bool isSelected = curChoice == typeChoices[i];
							if (ImGui::Selectable(typeChoices[i], isSelected))
							{
								if ((int)rb.GetType() != i)
								{
									curChoice = typeChoices[i];
									rb.SetType((Rigidbody2DType)i);
									//bTypeChanged = true;
								}
							}

							// 高亮当前已经选择的Item
							if (isSelected)
								ImGui::SetItemDefaultFocus();
						}

						ImGui::EndCombo();
					}

					// 临时绘制Vec3代表Vec2
					glm::vec3 ext(rb.GetExtents().x, rb.GetExtents().y, 0);
					DrawVec3Control("BoxExtent", ext);
					rb.GetExtents() = { ext.x, ext.y };

					//	const int shapsCnt = 4;
					//	const char* shapesChoices[typesCnt] = { "Box", "CirCle", "Polygon", "Line" };
					//	// 当前选项从数组中找
					//	const char* curChoice = typeChoices[(int)rb.GetType()];

					//	//bool bTypeChanged = false;

					//	// BeginCombo是ImGui绘制EnumPopup的方法
					//	if (ImGui::BeginCombo("", curChoice))
					//	{
					//		for (int i = 0; i < typesCnt; i++)
					//		{
					//			bool isSelected = curChoice == typeChoices[i];
					//			if (ImGui::Selectable(typeChoices[i], isSelected))
					//			{
					//				if ((int)rb.GetType() != i)
					//				{
					//					curChoice = typeChoices[i];
					//					rb.SetType((Rigidbody2DType)i);
					//					//bTypeChanged = true;
					//				}
					//			}

					//			// 高亮当前已经选择的Item
					//			if (isSelected)
					//				ImGui::SetItemDefaultFocus();
					//		}

					//		ImGui::EndCombo();
					//	
				
				});
		}
	}

	void SceneHierarchyPanel::SetSelectedGameObject(const GameObject& go)
	{
		m_SelectedGOId = go.GetInstanceId();
	}

	void SceneHierarchyPanel::SetSelectedGameObjectId(const uint32_t& goId)
	{
		m_SelectedGOId = goId;
	}

	uint64_t SceneHierarchyPanel::GetSelectedGameObjectId()
	{
		return m_SelectedGOId;
	}
}