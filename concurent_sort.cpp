#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <mutex>

#define LEN 90000000

using namespace std;

int randof(int a, int b) {
    return rand() % (b - a + 1) + a;
}

template <typename T>
void merge_tab(vector<T> & tab, int i, int j, int k, int l) {
    vector<T> help_tab(l - i + 1);
    int akt = 0;
    while (i <= j && k <= l) {
        if (tab[i] < tab[k]) {
            help_tab[akt++] = tab[i];
            ++i;
        }
        else if (tab[i] > tab[k]) {
            help_tab[akt++] = tab[k];
            ++k;
        }
        else {
            help_tab[akt++] = tab[i];
            help_tab[akt++] = tab[i];
            ++i;
            ++k;
        }
    }
    while (i <= j) {
        help_tab[akt++] = tab[i++];
    }
    while (k <= l) {
        help_tab[akt++] = tab[k++];
    }
    while (--akt >= 0) {
        tab[l--] = help_tab[akt];
    }
}



template <class T>
void merge_sort(vector<T> & tab, int i , int q) {
    if (i < q) {
        int s = (i+q)/2;
        merge_sort(tab, i, s);
        merge_sort(tab, s+1, q);
        merge_tab(tab, i, s, s+1, q);
    }
}

template <class T>
void concurent_sort2(vector <T> & tab, int * n_of, mutex & M, int i , int q) {
    if (i < q) {
        int s = (i+q)/2;
        thread t1,t2;
        M.lock();
        if (*n_of > 1) {
            *n_of -= 2;
            M.unlock();
            t1 = thread(concurent_sort2<T>, ref(tab), n_of, ref(M), i, s);
            t2 = thread(concurent_sort2<T>, ref(tab), n_of, ref(M), s + 1, q);
            t1.join();
            t2.join();
            M.lock();
            *n_of += 2;
            M.unlock();
        }
        else {
            M.unlock();
            merge_sort(tab, i, s);
            merge_sort(tab, s+1, q);
        }
        merge_tab(tab, i, s, s+1, q);
    }
}

void testing() {
    std::vector<int> first;
    std::vector<int> second;
    srand(time(NULL));
    for (int i = 0; i < LEN; ++i) {
        int a = randof(-1000, 1000);
        first.push_back(a);
        second.push_back(a);
    }
   // for (int x: first)
   //     cout << x << " ";
   // cout << endl;
    time_t s1 = time(NULL);
    merge_sort(first, 0, first.size() - 1);
    time_t s2 = time(NULL);
    cout << "Merge sort: " << difftime(s2, s1) << " sek\n";
   // cout << "Result:\n";
   // for (int x: first)
   //     cout << x << " ";
   // cout << endl;
    mutex M;
    int nr_of_threads = 6;
    s1 = time(NULL);
    concurent_sort2(second, &nr_of_threads, M, 0, second.size() - 1);
    s2 = time(NULL);
    cout << "Concurent sort: " << difftime(s2, s1) << " sek\n";
   // cout << "Result:\n";
   // for (int x: second)
   //     cout << x << " ";
   // cout << endl;
}

int main()
{
    testing();
    return 0;
}

