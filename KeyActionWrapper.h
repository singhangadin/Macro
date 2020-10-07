#include <ArduinoJson.h>
#include <LinkedList.h>


static String tempData = "{\"data\":[{\"pin\":\"0\",\"clickAction\":[1,2,3],\"longClickAction\":[4,5,6]},{\"pin\":\"1\",\"clickAction\":[1,2,3],\"longClickAction\":[4,5,6]}]}";

class KeyActionWrapper {
  private:
  LinkedList<Key> keys;

  public:
  KeyActionWrapper fromJson(String json);
  String toJson(KeyActionWrapper &data);
};

KeyActionWrapper KeyActionWrapper::fromJson(String json) {
  return KeyActionWrapper();
}

String KeyActionWrapper::toJson(KeyActionWrapper &data) {
  return "";
}
