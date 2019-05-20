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
  cout << "file_name: " << fn << endl;
  cout << "------------------\n";
  for (unsigned i = 0; i < a.size(); ++i)
    cout << i+1 << ". l: " << a[i].first << ", c: " << a[i].second << endl;
  cout << "##################\n\n";
  output_perm.unlock();
}


void PhraseSearch::searchfile(string & file_name) {
  fstream file;
  try {
    file.open(file_name, ios::in);
    if(!file.good())
      throw ": Permission denied\n";
  }
  catch (char const * s) {
    output_perm.lock();
    cout << file_name << s << endl;
    output_perm.unlock();
    return;
  }

  vector<pair<int, int>> result(0);
  int curr_line = 1, curr_col = 1, curr_pos = 0;
  pair <int, int> coordinates;

  while (!file.eof()) {
    char Ch = file.get();
    if (Ch == phrase[curr_pos]) {
        if (curr_pos == 0) {
          coordinates.first = curr_line;
          coordinates.second = curr_col;
        }
        if (++curr_pos == (int)phrase.length()) {
            result.push_back(coordinates);
            curr_pos = 0;
        }
        ++curr_col;
    }
    else {
        switch (Ch) {
        case '\n':
            ++curr_line;
            curr_col = 1;
            curr_pos = 0;
        break;
        default:
            ++curr_col;
            curr_pos = 0;
        break;
        }
    }
  }
  print_result(result, file_name);
}

void PhraseSearch::thread_task() {
  while (loaded < filenames.size()) {
    load_perm.lock();
    string & fn = filenames[loaded];
    ++loaded;
    load_perm.unlock();
    searchfile(fn);
  }
}

