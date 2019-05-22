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
        void print() {
          std::cout << "name: " << name;
          std::cout<<std::endl;
          for (auto x: categories) {
            std::cout << "Cat: " << x.first << ", grade: " << x.second;
            std::cout<<std::endl;
          }
          std::cout<<std::endl;
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
                std::cout << std::endl;
            }
            std::cout << std::endl;
        };
        void show_categories() {
          std::cout << "-----------\n";
          for (auto x: photo_categories) {
            std::cout << x.first << std::endl;
          }
          std::cout << "-----------\n";
        };
        void add_image();
        void remove_image(std::string file_name);
        void get_photos(const std::vector<std::string> & v);
        /**nadpisuje stary plik nowym wydrukiem z aktualnej bazy danych*/

        virtual ~TxtBase();
};


#endif // TXTBASE_H
