#ifndef PHRASESEARCH_H
#define PHRASESEARCH_H


/**
    Wspolbiezna przeszukiwarka plik�w

    Program wczytuje fraze/slowo @szukana a nastepnie
    przeszukuje wszystkie piliki .txt o nazwach na wejsciu programu
    W wyniku wypisuje Liste:

    nazwa pliku --> ilosc znalezionych @szukana
    1. l @nr_linni, c @nr kolumny.
    ..

    do dodania:
      opcja ktora zmienia fraze na inna
*/

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <mutex>
#include <string>
#include <utility>

const short THREADS = 4;
using namespace std;

class PhraseSearch {
  private:
    short n_threads; // ilosc watkow
    string phrase;   // szukana fraza
    unsigned loaded;
    mutex load_perm;        // zamek do wczytu ze zbioru nazw pikow
    mutex output_perm;      // zamek do cout
    vector <string> filenames;
    void thread_task();
    void print_result(vector<pair<int, int>> & a, string & fn);
    void searchfile(string & file_name);

  public:
    PhraseSearch() :n_threads(1), phrase(""), loaded(0) {};
    PhraseSearch(int n = THREADS, string ph = "") :n_threads(n), phrase(ph), loaded(0) {};
    void Set_phrase(string & str) {
      phrase = str;
    };
    void load_filenames() {
      string current;
      getline(cin, current);
      while(!current.empty()) {
        filenames.push_back(current);
        getline(cin, current);
      }
      cout << "Phrase - " << phrase << endl;
    };
    void search_for() {
      vector<thread> thrs(n_threads);
      for (int i = 0; i < n_threads; ++i)
        thrs[i] = thread(&PhraseSearch::thread_task, this);
      for (int i = 0; i < n_threads; ++i) {
        thrs[i].join();
      }
    }
};


#endif // PHRASESEARCH_H


