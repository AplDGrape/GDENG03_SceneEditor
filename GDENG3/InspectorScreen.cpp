#include "InspectorScreen.h"

InspectorScreen::InspectorScreen():AUIScreen("Inspector Screen")
{
	this->textureDialogue = new ImGui::FileBrowser();
	this->textureDialogue->SetTitle("Select Texture");
	this->textureDialogue->SetTypeFilters({ ".jpg", ".png" });
}

void InspectorScreen::drawUI()
{
	ImGui::Begin("Inspector Window");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 275, 25));
	ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT));
	this->generateEditor();
	ImGui::End();
}

void InspectorScreen::generateEditor()
{
	if (GameObjectManager::getInstance()->getSelectedObject() != NULL)
	{
		bool enabled = GameObjectManager::getInstance()->getSelectedObject()->getStatus();

		// Object State
		if (ImGui::Checkbox("Enabled", &enabled))
		{
			if (enabled)
				GameObjectManager::getInstance()->getSelectedObject()->enable();
			else
				GameObjectManager::getInstance()->getSelectedObject()->disable();
		}
		// Component System
		if(ImGui::Button("Remove Texture"))
		{
			if(GameObjectManager::getInstance()->getSelectedObject()->getObjectTexture() != NULL)
			{
				GameObjectManager::getInstance()->getSelectedObject()->setObjectTexture(NULL);
			}
		}

		if (enabled)
		{
			if (ImGui::Button("Select Texture"))
			{
				this->textureDialogue->Open();
			}

			ImGui::Text("Selected Object: %s", GameObjectManager::getInstance()->getSelectedObject()->getName().c_str());
			this->onTransformUpdate();

			if (ImGui::DragFloat3("Position", this->SelectedObjectposition, 0.01f))
			{
				this->TransformSelected(GameObjectManager::getInstance()->getSelectedObject());
			}
			if (ImGui::DragFloat3("Rotation", this->SelectedObjectRotation, 3))
			{
				this->TransformSelected(GameObjectManager::getInstance()->getSelectedObject());
			}
			if (ImGui::DragFloat3("Scale", this->SelectedObjectScale, 3))
			{
				this->TransformSelected(GameObjectManager::getInstance()->getSelectedObject());
			}

			// Attach Rigidbody
			if ((PhysicsComponent*)GameObjectManager::getInstance()->getSelectedObject()->findComponentbyType(AComponent::Physics, "Physics Component") == NULL)
			{
				if (ImGui::Button("Attach Rigidody"))
				{
					GameObjectManager::getInstance()->getSelectedObject()->ComputeLocalMatrix();
					GameObjectManager::getInstance()->getSelectedObject()->attachComponent(new PhysicsComponent(("Physics Component"), GameObjectManager::getInstance()->getSelectedObject()));
				}
			}
			else
			{
				if (ImGui::Button("Detach Rigidody"))
				{
					GameObjectManager::getInstance()->getSelectedObject()->ComputeLocalMatrix();
					PhysicsComponent* componentAttached = (PhysicsComponent*)GameObjectManager::getInstance()->getSelectedObject()->findComponentbyType(AComponent::Physics, "Physics Component");
					GameObjectManager::getInstance()->getSelectedObject()->detachComponent((PhysicsComponent*)GameObjectManager::getInstance()->getSelectedObject()->findComponentbyType(AComponent::Physics, "Physics Component"));
					delete componentAttached;
					delete (PhysicsComponent*)GameObjectManager::getInstance()->getSelectedObject()->findComponentbyType(AComponent::Physics, "Physics Component");
				}
			}
			
			// Delete Object
			if (ImGui::Button("Delete", ImVec2(70.0f, 0.0f)))
			{
				GameObjectManager::getInstance()->deleteObjectByName(GameObjectManager::getInstance()->getSelectedObject()->getName());
				GameObjectManager::getInstance()->setSelectedObject(NULL);
			}
		}

	}
	else 
	{
		ImGui::Text("No object selected");
	}

	this->textureDialogue->Display();

	if(this->textureDialogue->HasSelected())
	{
		Texture* text = TextureManager::getInstance()->createTextureFromFile(this->textureDialogue->GetSelected().c_str());
		GameObjectManager::getInstance()->getSelectedObject()->setObjectTexture(text);


		this->textureDialogue->ClearSelected();
		this->textureDialogue->Close();
	}
}

void InspectorScreen::onTransformUpdate()
{
	Vector3D position = GameObjectManager::getInstance()->getSelectedObject()->getLocalPosition();
	this->SelectedObjectposition[0] = position.m_x;
	this->SelectedObjectposition[1] = position.m_y;
	this->SelectedObjectposition[2] = position.m_z;

	Vector3D scale = GameObjectManager::getInstance()->getSelectedObject()->getLocalScale();
	this->SelectedObjectScale[0] = scale.m_x;
	this->SelectedObjectScale[1] = scale.m_y;
	this->SelectedObjectScale[2] = scale.m_z;

	Vector3D rotaion = GameObjectManager::getInstance()->getSelectedObject()->getLocalRotation();
	this->SelectedObjectRotation[0] = rotaion.m_x;
	this->SelectedObjectRotation[1] = rotaion.m_y;
	this->SelectedObjectRotation[2] = rotaion.m_z;
}

void InspectorScreen::TransformSelected(AGameObject* selected)
{
	ActionHistory::getInstance()->recordAction(selected);
	selected->setPosition(this->SelectedObjectposition[0], this->SelectedObjectposition[1], this->SelectedObjectposition[2]);
	selected->setRotation(this->SelectedObjectRotation[0], this->SelectedObjectRotation[1], this->SelectedObjectRotation[2]);
	//this->selectedObject->setEulerAnglesRotation(this->rotationDisplay[0], this->rotationDisplay[1], this->rotationDisplay[2]);
	selected->setScale(this->SelectedObjectScale[0], this->SelectedObjectScale[1], this->SelectedObjectScale[2]);
}

InspectorScreen::~InspectorScreen()
{
}