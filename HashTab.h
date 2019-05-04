#ifndef HASHTABLE_H
#define HASHTABLE_H

//template <> class HashTable<string>;

std::ostream & operator << (std::ostream & s, const HashItem & b) {
    s << "Key: " << b.key << "     " << "Value: " << b.value << "\n";
    return s;
};


template <typename T, typename N = int>
class HashItem {
    friend class HashTable;
    friend std::ostream & operator << (std::ostream & s, const HashItem & b);

    private:
        T key;
        N value;
    public:
        HashItem() : key(0), value(0) {};
        HashItem(const HashItem & a) : key(a.key), value(a.value) {};
        HashItem(T k, N v) : key(k), value(v) {};
};

template <typename T, typename N = int>
class HashTable
{

    private:
        int tab_size;
        HashItem<T, N> ** content;
        int hash_function(T key) {
            return key % tab_size;
        };

    public:
        HashTab() : tab_size(0), content(nullptr) {};
        HashTab(int len) : tab_size(len) {
            content = new HashItem<T, N>* [len];
            for (int i = 0; i < len; ++i)
                content[i] = nullptr;
        };
        HashTab(const HashTab & a) {
            tab_size = a.tab_size;
            content = new HashItem<T, N>*[tab_size];
            for (int i = 0; i < tab_size; ++i) {
                content[i] = a.content[i];
            }
        };

        ~HashTab() {
            for (int i = 0; i < tab_size; ++i)
                delete content[i];
        };

        void HashTab::add_item(T key, N value) {
            int id = hash_function(key);
            if (id < 0) id = - id;
            if (id > tab_size)  id %= tab_size;
            while (content[id] != nullptr) {
                ++id;
                id %= tab_size;
            }
            content[id] = new HashItem(key, value);
        };
        void remove_item(T key) {
            int id;
            for (id = hash_function(key); content[id] != nullptr && content[id]->key != key; ++id, id %= tab_size);
            delete content[id];
            content[id] = nullptr
        };
        N & operator[] (T key) {
            int id;
            for (id = hash_function(key); content[id] != nullptr && content[id]->key != key; ++id, id %= tab_size);
            assert(content[id] != nullptr);
            return content[id]->value;
        };

        friend std::ostream & operator << (std::ostream & s, const HashTab & b);
};

#endif // HASHTABLE_H
