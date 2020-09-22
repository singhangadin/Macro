#include <AceButton.h>
#include <Keyboard.h>
#include <LinkedList.h>

using namespace ace_button;
typedef LinkedList<uint8_t> KeyCodes;

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
    
    const char asciiMap[47] = {
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
      'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
      'u', 'v', 'w', 'x', 'y', 'z', '+', '-', ',', '.', 
      '/', '\\', '`','[',']', '\'', '\"'
    };
  
    ButtonConfig* setup(uint8_t lPin);
    void check();
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
        if (longPressKeys.get(i) < 47) {
          Keyboard.press(asciiMap[longPressKeys.get(i) - 1]);
        } else {
          Keyboard.press(longPressKeys.get(i));
        }
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
