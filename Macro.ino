#include "Key.h"

//uint8_t inputPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15};
uint8_t inputPins[] = {8, 9, 10, 16};

int clickKeys[4][3] = {
  {'c', 'i', '{'}, 
  {'c', 'i', '\"'},
  {'c', 'i', '('},
  {'d', 'd'}
};

int longPressKeys[4][3] = {
  {KEY_LEFT_CTRL, KEY_LEFT_ARROW}, 
  {KEY_LEFT_CTRL, KEY_RIGHT_ARROW},
  {KEY_LEFT_CTRL, KEY_RIGHT_GUI, 'q'},
  {KEY_RIGHT_GUI ,KEY_LEFT_SHIFT, 't'}
};

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

  LinkedList<int> keyboardKeys = LinkedList<int>();
  for (int i = 0; i < arrSize; i++) {  

    // Setting click keys
    int clickKeySize = sizeof(clickKeys[i]) / sizeof(clickKeys[i][0]);
    
    for (int j = 0; j < clickKeySize; j++) {
      if (clickKeys[i][j] > 0) {
        keyboardKeys.add(clickKeys[i][j]);
      }
    }
    if (keyboardKeys.size() > 0) {
      buttons[i].setClickKeys(keyboardKeys);
    }

    keyboardKeys.clear();

    // Setting long click keys    
    int longPressKeySize = sizeof(longPressKeys[i]) / sizeof(longPressKeys[i][0]);
    
    for (int j = 0; j < longPressKeySize; j++) {
      if (longPressKeys[i][j] > 0) {
        keyboardKeys.add(longPressKeys[i][j]);
      }
    }
    if (keyboardKeys.size() > 0) {
      buttons[i].setLongPressKeys(keyboardKeys);
    }

    keyboardKeys.clear();
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
