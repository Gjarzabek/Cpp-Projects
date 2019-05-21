#include "TxtBase.h"
#include "Photo.h"
#include <vector>
#include <iostream>
#include <utility>
#include <fstream>
#include <string>
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
        int line_len = akt_line.length();
        bool cat_name = true;
        std::pair <std::string, int> akt;
        while (!(base.eof())) {
            std::cout << "akt_line: " << akt_line << std::endl;
            Photo * p = nullptr;
            char buff[line_len];
            /// zmienna j iteruje po buforze a zmienna i po stringu
            for(int i = 0, j = 0; i < line_len; ++i) {
                if (akt_line[i] == ' ') {
                    buff[j] = '\0';
                    if (i == j) {
                        p = new Photo(std::string(buff));
                    }
                    else {
                        if (cat_name) {
                            cat_name = false;
                            akt.first = std::string(buff);
                        }
                        else {
                            /// 1. indeks zdjecia w tablicy photos
                            /// 2. indeks danej kategorii w tablicy kategorii zdjêcia
                            cat_name = true;
                            akt.second = atoi(buff);
                            int id1 = photos.size();
                            unsigned id2;
                            for (id2 = 0 ; id2 < p->categories.size(); ++id2)
                                if (akt.first == p->categories[id2].first)
                                    break;
                            if (photo_categories.find(akt.first) == photo_categories.end()) {
                                photo_categories[akt.first] = std::vector<std::pair<int, int>>(0);
                            }
                            std::pair<int, int> p1(id1, id2);
                            photo_categories[akt.first].push_back(p1);
                            p->add_cat(akt.first, akt.second);
                        }
                    }
                    j = 0;
                }
                else {
                    buff[j] = akt_line[i];
                    putchar('\t');
                    putchar(akt_line[i]);
                    ++j;
                }
            }
            photos.push_back(p);
            getline(base, akt_line);
            line_len = akt_line.length();
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
            }
            base << std::endl;
    base.close();
    for (auto photo: photos) {
      delete photo;
    }
}

/*std::ostream & operator<<(std::ostream & st, const TxtBase & d) {
    for (auto photo: d.photos) {
        st << photo->name;
        for (auto p: photo->categories)
          st << " " << p.first << " " << p.second;
        st << std::endl;
    }
    return st;
};*/
