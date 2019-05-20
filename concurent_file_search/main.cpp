/**
    Wspolbiezna przeszukiwarka plik�w

    Program wczytuje fraze/slowo @szukana a nastepnie
    przeszukuje wszystkie piliki .txt o nazwach na wejsciu programu
    W wyniku wypisuje Liste:

    nazwa pliku --> ilosc znalezionych @szukana
    1. l @nr_linni, c @nr kolumny.
    ..
*/

#include <iostream>
#include "PhraseSearch.h"

int main()
{
    PhraseSearch ph(3, "a");
    ph.load_filenames();
    ph.search_for();
    return 0;
}
