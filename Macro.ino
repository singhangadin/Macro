#include "Key.h"

//uint8_t inputPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15};
uint8_t inputPins[] = {8, 9, 10, 16};
uint8_t keys[4][3] = {{KEY_LEFT_CTRL, KEY_LEFT_ARROW}, 
                      {KEY_LEFT_CTRL, KEY_RIGHT_ARROW},
                      {0, 0, 0},
                      {0 ,0 ,0}};

int arrSize = sizeof(inputPins) / sizeof(inputPins[0]);
void handleEvent(AceButton*, uint8_t, uint8_t);

Key *buttons;
String incomingByte;

void setup() {
  Serial.begin(115200);
  while(!Serial) {}
  
  Keyboard.begin();
  
  arrSize = sizeof(inputPins) / sizeof(inputPins[0]);
  buttons = new Key[arrSize];

  for (int i = 0; i < arrSize; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
    ButtonConfig* buttonConfig = buttons[i].setup(inputPins[i]);
    buttonConfig -> setEventHandler(handleEvent);
  }
  
  for (int i = 0; i < arrSize; i++) {  
    int keySize = 3;

    Vector<uint8_t> keyboardKeys;
    uint8_t tempArr[5];
    
    keyboardKeys.setStorage(tempArr);
    
    for (int j = 0; j < keySize; j++) {
      if (keys[i][j] > 0) {
        keyboardKeys.push_back(keys[i][j]);
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
