#include "Photo.h"
#include "txtBase.h"
#include <iostream>

void run_Base() {
    TxtBase base;
    std::cout << "aktualny stan bazy:\n";
    base.print();
    bool finish = false;
    while(!finish) {
        std::cout << "\n\nQ-koniec pracy\nadd - wprowadzanie zdjecia\nfind - szukaj zdjec po kategoriach\nprint - wypisanie bazy\n";
        std::cout << "rm - usun zdjecia o podanej nazwie\ncat - wyswietl kategorie\n";
        std::string a;
        std::string name;
        std::cin >> a;
        if (a == "Q")
            finish = true;
        else if (a == "add")
            base.add_image();
        else if (a == "find") {
            while(getchar()!='\n');
            std::cout << "wprowadz kategorie(cat1+cat2+...)\n";
            getline(std::cin, name);
            std::vector <std::string> temp;
            int i = 0;
            int j;
            for (j = 0; j < name.length(); ++j) {
                if (name[j] == '+') {
                    temp.push_back(name.substr(i,j-i));
                    i = j + 1;
                }
            }
            temp.push_back(name.substr(i,j-i));
            std::cout<<std::endl;
            base.get_photos(temp);
        }
        else if (a == "print")
            base.print();
        else if (a == "rm") {
            std::cout << "Podaj nazwe zdjecia: " << std::endl;
            std::cin >> name;
            base.remove_image(name+".jpg");
        }
        else if (a == "cat")
            base.show_categories();
        else {
            std::cout << "Nie ma takiej opcji!\n";
            std::cin.clear();
            while(getchar()!='\n');
        }
    }
}

int main()
{
    run_Base();
    return 0;
}
