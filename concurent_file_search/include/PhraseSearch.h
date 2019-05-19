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
    mutex load_perm;        // zamek do wczytu z cin
    mutex output_perm;      // zamek do cout
    void print_result(vector<pair<int, int>> & a, string & fn);
    void searchfile();

  public:
    PhraseSearch() :n_threads(1), phrase("") {};
    PhraseSearch(int n = THREADS, string ph = "") :n_threads(n), phrase(ph) {};
    void Set_phrase(string & str) {
      phrase = str;
    };
    void search_for() {
      thread thrs[n_threads];
      for (int i = 0; i < n_threads; ++i)
        thrs[i] = thread();
      for (int i = 0; i < n_threads; ++i)
        thrs[i].join();
    }
};


#endif // PHRASESEARCH_H

