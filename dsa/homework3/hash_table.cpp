#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <random>
#include <ctime>

// String_begin
struct String {
private:
    std::string _str;
public:
    String() = default;
    String(const char* str): _str(str) {}
    String(std::string str): _str(str) {}

    int hash() const {
        int h = 0;
        for (int i = 0; i < _str.size(); ++i) {
            h += _str[i] * i;
        }
        return h;
    }

    bool operator==(const String& other) const {
        return _str == other._str;
    }
    bool operator!=(const String& other) const {
        return !(_str == other._str);
    }

    friend std::ostream& operator <<(std::ostream& ost, const String& str);
};

std::ostream& operator <<(std::ostream& ost, const String& str) {
    ost << " " << str._str << " [" << str.hash() << "]";
    return ost;
}
// String_end


// HashTable_begin
template <typename Type>
class HashTable {
private:
    // using Type = String;
    const Type _default_value;
    double _max_load_factor = 0.8;
    double _el_count = 0;

    size_t _size;
    std::vector<Type> _container;

    bool _is_in_transfer_state = false;

    struct _Transfer {
        _Transfer (size_t size) {
                _container = std::vector<Type>(size);
                _last_idx = 0;
            }

        std::vector<Type> _container;
        size_t _transfer_el_count = 5;
        size_t _last_idx;
        double _el_count = 0;
    };

    _Transfer* _transfer_obj = nullptr;
public:
    HashTable(size_t size = 20) : _size(size) {
        _container = std::vector<Type>(_size, _default_value);
    }
    void insert(Type obj) {
        if (_is_in_transfer_state) {
            _insert(obj, _transfer_obj->_container);
            _transfer_obj->_el_count++;
        } else {
            _insert(obj, _container);
            ++_el_count;
        }
        _rehash();
    }

    int search(Type obj) {
        size_t idx;
        if (_is_in_transfer_state) {
            idx = _search(obj, _transfer_obj->_container);
            _rehash();
        } else {
            idx = _search(obj, _container);
        }
        return idx;
    }

    void remove(Type obj) {
        if (_is_in_transfer_state) {
            _remove(obj, _transfer_obj->_container);
            _transfer_obj->_el_count--;
            _rehash();
        } else {
            _remove(obj, _container);
            --_el_count;
        }
    }

    void primary_cluster() {
        std::cout << "Primary cluster: ";
        for (int i = 0; i < _size; ++i) {
            if (_container[i] == _default_value) {
                std::cout << '_';
            }
            else {
                std::cout << '*';
            }
        }
        std::cout << std::endl;
    }

    void print_runs() {
        size_t idx1 = 0;
        while (_container[idx1] == _default_value) {
            idx1 = (idx1 + 1) % _size;
        }

        int run_length = 0;
        std::cout << "Runs: ";

        size_t idx2 = idx1;
        while (true) {
            if (_container[idx2] == _default_value) {
                if (run_length > 0) {
                    std::cout << run_length << " ";
                    run_length = 0;
                }
            } else {
                ++run_length;
            }
            idx2 = (idx2 + 1) % _size;
            if (idx2 == idx1) break;
        }
        std::cout << std::endl;
    }

private:
    void _insert(Type obj, std::vector<Type>& container) {
        int obj_hash = obj.hash() % container.size();
        int idx = _next_empty_index(obj_hash, container);
        container[idx] = obj;
    }

    int _search(Type obj, std::vector<Type>& container) const {
        int obj_hash = obj.hash() % container.size();
        while(container[obj_hash] != obj && container[obj_hash] != _default_value) {
            obj_hash = (obj_hash + 1) % container.size();
        }
        if (container[obj_hash] == _default_value) return -1;
        return obj_hash;
    }

    void _remove(Type obj, std::vector<Type>& container) {
        int idx = _search(obj, container);
        if (idx == -1) {
            return;
        }

        for (int i = (idx + 1) % container.size(); container[i] != _default_value; i = (i + 1) % container.size()) {
            int obj_hash = container[i].hash() % container.size();
            if ((i > idx && obj_hash <= idx) ||
                (i < idx && obj_hash <= idx && obj_hash > i)) {
                container[idx] = container[i];
                idx = i;
            }
        }
        container[idx] = _default_value;
    }

    int _next_empty_index(int starting_index, std::vector<Type>& container) {
        int idx = starting_index;
        do {
            if (container[idx] == _default_value) {
                return idx;
            }
            idx = (idx + 1) % container.size();
        } while(idx != starting_index);

        // should be unreachable
        throw "Unreachable code";
    }

    double _current_load_factor() const {
        return _el_count / _size;
    }

    void _rehash() {
        if (!_is_in_transfer_state && _current_load_factor() <= _max_load_factor) {
            return;
        }
        _is_in_transfer_state = true;

        // create transfer object
        if(_transfer_obj == nullptr) {
            _transfer_obj = new _Transfer(2 * _size);
        }

        // transfer elements
        size_t transfered_elements_count = 0;
        size_t& idx = _transfer_obj->_last_idx;
        while (idx < _container.size()) {
            if (transfered_elements_count == _transfer_obj->_transfer_el_count) break;
            if (_container[idx] != _default_value) {
                _insert(_container[idx], _transfer_obj->_container);
                ++transfered_elements_count;
                _transfer_obj->_el_count++;
            }
            ++idx;
        }

        // if all elements are transfered
        if (idx == _container.size()) {
            _container = _transfer_obj->_container;
            _size = _container.size();
            delete _transfer_obj;
            _transfer_obj = nullptr;
            _is_in_transfer_state = false;
        }
    }

public:
    template<typename V>
    friend std::ostream& operator<<(std::ostream& os, const HashTable<V>& hash);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const HashTable<T>& hash) {
    String default_str;
    for (int i = 0; i < hash._size; ++i) {
        os << i << ": ";
        if (hash._container[i] != default_str) {
            os << hash._container[i];
        }
        os << std::endl;
    }
    os << "\n- Load factor: " << hash._current_load_factor() << std::endl;
    if (hash._transfer_obj != nullptr) {
        os << "Table is in transfer mode" << std::endl;
    }
    return os;
}
// HashTable_end

template<typename T>
void print(HashTable<T>& hash){
    std::cout << hash << std::endl;
    hash.primary_cluster();

    std::cout << "--------------------------------------" << std::endl;
}

template<typename T>
void insert_and_print(String&& str, HashTable<T>& hash) {
    hash.insert(str);
    print(hash);
}

template<typename T>
void search(String&& str, HashTable<T>& hash) {
    int idx = hash.search(str);
    if (idx == -1) {
        std::cout << str << " doesn't exist"<< std::endl;
    }
    else {
        std::cout << "Index of " << str << ": " << idx << std::endl;
    }
    std::cout << std::endl;
    print(hash);
}



std::string generateRandomString(int min, int max) {
    // Define the set of characters to choose from
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz"
                                   "0123456789";

    // Seed the random number generator with the current time
    std::random_device rd;
    std::mt19937 generator(rd());

    // Generate a random length for the string
    std::uniform_int_distribution<int> lengthDist(min, max); // Adjust the range as needed
    int length = lengthDist(generator);

    // Create the random string
    std::string randomString(length, ' ');
    std::uniform_int_distribution<int> charDist(0, characters.size() - 1);
    for (int i = 0; i < length; ++i) {
        randomString[i] = characters[charDist(generator)];
    }

    return randomString;
}

void test_string() {
    HashTable<String> hash(3);
    insert_and_print("Lorem", hash);
    insert_and_print("Ipsum", hash);
    insert_and_print("Flan", hash);
    insert_and_print("fstan", hash);
    insert_and_print("xyz", hash);
    insert_and_print("alt", hash);
    insert_and_print("prog", hash);
    insert_and_print("python", hash);
    insert_and_print("go", hash);
    search("go", hash);
    search("x", hash);
    search("y", hash);
    search("prog", hash);
    search("go", hash);

    hash.print_runs();
}

void test_random() {
    HashTable<String> hash(50);
    for (int i = 0; i < 400; ++i) {
        insert_and_print(String(generateRandomString(2, 8)), hash);
    }
    search("go", hash);
}

int main() {
    test_string();
    return 0;
}
