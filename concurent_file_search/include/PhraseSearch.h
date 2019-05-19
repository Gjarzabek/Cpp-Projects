#ifndef PHRASESEARCH_H
#define PHRASESEARCH_H


/**
    Wspolbiezna przeszukiwarka plików

    Program wczytuje fraze/slowo @szukana a nastepnie
    przeszukuje wszystkie piliki .txt o nazwach na wejsciu programu
    W wyniku wypisuje Liste:

    nazwa pliku --> ilosc znalezionych @szukana
    1. l @nr_linni, c @nr kolumny.
    ..
*/

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <mutex>
#include <string>
#include <pair>

const short THREADS = 4;
using namespace std;

class PhraseSearch {
  private:
    static short n_threads;
    vector<thread> threads;
    vector<fstream> files;
    mutex load_perm;
    mutex output_perm;
    static string phrase;

  public:
    PhraseSearch(int n = THREADS) n_threads(n) {
      cout << "Phrase to search for: ";
      cin >> phrase;
    };
    void searchfile(); /// simple thread function
    void print_result();
};


#endif // PHRASESEARCH_H
