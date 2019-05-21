#ifndef TXTBASE_H
#define TXTBASE_H

#include <vector>
#include <iostream>
#include <utility>
#include <fstream>
#include <unordered_map>

class TxtBase;
std::ostream & operator<<(std::ostream & st, const TxtBase & d);

class Photo
{
    friend class TxtBase;
    friend std::ostream& operator<<(std::ostream& st, TxtBase const & d);

    private:
        std::string name;
        std::vector < std::pair<std::string, int> > categories;
    public:
        Photo() : name("") {};
        Photo(std::string a) : name(a) {};
        void add_cat(std::string name, int value) {
            categories.push_back(std::pair<std::string, int>(name, value));
        };
        std::string get_name() {
            return name;
        };
        ~Photo() {};
};



class TxtBase
{
    friend std::ostream& operator<<(std::ostream& st, const TxtBase & d);

    private:
        /// hash table, photo_categories - tablica gdzie kluczami sa kategorie a wartoscia kazdej kategorii
        /// jest lista par indeksow:
        /// 1. indeks zdjecia w tablicy photos
        /// 2. indeks danej kategorii w tablicy kategorii zdjêcia

        std::fstream base;
        std::unordered_map <std::string, std::vector<std::pair<int, int>>> photo_categories;
        std::vector <Photo*> photos;

    public:
        TxtBase();
        /**wpisuje do tablicy photos, kategorie do hasz mapy*/
        void print() {
            for (auto photo: photos) {
                std::cout << photo->name;
                for (auto p: photo->categories)
                    std::cout << " " << p.first << " " << p.second;
            }
            std::cout << std::endl;
        };
        void add_image(Photo * ph) {
            photos.push_back(ph);
            std::vector<std::pair<std::string, int>>::iterator cat;
            int i = 0;
            for (cat = ph->categories.begin(); cat != ph->categories.end(); ++i, ++cat) {
                if (photo_categories.find((*cat).first) == photo_categories.end())
                    photo_categories[(*cat).first] = std::vector<std::pair<int, int>>(0);
                photo_categories[(*cat).first].push_back(std::pair<int, int>(photos.size(), i));
            }
        };
        void remove_image(std::string file_name) {
            unsigned i; /// indeks zdjecie w tablicy photos
            for (i = 0; i < photos.size(); ++i) {
                if (photos[i]->get_name() == file_name)
                    break;
            }
            if (i == photos.size()) {
                std::cout << "Brak zdjecia w bazie danych - nie mozna go usunac.\n";
            }
            else {
                for (auto x: photos[i]->categories) {
                    if (photo_categories.find(x.first) != photo_categories.end()) {
                        std::vector<std::pair<int, int>>::iterator j = photo_categories[x.first].begin();
                        while ((*j).first != (int)i) {
                                ++j;
                        }
                        photo_categories[x.first].erase(j);
                    }
                }
            }
        };
        /**nadpisuje stary plik nowym wydrukiem z aktualnej bazy danych*/
        virtual ~TxtBase();
};


#endif // TXTBASE_H
