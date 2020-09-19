#include "Key.h"

uint8_t inputPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15};
int arrSize = sizeof(inputPins) / sizeof(inputPins[0]);
void handleEvent(AceButton*, uint8_t, uint8_t);

Key *buttons;
String incomingByte;

void setup() {
  Keyboard.begin();
  
  arrSize = sizeof(inputPins) / sizeof(inputPins[0]);
  buttons = new Key[arrSize];
  
  for (int i = 0; i < arrSize; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
    ButtonConfig* buttonConfig = buttons[i].setup(inputPins[i]);
    buttonConfig -> setEventHandler(handleEvent);
  }
}

void loop() {
  for (int i = 0; i < arrSize; i++) {
      buttons[i].check();
  }
}

void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  uint8_t selectedIndex = getIndexForPin(button -> getPin());
  buttons[selectedIndex].handleEvent(button, eventType, buttonState);
}

int getIndexForPin(int pinNumber) {
  for(int i = 0; i < arrSize; i++) {
    if (inputPins[i] == pinNumber) {
      return i;
    }
  }
}
