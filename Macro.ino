#include "Key.h"

static const uint8_t NUM_PINS = 4;
static const uint8_t NUM_BUTTONS = 12;
static const uint8_t PINS[NUM_PINS] = {4, 5, 6, 7};

Key *keys;

static AceButton b01(1);
static AceButton b02(2);
static AceButton b03(3);
static AceButton b04(4);
static AceButton b05(5);
static AceButton b06(6);
static AceButton b07(7);
static AceButton b08(8);
static AceButton b09(9);
static AceButton b10(10);
static AceButton b11(11);
static AceButton b12(12);

static AceButton* const BUTTONS[] = {
    &b01, &b02, &b03, &b04, &b05, &b06, &b07,
    &b08, &b09, &b10, &b11, &b12
};

static EncodedButtonConfig buttonConfig(NUM_PINS, PINS, NUM_BUTTONS, BUTTONS);

void handleEvent(AceButton*, uint8_t, uint8_t);

int clickKeys[NUM_BUTTONS][4] = {
  {KEY_ESC, 'c', 'i', '{'}, {KEY_ESC, 'c', 'i', '('}, {KEY_ESC, 'c', 'i', '\"'}, {KEY_ESC, 'c', 'i', '\''},
  {KEY_ESC, 'd', 'd'}, {KEY_ESC, 'd', '$'}, {KEY_ESC, 'd', '0'}, {KEY_ESC, KEY_LEFT_SHIFT, 'a'},
  {KEY_LEFT_CTRL, KEY_LEFT_ARROW}, {KEY_LEFT_CTRL, KEY_RIGHT_ARROW},{KEY_LEFT_CTRL, KEY_RIGHT_GUI, 'q'},  {KEY_RIGHT_GUI ,KEY_LEFT_SHIFT, 't'}
};

int longPressKeys[NUM_BUTTONS][4] = {
  {KEY_ESC, 'c', 'i', '{'},
  {KEY_ESC, 'c', 'i', '('},
  {KEY_ESC, 'c', 'i', '\"'},
  {KEY_ESC, 'c', 'i', '\''},
  {KEY_ESC, 'd', 'd'},
  {KEY_ESC, 'd', '$'},
  {KEY_ESC, 'd', '0'},
  {KEY_ESC, KEY_LEFT_SHIFT, 'a'},
  {KEY_ESC, KEY_LEFT_CTRL, KEY_LEFT_ARROW}, 
  {KEY_ESC, KEY_LEFT_CTRL, KEY_RIGHT_ARROW},
  {KEY_ESC, KEY_LEFT_CTRL, KEY_RIGHT_GUI, 'q'},
  {KEY_ESC, KEY_RIGHT_GUI ,KEY_LEFT_SHIFT, 't'}
};

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  
  keys = new Key[NUM_BUTTONS];

  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(PINS[i], INPUT_PULLUP);
  }

  LinkedList<int> keyboardKeys = LinkedList<int>();
  for (int i = 0; i < NUM_BUTTONS; i++) {  
    keys[i].setup(i);
    
    // Setting click keys
    int clickKeySize = sizeof(clickKeys[i]) / sizeof(clickKeys[i][0]);
    
    for (int j = 0; j < clickKeySize; j++) {
      if (clickKeys[i][j] > 0) {
        keyboardKeys.add(clickKeys[i][j]);
      }
    }
    if (keyboardKeys.size() > 0) {
      keys[i].setClickKeys(keyboardKeys);
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
      keys[i].setLongPressKeys(keyboardKeys);
    }

    keyboardKeys.clear();
  }

  buttonConfig.setEventHandler(handleEvent);
  buttonConfig.setFeature(ButtonConfig::kFeatureClick);
}

void loop() {
    buttonConfig.checkButtons();
}

void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println(button -> getPin());
  uint8_t selectedIndex = button -> getPin();
  keys[selectedIndex - 1].handleEvent(button, eventType, buttonState);
}
