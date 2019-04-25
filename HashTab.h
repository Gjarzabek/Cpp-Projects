/// ipmlementacja klasy hashtable
/// docelowo na szablonach dla wszystkich podstawowych typów

class HastItem {
private:
  int key;
  int value;
public:
  HashItem() : key(0), value(0);
  HashItem(const HashItem a) : key(a.key), value(a.value);
};

class HasTab {
private:
  int * content;
  int size;

public:
  HashTab() : size(0), content(NULL);
  HasTab(HasTab a) {
    size = a.size;
    content = new int[size];
    for (int i = 0; i < size; ++i) {
      content[i] = a.content[i];
    }
  }



};
