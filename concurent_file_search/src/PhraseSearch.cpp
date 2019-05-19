#include "PhraseSearch.h"

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <mutex>
#include <string>
#include <utility>

using namespace std;


void PhraseSearch::print_result(vector<pair<int, int>> & a, string & fn) {
  output_perm.lock();
  cout << fn << ", found: " << a.size() << endl;
  for (unsigned i = 0; i < a.size(); ++i)
    cout << i+1 << ". l: " << a[i].first << ", c: " << a[i].second << endl;
}


void PhraseSearch::searchfile() {
  string file_name;
  load_perm.lock();
  cin >> file_name;
  load_perm.unlock();
  if (file_name.empty())
    return;

  fstream file;
  try {
    file.open(file_name, ios::in);
    if(!file.good())
      throw ": Permission denied";
  }
  catch (char * s) {
    output_perm.lock();
    cout << file_name << s << endl;
    output_perm.unlock();
  }

  vector<pair<int, int>> result(0);
  int curr_line, curr_col, curr_pos = 0;
  pair <int, int> coordinates;

  while (!file.eof()) {
    const char C = phrase[curr_pos];
    switch (file.get()) {
      case C:
        if (curr_pos == 0) {
          coordinates.first = curr_line;
          coordinates.second = curr_col;
        }
        if (++curr_pos == phrase.length()) {
          result.push_back(coordinates);
          curr_pos = 0;
        }
        ++curr_col;
      break;
      case '\n':
        ++curr_line;
        curr_col = 0;
        curr_pos = 0;
      break;
      default:
        ++curr_col;
        curr_pos = 0;
      break;
    }
  }
}
