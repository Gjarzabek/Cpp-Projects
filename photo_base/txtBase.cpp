#include "TxtBase.h"
#include "Photo.h"
#include <vector>
#include <iostream>
#include <utility>
#include <fstream>
#include <set>
#include <string>
#include <functional>
#include <unordered_map>

const std::string BASE_NAME = "data.txt";

/**
    postac danych zapisywanych w pliku:
    las.jpg przyroda 3 przestrzen 1 wies 4
    osiedle.jpg przyroda 1 miasto 4 wiosna 2
*/


TxtBase::TxtBase()
{
    base.open(BASE_NAME, std::ios::in | std::ios::out);
    //Jesli nie udalo sie otworzyc pliku to tworze nowy
    if (!base.is_open()) {
        base.open(BASE_NAME,std::ios::out);
        base.close();
        base.open(BASE_NAME, std::ios::in | std::ios::out);
    }
    else { /// plik juz istnial
        std::string akt_line;
        getline(base, akt_line);
        akt_line+=" ";
        bool cat_name = true;
        std::pair <std::string, int> akt;
        while (!(base.eof())) {
            Photo * p = nullptr;
            std::string buff = "";
            /// zmienna @i iteruje po aktualnej linii
            for(unsigned i = 0; i < akt_line.length(); ++i) {
                if (akt_line[i] == ' ') {
                    if (!p) {
                        p = new Photo(std::string(buff));
                    }
                    else {
                        if (cat_name) {
                            cat_name = false;
                            akt.first = buff;
                        }
                        else {
                            /// 1. indeks zdjecia w tablicy photos
                            /// 2. indeks danej kategorii w tablicy kategorii zdjêcia
                            cat_name = true;
                            akt.second = atoi(buff.c_str());
                            int id1 = photos.size();
                            unsigned id2;
                            for (id2 = 0 ; id2 < p->categories.size(); ++id2)
                                if (akt.first == p->categories[id2].first)
                                    break;
                            if (photo_categories.find(akt.first) == photo_categories.end()) {
                                photo_categories.insert(std::make_pair(akt.first, std::vector<std::pair<int, int>>(0)));
                            }
                            std::pair<int, int> p1(id1, id2);
                            photo_categories[akt.first].push_back(p1);
                            p->add_cat(akt.first, akt.second);
                        }
                    }
                    buff.clear();
                }
                else {
                    buff += akt_line[i];
                }
            }
            photos.push_back(p);
            getline(base, akt_line);
            akt_line+=" ";
        }
    }
    base.close();
}

TxtBase::~TxtBase()
{
    base.open(BASE_NAME, std::ios::out);
    if (!base.is_open()) {
      std::cerr << "TxtBase::~TxtBase(): file write error\n";
    }
    for (auto photo: photos) {
        base << photo->name;
        for (auto p: photo->categories)
            base << " " << p.first << " " << p.second;
        base << std::endl;
    }
    base.close();
    for (auto photo: photos) {
      delete photo;
    }
}

void TxtBase::add_image() {
    Photo * ph = nullptr;
    std::cout << "Podaj nazwe zdjecia: ";
    std::string n;
    std::cin >> n;
    ph = new Photo(n + ".jpg");
    std::cout << "Podawaj kategorie i oceny w parach(nazwa_kategori , enter, ocena)\nquit - konczy wprowadzanie\n";
    while(true) {
      std::cin >> n;
      if (n == "quit")  break;
      std::string grade;
      std::cin >> grade;
      while(std::cin.fail()) {
        std::cin.clear();
        while(getchar() != '\n');
        std::cout << "Sprobuj jescze raz\n";
        std::cin >> n;
        std::cin >> grade;
      }
      ph->categories.push_back(std::make_pair(n, atoi(grade.c_str())));
    }
    photos.push_back(ph);
    std::vector<std::pair<std::string, int>>::iterator cat;
    int i = 0;
    for (cat = ph->categories.begin(); cat != ph->categories.end(); ++i, ++cat) {
        if (photo_categories.find((*cat).first) == photo_categories.end())
            photo_categories.insert(std::make_pair((*cat).first, std::vector<std::pair<int, int>>(0)));
        photo_categories[(*cat).first].push_back(std::make_pair(photos.size(), i));
    }
}

void TxtBase::remove_image(std::string file_name) {
    std::vector<Photo*>::iterator i; /// indeks zdjecie w tablicy photos
    int k; // indeks zdjecia w tablicy photos
    for (i = photos.begin(), k = 0; i != photos.end(); ++i, ++k) {
        if ((*i)->get_name() == file_name)
            break;
    }
    if (i == photos.end()) {
        std::cout << "Brak zdjecia w bazie danych - nie mozna go usunac.\n";
        return;
    }
    else {
        for (auto x: (*i)->categories) {
            if (photo_categories.find(x.first) != photo_categories.end()) {
                std::vector<std::pair<int, int>>::iterator j = photo_categories[x.first].begin();
                while ((*j).first != k) {
                        ++j;
                }
                photo_categories[x.first].erase(j);
            }
        }
    }
    Photo * d = *i;
    photos.erase(i);
    delete d;
}

void TxtBase::get_photos(const std::vector<std::string> & v) {
  std::multiset <std::pair<int, Photo*>> result; /// int to ocena dla danej kategorii @v[k]
  for (unsigned k = 0; k < v.size(); ++k) {
    if(photo_categories.find(v[k]) == photo_categories.end()) {
      std::cout<< "TxtBase::get_photos: "<< v[k] << " - no such categorie\n";
      continue;
    }
    std::multiset <std::pair<int, Photo*>> cat;
    std::vector<std::pair<int, int>> & container = photo_categories.at(v[k]);
    /// dodaje wszystkie zdjecia z danej kategorii
    for (auto i = container.begin(); i != container.end(); ++i) {
      cat.insert(std::make_pair(photos[(*i).first]->categories[(*i).second].second, photos[(*i).first]));
    }
    if (k == 0) {
        result = std::multiset<std::pair<int, Photo*>>(cat);
    }
    std::multiset <std::pair<int, Photo*>> temp;
    std::unordered_map<Photo*, std::pair<int, int>> counting; ///pierwszy int to ocena drugi to ilosc wystapien
    /// zliczam zdjecia z kategorii
    for (auto x: cat) {
        counting.insert(std::make_pair(x.second, std::make_pair(x.first, 1)));
    }
    for (auto x: result) {
      if (counting.find(x.second) != counting.end()) {
        (counting[x.second].second)++;
      }
      else
        counting.insert(std::make_pair(x.second, std::make_pair(x.first, 1)));
    }
    for (auto p: counting) {
        if (p.second.second > 1)
          temp.insert(std::make_pair(p.second.first, p.first));
    }

    result.swap(temp);
  }
  for (auto i = result.rbegin(); i != result.rend(); ++i) {
      (*i).second->print();
  }
}
