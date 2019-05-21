#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;

template <typename T>
class tab_heap {
  private:
    const float INCREASE;
    T * data;
    int size_h;
    int elements_num;
    bool root_MAX;
    void swap_h(T & a, T & b) {
      T temp = a;
      a = b;
      b = temp;
    }
    int parent_id(int i) {
      return i / 2;
    };
    void resize_h() {
      int new_size = size_h * INCREASE;
      T * new_data;
      try {
        new_data = new T[new_size];
      }
      catch (std::bad_alloc& exc) {
        cerr << "Cannot allocate memory\nexit(1)";
        exit(1);
      }
      for (int i = 0; i < size_h; ++i)
        new_data[i] = data[i];
      size_h = new_size;
      delete [] data;
      data = new_data;
    };

  public:
    tab_heap() : INCREASE(1.5), data(nullptr), size_h(0), elements_num(0), root_MAX(true) {};
    tab_heap(bool root_max) : INCREASE(1.5), data(nullptr), size_h(0), elements_num(0), root_MAX(root_max) {};
    tab_heap(int s, bool rm=true): INCREASE(1.5), data(new T[s]), size_h(0), elements_num(0), root_MAX(rm) {};
    T root() {
        assert(data != nullptr);
        return data[0];
    }
    void insert_h(T element) {
      if (elements_num == size_h)
        resize_h();
      data[elements_num] = element;
      int curr_pos = elements_num;
      ++elements_num;
      if (root_MAX) {
        while (curr_pos != 0 && data[parent_id(curr_pos)] < data[curr_pos]) {
          swap_h(data[parent_id(curr_pos)], data[curr_pos]);
          curr_pos = parent_id(curr_pos);
        }
      }
      else {
        while (curr_pos != 0 && data[parent_id(curr_pos)] > data[curr_pos]) {
          swap_h(data[parent_id(curr_pos)], data[curr_pos]);
          curr_pos = parent_id(curr_pos);
        }
      }
    };
    void file_load(const string & filename) {
      fstream file;
      file.open(filename, ios::in);
      if(!(file.is_open())) {
        cerr << "File open error\n";
        exit(1);
      }
      string akt_line;
      while (!(file.eof())) {
        getline(file, akt_line);
        T x = atoi(akt_line.c_str());
        insert_h(x);
      }
      file.close();
    };
    ~tab_heap() {
      delete [] data;
    };
};


int main()
{
    cout << "Podaj nazwe pliku: ";
    string name;
    cin >> name;
    tab_heap<int> greatest(true);
    tab_heap<int> lowest(false);
    greatest.file_load(name);
    lowest.file_load(name);
    cout << greatest.root() << " " << lowest.root();
    return 0;
}
