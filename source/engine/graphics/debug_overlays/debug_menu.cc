#include "../../Graphics/Text.h"
#include "../EngineCore/EngineCore.h"
#include "../EngineCore/Objects/Scene.h"
#include "../Utilities/IObjectController.h"
#include "DebugMenu.h"

SharedPointer<Debug::DebugMenu>
    Debug::DebugMenu::mDebugMenu;

void Debug::DebugMenu::HandleMessage(
    utils::StringHash& i_message, SharedPointer<RTTI> i_MessageSender,
    void* i_pMessageData) {
  if (!i_MessageSender.isNull()) {
    if (!i_MessageSender.isNull() &&
        utils::StringHash("DebugMenuHandler") == i_message &&
        !mObjectController.isNull())
      mObjectController->updateObject(
          *this, *reinterpret_cast<typedefs::ActionWithKeyBound*>(
                     i_pMessageData));
  }
}

void Debug::DebugMenu::Activate(bool iRequest) {
  isActive = iRequest;

  for (std::map<int, SharedPointer<UI::UIElement>>::iterator i =
           mDebugMenuAssociatedObjectList.begin();
       i != mDebugMenuAssociatedObjectList.end(); ++i) {
    if (iRequest) {
      i->second->GetUIElementName()->setRenderable(true);
      i->second->GetUIElement()->setRenderable(true);
    } else {
      i->second->GetUIElementName()->setRenderable(false);
      i->second->GetUIElement()->setRenderable(false);
      i->second->GetAssociatedObject()->setRenderable(false);
    }
  }
}

uint16_t Debug::DebugMenu::GetCurrentSelectionIndex() const {
  return currentlySelected;
}

std::map<int, SharedPointer<UI::UIElement>>
Debug::DebugMenu::GetDebugObjects() const {
  return mDebugMenuAssociatedObjectList;
}

uint16_t Debug::DebugMenu::GetElementCount() const {
  return UIElementCount;
}

void Debug::DebugMenu::SetCurrentlySelected(uint8_t iSelected) {
  currentlySelected = iSelected;
}

void Debug::DebugMenu::CreateButton(
    std::string buttonName, SharedPointer<MeshObject> associatedObject) {
  mDebugMenu->UIElementCount++;
  SharedPointer<Graphics::Text> tempUIElementName = Graphics::Text::CreateText(
      "Game/textEffect.effect", "arial.ttf", mTransform);
  tempUIElementName->SetTextToRender(buttonName);
  tempUIElementName->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);
  tempUIElementName->setRenderable(false);

  Math::Vector3 tempPosition = mTransform.getPosition();
  tempPosition.x += 300.0f;

  SharedPointer<Graphics::Text> tempUIElement = Graphics::Text::CreateText(
      "Game/textEffect.effect", "arial.ttf",
      Math::Transform(tempPosition, Math::Quaternion::getIdentityQuartenion()));
  tempUIElement->SetTextToRender("OFF");
  tempUIElement->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);
  tempUIElement->setRenderable(false);

  Scene::getRenderableScene()->addObjectToScene(tempUIElementName);
  Scene::getRenderableScene()->addObjectToScene(tempUIElement);

  tempPosition.x = mTransform.getPosition().x;
  tempPosition.y -= 30.0f;
  mTransform.setPosition(tempPosition);

  SharedPointer<UI::UIElement> tempElement = UI::UIElement::CreateUIElement(
      UI::Button, associatedObject, tempUIElementName, tempUIElement);
  mDebugMenuAssociatedObjectList[mDebugMenu->UIElementCount] = tempElement;
}

void Debug::DebugMenu::CreateCheckBox(
    std::string iCheckBoxName, SharedPointer<MeshObject> associatedObject) {
  mDebugMenu->UIElementCount++;
  SharedPointer<Graphics::Text> tempUIElementName = Graphics::Text::CreateText(
      "Game/textEffect.effect", "arial.ttf", mTransform);
  tempUIElementName->SetTextToRender(iCheckBoxName);
  tempUIElementName->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);

  Math::Vector3 tempPosition = mTransform.getPosition();
  tempPosition.x += 300.0f;

  SharedPointer<Graphics::Text> tempUIElement = Graphics::Text::CreateText(
      "Game/textEffect.effect", "arial.ttf",
      Math::Transform(tempPosition, Math::Quaternion::getIdentityQuartenion()));
  tempUIElement->SetTextToRender("[ ]");
  tempUIElement->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);
  tempUIElement->setRenderable(false);

  Scene::getRenderableScene()->addObjectToScene(tempUIElementName);
  Scene::getRenderableScene()->addObjectToScene(tempUIElement);

  tempPosition.x = mTransform.getPosition().x;
  tempPosition.y -= 30.0f;
  mTransform.setPosition(tempPosition);

  SharedPointer<UI::UIElement> tempElement = UI::UIElement::CreateUIElement(
      UI::CheckBox, associatedObject, tempUIElementName, tempUIElement);

  mDebugMenuAssociatedObjectList[mDebugMenu->UIElementCount] = tempElement;
}

void Debug::DebugMenu::CreateSlider(
    std::string iSliderName, SharedPointer<MeshObject> associatedObject,
    float min, float max) {
  mDebugMenu->UIElementCount++;
  SharedPointer<Graphics::Text> tempUIElementName = Graphics::Text::CreateText(
      "Game/textEffect.effect", "arial.ttf", mTransform);
  tempUIElementName->SetTextToRender(iSliderName);
  tempUIElementName->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);

  Math::Vector3 tempPosition = mTransform.getPosition();
  tempPosition.x += 300.0f;

  SharedPointer<Graphics::Text> tempUIElement = Graphics::Text::CreateText(
      "Game/textEffect.effect", "arial.ttf",
      Math::Transform(tempPosition, Math::Quaternion::getIdentityQuartenion()));
  tempUIElement->SetTextToRender("[. . . . . . . . . . . . . . . . . . . .]");
  tempUIElement->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);
  tempUIElement->setRenderable(false);

  Scene::getRenderableScene()->addObjectToScene(tempUIElementName);
  Scene::getRenderableScene()->addObjectToScene(tempUIElement);

  tempPosition.x = mTransform.getPosition().x;
  tempPosition.y -= 30.0f;
  mTransform.setPosition(tempPosition);

  SharedPointer<UI::UIElement> tempElement = UI::UIElement::CreateUIElement(
      UI::Slider, associatedObject, tempUIElementName, tempUIElement, max, min);
  mDebugMenuAssociatedObjectList[mDebugMenu->UIElementCount] = tempElement;
}

void Debug::DebugMenu::CreateText(
    std::string textName, std::string iText,
    SharedPointer<MeshObject> associatedObject) {
  mDebugMenu->UIElementCount++;
  SharedPointer<Graphics::Text> tempUIElementName = Graphics::Text::CreateText(
      "Game/textEffect.effect", "arial.ttf", mTransform);
  tempUIElementName->SetTextToRender(textName);
  tempUIElementName->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);

  Math::Vector3 tempPosition = mTransform.getPosition();
  tempPosition.x += 300.0f;

  SharedPointer<Graphics::Text> tempUIElement = Graphics::Text::CreateText(
      "Game/textEffect.effect", "arial.ttf",
      Math::Transform(tempPosition, Math::Quaternion::getIdentityQuartenion()));
  tempUIElement->SetTextToRender(iText);
  tempUIElement->SetVertexColor(0.0f, 1.0f, 0.0f, 0.5f);
  tempUIElement->setRenderable(false);

  Scene::getRenderableScene()->addObjectToScene(tempUIElementName);
  Scene::getRenderableScene()->addObjectToScene(tempUIElement);

  tempPosition.x = mTransform.getPosition().x;
  tempPosition.y -= 30.0f;
  mTransform.setPosition(tempPosition);

  SharedPointer<UI::UIElement> tempElement = UI::UIElement::CreateUIElement(
      UI::Text, associatedObject, tempUIElementName, tempUIElement, iText);
  mDebugMenuAssociatedObjectList[mDebugMenu->UIElementCount] = tempElement;
}

Debug::DebugMenu::DebugMenu() {
  UIElementCount = 0;
  isActive = false;
  currentlySelected = 0;
  mTransform.setPosition(Math::Vector3(
      10.0f, EngineCore::getWindowingSystem()->getWindowHeight() - 30.0f,
      0.0f));
  mTransform.setOrientation(Math::Quaternion::getIdentityQuartenion());
}

SharedPointer<Debug::DebugMenu>
Debug::DebugMenu::GetDebugMenu() {
  if (mDebugMenu.isNull()) {
    SharedPointer<DebugMenu> tempDebugMenu =
        SharedPointer<DebugMenu>(new DebugMenu(), "DebugMenu");

    mDebugMenu = tempDebugMenu;
    utils::StringHash temp = utils::StringHash(
        EngineCore::getStringPool()->findString("DebugMenuHandler"));

    EngineCore::getMessagingSystem()->addMessageHandler(
        temp, mDebugMenu.CastSharedPointer<IMessageHandler>(),
        typedefs::HIGH);
  }
  return mDebugMenu;
}

bool Debug::DebugMenu::isActivated() const { return isActive; }

bool Debug::DebugMenu::isExist() const {
  return mDebugMenuAssociatedObjectList.size() > 0 ? true : false;
}

void Debug::DebugMenu::updateObject() {
  typedefs::ActionWithKeyBound action;
  action.action = typedefs::Default;
  action.keyVal = 0x00;
  if (!mObjectController.isNull())
    mObjectController->updateObject(*this, action);
}

void Debug::DebugMenu::setObjectController(
    SharedPointer<IObjectController> i_ObjectControlller) {
  if (!i_ObjectControlller.isNull()) mObjectController = i_ObjectControlller;
}
