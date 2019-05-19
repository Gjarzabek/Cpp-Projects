#include "PhraseSearch.h"
#include <vector>
#include <fstream>
#include <mutex>
#include <string>
#include <pair>

void PhraseSearch::searchfile(s) {
  string file_name;
  load_perm.lock();
  cin >> file_name;
  load_perm.unlock();
  int seen;
  vector<pair<int, int>> result;
  int curr_line;
  int curr_col;

}
