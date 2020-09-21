#include <AceButton.h>
#include <Keyboard.h>
#include <Vector.h>

using namespace ace_button;
typedef Vector<uint8_t> KeyCodes;

class Key: public IEventHandler {
  private:
  
    uint8_t pin;
    AceButton acebutton;
    Vector<uint8_t> clickKeys, longPressKeys;

  public:
    Key() {
      uint8_t arr1[5], arr2[5];
      clickKeys.setStorage(arr1);
      longPressKeys.setStorage(arr2);
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
    void setClickKeys(Vector<uint8_t> keyCodes);
    void setLongPressKeys(Vector<uint8_t> keyCodes);
    void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
};

void Key::setClickKeys(Vector<uint8_t> keyCodes) {
  clickKeys.clear();
  for (int i = 0; i < keyCodes.size(); i++) {
    clickKeys.push_back(keyCodes.at(i));   
  }
}

void Key::setLongPressKeys(Vector<uint8_t> keyCodes) {
  longPressKeys.clear();
  for (int i = 0; i < keyCodes.size(); i++) {
    longPressKeys.push_back(keyCodes.at(i));   
  }
}

void Key::handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventClicked: {
      for (int i = 0; i < clickKeys.size(); i++) {
        Keyboard.press(clickKeys.at(i));
      }
      Keyboard.releaseAll();
      break;
    }
  
    case AceButton::kEventLongPressed: {
      for (int i = 0; i < longPressKeys.size(); i++) {
        if (longPressKeys.at(i) < 47) {
          Keyboard.press(asciiMap[longPressKeys.at(i) - 1]);
          Serial.println(asciiMap[longPressKeys.at(i) - 1]);
        } else {
          Keyboard.press(longPressKeys.at(i));
          Serial.println(longPressKeys.at(i));
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
