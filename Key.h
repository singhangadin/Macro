#include <AceButton.h>
#include <Keyboard.h>

using namespace ace_button;

class Key: public IEventHandler {
  private:
    uint8_t pin;
    AceButton acebutton;

  public:
    ButtonConfig* setup(uint8_t lPin);
    void check();
    void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
};

void Key::handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventClicked: {
      Keyboard.print(pin);
      break;
    }
  
    case AceButton::kEventLongPressed: {
      Keyboard.print(pin);
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
