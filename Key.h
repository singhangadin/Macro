#include <AceButton.h>
#include <Keyboard.h>
#include <LinkedList.h>

using namespace ace_button;
typedef LinkedList<int> KeyCodes;

class Key: public IEventHandler {
  private:
  
    uint8_t pin;
    AceButton acebutton;
    KeyCodes clickKeys, longPressKeys;

  public:
    Key() {
      clickKeys = KeyCodes();
      longPressKeys = KeyCodes();
    }
  
    ButtonConfig* setup(uint8_t lPin);
    void check();
    int ifasciiMapChar(char ch);
    void setClickKeys(KeyCodes &keyCodes);
    void setLongPressKeys(KeyCodes &keyCodes);
    void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
};

void Key::setClickKeys(KeyCodes &keyCodes) {
  clickKeys.clear();
  for (int i = 0; i < keyCodes.size(); i++) {
    clickKeys.add(keyCodes.get(i));   
  }
}

void Key::setLongPressKeys(KeyCodes &keyCodes) {
  longPressKeys.clear();
  for (int i = 0; i < keyCodes.size(); i++) {
    longPressKeys.add(keyCodes.get(i));   
  }
}

void Key::handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventClicked: {
      for (int i = 0; i < clickKeys.size(); i++) {
          Keyboard.press(clickKeys.get(i));
      }
      Keyboard.releaseAll();
      break;
    }
  
    case AceButton::kEventLongPressed: {
      for (int i = 0; i < longPressKeys.size(); i++) {
          Keyboard.press(longPressKeys.get(i));
      }
      Keyboard.releaseAll();
      break;
    }
  }
}

ButtonConfig* Key::setup(uint8_t lPin) {
  pin = lPin;
  acebutton.init(pin);
  
  ButtonConfig* buttonConfig = acebutton.getButtonConfig();
  buttonConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig->setFeature(ButtonConfig::kFeatureSuppressAfterLongPress);

  return buttonConfig;
}

void Key::check() {
  acebutton.check();
}
